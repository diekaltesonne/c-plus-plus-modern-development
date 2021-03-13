#include <iostream>
using namespace std;

/*Вам дана функция string AskTimeServer(), про которую известно следующее:
 *в процессе своей работы она обращается по сети к удалённому серверу, запрашивая текущее время;
 *если обращение к серверу прошло успешно, функция возвращает текущее время в виде строки;
 *если в процессе обращения к серверу возникла сетевая проблема, функция выбрасывает исключение system_error;
 *функция может выбрасывать другие исключения, чтобы сообщить о других проблемах.
*/
/* Для тестирования повставляйте сюда код, реализующий различное поведение этой функии:
   * нормальный возврат строкового значения
   * выброс исключения system_error
   * выброс другого исключения с сообщением.
*/

string AskTimeServer() {

    throw system_error() ;

}


class TimeServer {
public:

    string GetCurrentTime() {
        try{
           last_fetched_time = AskTimeServer();
           return last_fetched_time;
        }catch(system_error &e){
           //cout << e.what();
           return last_fetched_time;
        }

        /* Реализуйте этот метод:
            * если AskTimeServer() вернула значение, запишите его в last_fetched_time и верните
            * если AskTimeServer() бросила исключение system_error, верните текущее значение
            поля last_fetched_time
            * если AskTimeServer() бросила другое исключение, пробросьте его дальше.
        */
    }

private:
    string last_fetched_time = "00:00:00";
};

int main(){
    // Меняя реализацию функции AskTimeServer, убедитесь, что это код работает корректно
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    } catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}

