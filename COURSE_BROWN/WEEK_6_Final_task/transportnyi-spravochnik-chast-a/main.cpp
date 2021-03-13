#include <iostream>
#include <vector>
#include <cmath>
#include <test_runner.h>
#include <sstream>
#include <map>
#include <iomanip>
#include <set>
#include <algorithm>
#include <unordered_map>
#define pi 3.1415926535
using namespace std;
struct Stop_info{
    Stop_info(){
    }
    Stop_info(string name, pair<double,double> coordinates, unordered_map<string,double> dis_to):
        name(name),
        coordinates(coordinates),
        dis_to(dis_to){
    }
    Stop_info(string name, pair<double,double> coordinates):
        name(name),
        coordinates(coordinates){

    }
    Stop_info(string name):
        name(name){
    }
    string name;
    pair<double,double> coordinates;
    set<string>  puss_bus;
    unordered_map<string,double> dis_to;
};
ostream& operator<<(ostream & out, const Stop_info &v){
    out<<"Stop "<<v.name<<": "<<v.coordinates.first <<", "<<v.coordinates.second;
    for(auto i: v.dis_to){
        out<<", "<<i.second<<"m to "<<i.first;
    }
    out<<"\n";
    return out;
}
struct Bus_info{
    string name;
    vector<string> stops;
    int round = 0;
};
ostream& operator<<(ostream & out, const Bus_info &v){
    out<<"Bus_info"<<"\n";
    out<<"Bus "<<v.name<<":";
    for(auto &i: v.stops){
        out<<" - "<<i;
    }
    out<<" "<< v.round<< "\n";
    out<<"Bus_info"<<"\n";
    return out;
}


class Spravochnik{
private:
    double toRad(double degree) {
        return degree/180 * pi;
    }
    double calculateDistance(double lat1, double long1, double lat2, double long2) {
        return 6371000 * acos(sin(toRad(lat1)) * sin(toRad(lat2)) + cos(toRad(lat1)) * cos(toRad(lat2)) * cos(abs(toRad(long1 - long2))));
    }
    Stop_info get_stop(string stop){
        return stops.at(stop);
    }
    map <string,Bus_info> buses;
    map <string,Stop_info> stops;
public:
    int stop(string X, double latitude, double longitude){
        if(stops.count(X)!=0){
            stops.at(X).coordinates= make_pair(latitude,longitude);
        }else{
            Stop_info new_stop(X,make_pair(latitude,longitude));
            stops[X]= move(new_stop);
        }
        return 0;
    }
    int stop(string X, double latitude, double longitude, unordered_map<string,double> dis_to){
        if(stops.count(X)!=0){
            stops.at(X).coordinates= make_pair(latitude,longitude);
            stops.at(X).dis_to = dis_to;
        }else{
            Stop_info new_stop(X,make_pair(latitude,longitude),dis_to);
            stops[X]= new_stop;
        }
        return 0;
    }

