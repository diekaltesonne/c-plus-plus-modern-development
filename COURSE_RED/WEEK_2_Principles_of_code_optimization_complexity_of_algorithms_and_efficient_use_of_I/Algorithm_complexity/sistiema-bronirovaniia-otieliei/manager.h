#pragma once
#include <iostream>
#include <map>
#include <deque>
#include <utility>
#include <stdint.h>
#include <set>
#include <algorithm>
using namespace std;
class Client{
public:
    Client(const int64_t& time,const string& hotel_name, const int64_t &client_id,const int&room_count,const int64_t &spec_id):client_id(client_id),time(time),spec_id(spec_id){
       pair_of_booking={hotel_name, room_count};
    }
    Client(){
        int64_t time = 0 ;
        int64_t client_id = 0;
    }
    int64_t time;
    int64_t client_id;
    pair<string,int>pair_of_booking;//booking map of client
    int64_t spec_id;

};
bool operator <(const Client &lhs, const Client& rhs);
class BookingManager {
public:
    void Book(const int64_t& time,const string& hotel_name, const int64_t &client_id,const int&room_count);
    size_t getClients(const string& hotel_name);
    int getRooms(const string& hotel_name);
private:
    map<string,pair<int,map<int64_t,set<int64_t>>>> hotel_map; // map of hotel with room_count and client_id
    deque<Client> stack_of_client; // stack of client that remove with time
    int64_t current_time;
    int64_t counter = 0 ;
};


