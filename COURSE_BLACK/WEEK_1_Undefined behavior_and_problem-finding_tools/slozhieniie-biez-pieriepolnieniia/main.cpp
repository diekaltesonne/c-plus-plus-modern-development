#include <iostream>
#include <stdint.h>
using namespace std;

int64_t addOvf(int64_t rhs, int64_t lhs){

    if (!((rhs ^ lhs) < 0)) {                    //test for +/- combo
        //either two negatives or two positives
        if (rhs < 0) {
          //two negatives
          if (lhs < INT64_MIN - rhs) {              //remember rhs < 0
            cout<<"Overflow!";
            return 0;
          }
          //ok
       }
       else {
         //two positives
         if (INT64_MAX - lhs < rhs) {
             cout<<"Overflow!";
             return 0;
         }
         //OK
       }
     }
     cout<<lhs + rhs;
     return 0;

}

int main()
{
    int64_t x;
    int64_t y;
    cin>>x>>y;
    addOvf(x,y);
    return 0;
}
