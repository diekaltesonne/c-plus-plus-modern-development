#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

/*Люди стоят в очереди, но никогда не уходят из её начала,
 * зато могут приходить в конец и уходить оттуда.
 * Более того, иногда некоторые люди могут прекращать и начинать беспокоиться из-за того,
 * что очередь не продвигается.
 * Реализуйте обработку следующих операций над очередью:
 *
 * WORRY i: пометить i-го человека с начала очереди (в нумерации с 0) как беспокоящегося;
 * QUIET i: пометить i-го человека как успокоившегося;
 * COME k: добавить k спокойных человек в конец очереди;
 * COME -k: убрать k человек из конца очереди;
 * WORRY_COUNT: узнать количество беспокоящихся людей в очереди.
 * Изначально очередь пуста.
 *
 * Формат ввода
 * Количество операций Q, затем описания операций.
 *
 * Для каждой операции WORRY i и QUIET i гарантируется, что человек с номером i существует в очереди на момент операции.
 *
 * Для каждой операции COME -k гарантируется, что k не больше текущего размера очереди.
 *
 * Формат вывода
 * Для каждой операции WORRY_COUNT выведите одно целое число — количество беспокоящихся людей в очереди.
 *
*/

void operation(const vector<string> &command, const vector<int> &num);

int main()
{

    int Q =0 ;
    string command;
    int num =0;
    vector<string> command1;
    vector<int> num1;
    cin >>Q;

    for(int i =0 ;i < Q; i++){
        cin>>command;
        if(command == "WORRY_COUNT"){
            //cout<<"esp";
            command1.push_back(command);
            num1.push_back(0);
            continue;
        }
        cin>>num;
        command1.push_back(command);
        num1.push_back(num);
    }

    operation(command1,num1);

    return 0;
}


void operation(const vector<string> &command, const vector<int> &num){

    vector <string> queue;
    int k = 0;

    for (int i = 0; i < command.size(); i++ ){

        //COME k: добавить k спокойных человек в конец очереди;
        //COME -k: убрать k человек из конца очереди;

        if(command[i] == "COME"){
            //cout<<num[i]<<endl;
            if(num[i] > 0){
                for(int  j= 0; j< num[i];j++){
                    queue.push_back("conf");
                }
            }

            if(num[i] < 0){
                for(int j = 0; j< abs(num[i]);j++){
                    queue.pop_back();
                }
//                for(string i:queue){
//                    cout<<i<<endl;
//                }
            }

//            for(string i:queue){
//                cout<<i;
//            }

        }

        //WORRY i: пометить i-го человека с начала очереди (в нумерации с 0) как беспокоящегося;
        if(command[i] == "WORRY"){
           queue[num[i]] = "unconf";
//           for(string i:queue){
//               cout<<i;
//           }

        }

        // QUIET i: пометить i-го человека как успокоившегося;
        if(command[i] == "QUIET"){
           queue[num[i]] = "conf";

        }
        //WORRY_COUNT: узнать количество беспокоящихся людей в очереди;
        if(command[i] == "WORRY_COUNT"){
           for(string i:queue){
               if(i == "unconf"){
                   k++;
               }
           }
           cout<<(k)<<endl;
           k = 0;
        }

    }

}
