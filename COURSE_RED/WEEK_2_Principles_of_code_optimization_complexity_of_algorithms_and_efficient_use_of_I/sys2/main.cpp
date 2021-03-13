
#include <iostream>
#include <map>
#include <utility>
#include <stdint.h>

using namespace std;
struct Client{
    Client(const int64_t& client_id ,const int& count ,const int64_t& time):client_id(client_id) ,count(count) , time(time){
    }
    Client(){
    }
    int64_t client_id = 0;
    int count = 0;
    int64_t time = 0;
};

struct Hotel{
    Hotel(const int64_t& client_id ,const int& count ,const int64_t& time){
        Client r = {client_id,count,time};
        book_of_client = {{client_id,r}};
        room_count =room_count;

    }
    Hotel(){
    }
    map<int64_t,Client> book_of_client;
    int room_count;
};

class BookingManager {
private:
    map<string,Hotel> Hotel_map;
    int64_t current_time;
public:
    void booking(const int64_t& time,const string& hotel_name, const int64_t &client_id,const int&room_count){
        current_time = time;
        map<string,Hotel>::iterator hotel = Hotel_map.begin();
        while (hotel!= Hotel_map.end()){
            map<int64_t,Client>::iterator i = hotel->second.book_of_client.begin();
            while (i!= hotel->second.book_of_client.end()) {
                if (!(((current_time - 86400) < i->second.time) && (i->second.time <= current_time))) {
                    hotel->second.room_count -= i->second.count;
                    //cout<<"test "<< i->second.count<<" test";
                    //cout<<"test "<< hotel->second.room_count<<" test";
                    i = hotel->second.book_of_client.erase(i);
                } else {
                   ++i;
                }
            }
            ++hotel;
        }
        if(Hotel_map.count(hotel_name)!=0){
            if(Hotel_map.at(hotel_name).book_of_client.count(client_id)!=0){
                Hotel_map.at(hotel_name).book_of_client.at(client_id).count+=room_count;
                Hotel_map.at(hotel_name).room_count+=room_count;

            }else{
                 Hotel_map.at(hotel_name).book_of_client[client_id] = {client_id,room_count,time};
                 Hotel_map.at(hotel_name).room_count+=room_count;

            }
        } else{
            Hotel hotel(client_id,room_count,time);
            Hotel_map[hotel_name]= hotel;

        }

    }

    // CLIENTS hotel_name — вывести количество различных клиентов,
    // бронировавших номера в отеле hotel_name за последние сутки.
    // Более формально интересующий диапазон времени описывается следующим образом: пусть current_time —    ,
    // тогда в данном запросе нужно учесть все события с current_time − 86400 < time ⩽ current_time, где 86400 — количество секунд в сутках.
    // Обратите внимание, что последнее бронирование должно учитываться, а бронирование, случившееся ровно за сутки до него, учитываться не должно.

    size_t client_output(const string& hotel_name){
        if (Hotel_map.count(hotel_name) !=0 ){
            return Hotel_map.at(hotel_name).book_of_client.size();
        }else{
            return 0;
        }
    }

    //ROOMS hotel_name — вывести количество номеров, забронированных за последние сутки в отеле hotel_name.
    int room_output(const string& hotel_name){
        if (Hotel_map.count(hotel_name) !=0 ){
            return Hotel_map.at(hotel_name).room_count;
        }else{
            return 0;
        }
    }


};


void Run_check();
int main(){
    Run_check();
    return 0;
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
      for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        if (query_type == "BOOK") {
          long long time;
          int  client_id,room_count;
          string hotel_name;
          cin >> time >> hotel_name >> client_id >>room_count;
          manager.booking(time,hotel_name,client_id,room_count);
        }else if (query_type == "CLIENTS") {
          string hotel_name;
          cin >> hotel_name;
          cout<<manager.client_output(hotel_name)<<"\n";
        }else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout<<manager.room_output(hotel_name)<<"\n";
        }
      }
}

//            for(auto i : Hotel_map.at(hotel_name).book_of_client){
//                if(((current_time - 86400) < i.second.time) && (i.second.time <= current_time)){

//                }
//                else{
//                    Hotel_map.at(hotel_name).room_count -= i.second.count;
//                    cout<<"test "<< i.second.count<<" test";
//                    cout<<"test "<< Hotel_map.at(hotel_name).room_count<<" test";
//                    Hotel_map.at(hotel_name).book_of_client.erase(i.first);
//                }
//            }
