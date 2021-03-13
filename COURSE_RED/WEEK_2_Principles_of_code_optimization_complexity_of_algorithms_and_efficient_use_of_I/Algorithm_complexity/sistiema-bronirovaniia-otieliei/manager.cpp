#include "manager.h"
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
                if(hotel_map.at(first->pair_of_booking.first).second.at(first->client_id).size() == 0){
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


