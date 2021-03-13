#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;
int main(){
    int Q = 0;
    cin >> Q;
    int number = 0;
    int k = 1;
    string stop;
    map<set<string>,int> data_base;
    for (int i = 0; i < Q; ++i) {
        cin >> number;
        set<string>stops;
        for(int i =0 ; i<number;i++){
            cin>> stop;
            stops.insert(stop);
        }
        if(data_base.count(stops)!=0){
            cout <<"Already exists for "<<data_base[stops]<<endl;
        }
        else{
            cout <<"New bus "<<k<<endl;
            data_base[stops] = k ;
            k++;
        }
    }
    return 0;
}

