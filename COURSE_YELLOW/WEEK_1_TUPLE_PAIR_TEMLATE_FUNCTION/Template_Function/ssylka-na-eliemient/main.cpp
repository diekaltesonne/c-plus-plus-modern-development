#include <iostream>
#include <map>


template <typename KEY,typename VALUE>
VALUE& GetRefStrict(std:: map <KEY , VALUE> &input_map,KEY key){
    try {
           return  input_map.at(key);
        }
        catch (const std::out_of_range& oor) {
            throw std::runtime_error("no such key in dictionary");
        }

}

int main() {
    std::map<int, std::string> m = {{0, "value"}};
    std::string& item = GetRefStrict(m, 0);
    item = "newvalue";
    std::cout << m[0] << std::endl; // выведет newvalue

    return 0;
}
