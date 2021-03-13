#include <exception>
#include <system_error>

using namespace std;

string AskTimeServer3() {

    throw system_error() ;

}

class TimeServer {
public:
  string GetCurrentTime() {
    // поместим вызов функции AskTimeServer в try-catch блок
    try {
      last_fetched_time = AskTimeServer3();
    } catch (const system_error&) {  // ловим только system_error
    }
    // возвращаем значение поля — либо обновлённое, либо нет
    return last_fetched_time;
  }

private:
  string last_fetched_time = "00:00:00";
};

