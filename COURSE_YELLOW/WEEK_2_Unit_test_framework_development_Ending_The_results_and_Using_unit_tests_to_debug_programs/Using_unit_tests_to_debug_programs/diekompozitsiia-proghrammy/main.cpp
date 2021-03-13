#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
using namespace std;

string x;
enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {

  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string typeStr;
    is >> typeStr;
    if (typeStr == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count = 0;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (auto& stop : q.stops) {
            is >> stop;
        }
    }
    if (typeStr == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    if (typeStr == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    if (typeStr == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }
  return is;
}


// Наполните полями эту структуру - DONE
struct BusesForStopResponse {
    map<string, vector<string>> buses_to_stops;
    map<string, vector<string>> stops_to_buses;


};
// Наполните полями эту структуру - DONE
struct StopsForBusResponse {
    BusesForStopResponse &bfsr;
};
// Наполните полями эту структуру
struct AllBusesResponse{
    BusesForStopResponse &bfsr;
    StopsForBusResponse  &sfbr;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    //x = stop;
    if (r.stops_to_buses.count(x) == 0){
        os << "No stop" << endl;
    }else{
        for (const string& bus: r.stops_to_buses.at(x)) {
            os << bus << " ";
        }
        os<< endl;
    }
    return os;

}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    //x = bus;
    if (r.bfsr.buses_to_stops.count(x) == 0) {
            os << "No bus" << endl;
    } else {
    for (const string& stop : r.bfsr.buses_to_stops.at(x)) {
          os << "Stop " << stop << ": ";
          if (r.bfsr.stops_to_buses.at(stop).size() == 1) {
            os << "no interchange";

          } else {
              for (const string& other_bus : r.bfsr.stops_to_buses.at(stop)){
                if (x!= other_bus){
                    os << other_bus << " ";
                }
              }
          }
          os << endl;
    }
    }
    return os;
}
ostream& operator << (ostream& os, const AllBusesResponse& r) {

    if (r.bfsr.buses_to_stops.empty()) {
            os << "No buses" << endl;
    } else {
        for (const auto& bus_item : r.bfsr.buses_to_stops) {
            os << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                os << stop << " ";
            }
            os << endl;
        }
    }
    return os;
}

class BusManager {
public:

    // Реализуйте этот метод - DONE
    void AddBus(const string& bus, const vector<string>& stops) {

        int i =0;
        vector<string>& stops_2 = BFSR.buses_to_stops[bus];
        stops_2.resize(stops.size());
        for (string & st : stops_2){
            st=stops[i];
            BFSR.stops_to_buses[st].push_back(bus);
            i++;
        }

    }
    BusesForStopResponse GetBusesForStop(const string& stop) const {
        x = stop;
        return BFSR;
    }
    StopsForBusResponse GetStopsForBus(const string& bus) const {
        x = bus;
        return SFBR;
    }
  AllBusesResponse GetAllBuses() const {
    // Реализуйте этот метод
    return ABR;
  }

private:
  BusesForStopResponse BFSR;
  StopsForBusResponse SFBR = {BFSR};
  AllBusesResponse ABR = {BFSR,SFBR};

};
// Не меняя тела функции main, реализуйте функции и классы выше

int main(){

  int query_count;
  Query q;
  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
