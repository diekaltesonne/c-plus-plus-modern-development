#include <iostream>
#include <string>

using namespace std;


int main(){

    string a;
    int count = 0;

    cin>>a;

    for(auto i = 0; i < a.size(); i++){
        if(a[i] == 'f'){
            count++;
            if(count == 2){
                cout<< i;
                break;
            }

        }
    }

    if(count == 1){
        cout<< -1;
    }
    if(count == 0){
        cout<< -2;
    }

    return 0;
}


