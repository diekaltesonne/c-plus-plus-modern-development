#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
/*

 *Замечания: *Историю списков дел хранить не требуется, работа ведется только с текущим списком дел текущего месяца.
 *Более того, при создании списка дел на следующий месяц, он «перетирает» предыдущий список.
 *Обратите внимание, что количество команд NEXT в общей последовательности команд при работе со списком дел может превышать 11.
 *Начальным текущим месяцем считается январь.
 *Количества дней в месяцах соответствуют Григорианскому календарю с той лишь разницей, что в феврале всегда 28 дней.
 *
 *
*/
/*
*Формат вывода:
*Для каждой операции типа DUMP в отдельной строке выведите количество дел в соответствующий день,
*а затем их названия, разделяя их пробелом. Порядок вывода дел в рамках каждой операции значения не имеет.
*
*
*
* ADD i s
Назначить дело с названием s на день i текущего месяца.
DUMP i
Вывести все дела, запланированные на день i текущего месяца.
*/
/*NEXT
*Перейти к списку дел на новый месяц.
*При выполнении данной команды вместо текущего (старого) списка дел на текущий месяц
*создаётся и становится активным (новый) список дел на следующий месяц:
*все дела со старого списка дел копируются в новый список.
*После выполнения данной команды новый список дел и следующий месяц становятся текущими,
*а работа со старым списком дел прекращается.
*При переходе к новому месяцу необходимо обратить внимание на разное количество дней в месяцах:
*если следующий месяц имеет меньше дней, чем текущий, меньше дней, дела со всех
*«лишних» дней необходимо переместить на последний день следующего месяца.
*/

void Print(const vector<string>& v){

    for (auto elem : v)	cout <<elem<<" ";

}

void next(vector<vector<string>>& v, int& m) {
    vector<int> days_in_months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 12) {
        m = 0;
    }
    if (m == 0) {
    } else {
                    if (days_in_months[m] == 28) {
                        v[27].insert(end(v[27]), begin(v[28]), end(v[28]));
                        v[28].clear();
                        v[27].insert(end(v[27]), begin(v[29]), end(v[29]));
                        v[29].clear();
                        v[27].insert(end(v[27]), begin(v[30]), end(v[30]));
                        v[30].clear();
                    } else if (days_in_months[m] == 30) {
                        v[29].insert(end(v[29]), begin(v[30]), end(v[30]));
                        v[30].clear();
                    }
                }

}

int main() {
    int Q, month = 1;
    string operation, name;
    vector<vector<string>> plans(31);
    int number = 0;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> operation;
        if (operation == "NEXT") {
            next(plans, month);
            month++;
        } else if (operation == "DUMP") {
            cin >> number;

            if(plans[number - 1].size() == 0){
                cout << plans[number - 1].size();
            }
            else{
                cout << plans[number - 1].size()<<" ";
                Print(plans[number - 1]);
            }
            cout << endl;
        } else if (operation == "ADD") {
            cin >> number >> name;
            plans[number - 1].push_back(name);

        }
    }
    return 0;
}
