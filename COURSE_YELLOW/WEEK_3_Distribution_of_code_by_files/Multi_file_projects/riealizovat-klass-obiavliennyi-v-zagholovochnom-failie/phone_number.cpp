#include <phone_number.h>
#include <stdexcept>
#include <vector>

using namespace std;
/* Принимает строку в формате +XXX-YYY-ZZZZZZ
   Часть от '+' до первого '-' - это код страны.
   Часть между первым и вторым символами '-' - код города
   Всё, что идёт после второго символа '-' - местный номер.
   Код страны, код города и местный номер не должны быть пустыми.
   Если строка не соответствует этому формату, нужно выбросить исключение invalid_argument. Проверять, что номер содержит только цифры, не нужно.

   Примеры:
   * +7-495-111-22-33
   * +7-495-1112233
   * +323-22-460002
   * +1-2-coursera-cpp
   * 1-2-333 - некорректный номер - не начинается на '+'
   * +7-1233 - некорректный номер - есть только код страны и города
*/

PhoneNumber::PhoneNumber( const string  &international_number){
    vector <size_t> x;

    for(size_t i = 0; i<international_number.size() ;i++){

        if(international_number[i] =='+'&& i == 0){
            x.push_back(i);
            //cout<<i<<endl;
        }else if(international_number[i] =='-'){
            x.push_back(i);
            //cout<<i<<endl;

        }
    }

    if((x.size() <3) ||(x[0] != 0)||(x[1] == 1)||(x[2] == 2)){
        throw invalid_argument("1");
    }

    else{

        country_code_.assign(international_number.begin()+1,international_number.begin()+x[1]);
        city_code_.assign(international_number.begin()+x[1]+1,international_number.begin()+x[2]);
        local_number_.assign(international_number.begin()+x[2]+1,international_number.end());

    }
}


string PhoneNumber:: GetCountryCode() const {
    return country_code_;

}

string PhoneNumber:: GetCityCode() const {
    return city_code_;

}

string PhoneNumber:: GetLocalNumber() const {
    return local_number_;

}

string PhoneNumber:: GetInternationalNumber() const {
    return "+"+country_code_+"-"+city_code_+"-"+ local_number_;

}
