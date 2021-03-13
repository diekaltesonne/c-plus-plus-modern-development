#include <iostream>
#include <cmath>
using namespace std;

void setBinNumber(int Number){

    char tmp;   //0 or 1 for next adding to string binNumber_

    string binNumber_;  //string to return

    while(Number){
        tmp = '0' + Number % 2;
        //cout<<"tmp="<<tmp<<endl;
        binNumber_ = tmp + binNumber_;  //concatenation
        //cout<<"binNumber_="<<binNumber_<<endl;
        Number /= 2;

    }
    cout<<binNumber_;
}


int main()
{

    int n = 0;
    cin >> n;
    //long res = _10_to_2_(n);
    setBinNumber(n);

    return 0;

}

