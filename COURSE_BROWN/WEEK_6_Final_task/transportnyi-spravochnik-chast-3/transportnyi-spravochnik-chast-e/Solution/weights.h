#pragma once
#include <string>
#include <vector>
using namespace std;

enum type_o_w{busing,stoping};

//struct bus{
//    string type = "Bus";
//    string name;
//    double time;
//    int span_count =0;
//    bus(string name,double time,int span_count): name(move(name)), time(move(time)),span_count(move(span_count)){
//    }
//};

//struct stop{
//    string type = "Wait";
//    string name;
//    double time =0;
//    stop(string name,double time): name(move(name)), time(move(time)){
//    }
//};




struct Weight{
    double wait_time;
    type_o_w type;
    string name;
    double time ;
    size_t index;

    Weight(){
    }
    Weight(type_o_w type,string name,double time,double wait_time,size_t index):type(move(type)),name(move(name)),time(move(time)),
    wait_time(move(wait_time)),index(move(index)){
    }
    Weight(int i){
       time =0;
    }
};

bool operator < (Weight c1, Weight c2)
{
    return c1.time <c2.time;
}
bool operator < (Weight c1, int i)
{
    return c1.time < i;
}
bool operator > (Weight c1, const  Weight c2 )
{
    return c1.time > c2.time;
}

bool operator >= (Weight c1, int i)
{
    return c1.time >= i;
}

const Weight operator+(const Weight& first,const Weight& other) {

    Weight result;

    if(first.type==stoping && other.type== busing){
        //result.time = first.time + other.time;
        if(first.index == other.index){
            result.time = other.time;
            //result.time-=first.wait_time;
        }else{
            result.time = first.time + other.time;
        }
        result.name =other.name;
        result.type = busing;
    }

    if(first.type==busing && other.type== stoping){
        if(first.index == other.index){
            result.time =first.time;
        }else{
            result.time =first.time+other.time;
        }
        result.name = other.name;
        result.type = stoping;
    }
    return result;

}


