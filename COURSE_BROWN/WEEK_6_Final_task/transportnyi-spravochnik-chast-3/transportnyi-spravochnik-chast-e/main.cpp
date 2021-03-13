#include <iostream>
#include <iomanip>
#include <sstream>
#include <tuple>

#include <unordered_map>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <variant>

#include <cmath>
#include <algorithm>

#include "test_runner.h"
#include "json.hpp"
#include "graph.h"
#include "router.h"
#include "stops_buses.h"

using json = nlohmann::json;
using router = Graph::Router<double>;
using router_info = Graph::Router<double>::RouteInfo;

using graph = Graph::DirectedWeightedGraph<double>;
using edge = Graph::Edge<double>;
using EDGE_TYPE = Graph::EDGE_TYPE;

#define pi 3.1415926535
using namespace std;




class Spravochnik{
private:
    double toRad(double degree) {
        return degree/180 * pi;
    }
    double calculateDistance(double lat1, double long1, double lat2, double long2) {
        return 6371000 * acos(sin(toRad(lat1)) * sin(toRad(lat2)) + cos(toRad(lat1)) * cos(toRad(lat2)) * cos(abs(toRad(long1 - long2))));
    }
    Stops_Buses sab;
    graph grap;
    router new_route;

public:
    json jhon;
    Spravochnik(const Stops_Buses& sb,const graph& gr):sab(sb),grap(gr),new_route(grap){
    }
    void bus_info(string X,int id){
        if(sab.buses.count(X)!=0){
            Bus_info bus = sab.buses.at(X);
            set<string> un_stops(bus.stops.begin(),bus.stops.end());
            Stop_info prev = sab.get_stop(*bus.stops.begin());
            double distance = 0;
            double distance_long = 0;
            for(auto it_stop = bus.stops.begin() + 1; it_stop != bus.stops.end(); it_stop++){
                Stop_info cur = sab.get_stop(*it_stop);

                double dist_long = calculateDistance(prev.coordinates.first, prev.coordinates.second, cur.coordinates.first, cur.coordinates.second);
                double dist;
                if(prev.dis_to.count(cur.name) != 0){
                    dist = prev.dis_to.at(cur.name);
                }else{
                    dist = cur.dis_to.at(prev.name);
                }
                distance += dist;
                distance_long += dist_long;
                prev = cur;
            }
            double curv = distance/distance_long;
            if(bus.round == 1){
                jhon.push_back( {{"route_length",int(distance)},{"request_id", id},{"curvature",curv},{"stop_count",bus.stops.size()},{"unique_stop_count",un_stops.size()}});
            }else{
                vector<string> stops_2 = bus.stops;
                reverse(stops_2.begin(),stops_2.end());
                double distance_2 = 0;
                double distance_long_2 = 0;
                Stop_info prev = sab.get_stop(*stops_2.begin());
                for(auto it_stop = stops_2.begin() + 1; it_stop != stops_2.end(); it_stop++){
                    Stop_info cur = sab.get_stop(*it_stop);
                    double dist_long = calculateDistance(prev.coordinates.first, prev.coordinates.second, cur.coordinates.first, cur.coordinates.second);
                    double dist;
                    if(prev.dis_to.count(cur.name) != 0){
                        dist = prev.dis_to.at(cur.name);
                    }else{
                        dist = cur.dis_to.at(prev.name);
                    }
                    distance_2 += dist;
                    distance_long_2 += dist_long;
                    prev = cur;
                }
                double curv_2 = distance_2/distance_long_2;
                jhon.push_back({{"route_length",int(distance+distance_2)},{"request_id", id},{"curvature",(curv+curv_2)/2},{"stop_count",bus.stops.size()+bus.stops.size()-1},{"unique_stop_count",un_stops.size()}});
            }
        }else{
            jhon.push_back({ {"request_id", id},{"error_message", "not found"}});
        }
   }
   void stop_info(string X,int id){
       // cout<<"            ИНФА      "<<X<<endl;
        if(sab.stops.count(X)!=0){
            if(sab.stops.at(X).puss_bus.size()!=0){
                jhon.push_back({ {"buses", sab.stops.at(X).puss_bus} ,{"request_id", id}});
            }else{
               jhon.push_back({ {"buses", sab.stops.at(X).puss_bus} ,{"request_id", id}});
            }
        }else{
            jhon.push_back({ {"request_id", id},{"error_message", "not found"}});
        }
    }

