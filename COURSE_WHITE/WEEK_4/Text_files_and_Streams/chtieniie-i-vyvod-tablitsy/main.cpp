#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;
/*
 * В первой строке файла input.txt записаны два числа N и M.
 * Далее в файле находится таблица из N строк и M столбцов, представленная в формате CSV (comma-separated values).
 * Такой формат часто используется для текстового представления таблиц с данными: в файле несколько строк,
 * значения из разных ячеек внутри строки отделены друг от друга запятыми. Ваша задача — вывести данные на экран в виде таблицы. Формат таблицы:
 *
 *1) размер ячейки равен 10,
 *2) соседние ячейки отделены друг от друга пробелом,
 *
 *3) последняя ячейка в строке НЕ оканчивается пробелом,
 *
 *4) последняя строка НЕ оканчивается символом перевода строки.
 *Гарантируется, что в таблице будет ровно N строк и M столбцов, значение каждой из ячеек — целое число.
*/
void PrintTable(const int& N,const int& M, ifstream& input){

    for (int i=0;i<N;++i){
        int value;
        for (int j=0;j<M;++j){
            input>> value;
            cout << setw(10)<<value;
            if (j<M-1) {
                input.ignore(1);
                cout <<" ";
            }
        }
        if (i<N-1) cout << "\n";
    }
}

int main() {
    //ifstream input("input.txt");
    ifstream input("/home/ivan/C_COURSE/C-_COURSE/COURSE_WHITE/WEEK_4/Text_files_and_Streams/chtieniie-i-vyvod-tablitsy/input.txt");
    int N, M;
    input >> N >> M;
    if (input)
    PrintTable(N,M,input);
    else cerr<<"Error!!!";
    return 0;
}

