#include <iostream>
#include <vector>
#include <algorithm>
#include "profile.h"


using namespace std;

template<typename val>
class Deque{
public:

    explicit Deque(){
        v_front ={};
        v_back ={};
    }


    void PushFront(const val& _val){
            v_front.push_back(_val);
            //reverse(v_front.begin(),v_front.end());
    }
    void PushBack(const val& _val){
            v_back.push_back(_val);
    }

    val& operator[] (const size_t& index) {
        if (index < v_front.size()&&(!v_front.empty())) {
            return v_front.at(v_front.size() - index-1);
        }
        else return v_back.at(index - v_front.size());
    }
    val& operator[] (const size_t& index) const {
        if (index < v_front.size()&&(!v_front.empty())) {
            return v_front.at(v_front.size() - index-1);
        }
        else return v_back.at(index - v_front.size());
    }

    val& At(size_t index) {
            if (index < v_front.size() && (!v_front.empty())) {
                return v_front.at(v_front.size() - index-1);
            }
            else return v_back.at(index - v_front.size());
        }
    val& At(size_t index)const {
            if (index < v_front.size() && (!v_front.empty())) {
                return v_front.at(v_front.size() - index-1);
            }
            else return v_back.at(index - v_front.size());
        }
    val& Front() {
            if (!v_front.empty()) {
                return v_front.back();
            }
            else return *(v_back.begin());
        }

    const val& Front() const {

            if (!v_front.empty()) {
                return v_front.back();
            }
            else return *(v_back.begin());
        }

    val& Back() {
            if (!v_back.empty()) {
                return v_back.back();
            }
            else return *(v_front.begin());
        }

    const val& Back() const {

        if (!v_back.empty()) {
                return v_back.back();
        }
            else return *(v_front.begin());
    }

    size_t Size()const{return v_front.size() +  v_back.size();}
    bool Empty() const {return v_front.empty() && v_back.empty();}


    //    val& GetElem(size_t index){
    //        if (index < _vector_pf.size())
    //                    return _vector_pf[_vector_pf.size()- index - 1];

    //                return _vector_pb[index-_vector_pf.size()];
    //    }


private:
    vector<val> v_front;
    vector<val> v_back;

};







int main(){
    LOG_DURATION("MAIN");
    Deque<int> a;

    cout<<a.Empty()<< endl;
    a.PushFront(1);
    a.PushFront(2);
    a.PushFront(3);
    a.PushFront(4);
    a.PushFront(5);
    a.PushFront(6);
    a.PushFront(7);
    a.PushBack(3);
    a.PushBack(3);
    a.PushBack(3);
    a.PushBack(3);

    cout << a[0] << endl;
    cout << a.Front() << endl;
    cout << a.Back() << endl;
    cout << a.Size() << endl;

////    for(auto l:a){
////        cout<<l<<"\n";
////    }

    return 0;
}