    void road_info(string from,string to ,int id){
        json result;
        auto res = new_route.BuildRoute(sab.stops.at(from).start_waiting,sab.stops.at(to).start_waiting);
        if(res){
            if(res->data.size()!=0){
                for(auto&i:res->data){
                    if(grap.GetEdge(i).edge_type==Graph::EDGE_TYPE::BUS){
                        result.push_back({ {"type","Bus" },{"bus",grap.GetEdge(i).name },{"span_count",grap.GetEdge(i).span},{"time",grap.GetEdge(i).weight}});
                    }else{
                        result.push_back({ {"type","Wait" },{"stop_name",grap.GetEdge(i).name},{"time",grap.GetEdge(i).weight}});
                    }
                }
            }else{
                result =json::array();
            }
        }
        if(res){
            jhon.push_back({{"total_time",res->weight },{"request_id", id},{"items",result}});
        }else{
            jhon.push_back({ {"request_id", id},{"error_message", "not found"}});
        }

    }
    void Print(){
        cout<<jhon.dump()<<endl;
    }
};


 Stops_Buses loadfromjson_to_sab(json &j) {
    Stops_Buses sab;
    sab.sts(j["routing_settings"]["bus_wait_time"],j["routing_settings"]["bus_velocity"]);
    for(auto & i : j["base_requests"]){
        if(i["type"] == "Bus"){
            string name = i["name"];
            vector <string> stops = i["stops"];
            bool round = i["is_roundtrip"];
            if(round){
                sab.bus_circle(name,stops);
            }else{
                sab.bus_straight(name,stops);
            }
        }else{
            string name =  i["name"];
            unordered_map<string,double> dis_to = i["road_distances"];
            double latitude = i["latitude"];
            double longitude = i["longitude"];
            if(dis_to.size()!=0){
                sab.stop(name,latitude,longitude,dis_to);
            }else{
                sab.stop(name,latitude,longitude);
            }
        }
    }
    return sab;
}

 void request_getter(json &j,Spravochnik& sprav){
     for(auto & i : j["stat_requests"]){
         if(i["type"] ==  "Bus"){
             string name =  i["name"];
             int id = (int)i["id"];
             sprav.bus_info(name,id);
         }
         if(i["type"] ==  "Stop"){
             string name =  i["name"];
             int id = (int)i["id"];
             sprav.stop_info(name,id);
         }
         if(i["type"] ==  "Route"){
             string from =  i["from"];
             string to =  i["to"];
             int id = (int)i["id"];
             sprav.road_info(from,to,id);
         }
     }

 }

 graph initialize_graph(Stops_Buses & sab){
    graph result(sab.stops.size()*2);
    set<string> set_of_stops;
    for(auto &bus: sab.buses){
        vector<pair<size_t,vector<double>>> time_of_bus_ridings;
        Stop_info prev = sab.get_stop(*bus.second.stops.begin());
        if(set_of_stops.count(prev.name)==0){
            result.AddEdge({prev.start_waiting,prev.stop_waiting,sab.settings.bus_wait_time,EDGE_TYPE::WAIT,prev.name});
            set_of_stops.insert(prev.name);
        }
        for(auto it_stop = bus.second.stops.begin() + 1; it_stop != bus.second.stops.end(); it_stop++){
            Stop_info cur = sab.get_stop(*it_stop);
            if(set_of_stops.count(cur.name)==0){
                result.AddEdge({cur.start_waiting,cur.stop_waiting,sab.settings.bus_wait_time,EDGE_TYPE::WAIT,cur.name});
                set_of_stops.insert(cur.name);
            }
            double time_of_bus_riding;
            if(prev.dis_to.count(cur.name) != 0){
                time_of_bus_riding = ((prev.dis_to.at(cur.name)/1000)/sab.settings.bus_velocity)*60;
            }else{
                time_of_bus_riding = ((cur.dis_to.at(prev.name)/1000)/sab.settings.bus_velocity)*60;
            }
            vector<double> new_vec;
            time_of_bus_ridings.push_back(make_pair(prev.stop_waiting,move(new_vec)));
            for(auto &i: time_of_bus_ridings){
                i.second.push_back(time_of_bus_riding);
            }
            for(auto &i: time_of_bus_ridings){
                double time_of_bus_riding_all= accumulate(i.second.begin(),i.second.end(),0.0);
                result.AddEdge({i.first,cur.start_waiting,time_of_bus_riding_all,EDGE_TYPE::BUS,bus.second.name,i.second.size()});
            }
            prev = cur;
        }
        if(bus.second.round  != 1){
            vector<pair<size_t,vector<double>>> time_of_bus_ridings;
            vector<string> stops_2 = bus.second.stops;
            reverse(stops_2.begin(),stops_2.end());
            Stop_info prev = sab.get_stop(*stops_2.begin());
            for(auto it_stop = stops_2.begin() + 1; it_stop != stops_2.end(); it_stop++){

                Stop_info cur = sab.get_stop(*it_stop);
                double time_of_bus_riding;
                if(prev.dis_to.count(cur.name) != 0){
                    time_of_bus_riding = ((prev.dis_to.at(cur.name)/1000)/sab.settings.bus_velocity)*60;
                }else{
                    time_of_bus_riding = ((cur.dis_to.at(prev.name)/1000)/sab.settings.bus_velocity)*60;
                }
                vector<double> new_vec;
                time_of_bus_ridings.push_back(make_pair(prev.stop_waiting,move(new_vec)));

                for(auto &i: time_of_bus_ridings){
                    i.second.push_back(time_of_bus_riding);
                }
                for(auto &i: time_of_bus_ridings){
                    double time_of_bus_riding_all= accumulate(i.second.begin(),i.second.end(),0.0);
                    result.AddEdge({i.first,cur.start_waiting,time_of_bus_riding_all,EDGE_TYPE::BUS,bus.second.name,i.second.size()});
                }
                prev = cur;
            }

        }
    }
    return result;
 }


