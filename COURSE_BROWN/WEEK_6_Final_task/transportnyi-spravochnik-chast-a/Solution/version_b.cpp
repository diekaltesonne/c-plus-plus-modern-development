#include <iostream>
#include <vector>
#include <cmath>
#include <test_runner.h>
#include <sstream>
#include <map>
#include <iomanip>
#include <set>
#define pi 3.1415926535
using namespace std;

//output << fixed << setprecision(6); - у меня вывод организован так.
//Для тех, у кого возникают непреодолимые трудности с решением, могу посоветовать небольшой лайфхак, который помог мне самому найти многие ошибки.
//Можно логировать (писать в string или в любой другой тип данных) всю интересующую Вас информацию (запросы, состояния переменных на любых этапах работы программы и
//т.д.)
//и в том месте, где Вы считаете, что программа может работать неправильно писать этот "лог" в std::cerr (поток ошибок) и
//тут же кидать любое исключение (runtime_error, out_of_range и т.д.).
//Прикол в том, что выбрасывании исключения программа аварийно упадет грейдер напишет Вам "wrong answer (unknown signal)",
//но в тоже время он пришлет всё содержимое std::cerr, где будут находится Ваш лог и вы сможете посмотреть как работает ваша программа
//на реальных входных данных.
//Я сам лично не раз пользовался этим способом, и
//благодаря ему нашел ошибки в частях A, B и E, когда уже казалось, что всё перепробовано, а ошибка не находилась.
//И в итоге сдал все части.
//P.S. Надеюсь, после обнаружения этого лайфхака у грейдера не отключат вывод stderr и этот способ ещё кому нибудь поможет.


class Spravochnik{
private:
    class Stop_info{
    public:
        string name;
        pair<double,double> coordinates;
        set<string>  puss_bus;
    };
    class Bus_info{
    public:
        string name;
        vector<string> stops;
        int round = 0;
    };
    double toRad(double degree) {
        return degree/180 * pi;
    }
    double calculateDistance(double lat1, double long1, double lat2, double long2) {
        double dist = sin(toRad(lat1)) * sin(toRad(lat2)) + cos(toRad(lat1)) * cos(toRad(lat2)) * cos(abs(toRad(long1 - long2)));
        dist = acos(dist);
        dist = 6371000 * dist;
        return dist;
    }
    pair<double, double> get_stop(string stop){
        return stops.at(stop).coordinates;
    }
    map <string,Bus_info> buses;
    map <string,Stop_info> stops;


public:
    int stop(string X, double latitude, double longitude){
        if(stops.count(X)!=0){
            stops.at(X).coordinates= make_pair(latitude,longitude);
        }else{
            Stop_info new_stop;
            new_stop.name =X;
            new_stop.coordinates = make_pair(latitude,longitude);
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
                Stop_info x;
                x.name = i;
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
                Stop_info x;
                x.name = i;
                stops[i]= x;
                stops.at(i).puss_bus.insert(X);
            }
        }
        return 0;
        return 0;

    }
    ostream& bus_info(string X,ostream & out){
        //cout<<X;
        if(buses.count(X)!=0){
           Bus_info bus = buses.at(X);
            set<string> un_stops(bus.stops.begin(),bus.stops.end());
            pair<double, double> prev = get_stop(*bus.stops.begin());
            double distance = 0;
            for(auto it_stop = bus.stops.begin() + 1; it_stop != bus.stops.end(); it_stop++) {
                auto cur = get_stop(*it_stop);
                double dist = calculateDistance(prev.first, prev.second, cur.first, cur.second);
                distance += dist;
                prev = cur;
            }
            if(bus.round == 1){
                    cout<<"Bus "<<X<<": "<< bus.stops.size() <<" stops on route, "<< un_stops.size() <<" unique stops, "<< fixed << setprecision(6)<<distance <<" route length"<<endl;
            }else{
                 //cout<< distance;
                 distance *= 2;
                     cout<<"Bus "<<X<<": "<< bus.stops.size()+bus.stops.size()-1 <<" stops on route, "<< un_stops.size() <<" unique stops, "<< fixed << setprecision(6)<<distance <<" route length"<<endl;
            }
            return out;
        }else{
            cout<<"Bus "<<X<<":"<<" not found"<<endl;
            return out;
        }
        return out;
    }
    ostream& stop_info(string X,ostream & out){
        if(stops.count(X)!=0){
            if(stops.at(X).puss_bus.size()!=0){
                cout<<"Stop  "<<X<<": buses";
                for(auto & i:stops.at(X).puss_bus){
                    cout<<" "<<i;
                }
                cout<<endl;
            }else{
                cout<<"Stop  "<<X<<":"<<" no buses"<<endl;
            }
        }else{
            cout<<"Stop  "<<X<<":"<<" not found"<<endl;
            return out;
        }
        return out;
    }
};
std::vector<std::string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  ss.ignore(1);
  while (std::getline(ss, item, delim)){
    item.pop_back();
    elems.push_back(move(item));
    ss.ignore(1);

  }
  return elems;
}

void processor(Spravochnik& sprav){
    int query_count =0;
    cin >> query_count;
    for (int query_id = 0; query_id < query_count; ++query_id){
        string query_type;
        cin >> query_type;
        if (query_type == "Stop"){
            string stop;
            double latitude,longitude;
            //cin >>stop;
            //stop.pop_back();
            cin.ignore(1);
            getline(std::cin,stop,':');
            cin.ignore(1);
            cin >> latitude;
            cin.ignore(2);
            cin >> longitude;
            sprav.stop(stop,latitude,longitude);
        }else if (query_type == "Bus") {
            string num;
            cin.ignore(1);
            getline(std::cin,num,':');
            string track;
            getline(std::cin,track);
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
    }
    query_count =0;
    cin >> query_count;
    for (int query_id = 0; query_id < query_count; ++query_id){
        string query_type;
        cin >> query_type;
        if (query_type == "Bus") {
            string num;
            cin.ignore(1);
            getline(std::cin,num);
           sprav.bus_info(num,cout);
        }else if (query_type == "Stop") {
                string stop;
                cin.ignore(1);
                getline(std::cin,stop);
                sprav.stop_info(stop,cout);
        }
    }
}



int main(){
    Spravochnik gor_sprav;
    processor(gor_sprav);



    return 0;
}
