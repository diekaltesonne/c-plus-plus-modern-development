#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;
/*
 * читайте, что в каждый год может произойти не более одного изменения фамилии и не более одного изменения имени.
 * При этом с течением времени могут открываться всё новые факты из прошлого человека,
 * поэтому года́ в последовательных вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.
 * Гарантируется, что все имена и фамилии непусты.
 * Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и фамилию человека
 * по состоянию на конец данного года.
 * Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".
 * Если к данному году случилось изменение фамилии, но не было ни одного изменения имени, верните "last_name with unknown first name".
 * Если к данному году случилось изменение имени, но не было ни одного изменения фамилии, верните "first_name with unknown last name".
*/


/*
    Incognito
    Polina with unknown last name
    Polina Sergeeva
    Polina Sergeeva
    Appolinaria Sergeeva

    Polina Volkova
    Appolinaria Volkova
*/
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
        return fnames_of_person[a]+" "+lnames_of_person[b];
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

    map<int,string> fnames_of_person;
    map<int,string> lnames_of_person;
  // приватные поля
};

int main()
{
    /*
        Incognito
        Polina with unknown last name
        Polina Sergeeva
        Polina Sergeeva
        Appolinaria Sergeeva
        Polina Volkova
        Appolinaria Volkova
    */
    Person person;
     person.ChangeFirstName(1965, "Polina");
     person.ChangeLastName(1967, "Sergeeva");
     for (int year : {1900, 1965, 1990}) {
       cout << person.GetFullName(year) << endl;
     }

     person.ChangeFirstName(1970, "Appolinaria");
     for (int year : {1969, 1970}) {
       cout << person.GetFullName(year) << endl;
     }
     person.ChangeLastName(1968, "Volkova");
     for (int year : {1969, 1970}) {
       cout << person.GetFullName(year) << endl;
     }

     return 0;
}




/*
     for(auto it:data){
         if(it.first == year){
             cout<<it.second.m<<" "<<it.second.lnp<<"Проверка"<<endl;
             if(it.second.fnp == "Inc"){
                 return  it.second.lnp + " with unknown first name";
             }
             else if(it.second.lnp == "Inc"){
                 return  it.second.fnp +" with unknown last name";;
             }
             else if(it.second.lnp == "Inc"&& it.second.fnp == "Inc"){
                 return "Incognito";
             }
             return it.second.fnp+" "+it.second.lnp;

         }
     }
*/
/*
//     if(data[last_year_ch].fnp == "Inc"){
//                 return  data[last_year_ch].lnp + " with unknown first name";
//             }
//             else if(it.second.lnp == "Inc"){
//                 return  data[last_year_ch].fnp +" with unknown last name";;
//             }
//             else if(it.second.lnp == "Inc"&& it.second.fnp == "Inc"){
//                 return "Incognito";
//             }
//             return it.second.fnp+" "+it.second.lnp;
//             break;


//     }
*/





