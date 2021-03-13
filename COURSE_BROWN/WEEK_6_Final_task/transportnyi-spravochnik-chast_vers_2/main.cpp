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
#include <variant>
#include <string>
#include <istream>
#include <json.hpp>
// for convenience
using json = nlohmann::json;

#define pi 3.1415926535

using namespace std;


class Node : std::variant<std::vector<Node>,std::map<std::string, Node>,double, bool ,std::string> {
  public:
    using variant::variant;

    const auto& AsArray() const {
      return std::get<std::vector<Node>>(*this);
    }

    const auto& AsMap() const {
      return std::get<std::map<std::string, Node>>(*this);
    }

    double AsDouble() const {
      return std::get<double>(*this);
    }

    const auto& AsString() const {
      return std::get<std::string>(*this);
    }
    bool AsBool() const {
      return std::get<bool>(*this);
    }
};

  class Document {
  public:
    explicit Document(Node root);
    const Node& GetRoot() const;

  private:
    Node root;
  };

  Document Load(std::istream& input);

  Document::Document(Node root) : root(move(root)) {
  }

  const Node& Document::GetRoot() const {
    return root;
  }

  Node LoadNode(istream& input);
  Node LoadArray(istream& input) {
    vector<Node> result;

    for (char c; input >> c && c != ']'; ) {
      if (c != ',') {
        input.putback(c);
      }
      result.push_back(LoadNode(input));
    }
    return Node(move(result));
  }

  Node LoadDouble(istream& input) {
    double result = 0;
    int min = 1;
    char c;
    input>> c;
    if(c== '-'){
        min =-1;
    }else{
        input.putback(c);
    }
    while (isdigit(input.peek())) {
      result *= 10;
      result += input.get() - '0';
    }
    input>> c;
    if(c =='.'){
        double res =0;
        int i =0;
        while (isdigit(input.peek())) {
          //result += 0.1;
          res *= 10;
          res += (input.get() - '0');
          i++;
        }
//        //cout<<i<<endl;
//        //cout<<res<<endl;
          res= res/(pow(10,i));
//        //cout<<res<<endl;
//        res = 0.000001;
         result=result+res;
         //cout<<result<<"asas"<<endl;
    }else{
        input.putback(c);
    }
    result*=min;
    //cout<<result<<" конечный "<<endl;
    return Node(result);
  }

  Node LoadString(istream& input) {
    string line;
    getline(input, line, '"');
    return Node(move(line));
  }
  Node LoadBool(istream& input) {
    bool c;
    input >>std::boolalpha>>c;
    return Node(move(c));
  }
  Node LoadDict(istream& input) {
    map<string, Node> result;
    for (char c; input >> c && c != '}'; ) {
      if (c == ',') {
        input >> c;
      }
      string key = LoadString(input).AsString();
      input >> c;
      result.emplace(move(key), LoadNode(input));
    }
    return Node(move(result));
  }

  Node LoadNode(istream& input) {
    char c;
    input >> c;

    if (c == '[') {
      return LoadArray(input);
    } else if (c == '{') {
      return LoadDict(input);
    } else if (c == '"') {
      return LoadString(input);
    }else if (c == 'f' || c=='t'){
        input.putback(c);
        return LoadBool(input);
    }else{
        input.putback(c);
        return LoadDouble(input);
    }

  }
  Document Load(istream& input) {
    return Document{LoadNode(input)};
  }

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
    json jhon;
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
    void bus_info(string X,int id){
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
                jhon.push_back( {{"route_length",int(distance)},{"request_id", id},{"curvature",curv},{"stop_count",bus.stops.size()},{"unique_stop_count",un_stops.size()}});
                 //out<<"Bus "<<X<<": "<< bus.stops.size() <<" stops on route, "<< un_stops.size() <<" unique stops, "<< fixed << setprecision(6)<<int(distance) <<" route length, "<<curv<<" curvature"<<endl;
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
                jhon.push_back({{"route_length",int(distance+distance_2)},{"request_id", id},{"curvature",(curv+curv_2)/2},{"stop_count",bus.stops.size()+bus.stops.size()-1},{"unique_stop_count",un_stops.size()}});
                //out<<"Bus "<<X<<": "<< bus.stops.size()+bus.stops.size()-1 <<" stops on route, "<< un_stops.size() <<" unique stops, "<< fixed << setprecision(6)<<int(distance+distance_2 )<<" route length, "<<(curv+curv_2)/2<<" curvature"<<endl;
            }
        }else{
            jhon.push_back({ {"request_id", id},{"error_message", "not found"}});
            //out<<"Bus "<<X<<":"<<" not found"<<endl;
        }
    }
    void stop_info(string X,int id){
        if(stops.count(X)!=0){
            if(stops.at(X).puss_bus.size()!=0){
                jhon.push_back({ {"buses", stops.at(X).puss_bus} ,{"request_id", id}});
            }else{

                jhon.push_back({ {"buses", stops.at(X).puss_bus} ,{"request_id", id}});
            }
        }else{
            jhon.push_back({ {"request_id", id},{"error_message", "not found"}});
        }
    }
    void Print(){
        cout<<jhon.dump()<<endl;
    }
};

