double Personal_Budget::compute_income(Date& first,Date& second)const{
    //first.date_info();
    //second.date_info();
    //size_t range = compute_days_diff(first,second);
    //cout<<range<<"range"<<endl;
    //size_t first_day_of_range = compute_day_index(first);
    //cout<<first_day_of_range<<"compute_day_index"<<endl;
    vector<double>::const_iterator it = budget_.begin()+compute_day_index(first);
    double income = accumulate(it,it+compute_days_diff(first,second),0.0);
    return income;
}
double Personal_Budget::earn_from_to_value(Date& first,Date& second,double value){
    //cout<<range<<" range"<<endl;
    //size_t first_day_of_range = compute_day_index(first);
    //cout<<first_day_of_range<<" compute_day_index"<<endl;
    size_t range = compute_days_diff(first,second);
    vector<double>::iterator it = budget_.begin()+ compute_day_index(first);
    double budget_per_day = value/range;
    fill(it,it+range,budget_per_day);
    return value;
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSelector);
}
во
/*
6
Earn 2000-01-02 2000-01-06 20
ComputeIncome 2000-01-01 2001-01-01
PayTax 2000-01-02 2000-01-03
ComputeIncome 2000-01-01 2001-01-01
Earn 2000-01-03 2000-01-03 10
ComputeIncome 2000-01-01 2001-01-01
*/
/*
4
Earn 2000-01-02 2000-01-06 20
ComputeIncome 2000-01-02 2000-01-06
PayTax 2000-01-02 2000-01-06
ComputeIncome 2000-01-02 2000-01-06
*/
/*
4
Earn 2000-01-02 2000-01-06 20
ComputeIncome 2000-01-01 2001-01-01
PayTax 2000-01-02 2000-01-03
ComputeIncome 2000-01-01 2001-01-01
*/

//vector<double>::iterator it = budget_.begin()+ compute_day_index(first);
//    if(range !=0){
//        val = value/range;
//        for(auto i =compute_day_index(first) ;i<compute_day_index(first)+range;i++){
//            budget_[i] = budget_[i]+val;
//        }
//    }else{
//        val = value;
//        budget_[compute_day_index(first)] =budget_[compute_day_index(first)]+val;
//    }
    //cout<<range<<" range"<<endl;
//    if(range !=0){
//        double val = (0.87*income)/range;
//        for(auto i =compute_day_index(first) ;i<compute_day_index(first)+range;i++){
//            budget_[i] = val;
//        }
//    }else{
//        budget_[compute_day_index(first)] = budget_[compute_day_index(first)] * 0.87;
//    }
