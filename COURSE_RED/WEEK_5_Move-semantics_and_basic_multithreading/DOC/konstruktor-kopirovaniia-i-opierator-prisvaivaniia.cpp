#include <iostream>
#include <vector>

using namespace std;

class Logger{
public:
  Logger(){cout<<"Default ctor\n";}
  Logger(const Logger&){cout<<"Copy ctor\n";}
  void operator= (const Logger&){cout<<"Copy assignment\n";}
}
Logger MakeLogger(){
  // copy elision;
  return Logger(); // temporary -> returned temporary
}

int main(){
  Logger source;
  Logger target = source;
  vector<Logger> loggers;
  loggers.push_back(target);
  source = target;
  // copy elision;
  Logger logger = MakeLogger();   // initialize with temporary
  return 0;

}

// если самостоятельно управляет памятью;
template <typename T>
SimpleVector<T>:: SimpleVector(const SimpleVector<T> & other)
  : data(new T[other.capacity]),
    size(other.size),
    capacity(other.capacity)
{
  copy(other.begin(),other.end(), begin());
}
