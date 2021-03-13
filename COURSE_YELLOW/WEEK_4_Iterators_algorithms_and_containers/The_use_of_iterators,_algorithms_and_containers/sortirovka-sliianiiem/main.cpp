#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;
template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end);

//template <typename RandomIt>
//void MergeSort2(RandomIt range_begin, RandomIt range_end);

int main(){
//    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
//    MergeSort(begin(v), end(v));
//    for (int x : v) {
//      cout << x << " ";
//    }
//    cout << endl;
//    return 0;

    vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v) {
        cout << x << " ";
    }
      cout << endl;
      return 0;
}


//template <typename RandomIt>
//void MergeSort2(RandomIt range_begin, RandomIt range_end){
//    if (range_end - range_begin < 2) {return;
//    }else{
//        vector<typename RandomIt::value_type> elements(range_begin, range_end);
//        MergeSort(elements.begin(),elements.begin()+elements.size()/2);
//        MergeSort(elements.begin()+elements.size()/2,elements.end());
//        merge(elements.begin(), elements.begin()+elements.size()/2,elements.begin()+elements.size()/2,elements.end(), range_begin);
//    }
//}


template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end){

    if (distance(range_begin,range_end) < 2){
        return;
    }else{

        vector<typename RandomIt::value_type> elements(range_begin, range_end);
        MergeSort(elements.begin(),elements.begin()+elements.size()/3);
        MergeSort(elements.begin()+elements.size()/3,elements.begin()+((elements.size()/3)*2));
        MergeSort(elements.begin()+((elements.size()/3)*2),elements.end());

        vector<typename RandomIt::value_type> rand_vec;

        merge(elements.begin(),elements.begin()+elements.size()/3,elements.begin()+elements.size()/3,elements.begin()+((elements.size()/3)*2),
        back_inserter(rand_vec));
        merge(rand_vec.begin(),rand_vec.end(),elements.begin()+((elements.size()/3)*2),elements.end(),range_begin);


    }
    //cout<<x;
    //vector<typename RandomIt::value_type> elements(range_begin, range_end);

//    MergeSort(range_begin,range_begin+x/3);
//    MergeSort(range_begin+x/3,range_begin+(x/3*2));
//    MergeSort(range_begin+(x/3*2),range_end);
//    vector<typename RandomIt::value_type> rand_vec;
//    merge(range_begin,range_begin+x/3,range_begin+x/3,range_begin+(x/3*2),
//    back_inserter(rand_vec));
//    merge(range_begin+(x/3*2),range_end,rand_vec.begin(),rand_vec.end(),range_begin);

}


