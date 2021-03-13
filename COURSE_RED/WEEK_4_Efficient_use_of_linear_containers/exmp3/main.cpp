#include <iostream>
#include <algorithm>
#include <array>

#include <random>
#include <vector>
using namespace std;
// Определяем новый перечисляемый тип Animals

enum class MoscowAirport {
  VKO,
  SVO,
  DME,
  ZIA,
  Last_
};

template <typename TIterator>
void XB(TIterator begin, TIterator end, array< pair <MoscowAirport, size_t>, uint32_t>& A){

    while(begin!=end){
        A[*begin] = {*begin,0};
        begin++;
    }
}

int main()
{
    const vector<MoscowAirport> airports = {
        MoscowAirport::SVO,
        MoscowAirport::VKO,
        MoscowAirport::ZIA,
        MoscowAirport::SVO,
    };
    array<pair<MoscowAirport, size_t>,static_cast<uint32_t>(MoscowAirport::Last_)> A;

    XB(begin(airports), end(airports),A);

    return 0;
}
