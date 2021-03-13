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

    void BookingManager::Book(const int64_t& time,const string& hotel_name, const int64_t &client_id,const int&room_count){
        current_time = time;
        counter++;
        //pair_of_booking
        deque<Client>::iterator first = stack_of_client.begin();
        while(first != stack_of_client.end()){
            if(((current_time - 86400)<first->time) && (first->time <= current_time)){
                break;
            }else{
                hotel_map.at(first->pair_of_booking.first).first-=first->pair_of_booking.second;
                size_t t= hotel_map.at(first->pair_of_booking.first).second.at(first->client_id).erase(first->spec_id);
                //cout <<t<<"werwer"<<endl;
                //cout<<hotel_map.at(first->pair_of_booking.first).second.at(first->client_id).size()<<"ewrwer"<<endl;
                if(hotel_map.at(first->pair_of_booking.first).second.at(first->client_id).size() == 0){
                    //cout<<"fkkt"<<endl;
                    hotel_map.at(first->pair_of_booking.first).second.erase(first->client_id);
                }
            }
            first++;
        }
        stack_of_client.erase(stack_of_client.begin(),first);
        Client new_client = {time,hotel_name,client_id,room_count,counter};//warning
        if (hotel_map.count(hotel_name) !=0 ){
            hotel_map.at(hotel_name).first+=room_count;
            if(hotel_map.at(hotel_name).second.count(client_id)!=0){
                hotel_map.at(hotel_name).second.at(client_id).insert(counter);
            }else{
                hotel_map.at(hotel_name).second[client_id]={counter};
            }
        }else{
            hotel_map[hotel_name];
            hotel_map.at(hotel_name).first = room_count;
            hotel_map.at(hotel_name).second[client_id]={counter};
        }
        stack_of_client.push_back(move(new_client));

    }
    size_t BookingManager::getClients(const string& hotel_name){
        if (hotel_map.count(hotel_name) !=0 ){
            //cout<<hotel_map.at(hotel_name).second.size()<<endl;
            return hotel_map.at(hotel_name).second.size();
        }else{
            return 0;
        }
    }
    int BookingManager::getRooms(const string& hotel_name){
        if (hotel_map.count(hotel_name) !=0 ){
            return hotel_map.at(hotel_name).first;
        }else{
            return 0;
        }
    }
    void Run_check(){
      // Для ускорения чтения данных отключается синхронизация
      // cin и cout с stdio,
      // а также выполняется отвязка cin от cout
      ios::sync_with_stdio(false);
      cin.tie(nullptr);
      BookingManager manager;
      int query_count;
      cin >> query_count;
      for (int query_id = 0; query_id < query_count; ++query_id){
        string query_type;
        cin >> query_type;
        if (query_type == "BOOK") {
          int64_t time;
          int64_t client_id;
          int room_count;
          string hotel_name;
          cin >> time >> hotel_name >> client_id >>room_count;
          manager.Book(time,hotel_name,client_id,room_count);
        }else if (query_type == "CLIENTS") {
          string hotel_name;
          cin >> hotel_name;
          cout<<manager.getClients(hotel_name)<<"\n";
        }else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout<<manager.getRooms(hotel_name)<<"\n";
        }
      }
  }

    int main(){
        Run_check();
        return 0;
    }
