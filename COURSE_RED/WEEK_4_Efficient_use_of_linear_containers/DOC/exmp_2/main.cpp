#include <iostream>
#include <array>
#include <string_view>

using namespace std;

int main()
{
    array<char, 5> a = {'q','w','e','r','t'};
    string_view b = string_view(&a[0]);
    string_view c = string_view(a.begin());
    cout << "Hello World!" << endl;
    return 0;
}

