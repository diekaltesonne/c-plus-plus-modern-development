#include <iostream>
using namespace std;

int Factorial_proff(int x) {
  if (x <= 1) {
    return 1;
  } else {
    return x * Factorial(x - 1);  // вычисляем факториал от x-1 и умножаем на x
  }
}

int Factorial(int x){
    int a = x;

    if(a<=0){
        return 1;
    }

    else{

        for (int i =1; i<a;i++){
            x = i*x;
        }
        return x;
    }

}

int main()
{
    return 0;
}
