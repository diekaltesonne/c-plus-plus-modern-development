#include <iostream>
#include <cmath>
#include <typeinfo>

using namespace std;

int main(){

    float a, b, c;

    cin >> a >> b >> c;

    double x1;
    double x2;


   if(a == 0 && b == 0){
       return 0;

   }
   if((a == 0 && c == 0)||(b == 0 && c == 0)){
       cout << 0;
       return 0;

   }




    if( a == 0){
        x1 = (-c)/b;
        x2 = 0;
        cout << x1;
        return 0;
    }

    if( b == 0){

        x1 = (-b-sqrt(pow(b,2) - 4*a*c))/(2*a);
        x2 = (-b+sqrt(pow(b,2) - 4*a*c))/(2*a);
        if ((x1 != x1) && (x2 != x2) ){
            return 0;
        }
        else{

            if(x2!= x2 ){
                 cout<< x1;
            }
            if(x1!= x1 ){
                 cout<< x2;
            }
            if(x1 == x2) cout<< x1;
            else cout<<x2<<" "<<x1;
        }
        return 0;
    }

    if( c == 0){

        x1 = (-b-sqrt(pow(b,2) - 4*a*c))/(2*a);
        x2 = (-b+sqrt(pow(b,2) - 4*a*c))/(2*a);
        if ((x1 != x1) && (x2 != x2) ){
            return 0;
        }
        else{

            if(x2!= x2 ){
                 cout<< x1;
            }
            if(x1!= x1 ){
                 cout<< x2;
            }
            if(x1 == x2) cout<< x1;
            else cout<<x2<<" "<<x1;
        }
        return 0;


    }


    x1 = (-b-sqrt(pow(b,2) - 4*a*c))/(2*a);
    x2 = (-b+sqrt(pow(b,2) - 4*a*c))/(2*a);

    if ((x1 != x1) && (x2 != x2) ){
        return 0;
    }
    else{

        if(x2!= x2 ){
             cout<< x1;
        }
        if(x1!= x1 ){
             cout<< x2;
        }
        if(x1 == x2) cout<< x1;
        else cout<<x2<<" "<<x1;
    }

    return 0;

}