//cout<<"OK"<<endl;
void LoadFromJson_to_Sprav(istream& input,Spravochnik& sprav) {

  Document doc = Load(input);

  for(const Node& node : doc.GetRoot().AsMap().at("base_requests").AsArray()){
        if(node.AsMap().at("type").AsString() ==  "Bus"){

              string name =  node.AsMap().at("name").AsString();
              vector <string> stops;
              for (const Node& node_2 : node.AsMap().at("stops").AsArray()){
                   stops.push_back(node_2.AsString());
              }

              bool round = node.AsMap().at("is_roundtrip").AsBool();

              if(round){
                  sprav.bus_circle(move(name),move(stops));
              }else{
                  sprav.bus_straight(move(name),move(stops));
              }
          }else{
              unordered_map<string,double> dis_to;
              string name =  node.AsMap().at("name").AsString();

              for ( const auto & i  : node.AsMap().at("road_distances").AsMap()){

                  dis_to.insert(make_pair(i.first,i.second.AsDouble()));
              }

              double latitude = node.AsMap().at("latitude").AsDouble();

              double longitude = node.AsMap().at("longitude").AsDouble();

              if(dis_to.size()!=0){
                  sprav.stop(name,latitude,longitude,dis_to);
              }else{
                  sprav.stop(move(name),move(latitude),move(longitude));
              }

        }
  }
  for(const Node& node : doc.GetRoot().AsMap().at("stat_requests").AsArray()){
      if(node.AsMap().at("type").AsString() ==  "Bus"){

            string name =  node.AsMap().at("name").AsString();
            int id = (int)node.AsMap().at("id").AsDouble();
            sprav.bus_info(move(name),id);
        }else{
            string name =  node.AsMap().at("name").AsString();
            int id = (int)node.AsMap().at("id").AsDouble();
            sprav.stop_info(move(name),id);
      }

  }
}
void processor(Spravochnik& sprav ,istream& input){
    LoadFromJson_to_Sprav(input, sprav);
    sprav.Print();
}
/*
    {
      "type": "Bus",
      "name": "256",
      "stops": [
        "Biryulyovo Zapadnoye",
        "Biryusinka",
        "Universam",
        "Biryulyovo Tovarnaya",
        "Biryulyovo Passazhirskaya",
        "Biryulyovo Zapadnoye"
      ],
      "is_roundtrip": true
    }
*/
int main(){
    std::cout << std::setprecision(25);
    Spravochnik gor_sprav;
    processor(gor_sprav,cin);
    return 0;
}

/*
{
  "base_requests": [
    {
      "type": "Stop",
      "road_distances": {
        "Marushkino": 3900
      },
      "longitude": 37.20829,
      "name": "Tolstopaltsevo",
      "latitude": 55.611087
    },
    {
      "type": "Stop",
      "road_distances": {
        "Rasskazovka": 9900
      },
      "longitude": 37.209755,
      "name": "Marushkino",
      "latitude": 55.595884
    },
    {
      "type": "Stop",
      "road_distances": {},
      "longitude": 37.333324,
      "name": "Rasskazovka",
      "latitude": 55.632761
    },
    {
      "type": "Stop",
      "road_distances": {
        "Rossoshanskaya ulitsa": 7500,
        "Biryusinka": 1800,
        "Universam": 2400
      },
      "longitude": 37.6517,
      "name": "Biryulyovo Zapadnoye",
      "latitude": 55.574371
    },
    {
      "type": "Stop",
      "road_distances": {
        "Universam": 750
      },
      "longitude": 37.64839,
      "name": "Biryusinka",
      "latitude": 55.581065
    },
    {
      "type": "Stop",
      "road_distances": {
        "Rossoshanskaya ulitsa": 5600,
        "Biryulyovo Tovarnaya": 900
      },
      "longitude": 37.645687,
      "name": "Universam",
      "latitude": 55.587655
    },
    {
      "type": "Stop",
      "road_distances": {
        "Biryulyovo Passazhirskaya": 1300
      },
      "longitude": 37.653656,
      "name": "Biryulyovo Tovarnaya",
      "latitude": 55.592028
    },
    {
      "type": "Stop",
      "road_distances": {
        "Biryulyovo Zapadnoye": 1200
      },
      "longitude": 37.659164,
      "name": "Biryulyovo Passazhirskaya",
      "latitude": 55.580999
    },
    {
      "type": "Stop",
      "road_distances": {},
      "longitude": 37.605757,
      "name": "Rossoshanskaya ulitsa",
      "latitude": 55.595579
    },
    {
      "type": "Stop",
      "road_distances": {},
      "longitude": 37.603831,
      "name": "Prazhskaya",
      "latitude": 55.611678
    }
  ]
}
*/

