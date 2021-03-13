#include <iostream>
#include <vector>
#include <cmath>
#include <test_runner.h>
#include <sstream>
#include <map>
#include <iomanip>
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
    double toRad(double degree) {
        return degree/180 * pi;
    }
    double calculateDistance(double lat1, double long1, double lat2, double long2) {
        double dist = std::sin(toRad(lat1)) * std::sin(toRad(lat2)) + std::cos(toRad(lat1)) * std::cos(toRad(lat2)) * std::cos(std::abs(toRad(long1 - long2)));
        dist = std::acos(dist);
        dist = 6371000 * dist;
        return dist;
    }
    pair<double, double> get_stop(string stop){
        //cout<<"ASDAD"<<endl;
        return stops.at(stop);
    }
    map <string,pair<vector<string>,int>> bus_track;
    map <string,pair<double,double>> stops;
public:
    int stop(string X, double latitude, double longitude){
        //cout<<X<<" "<<latitude<<" "<<longitude;
        stops[X]= make_pair(latitude,longitude);
        return 0;
    }
    int bus_straight(string X,vector<string>points){

        bus_track[X] = make_pair(points,0);
        return 0;
    }
    int bus_circle(string X,vector<string>points){

        bus_track[X] = make_pair(points,1);
        return 0;
    }
    ostream& bus_info(string X,ostream & out){
        //cout<<X;
        if(bus_track.count(X)!=0){
            //cout<<X;
            pair<vector<string>,int> bus_info = bus_track.at(X);
            //cout<<"OKO"<<endl;
            set<string> un_stops(bus_info.first.begin(),bus_info.first.end());
            pair<double, double> prev = get_stop(*bus_info.first.begin());
            double distance;
            for(auto it_stop = bus_info.first.begin() + 1; it_stop != bus_info.first.end(); it_stop++) {
                auto cur = get_stop(*it_stop);
                double dist = calculateDistance(prev.first, prev.second, cur.first, cur.second);
                distance += dist;
                prev = cur;
            }
            //флаг если маршрут круговой
            if(bus_info.second == 1){
                    cout<<"Bus "<<X<<": "<< bus_info.first.size() <<" stops on route, "<< un_stops.size() <<" unique stops, "<< fixed << setprecision(6)<<distance <<" route length"<<endl;
            }else{
                 distance *= 2;
                     cout<<"Bus "<<X<<": "<< bus_info.first.size()+bus_info.first.size()-1 <<" stops on route, "<< un_stops.size() <<" unique stops, "<< fixed << setprecision(6)<<distance <<" route length"<<endl;

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
            pair<vector<string>,int> bus_info = bus_track.at(X);
            set<string> un_stops(bus_info.first.begin(),bus_info.first.end());
            pair<double, double> prev = get_stop(*bus_info.first.begin());
            double distance;
            for(auto it_stop = bus_info.first.begin() + 1; it_stop != bus_info.first.end(); it_stop++) {
                auto cur = get_stop(*it_stop);
                double dist = calculateDistance(prev.first, prev.second, cur.first, cur.second);
                distance += dist;
                prev = cur;
            }
            //флаг если маршрут круговой
            if(bus_info.second == 1){
                 cout<<"Bus "<<X<<": "<< bus_info.first.size() <<" stops on route, "<< un_stops.size() <<" unique stops, "<< fixed << setprecision(6)<<distance <<" route length"<<endl;
            }else{
                 distance *= 2;
                 cout<<"Bus "<<X<<": "<< bus_info.first.size()+bus_info.first.size()-1 <<" stops on route, "<< un_stops.size() <<" unique stops, "<< fixed << setprecision(6)<<distance <<" route length"<<endl;
            }
            return out;
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

void test_req(){
}

int main(){
    Spravochnik gor_sprav;
    processor(gor_sprav);


    //TestRunner tr;
    //RUN_TEST(tr,test_req);
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