void processor(json &j ){
    Stops_Buses sab = loadfromjson_to_sab(j);
    graph dwg = initialize_graph(sab);
    Spravochnik sprav(sab,dwg);
    request_getter(j,sprav);
    sprav.Print();
}
json test_processor(json& j){
    Stops_Buses sab = loadfromjson_to_sab(j);
    graph dwg = initialize_graph(sab);
    Spravochnik sprav(sab,dwg);
    request_getter(j,sprav);
    return sprav.jhon;

}
void test_1(){
    string input = R"({
                   "routing_settings": {
                     "bus_wait_time": 6,
                     "bus_velocity": 40
                   },
                   "base_requests": [
                     {
                       "type": "Bus",
                       "name": "297",
                       "stops": [
                         "Biryulyovo Zapadnoye",
                         "Biryulyovo Tovarnaya",
                         "Universam",
                         "Biryulyovo Zapadnoye"
                       ],
                       "is_roundtrip": true
                     },
                     {
                       "type": "Bus",
                       "name": "635",
                       "stops": [
                         "Biryulyovo Tovarnaya",
                         "Universam",
                         "Prazhskaya"
                       ],
                       "is_roundtrip": false
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Biryulyovo Tovarnaya": 2600
                       },
                       "longitude": 37.6517,
                       "name": "Biryulyovo Zapadnoye",
                       "latitude": 55.574371
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Prazhskaya": 4650,
                         "Biryulyovo Tovarnaya": 1380,
                         "Biryulyovo Zapadnoye": 2500
                       },
                       "longitude": 37.645687,
                       "name": "Universam",
                       "latitude": 55.587655
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Universam": 890
                       },
                       "longitude": 37.653656,
                       "name": "Biryulyovo Tovarnaya",
                       "latitude": 55.592028
                     },
                     {
                       "type": "Stop",
                       "road_distances": {},
                       "longitude": 37.603938,
                       "name": "Prazhskaya",
                       "latitude": 55.611717
                     }
                   ],
                   "stat_requests": [
                     {
                       "type": "Bus",
                       "name": "297",
                       "id": 1
                     },
                     {
                       "type": "Bus",
                       "name": "635",
                       "id": 2
                     },
                     {
                       "type": "Stop",
                       "name": "Universam",
                       "id": 3
                     },
                     {
                       "type": "Route",
                       "from": "Biryulyovo Zapadnoye",
                       "to": "Universam",
                       "id": 4
                     },
                     {
                       "type": "Route",
                       "from": "Biryulyovo Zapadnoye",
                       "to": "Prazhskaya",
                       "id": 5
                     }
                   ]
                 })";
    string output = R"([
    {
        "curvature": 1.42963,
        "unique_stop_count": 3,
        "stop_count": 4,
        "request_id": 1,
        "route_length": 5990
    },
    {
        "curvature": 1.30156,
        "unique_stop_count": 3,
        "stop_count": 5,
        "request_id": 2,
        "route_length": 11570
    },
    {
        "request_id": 3,
        "buses": [
            "297",
            "635"
        ]
    },
    {
        "total_time": 11.235,
        "items": [
            {
                "time": 6,
                "type": "Wait",
                "stop_name": "Biryulyovo Zapadnoye"
            },
            {
                "span_count": 2,
                "bus": "297",
                "type": "Bus",
                "time": 5.235
            }
        ],
        "request_id": 4
    },
    {
        "total_time": 24.21,
        "items": [
            {
                "time": 6,
                "type": "Wait",
                "stop_name": "Biryulyovo Zapadnoye"
            },
            {
                "span_count": 2,
                "bus": "297",
                "type": "Bus",
                "time": 5.235
            },
            {
                "time": 6,
                "type": "Wait",
                "stop_name": "Universam"
            },
            {
                "span_count": 1,
                "bus": "635",
                "type": "Bus",
                "time": 6.975
            }
        ],
        "request_id": 5
    }
])";
istringstream k(input);
json a;
k>>a;
istringstream l(output);
json b;
l>>b;
json c = test_processor(a);
ASSERT_EQUAL(b,c);
}

