#include <iostream>
using namespace std;
class Animal {

public:
    Animal ( const string & t = " animal ")
    : Name(t) { // хотим проинициализировать type значением t
    }
    // ваш код
    const string Name;
};

class Dog: public Animal {
public:

    Dog(const string &type):Animal (type){

    }

    void Bark(){

        cout << Name << " barks: woof!" << endl;
    }
};

/*int main(){
 * //Dog f("ANUS");
 * f.Bark();
 * return 0;
}
*/
