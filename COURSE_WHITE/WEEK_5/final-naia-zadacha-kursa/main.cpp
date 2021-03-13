#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <stdexcept>

using namespace std;

class Date{
public:
  explicit Date(const int& X,const int& Y,const int& Z){
    year= X;
    month = Y;
    day = Z;
  }
  int GetYear() const{
      return year;
  }

  int GetMonth() const{
      return month;
  }

  int GetDay() const{
      return day;
  }

private:
  int year = 0;
  int month = 0;
  int day = 0;

};

bool operator<(const Date& lhs, const Date& rhs){
    if(lhs.GetYear()==rhs.GetYear()){
        if(lhs.GetMonth()==rhs.GetMonth()){
            return lhs.GetDay()<rhs.GetDay();
        }
        else return lhs.GetMonth()<rhs.GetMonth();
    }
    else return lhs.GetYear()<rhs.GetYear();
}

 ostream& operator<<(ostream& stream,const Date& date){
    string a = to_string(date.GetYear());
    string b = to_string(date.GetMonth());
    string c = to_string(date.GetDay());
    while(a.size()<4){
        a= "0"+a;
    }
    while(b.size()<2){
        b= "0"+b;
    }
    while(c.size()<2){
        c ="0"+ c;
    }
    a = a +"-"+b+"-"+c;
    stream << a;
    return stream;
}

class Database {
public:

void AddEvent(const Date& date, const string& event){
      if (db.count(date)==0){db[date].insert(event);}
      else{db.at(date).insert(event);}
}

bool DeleteEvent(const Date& date, const string& event){

      if (db.count(date) > 0 && db.at(date).count(event)!=0){
          db.at(date).erase(event);
          cout<<"Deleted successfully"<<endl;
          return true;
      }
      else{
          cout<<"Event not found"<<endl;
          return false;
      }

}

int  DeleteDate(const Date& date){
    int N=0;
    if (db.count(date) > 0){
        N = db.at(date).size();
        db.erase(date);
    }
        cout<<"Deleted "+to_string(N)+" events" << endl;
        return N;
}
void Find(const Date& date) const{
    if(db.count(date)>0){
        for(auto& i: db.at(date)){
            cout << i << endl;
        }
    }


}
void Print() const{
    for(auto& i: db){
        for(auto& j:i.second){
            cout<< i.first << " " << j<<endl ;
        }
    }
}


private:

map<Date,set<string>> db;

};
bool qval(const int& m,const int& d){
    if(m>=1&&m<=12){
        if(d>=1&&d<=31){
            return true;
        }
        else {
            throw logic_error("Day value is invalid: "+to_string(d));
        }
    }else{

        throw logic_error("Month value is invalid: "+to_string(m));
    }
    return false;

}
void formate_out(istringstream &input){
    string command;
    string Datum;
    input.clear();
    input.seekg(0, ios::beg);
    input>> command;
    input>> Datum;
    throw logic_error("Wrong date format: "+Datum);
}

bool check_format(istringstream &input,int& y,int& m,int& d){
    char def1;
    char def2;
    if(input >> y >>def1 >> m >> def2>> d){
        if((input.peek()==' '||input.peek()==EOF)&&(def1 =='-'&&def2 =='-')){
            return true;
        }else{
            formate_out(input);
        }
    }
    else{
        formate_out(input);
    }
    return false;
}

bool Reciver(Database& db,const string& command){
    istringstream input(command);
    string operation;
    input>>operation;
    int y = 0;
    int m = 0;
    int d = 0;
    string Event;
    if (operation == "Add") {
        if(check_format(input,y,m,d)){
            if(qval(m,d)){
                input >> Event;
                Date date(y,m,d);
                db.AddEvent(date,Event);
            }
        }

    } else if(operation == "Del") {
        if(check_format(input,y,m,d)){
                if(qval(m,d)){
                    input >> Event;
                    Date date(y,m,d);
                    if (Event.size() == 0) db.DeleteDate(date);
                    else db.DeleteEvent(date,Event);
                }
         }
    } else if (operation == "Find") {
        if(check_format(input,y,m,d)){
            if(qval(m,d)){
                Date date(y,m,d);
                db.Find(date);
            }
        }

    } else if (operation == "Print") {
         db.Print();
    }
    else if (!command.size())
    {
                return (true);
     }else {
        throw logic_error("Unknown command: "+operation);
    }
    return(true);
}

int main(){
  Database db;
  string command;
  try{
      while (getline(cin,command)) {
          if(!Reciver(db,command))break;

      }
  }catch(logic_error& ex){
      cout << ex.what() << endl;
  }
  return 0;
}