void test_2(){
    string input = R"({
                   "routing_settings": {
                     "bus_wait_time": 2,
                     "bus_velocity": 30
                   },
                   "base_requests": [
                     {
                       "type": "Bus",
                       "name": "297",
                       "stops": [
                         "Biryulyovo Zapadnoye",
                         "Biryulyovo Tovarnaya",
                         "Universam",
                         "Biryusinka",
                         "Apteka",
                         "Biryulyovo Zapadnoye"
                       ],
                       "is_roundtrip": true
                     },
                     {
                       "type": "Bus",
                       "name": "635",
                       "stops": [
                         "Biryulyovo Tovarnaya",
                         "Universam",
                         "Biryusinka",
                         "TETs 26",
                         "Pokrovskaya",
                         "Prazhskaya"
                       ],
                       "is_roundtrip": false
                     },
                     {
                       "type": "Bus",
                       "name": "828",
                       "stops": [
                         "Biryulyovo Zapadnoye",
                         "TETs 26",
                         "Biryusinka",
                         "Universam",
                         "Pokrovskaya",
                         "Rossoshanskaya ulitsa"
                       ],
                       "is_roundtrip": false
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Biryulyovo Tovarnaya": 2600,
                         "TETs 26": 1100
                       },
                       "longitude": 37.6517,
                       "name": "Biryulyovo Zapadnoye",
                       "latitude": 55.574371
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Biryusinka": 760,
                         "Biryulyovo Tovarnaya": 1380,
                         "Pokrovskaya": 2460
                       },
                       "longitude": 37.645687,
                       "name": "Universam",
                       "latitude": 55.587655
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Universam": 890
                       },
                       "longitude": 37.653656,
                       "name": "Biryulyovo Tovarnaya",
                       "latitude": 55.592028
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Apteka": 210,
                         "TETs 26": 400
                       },
                       "longitude": 37.64839,
                       "name": "Biryusinka",
                       "latitude": 55.581065
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Biryulyovo Zapadnoye": 1420
                       },
                       "longitude": 37.652296,
                       "name": "Apteka",
                       "latitude": 55.580023
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Pokrovskaya": 2850
                       },
                       "longitude": 37.642258,
                       "name": "TETs 26",
                       "latitude": 55.580685
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Rossoshanskaya ulitsa": 3140
                       },
                       "longitude": 37.635517,
                       "name": "Pokrovskaya",
                       "latitude": 55.603601
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Pokrovskaya": 3210
                       },
                       "longitude": 37.605757,
                       "name": "Rossoshanskaya ulitsa",
                       "latitude": 55.595579
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Pokrovskaya": 2260
                       },
                       "longitude": 37.603938,
                       "name": "Prazhskaya",
                       "latitude": 55.611717
                     },
                     {
                       "type": "Bus",
                       "name": "750",
                       "stops": [
                         "Tolstopaltsevo",
                         "Rasskazovka"
                       ],
                       "is_roundtrip": false
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Rasskazovka": 13800
                       },
                       "longitude": 37.20829,
                       "name": "Tolstopaltsevo",
                       "latitude": 55.611087
                     },
                     {
                       "type": "Stop",
                       "road_distances": {},
                       "longitude": 37.333324,
                       "name": "Rasskazovka",
                       "latitude": 55.632761
                     }
                   ],
                   "stat_requests": [
                     {
                       "type": "Bus",
                       "name": "297",
                       "id": 1
                     },
                     {
                       "type": "Bus",
                       "name": "635",
                       "id": 2
                     },
                     {
                       "type": "Bus",
                       "name": "828",
                       "id": 3
                     },
                     {
                       "type": "Stop",
                       "name": "Universam",
                       "id": 4
                     },
                     {
                        "type": "Route",
                        "from": "Biryulyovo Zapadnoye",
                        "to": "Apteka",
                        "id": 5
                     },
                     {
                       "type": "Route",
                       "from": "Biryulyovo Zapadnoye",
                       "to": "Pokrovskaya",
                       "id": 6
                     },
                     {
                       "type": "Route",
                       "from": "Biryulyovo Tovarnaya",
                       "to": "Pokrovskaya",
                       "id": 7
                     },
                     {
                       "type": "Route",
                       "from": "Biryulyovo Tovarnaya",
                       "to": "Biryulyovo Zapadnoye",
                       "id": 8
                     },
                     {
                       "type": "Route",
                       "from": "Biryulyovo Tovarnaya",
                       "to": "Prazhskaya",
                       "id": 9
                     },
                     {
                       "type": "Route",
                       "from": "Apteka",
                       "to": "Biryulyovo Tovarnaya",
                       "id": 10
                     },
                     {
                       "type": "Route",
                       "from": "Biryulyovo Zapadnoye",
                       "to": "Tolstopaltsevo",
                       "id": 11
                     }
                   ]
                 })";
    string output = R"([
    {
        "stop_count": 6,
        "route_length": 5880,
        "unique_stop_count": 5,
        "curvature": 1.36159,
        "request_id": 1
    },
    {
        "stop_count": 11,
        "route_length": 14810,
        "unique_stop_count": 6,
        "curvature": 1.12195,
        "request_id": 2
    },
    {
        "stop_count": 11,
        "route_length": 15790,
        "unique_stop_count": 6,
        "curvature": 1.31245,
        "request_id": 3
    },
    {
        "buses": [
            "297",
            "635",
            "828"
        ],
        "request_id": 4
    },
    {
        "items": [
            {
                "time": 2,
                "stop_name": "Biryulyovo Zapadnoye",
                "type": "Wait"
            },
            {
                "time": 3,
                "bus": "828",
                "span_count": 2,
                "type": "Bus"
            },
            {
                "time": 2,
                "stop_name": "Biryusinka",
                "type": "Wait"
            },
            {
                "time": 0.42,
                "bus": "297",
                "span_count": 1,
                "type": "Bus"
            }
        ],
        "request_id": 5,
        "total_time": 7.42
    },
    {
        "items": [
            {
                "time": 2,
                "stop_name": "Biryulyovo Zapadnoye",
                "type": "Wait"
            },
            {
                "time": 9.44,
                "bus": "828",
                "span_count": 4,
                "type": "Bus"
            }
        ],
        "request_id": 6,
        "total_time": 11.44
    },
    {
        "items": [
            {
                "time": 2,
                "stop_name": "Biryulyovo Tovarnaya",
                "type": "Wait"
            },
            {
                "time": 1.78,
                "bus": "635",
                "span_count": 1,
                "type": "Bus"
            },
            {
                "time": 2,
                "stop_name": "Universam",
                "type": "Wait"
            },
            {
                "time": 4.92,
                "bus": "828",
                "span_count": 1,
                "type": "Bus"
            }
        ],
        "request_id": 7,
        "total_time": 10.7
    },
    {
        "items": [
            {
                "time": 2,
                "stop_name": "Biryulyovo Tovarnaya",
                "type": "Wait"
            },
            {
                "time": 6.56,
                "bus": "297",
                "span_count": 4,
                "type": "Bus"
            }
        ],
        "request_id": 8,
        "total_time": 8.56
    },
    {
        "items": [
            {
                "time": 2,
                "stop_name": "Biryulyovo Tovarnaya",
                "type": "Wait"
            },
            {
                "time": 14.32,
                "bus": "635",
                "span_count": 5,
                "type": "Bus"
            }
        ],
        "request_id": 9,
        "total_time": 16.32
    },
    {
        "items": [
            {
                "time": 2,
                "stop_name": "Apteka",
                "type": "Wait"
            },
            {
                "time": 2.84,
                "bus": "297",
                "span_count": 1,
                "type": "Bus"
            },
            {
                "time": 2,
                "stop_name": "Biryulyovo Zapadnoye",
                "type": "Wait"
            },
            {
                "time": 5.2,
                "bus": "297",
                "span_count": 1,
                "type": "Bus"
            }
        ],
        "request_id": 10,
        "total_time": 12.04
    },
    {
        "error_message": "not found",
        "request_id": 11
    }
])";

    istringstream k(input);
    json a;
    k>>a;
    istringstream l(output);
    json b;
    l>>b;
    json c = test_processor(a);
    ASSERT_EQUAL(b,c);

}

