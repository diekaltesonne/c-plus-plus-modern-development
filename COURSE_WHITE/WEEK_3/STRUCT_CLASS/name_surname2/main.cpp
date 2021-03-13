#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

/*
 * Дополните класс из предыдущей задачи «Имена и фамилии — 1» методом GetFullNameWithHistory:
 * В отличие от метода GetFullName, метод GetFullNameWithHistory должен вернуть не только последние имя и фамилию
 *  к концу данного года, но ещё и все предыдущие имена и фамилии в обратном хронологическом порядке.
 * Если текущие факты говорят о том, что человек два раза
 * подряд изменил фамилию или имя на одно и то же, второе изменение при формировании истории нужно игнорировать.
 * Для лучшего понимания формата см. примеры.
 * */


class Person{
public:
  void ChangeFirstName(int year, const string& first_name) {
         fnames_of_person[year] = first_name;

      // добавить факт изменения имени на first_name в год year
  }
  void ChangeLastName(int year, const string& last_name) {
         lnames_of_person[year] =last_name;

  }
  string GetFullName(int year) {
      int a = sorted(fnames_of_person,year);
      int b = sorted(lnames_of_person,year);

      if(a==0&&b==0){
          return "Incognito";
      }
      if(a==0&&b!=0){
        return  lnames_of_person[b] + " with unknown first name";
      }
      else if(a!=0&&b==0){
        return  fnames_of_person[a] +" with unknown last name";
      }
      else{
        return  fnames_of_person[a]+" "+lnames_of_person[b];
      }
      return "Наебнулось";

  }

  string GetFullNameWithHistory(int year) {
      // получить все имена и фамилии по состоянию на конец года year
      map<int,string> fnames_of_person1 = fnames_of_person;
      map<int,string> lnames_of_person1 = lnames_of_person;
      check(lnames_of_person1);
      check(fnames_of_person1);
      int a = sorted(fnames_of_person1,year);
      int b = sorted(lnames_of_person1,year);
      string l;
      string k;
      if(a==0&&b==0){
          return "Incognito";
      }
      if(a==0&&b!=0){
            l = req(lnames_of_person1,b);
            if(l.size()!=0){return  lnames_of_person1[b]+" "+l+" "+"with unknown first name";}
            return  lnames_of_person1[b]+" "+"with unknown first name";

      }
      else if(a!=0&&b==0){
            l = req(fnames_of_person1,a);
            if(l.size()!=0){return  fnames_of_person1[a]+" "+l+" "+"with unknown last name";}
            return  fnames_of_person1[a]+" "+"with unknown last name";
      }
      else{

            l = req(fnames_of_person1,a);
            k = req(lnames_of_person1,b);

            if(l.size()!=0 &&k.size()!=0){return fnames_of_person1[a]+" "+l+" "+lnames_of_person1[b]+" "+k;}
            if(l.size()==0 &&k.size()==0){return fnames_of_person1[a]+" "+lnames_of_person1[b];}
            if(l.size()!=0 &&k.size()==0){return fnames_of_person1[a]+" "+l+" "+lnames_of_person1[b];}
            if(l.size()==0 &&k.size()!=0){return fnames_of_person1[a]+" "+lnames_of_person1[b]+" "+k;}
      }
      return "Наебнулось";

   }

private:

    int sorted(map<int,string> &sort,int&year){
        int k = 0;
        for(auto i:sort){
            if(i.first <=year){
                if(i.first >= k){
                    k = i.first;
                }
            }
        }
        return k;
    }

    string formate(string &l,int &q){
        string ans;
        if(q != 0){
            l.pop_back();
            l.pop_back();
        }
        if(l.size()!=0){
            l = "("+l+")";
        }
        ans =l;
        return ans;

    }
    string sequring(map<int,string> &data){
        string ans;
        map<int,string>::reverse_iterator rit;
        for (rit=data.rbegin(); rit!=data.rend(); ++rit){
            ans.append(rit->second+", ");
        }
        return ans;

    }
    void check(map<int,string> &data){
        string ch ="a";
        vector<int> ref;

        for (auto i:data){
              if( i.second!= ch){
                 ch =i.second;
              }
              else{
                  ref.push_back(i.first);

              }
        }
        for(int i: ref){
            data.erase(i);
        }
    }
    string req(map<int,string> &data, int &number){

        string ans;
        map <int,string>  sequitor;
        int q = 0;
        for(auto i:data){
           if(i.first!=number){
              sequitor[i.first] = i.second;

              q++;
           }
           else{

              break;
           }
        }
        ans = sequring(sequitor);
        ans = formate(ans,q);
        return ans;
    }
    // приватные поля
    map<int,string> fnames_of_person;
    map<int,string> lnames_of_person;

};

int main() {

    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Polina");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    person.ChangeLastName(1989, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1995) << endl;

    return 0;


}