    int bus_straight(string X,vector<string>bus_stops){
        set<string> un_stops(bus_stops.begin(),bus_stops.end());
        Bus_info new_bus;
        new_bus.name=X,
        new_bus.stops=bus_stops;
        new_bus.round = 0;
        buses[X] = new_bus;
        for(auto &i: un_stops){
            if(stops.count(i)!=0){
                stops.at(i).puss_bus.insert(X);
            } else {
                Stop_info x(i);
                stops[i]= x;
                stops.at(i).puss_bus.insert(X);
            }
        }
        return 0;
    }
    int bus_circle(string X,vector<string>bus_stops){
        set<string> un_stops(bus_stops.begin(),bus_stops.end());
        Bus_info new_bus;
        new_bus.name=X,
        new_bus.stops=bus_stops;
        new_bus.round = 1;
        buses[X] = move(new_bus);
        for(auto &i: un_stops){
            if(stops.count(i)!=0){
                stops.at(i).puss_bus.insert(X);
            } else {
                Stop_info x(i);
                stops[i]= x;
                stops.at(i).puss_bus.insert(X);
            }
        }
        return 0;
    }
    void bus_info(string X,ostream & out){

        if(buses.count(X)!=0){
            Bus_info bus = buses.at(X);
            //cerr<<bus;
            set<string> un_stops(bus.stops.begin(),bus.stops.end());
            Stop_info prev = get_stop(*bus.stops.begin());
           // cerr<<prev;
            double distance = 0;
            double distance_long = 0;
            for(auto it_stop = bus.stops.begin() + 1; it_stop != bus.stops.end(); it_stop++){
                Stop_info cur = get_stop(*it_stop);
                //cerr<< cur;
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
                 out<<"Bus "<<X<<": "<< bus.stops.size() <<" stops on route, "<< un_stops.size() <<" unique stops, "<< fixed << setprecision(6)<<int(distance) <<" route length, "<<curv<<" curvature"<<endl;
            }else{
                vector<string> stops_2 = bus.stops;
                reverse(stops_2.begin(),stops_2.end());
                double distance_2 = 0;
                double distance_long_2 = 0;
                Stop_info prev = get_stop(*stops_2.begin());
                for(auto it_stop = stops_2.begin() + 1; it_stop != stops_2.end(); it_stop++){
                    Stop_info cur = get_stop(*it_stop);
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
                out<<"Bus "<<X<<": "<< bus.stops.size()+bus.stops.size()-1 <<" stops on route, "<< un_stops.size() <<" unique stops, "<< fixed << setprecision(6)<<int(distance+distance_2 )<<" route length, "<<(curv+curv_2)/2<<" curvature"<<endl;
            }
        }else{

            out<<"Bus "<<X<<":"<<" not found"<<endl;
        }
    }
    void stop_info(string X,ostream & out){
        if(stops.count(X)!=0){
            if(stops.at(X).puss_bus.size()!=0){
                cout<<"Stop  "<<X<<": buses";
                for(auto & i:stops.at(X).puss_bus){
                    cout<<" "<<i;
                }
                cout<<endl;
            }else{
                out<<"Stop  "<<X<<":"<<" no buses"<<endl;
            }
        }else{
            out<<"Stop  "<<X<<":"<<" not found"<<endl;

        }
    }
};

class Processor{
    vector<string> split(const std::string &s, char delim) {
      stringstream ss(s);
      string item;
      vector<string> elems;
      ss.ignore(1);
      while (std::getline(ss, item, delim)){
        item.pop_back();
        elems.push_back(move(item));
        ss.ignore(1);

      }
      return elems;
    }
    vector<std::string> split_1(const std::string &s, char delim) {
      stringstream ss(s);
      string item;
      vector<std::string> elems;
      while (std::getline(ss, item, delim)){
        elems.push_back(move(item));
        ss.ignore(1);

      }
      return elems;
    }
    unordered_map<string,double> doubler(const vector<string> &routes){
        unordered_map<string,double> result;
        for(const auto&i:routes){
            double dist;
            string name;
            stringstream ss(i);
            ss>>dist;
            ss.ignore(5);
            getline(ss, name);
            result.insert(make_pair(name,dist));
        }
        return result;
    }

