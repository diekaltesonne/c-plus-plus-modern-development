#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  std::vector<ofstream> streams;
  for (int i = 0; i<5;++i){
    ofstream stream(to_string(i)+".txt")
    stream <<"File#"<<i<<"\n";
    streams.push_back(move(stream));//только так  
  }
  return 0;
}