void test_3(){
    string input = R"({
                   "routing_settings": {
                     "bus_wait_time": 2,
                     "bus_velocity": 30
                   },
                   "base_requests": [
                     {
                       "type": "Bus",
                       "name": "289",
                       "stops": [
                         "Zagorye",
                         "Lipetskaya ulitsa 46",
                         "Lipetskaya ulitsa 40",
                         "Lipetskaya ulitsa 40",
                         "Lipetskaya ulitsa 46",
                         "Moskvorechye",
                         "Zagorye"
                       ],
                       "is_roundtrip": true
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Lipetskaya ulitsa 46": 230
                       },
                       "longitude": 37.68372,
                       "name": "Zagorye",
                       "latitude": 55.579909
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Lipetskaya ulitsa 40": 390,
                         "Moskvorechye": 12400
                       },
                       "longitude": 37.682205,
                       "name": "Lipetskaya ulitsa 46",
                       "latitude": 55.581441
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Lipetskaya ulitsa 40": 1090,
                         "Lipetskaya ulitsa 46": 380
                       },
                       "longitude": 37.679133,
                       "name": "Lipetskaya ulitsa 40",
                       "latitude": 55.584496
                     },
                     {
                       "type": "Stop",
                       "road_distances": {
                         "Zagorye": 10000
                       },
                       "longitude": 37.638433,
                       "name": "Moskvorechye",
                       "latitude": 55.638433
                     }
                   ],
                   "stat_requests": [
                     {
                       "type": "Bus",
                       "name": "289",
                       "id": 1
                     },
                     {
                       "type": "Route",
                       "from": "Zagorye",
                       "to": "Moskvorechye",
                       "id": 2
                     },
                     {
                       "type": "Route",
                       "from": "Moskvorechye",
                       "to": "Zagorye",
                       "id": 3
                     },
                     {
                       "type": "Route",
                       "from": "Lipetskaya ulitsa 40",
                       "to": "Lipetskaya ulitsa 40",
                       "id": 4
                     }
                   ]
                 })";
    string output = R"([
    {
        "unique_stop_count": 4,
        "stop_count": 7,
        "request_id": 1,
        "curvature": 1.63414,
        "route_length": 24490
    },
    {
        "total_time": 29.26,
        "items": [
            {
                "time": 2,
                "stop_name": "Zagorye",
                "type": "Wait"
            },
            {
                "time": 0.46,
                "bus": "289",
                "span_count": 1,
                "type": "Bus"
            },
            {
                "time": 2,
                "stop_name": "Lipetskaya ulitsa 46",
                "type": "Wait"
            },
            {
                "time": 24.8,
                "bus": "289",
                "span_count": 1,
                "type": "Bus"
            }
        ],
        "request_id": 2
    },
    {
        "total_time": 22,
        "items": [
            {
                "time": 2,
                "stop_name": "Moskvorechye",
                "type": "Wait"
            },
            {
                "time": 20,
                "bus": "289",
                "span_count": 1,
                "type": "Bus"
            }
        ],
        "request_id": 3
    },
    {
        "total_time": 0,
        "items": [],
        "request_id": 4
    }
])";
    istringstream k(input);
    json a;
    k>>a;
    istringstream l(output);
    json b;
    l>>b;
    json c = test_processor(a);
    ASSERT_EQUAL(b,c);

}


int main(){
//    TestRunner tr;
//    RUN_TEST(tr,test_1);
//    RUN_TEST(tr,test_2);
//    RUN_TEST(tr,test_3);

    json j;
    cin>>j;
    std::cout << std::setprecision(25);
    //cout<<"РАБОТА"<<endl;
    processor(j);

    return 0;
}