    void processor_stop(Spravochnik& sprav,istream& in){
        string stop;
        double latitude,longitude;
        in.ignore(1);
        getline(in,stop,':');
        in.ignore(1);
        in >> latitude;
        in.ignore(2);
        in >> longitude;
        if(in.peek()!='\n'){
            in.ignore(2);
            string track;
            getline(in,track);
            vector <string> stops;
            stops = split_1(track,',');
            sprav.stop(stop,latitude,longitude,doubler(stops));
        }else{
            sprav.stop(stop,latitude,longitude);
        }
    }
    void processor_bus(Spravochnik& sprav,istream &in){
        string num;
        in.ignore(1);
        getline(in,num,':');
        string track;
        getline(in,track);
        track.push_back(' ');
        vector <string> stops;
        if (track.find('>')!=std::string::npos){
            stops = split(track,'>');
            sprav.bus_circle(num,stops);
        }else if(track.find('-')!=std::string::npos){
            stops = split(track,'-');
            sprav.bus_straight(num,stops);
        }
    }
    void processor_bus_req(Spravochnik& sprav,istream& in){
        string num;
        in.ignore(1);
        getline(in,num);
        sprav.bus_info(num,cout);
    }
    void processor_stop_req(Spravochnik& sprav,istream& in){
        string stop;
        in.ignore(1);
        getline(in,stop);
        sprav.stop_info(stop,cout);

    }
    void processor(Spravochnik& sprav,istream &in ){
        int query_count =0;
        in >> query_count;
        for (int query_id = 0; query_id < query_count; ++query_id){
            string query_type;
            in >> query_type;
            if (query_type == "Stop"){
                processor_stop(sprav,cin);

            }else if (query_type == "Bus") {
                processor_bus(sprav,cin);
            }
        }
        query_count =0;
        in>>query_count;
        for (int query_id = 0; query_id < query_count; ++query_id){
            string query_type;
            in >> query_type;
            if (query_type == "Bus") {
                processor_bus_req(sprav,in);
            }else if (query_type == "Stop") {
                processor_stop_req(sprav,in);
            }
        }
    }
};

vector<string> split(const std::string &s, char delim) {
  stringstream ss(s);
  string item;
  vector<string> elems;
  ss.ignore(1);
  while (std::getline(ss, item, delim)){
    item.pop_back();
    elems.push_back(move(item));
    ss.ignore(1);

  }
  return elems;
}

vector<std::string> split_1(const std::string &s, char delim) {
  stringstream ss(s);
  string item;
  vector<std::string> elems;
  while (std::getline(ss, item, delim)){
    elems.push_back(move(item));
    ss.ignore(1);

  }
  return elems;
}

unordered_map<string,double> doubler(const vector<string> &routes){
    unordered_map<string,double> result;
    for(const auto&i:routes){
        double dist;
        string name;
        stringstream ss(i);
        ss>>dist;
        ss.ignore(5);
        getline(ss, name);
        result.insert(make_pair(name,dist));
    }
    return result;
}

void processor_stop(Spravochnik& sprav,istream& in){
    string stop;
    double latitude,longitude;
    in.ignore(1);
    getline(in,stop,':');
    in.ignore(1);
    in >> latitude;
    in.ignore(2);
    in >> longitude;
    if(in.peek()!='\n'){
        in.ignore(2);
        string track;
        getline(in,track);
        vector <string> stops;
        stops = split_1(track,',');
        sprav.stop(stop,latitude,longitude,doubler(stops));
    }else{
        sprav.stop(stop,latitude,longitude);
    }
}
void processor_bus(Spravochnik& sprav,istream &in){
    string num;
    in.ignore(1);
    getline(in,num,':');
    string track;
    getline(in,track);
    track.push_back(' ');
    vector <string> stops;
    if (track.find('>')!=std::string::npos){
        stops = split(track,'>');
        sprav.bus_circle(num,stops);
    }else if(track.find('-')!=std::string::npos){
        stops = split(track,'-');
        sprav.bus_straight(num,stops);
    }
}
void processor_bus_req(Spravochnik& sprav,istream& in){
    string num;
    in.ignore(1);
    getline(in,num);
    sprav.bus_info(num,cout);
}
void processor_stop_req(Spravochnik& sprav,istream& in){
    string stop;
    in.ignore(1);
    getline(in,stop);
    sprav.stop_info(stop,cout);

}
void processor(Spravochnik& sprav,istream &in ){
    int query_count =0;
    in >> query_count;
    for (int query_id = 0; query_id < query_count; ++query_id){
        string query_type;
        in >> query_type;
        if (query_type == "Stop"){
            processor_stop(sprav,cin);

        }else if (query_type == "Bus") {
            processor_bus(sprav,cin);
        }
    }
    query_count =0;
    in>>query_count;
    for (int query_id = 0; query_id < query_count; ++query_id){
        string query_type;
        in >> query_type;
        if (query_type == "Bus") {
            processor_bus_req(sprav,in);
        }else if (query_type == "Stop") {
            processor_stop_req(sprav,in);
        }
    }
}

int main(){
    Spravochnik gor_sprav;
    processor(gor_sprav,cin);
    return 0;
}
/*
10
Stop Tolstopaltsevo: 55.611087, 37.20829
Stop Marushkino: 55.595884, 37.209755
Bus AAAAA N256_bis: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
Bus foundBus: Tolstopaltsevo - Marushkino - Rasskazovka
Stop Rasskazovka: 55.632761, 37.333324
Stop Biryulyovo Zapadnoye: 55.574371, 37.6517
Stop Biryusinka: 55.581065, 37.64839
Stop Universam: 55.587655, 37.645687
Stop Biryulyovo Tovarnaya: 55.592028, 37.653656
Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164
3
Bus AAAAA N256_bis
Bus foundBus
Bus 750

*/
/*
5
Bus gazZviu ncDtm: 9CBIn uqPIOjG > C06g9m0rff9 > 9CBIn uqPIOjG
Stop C06g9m0rff9: 43.62643 39.91751
Bus lw5PH6 Ul3: 9CBIn uqPIOjG - C06g9m0rff9
Bus wUZPglHbh: 9CBIn uqPIOjG - C06g9m0rff9
Stop 9CBIn uqPIOjG: 43.63499 39.81305
10
Bus wUZPglHbh
Bus lw5PH6 Ul3
Bus gazZviu ncDtm
Bus gazZviu ncDtm
Bus lw5PH6 Ul3
Bus wUZPglHbh
Bus gazZviu ncDtm
Bus gazZviu ncDtm
Bus MYb6ycMmNaxXe
Bus wUZPglHbh
*/
/*
5
Bus gazZviu ncDtm: 9CBIn uqPIOjG > C06g9m0rff9 > 9CBIn uqPIOjG
Stop C06g9m0rff9: 43.626432, 39.917507
Bus lw5PH6 Ul3: 9CBIn uqPIOjG - C06g9m0rff9
Bus wUZPglHbh: 9CBIn uqPIOjG - C06g9m0rff9
Stop 9CBIn uqPIOjG: 43.634987, 39.813051
2
Bus wUZPglHbh
Bus lw5PH6
*/
/*
13
Stop Tolstopaltsevo: 55.611087, 37.20829
Stop Marushkino: 55.595884, 37.209755
Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka
Stop Rasskazovka: 55.632761, 37.333324
Stop Biryulyovo Zapadnoye: 55.574371, 37.6517
Stop Biryusinka: 55.581065, 37.64839
Stop Universam: 55.587655, 37.645687
Stop Biryulyovo Tovarnaya: 55.592028, 37.653656
Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164
Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye
Stop Rossoshanskaya ulitsa: 55.595579, 37.605757
Stop Prazhskaya: 55.611678, 37.603831
6
Bus 256
Bus 750
Bus 751
Stop Samara
Stop Prazhskaya
Stop Biryulyovo Zapadnoye
*/
/*
13
Stop Tolstopaltsevo: 55.611087, 37.20829
Stop Marushkino: 55.595884, 37.209755
Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka
Stop Rasskazovka: 55.632761, 37.333324
Stop Biryulyovo Zapadnoye: 55.574371, 37.6517
Stop Biryusinka: 55.581065, 37.64839
Stop Universam: 55.587655, 37.645687
Stop Biryulyovo Tovarnaya: 55.592028, 37.653656
Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164
Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye
Stop Rossoshanskaya ulitsa: 55.595579, 37.605757
Stop Prazhskaya: 55.611678, 37.603831
6
Bus 256
Bus 750
Bus 751
Stop Samara
Stop Prazhskaya
Stop Biryulyovo Zapadnoye
*/

/*
Bus 256: 6 stops on route, 5 unique stops, 4371.0172608446 route length
Bus 750: 5 stops on route, 3 unique stops, 29681.5175684403 route length
Bus 751: not found
Stop  Samara: not found
Stop  Prazhskaya: no buses
Stop  Biryulyovo Zapadnoye: buses 256 828
*/
/*
13
Stop Tolstopaltsevo: 55.611087, 37.20829, 3900m to Marushkino
Stop Marushkino: 55.595884, 37.209755, 9900m to Rasskazovka
Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka
Stop Rasskazovka: 55.632761, 37.333324
Stop Biryulyovo Zapadnoye: 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam
Stop Biryusinka: 55.581065, 37.64839, 750m to Universam
Stop Universam: 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya
Stop Biryulyovo Tovarnaya: 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya
Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164, 1200m to Biryulyovo Zapadnoye
Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye
Stop Rossoshanskaya ulitsa: 55.595579, 37.605757
Stop Prazhskaya: 55.611678, 37.603831
6
Bus 256
Bus 750
Bus 751
Stop Samara
Stop Prazhskaya
Stop Biryulyovo Zapadnoye
*/
/*
13
Stop Tolstopaltsevo: 55.611087, 37.20829, 3900m to Marushkino
Stop Marushkino: 55.595884, 37.209755, 9900m to Rasskazovka, 2400m to Biryulyovo Zapadnoye
Bus 256: Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
Bus 750: Tolstopaltsevo - Marushkino - Biryulyovo Zapadnoye
Stop Rasskazovka: 55.632761, 37.333324
Stop Biryulyovo Zapadnoye: 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam
Stop Biryusinka: 55.581065, 37.64839, 750m to Universam
Stop Universam: 55.587655, 37.645687, 5600m to Rossoshanskaya ulitsa, 900m to Biryulyovo Tovarnaya
Stop Biryulyovo Tovarnaya: 55.592028, 37.653656, 1300m to Biryulyovo Passazhirskaya
Stop Biryulyovo Passazhirskaya: 55.580999, 37.659164, 1200m to Biryulyovo Zapadnoye
Bus 828: Biryulyovo Zapadnoye > Universam > Rossoshanskaya ulitsa > Biryulyovo Zapadnoye
Stop Rossoshanskaya ulitsa: 55.595579, 37.605757
Stop Prazhskaya: 55.611678, 37.603831
6
Bus 256
Bus 750
Bus 751
Stop Samara
Stop Prazhskaya
Stop Biryulyovo Zapadnoye
*/
/*
16
Bus Looped_Single_Intrastop_Distance: A > B > C > A
Stop A: 55.574371, 37.6517, 100m to B
Stop B: 55.581065, 37.64839, 200m to C
Stop C: 55.587655, 37.645687, 300m to A
Bus Looped_Double_Intrastop_Distance: D > E > F > D
Stop D: 55.574371, 37.6517, 100m to E, 400m to F
Stop E: 55.581065, 37.64839, 200m to F, 500m to D
Stop F: 55.587655, 37.645687, 300m to D, 600m to E
Bus Straight_Single_Intrastop_Distance: G - H - I
Stop G: 55.574371, 37.6517, 100m to H
Stop H: 55.581065, 37.64839, 200m to I
Stop I: 55.587655, 37.645687, 300m to H
Bus Straight_Double_Intrastop_Distance: J - K - L
Stop J: 55.574371, 37.6517, 100m to K, 400m to L
Stop K: 55.581065, 37.64839, 200m to L, 500m to J
Stop L: 55.587655, 37.645687, 300m to J, 600m to K
4
Bus Looped_Single_Intrastop_Distance
Bus Looped_Double_Intrastop_Distance
Bus Straight_Single_Intrastop_Distance
Bus Straight_Double_Intrastop_Distance
*/
/*
"Bus Looped_Single_Intrastop_Distance: 4 stops on route, 3 unique stops, 600 route length, 0.196736 curvature\n"
"Bus Looped_Double_Intrastop_Distance: 4 stops on route, 3 unique stops, 600 route length, 0.196736 curvature\n"
"Bus Straight_Single_Intrastop_Distance: 5 stops on route, 3 unique stops, 700 route length, 0.229497 curvature\n"
"Bus Straight_Double_Intrastop_Distance: 5 stops on route, 3 unique stops, 1400 route length, 0.458993 curvature\n"
*/
/*
30
Bus lO6 Uibe0jj0JwbBVDEU0: DxeAU2Ln2M63 - zcHgqd5mq - 32 - V4oWUrgUhxYm - I - 11VdQ0Ld1p1xzDvAKA - 0kYAoodoWXBAC - QLuCbmf E39rLbOX - UYQjxmLk - g1kW2SQXt2wcOx - Y1h87A - igOWZWu - 7oyJ09eHGezpjwGuogm - 0d3U - PC CNf8sfZFBRkD30hG24Yj - 5YaSj4Prpv - 2PwanbZxuIvVN4GV9Wg - eqxztCvVY Cgdx - 0DV 5rBhbYocWFk7xg - ivGZC1AxAUYmFnP - gugBYEznmyZGEOR8wdShX - bjviQn5rCqBO1jVEZE2GPUB2 - Y1h87A - J3Wb4ipcwxGFPlKGuM3j8 - rpWQX7ACPNI9 - 0kYAoodoWXBAC - H3gnaEISkQiznF4RNH9lVS6H - BBnFN0IEf6GT2REpeq4NlQ - LIzYT7fnsgZzVJdLNmrEO1Ki1 - zcHgqd5mq - HJOFe4Mo9JW8V6yRiisNv - 6wTHRaoLEnk0TTNV4of - Os8bkjnFhOeK8uit3cshOK - nFKrGxtLtiPke31 - Uf8Ik6c4kPfH0mvOtRmG0RI0 - lyoh3s7jI2FQcR3VQkK9 - DxeAU2Ln2M63 - x4H - Z4Aqd - sArW9UJe - jPjZuMoYFf31Wi7Z1 - xaAB36yTBNuB4iPwruO3Pew0 - r5mS7GXTcBzemdRyJ1xF1JC
Stop DxeAU2Ln2M63: 38.6162, 34.7608, 521765m to l pQOKbEktVCVK, 283443m to x4H, 800636m to 35pqYv8Oo9vpuE, 623264m to zcHgqd5mq
Stop zcHgqd5mq: 38.4868, 34.8953, 298774m to GrBy VxO, 447756m to HJOFe4Mo9JW8V6yRiisNv, 957004m to 32, 857945m to 6FV6qUkHH, 598443m to vOeuPjYRCax
Stop 32: 38.6399, 34.9033, 683890m to ivGZC1AxAUYmFnP, 891860m to r0735in, 816700m to V4oWUrgUhxYm, 405782m to BCUPJrOHLYO, 987385m to 1hN, 561349m to 8N7ceg3XZCC7D
Stop V4oWUrgUhxYm: 38.4272, 34.818, 139917m to I, 182525m to J3Wb4ipcwxGFPlKGuM3j8, 386900m to CjmHLlmGMsHJDRD3WOhVJEws, 585298m to Mn9eeb
Stop I: 38.494, 34.645, 995451m to GrBy VxO, 559378m to 8OI1RK8RHK, 165275m to 11VdQ0Ld1p1xzDvAKA, 508246m to zcHgqd5mq, 721744m to IM82e0gwg3u5, 499000m to 47yCy ieILP
Stop 11VdQ0Ld1p1xzDvAKA: 38.4131, 34.8952, 350892m to 55Ur3oGkmwZjYH, 641222m to 0kYAoodoWXBAC
Stop 0kYAoodoWXBAC: 38.5525, 34.7508, 820989m to kdPkxd9Lw3zyu4tZAOjRrrl, 980215m to yLZnWlRnZ3HO62qgWX, 182664m to QLuCbmf E39rLbOX, 629399m to H3gnaEISkQiznF4RNH9lVS6H
Stop QLuCbmf E39rLbOX: 38.4939, 34.6574, 682528m to PgdvLcG5X, 134908m to 9wtmpDKfn, 791829m to UYQjxmLk, 589179m to 8PMd4h8eO52ZRiAf, 263465m to 32
Stop UYQjxmLk: 38.3941, 34.8245, 176672m to AwG1mRPMIHMjfX1BD, 550948m to g1kW2SQXt2wcOx
Stop g1kW2SQXt2wcOx: 38.5277, 34.8395, 61303m to vOeuPjYRCax, 363721m to 8GqDq6h4pmvBvWQFHdl0RN, 201112m to Y1h87A, 783065m to 9wtmpDKfn, 695673m to C1v5geZHwuTZ866f
Stop Y1h87A: 38.5232, 34.7629, 447483m to vOeuPjYRCax, 275208m to igOWZWu, 860787m to J3Wb4ipcwxGFPlKGuM3j8
Stop igOWZWu: 38.6431, 34.7042, 797963m to 7oyJ09eHGezpjwGuogm, 586894m to C7J1GKaqGcTWEsp, 299924m to VL2CaQIKTfGFlLqLpmzkVE, 7988m to tQSvq4JrXC ... 62m to JRSQGkT2, 208910m to G
Stop JRSQGkT2: 38.5448, 34.892, 876781m to 7oyJ09eHGezpjwGuogm, 750949m to YSlmzE, 768192m to PC CNf8sfZFBRkD30hG24Yj, 583077m to XcFCI7byCPTVcMXsIN6s9fni
Stop YSlmzE: 38.6043, 34.9703, 339316m to kWaWWHp, 804987m to 85IXX7FB7VGr
Stop 85IXX7FB7VGr: 38.6361, 34.8208, 362592m to C, 764177m to V6MfP, 416448m to HcX
Stop HcX: 38.6818, 34.8104, 475405m to EEYJcyvm XeFRC, 109215m to Uf8Ik6c4kPfH0mvOtRmG0RI0, 704255m to JRSQGkT2
Stop Uf8Ik6c4kPfH0mvOtRmG0RI0: 38.4171, 34.7498, 79592m to DOoNcs, 149798m to QtTl, 153692m to lyoh3s7jI2FQcR3VQkK9, 882047m to XcFCI7byCPTVcMXsIN6s9fni, 961441m to 9wtmpDKfn
Stop XcFCI7byCPTVcMXsIN6s9fni: 38.6381, 34.8101, 830210m to 0DV 5rBhbYocWFk7xg, 508357m to QE0QWM8c, 326744m to fFlYdGFOZTauI91UKvq yD, 962598m to 1DYiPdSm73RiF
Stop fFlYdGFOZTauI91UKvq yD: 38.5162, 34.8705, 661957m to ze X7qQ60fJJ9t1mlo, 841305m to LFyXb4M1d4AAZN  5, 767973m to lyoh3s7jI2FQcR3VQkK9
Stop LFyXb4M1d4AAZN  5: 38.6695, 34.7499, 26079m to xc5BCJ, 25122m to Z4Aqd
Stop Z4Aqd: 38.605, 34.7036, 277476m to sArW9UJe, 681677m to QrF5P, 487637m to 2LzWm6mBje70as, 191845m to q, 589975m to V6MfP
Stop V6MfP: 38.5796, 34.7794, 324690m to QLuCbmf E39rLbOX, 422938m to xaAB36yTBNuB4iPwruO3Pew0, 382248m to 8GqDq6h4pmvBvWQFHdl0RN
Stop 8GqDq6h4pmvBvWQFHdl0RN: 38.6906, 34.8746, 163070m to lyoh3s7jI2FQcR3VQkK9, 933628m to fFlYdGFOZTauI91UKvq yD, 34134m to r0735in
Stop lyoh3s7jI2FQcR3VQkK9: 38.4834, 34.9716, 475470m to 0d3U, 349440m to PDi8Wkv, 137342m to DxeAU2Ln2M63, 432412m to BbCSBtlCdDJ9jNbJ5wP4, 890042m to 12UwYRxF
Stop BbCSBtlCdDJ9jNbJ5wP4: 38.6718, 34.9099, 102134m to J3Wb4ipcwxGFPlKGuM3j8, 367161m to Sq, 623151m to WEFdJ
Stop J3Wb4ipcwxGFPlKGuM3j8: 38.4775, 34.926, 103347m to LIzYT7fnsgZzVJdLNmrEO1Ki1, 357030m to VL2CaQIKTfGFlLqLpmzkVE, 440708m to rpWQX7ACPNI9, 216385m to BBnFN0IEf6GT2REpeq4NlQ, 381470m to Mn9eeb, 605335m to DOoNcs
Stop DOoNcs: 38.6504, 34.9973, 433957m to xEpn6NemwekJsht8iulMQXQug, 439935m to H3gnaEISkQiznF4RNH9lVS6H, 784666m to 2LzWm6mBje70as, 764520m to 5E3wd3fDyB5arL, 833682m to PgdvLcG5X
Stop 5E3wd3fDyB5arL: 38.6706, 34.9872, 599172m to 5YaSj4Prpv, 330372m to 47yCy ieILP, 913986m to X4NLDcD 7785hbS
Stop X4NLDcD 7785hbS: 38.6352, 34.8821, 450345m to EbCPVPuOP1n071GfKS, 47987m to g
*/