/*
{
  "base_requests": [
    {
      "type": "Stop",
      "road_distances": {
        "Marushkino": 3900
      },
      "longitude": 37.20829,
      "name": "Tolstopaltsevo",
      "latitude": 55.611087
    },
    {
      "type": "Stop",
      "road_distances": {
        "Rasskazovka": 9900
      },
      "longitude": 37.209755,
      "name": "Marushkino",
      "latitude": 55.595884
    },
    {
      "type": "Bus",
      "name": "256",
      "stops": [
        "Biryulyovo Zapadnoye",
        "Biryusinka",
        "Universam",
        "Biryulyovo Tovarnaya",
        "Biryulyovo Passazhirskaya",
        "Biryulyovo Zapadnoye"
      ],
      "is_roundtrip": true
    },
    {
      "type": "Bus",
      "name": "750",
      "stops": [
        "Tolstopaltsevo",
        "Marushkino",
        "Rasskazovka"
      ],
      "is_roundtrip": false
    },
    {
      "type": "Stop",
      "road_distances": {},
      "longitude": 37.333324,
      "name": "Rasskazovka",
      "latitude": 55.632761
    },
    {
      "type": "Stop",
      "road_distances": {
        "Rossoshanskaya ulitsa": 7500,
        "Biryusinka": 1800,
        "Universam": 2400
      },
      "longitude": 37.6517,
      "name": "Biryulyovo Zapadnoye",
      "latitude": 55.574371
    },
    {
      "type": "Stop",
      "road_distances": {
        "Universam": 750
      },
      "longitude": 37.64839,
      "name": "Biryusinka",
      "latitude": 55.581065
    },
    {
      "type": "Stop",
      "road_distances": {
        "Rossoshanskaya ulitsa": 5600,
        "Biryulyovo Tovarnaya": 900
      },
      "longitude": 37.645687,
      "name": "Universam",
      "latitude": 55.587655
    },
    {
      "type": "Stop",
      "road_distances": {
        "Biryulyovo Passazhirskaya": 1300
      },
      "longitude": 37.653656,
      "name": "Biryulyovo Tovarnaya",
      "latitude": 55.592028
    },
    {
      "type": "Stop",
      "road_distances": {
        "Biryulyovo Zapadnoye": 1200
      },
      "longitude": 37.659164,
      "name": "Biryulyovo Passazhirskaya",
      "latitude": 55.580999
    },
    {
      "type": "Bus",
      "name": "828",
      "stops": [
        "Biryulyovo Zapadnoye",
        "Universam",
        "Rossoshanskaya ulitsa",
        "Biryulyovo Zapadnoye"
      ],
      "is_roundtrip": true
    },
    {
      "type": "Stop",
      "road_distances": {},
      "longitude": 37.605757,
      "name": "Rossoshanskaya ulitsa",
      "latitude": 55.595579
    },
    {
      "type": "Stop",
      "road_distances": {},
      "longitude": 37.603831,
      "name": "Prazhskaya",
      "latitude": 55.611678
    }
  ],
  "stat_requests": [
    {
      "type": "Bus",
      "name": "256",
      "id": 1965312327
    },
    {
      "type": "Bus",
      "name": "750",
      "id": 519139350
    },
    {
      "type": "Bus",
      "name": "751",
      "id": 194217464
    },
    {
      "type": "Stop",
      "name": "Samara",
      "id": 746888088
    },
    {
      "type": "Stop",
      "name": "Prazhskaya",
      "id": 65100610
    },
    {
      "type": "Stop",
      "name": "Biryulyovo Zapadnoye",
      "id": 1042838872
    }
  ]
}
*/
/*
{
  "stat_requests": [
    {
      "type": "Bus",
      "name": "256",
      "id": 1965312327
    },
    {
      "type": "Bus",
      "name": "750",
      "id": 519139350
    },
    {
      "type": "Bus",
      "name": "751",
      "id": 194217464
    },
    {
      "type": "Stop",
      "name": "Samara",
      "id": 746888088
    },
    {
      "type": "Stop",
      "name": "Prazhskaya",
      "id": 65100610
    },
    {
      "type": "Stop",
      "name": "Biryulyovo Zapadnoye",
      "id": 1042838872
    }
  ]
}
*/

