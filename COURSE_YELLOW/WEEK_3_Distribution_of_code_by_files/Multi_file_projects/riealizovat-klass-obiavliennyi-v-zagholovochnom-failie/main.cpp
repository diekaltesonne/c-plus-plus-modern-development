#include <iostream>
#include <phone_number.h>

using namespace std;

int main()
{
    PhoneNumber ph("+7-968-639-77-93");
    cout << ph.GetCountryCode() <<endl;
    cout << ph.GetCityCode()    <<endl;
    cout << ph.GetLocalNumber() <<endl;
    return 0;
}

