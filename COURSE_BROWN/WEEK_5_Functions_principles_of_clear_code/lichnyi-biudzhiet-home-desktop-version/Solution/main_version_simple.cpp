#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
//#include <test_runner.h>
using namespace std;

class Date{
private:
    time_t day_;
    time_t month_;
    time_t year_;
public:
    friend std::istream & operator>>(std::istream & input, Date & date);
    Date(){
    }
    Date(time_t day,time_t month,time_t year):day_(move(day)),month_(move(month)),
        year_(move(year)){
    }

    time_t AsTimestamp() const{
      std::tm t;
      t.tm_sec   = 0;
      t.tm_min   = 0;
      t.tm_hour  = 0;
      t.tm_mday  = day_;
      t.tm_mon   = month_ - 1;
      t.tm_year  = year_ - 1900;
      t.tm_isdst = 0;
      return mktime(&t);

    }

    void date_info(){
        cout<<this->year_<<" "<<this->month_<<" "<<this->day_<<endl;
    }

};
std::istream & operator>>(std::istream & input, Date& date){
    input >> date.year_;
    input.ignore(1);
    input >> date.month_;
    input.ignore(1);
    input >> date.day_;
    return input;
}
class Personal_Budget{
public:
    Personal_Budget(){
        budget_.assign(40000,0.0);
        budget_tax.assign(40000,0.0);
        expenses_.assign(40000,0.0);
    }
    int earn_from_to_value(Date& first,Date& second,double value);
    double compute_income(Date& first,Date& second)const;
    int pay_tax_NDS(Date& first,Date& second);
    int pay_tax(Date& first,Date& second,int value);
    int spend(Date& first,Date& second,double value);
private:
    const Date mill={01,01,2000};
    size_t compute_days_diff(const Date& first,const Date& second)const;
    size_t compute_day_index(const Date& date)const;
    const double PERSONAL_INCOME_TAX = 13;
    vector<double> budget_;
    vector<double> expenses_;
    vector<double>budget_tax;
};
size_t Personal_Budget::compute_day_index(const Date& date )const{
    return compute_days_diff(mill,date);
    //надо проверить куда кладется в вектор;TECТЫ
}
size_t Personal_Budget::compute_days_diff(const Date& first,const Date& second)const{
    return (second.AsTimestamp() - first.AsTimestamp())/86400;
}



double Personal_Budget::compute_income(Date& first,Date& second)const{
    double income = 0;
    size_t range = compute_days_diff(first,second)+1;
    auto i =compute_day_index(first);
    size_t range_= compute_day_index(first)+range;
    do{
        //cout<<expenses_[i]<<endl;
        income += budget_[i]-expenses_[i];
        i++;
    }while (i<range_);
    return income;
}

int Personal_Budget::pay_tax_NDS(Date& first,Date& second){
    size_t range = compute_days_diff(first,second)+1;
    size_t range_= compute_day_index(first)+range;
    auto i =compute_day_index(first);
    do{
        budget_[i] = 0.87*budget_[i];
        i++;
    }while (i<range_);
    return 0;

}
int Personal_Budget::pay_tax(Date& first,Date& second,int value){
    size_t range = compute_days_diff(first,second)+1;
    size_t range_= compute_day_index(first)+range;
    auto i =compute_day_index(first);
    double val = 1-(0.01*value);
    do{
        budget_[i] = val*budget_[i];
        i++;
    }while (i<range_);
    return 0;
}
int Personal_Budget:: spend(Date& first,Date& second,double value){
    size_t range = compute_days_diff(first,second)+1;
    size_t range_= compute_day_index(first)+range;
    double val = (range == 0)?value:value/(range);
    auto i = compute_day_index(first);
    do{

        expenses_[i] = expenses_[i]+val;
        //cout<<expenses_[i]<<endl;
        i++;
    }while (i<range_);
    return 0;
}

int Personal_Budget::earn_from_to_value(Date& first,Date& second,double value){
    size_t range = compute_days_diff(first,second)+1;
    size_t range_= compute_day_index(first)+range;
    double val = (range == 0)?value:value/(range);
    auto i =compute_day_index(first);
    do{
        budget_[i] = budget_[i]+val;
        i++;
    }while (i<range_);
    return 0;
}
void process_one_command(Personal_Budget& budget,istream & input){
    string command;
    Date first;
    Date second;
    input>>command;
    input.ignore(1);
    input>>first;
    input.ignore(1);
    input>>second;
    if(command ==  "Earn" ){
        double value;
        input >>value;
        budget.earn_from_to_value(first,second,value);
    }else if(command ==  "ComputeIncome"){
        cout.precision(25);
        cout<<budget.compute_income(first,second)<<"\n";
    }else if(command ==  "PayTax"){
        int value;
        input >>value;
        budget.pay_tax(first,second,value);
    }else if(command ==  "Spend"){
        double value;
        input >>value;
        budget.spend(first,second,value);
    }
}

int main(){
    Personal_Budget budget;
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; ++i)
    {
        process_one_command(budget, cin);
    }
    return 0;
}
/*
8
Earn 2000-01-02 2000-01-06 20
ComputeIncome 2000-01-01 2001-01-01
PayTax 2000-01-02 2000-01-03
ComputeIncome 2000-01-01 2001-01-01
Earn 2000-01-03 2000-01-03 10
ComputeIncome 2000-01-01 2001-01-01
PayTax 2000-01-03 2000-01-03
ComputeIncome 2000-01-01 2001-01-01
*/

/*
8
Earn 2000-01-02 2000-01-02 20
ComputeIncome 2000-01-02 2000-01-02
PayTax 2000-01-02 2000-01-02
ComputeIncome 2000-01-02 2000-01-02
Earn 2000-01-02 2000-01-02 10
ComputeIncome 2000-01-02 2000-01-02
PayTax 2000-01-02 2000-01-02
ComputeIncome 2000-01-02 2000-01-02
*/
/*
8
Earn 2000-01-02 2000-01-06 20
ComputeIncome 2000-01-01 2001-01-01
PayTax 2000-01-02 2000-01-03 13
ComputeIncome 2000-01-01 2001-01-01
Spend 2000-12-30 2001-01-02 14
ComputeIncome 2000-01-01 2001-01-01
PayTax 2000-12-30 2000-12-30 13
ComputeIncome 2000-01-01 2001-01-01
*/
