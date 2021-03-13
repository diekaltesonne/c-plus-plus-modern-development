#pragma once
#include <unordered_map>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cmath>
#include <algorithm>






struct Stop_info{
    Stop_info(){
    }
    Stop_info(string name, pair<double,double> coordinates, unordered_map<string,double> dis_to,size_t start_waiting, size_t stop_waiting):
        name(name),
        coordinates(coordinates),
        dis_to(dis_to),
        start_waiting(start_waiting),
        stop_waiting(stop_waiting)
    {
    }
    Stop_info(string name, pair<double,double> coordinates,size_t start_waiting, size_t stop_waiting):
        name(name),
        coordinates(coordinates),
        start_waiting(start_waiting),
        stop_waiting(stop_waiting){

    }
    Stop_info(string name):
        name(name){
    }
    string name;
    pair<double,double> coordinates;
    set<string>  puss_bus;
    unordered_map<string,double> dis_to;
    size_t start_waiting =0;
    size_t stop_waiting  =0;
};
struct Bus_info{
    string name;
    vector<string> stops;
    int round = 0;
};


struct Routing_Settings{
    double bus_wait_time =  0;
    double bus_velocity = 0 ;
};

class Stops_Buses{
public:
    map<string,Bus_info> buses;
    map<string,Stop_info> stops;
    Routing_Settings settings;
    size_t id = -1;
    int stop(string X, double latitude, double longitude){
        if(stops.count(X)!=0){
            stops.at(X).coordinates= make_pair(latitude,longitude);
        }else{
            id++;
            size_t start_waiting =id;
            id++;
            size_t stop_waiting = id;
            Stop_info new_stop(X,make_pair(latitude,longitude),start_waiting,stop_waiting);
            stops[X]= new_stop;
        }
        return 0;
    }
    int stop(string X, double latitude, double longitude, unordered_map<string,double> dis_to){
        if(stops.count(X)!=0){
            stops.at(X).coordinates= make_pair(latitude,longitude);
            stops.at(X).dis_to = dis_to;
        }else{
            id++;
            size_t start_waiting =id;
            id++;
            size_t stop_waiting = id;
            Stop_info new_stop(X,make_pair(latitude,longitude),dis_to,start_waiting,stop_waiting);
            stops[X]= new_stop;
        }
        return 0;
    } 
    int sts(int bus_wait_time,double bus_velocity){
        settings.bus_wait_time = bus_wait_time;
        settings.bus_velocity=bus_velocity;
        return 0;
    }

    Stop_info get_stop(string stop){
        return stops.at(stop);
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
                id++;
                x.start_waiting =id;
                id++;
                x.stop_waiting = id;
                stops[i]= x;
               // cout<<X<<endl;
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
        buses[X] = new_bus;
        for(auto &i: un_stops){
            if(stops.count(i)!=0){
                stops.at(i).puss_bus.insert(X);
            } else {
                Stop_info x(i);
                id++;
                x.start_waiting =id;
                id++;
                x.stop_waiting = id;
                stops[i]= x;
               // cout<<X<<endl;
                stops.at(i).puss_bus.insert(X);
            }
        }
        return 0;
    }
};

ostream& operator<<(ostream & out, const Stop_info &v){
    out<<"Stop "<<v.name<<": "<<v.coordinates.first <<", "<<v.coordinates.second;
    for(auto i: v.dis_to){
        out<<", "<<i.second<<"m to "<<i.first;
    }
    out<<"\n";
    return out;
}

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
