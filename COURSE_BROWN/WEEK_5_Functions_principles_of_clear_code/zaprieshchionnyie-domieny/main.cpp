#include <algorithm>
#include <iostream>
#include <string>
#include "test_runner.h"

#include <iostream>
#include <vector>
using namespace std;


vector<string> ReadDomains() {
  size_t count = 0;
  cin >> count;
  vector<string> domains;
  for (size_t i = 0; i < count; ++i) {
    string domain;
    cin>>domain;
    cerr<<domain<<endl;
    domains.push_back(domain);
  }
  return domains;
}

class Selector{
private:
    vector<string> banned_domains;
    vector<string> domains_to_check;

    bool IsSubdomain(const string& subdomain, const string& domain) const{
        int i = subdomain.size() - 1;
        int j = domain.size() - 1;
        bool a = true;
        while (i >= 0 && j >= 0) {
          if (((subdomain[i--] != domain[j--]))){
              a= false;
              break;
          }
        }
        if(a){
            if(j>0 && i<=0){
                return false;
            }
            if(j==i){
                return true;
            }
        }

        return (i < 0 && domain[j] == '.')||(j <= 0 && subdomain[i] == '.');
    }

    int adjusting(){
        for (string& domain : domains_to_check){
             reverse(domain.begin(),domain.end());
        }
        for (string& domain : banned_domains){
             reverse(domain.begin(),domain.end());
        }
        return 0;
    }

public:
    Selector(vector<string> banned_domains,vector<string> domains_to_check):
        banned_domains(move(banned_domains)),
        domains_to_check(move(domains_to_check)){
    }
    vector<string> selection(){
        vector<string>result;
        bool x =false;
        for (string& check_domain : domains_to_check) {
            for(string& ban_domain : banned_domains){
                if(IsSubdomain(check_domain,ban_domain)){
                    x = true;
                    break;
                }
            }
            if(x){
                result.push_back("Bad");
            }else{
                result.push_back("Good");
            }
            x = false;
        }
        return result;
    }
};
void TestSelector_1(){
     {
     const vector<string> banned_domains = {"ya.ru","maps.me","m.ya.ru","com"} ;
     const vector<string> domains_to_check ={"ya.ru","ya.com","m.maps.me",
                                             "moscow.m.ya.ru","maps.com","maps.ru","ya.ya"};
     vector<string> result = {"Bad","Bad","Bad","Bad","Bad","Good","Good"};
     ASSERT_EQUAL(Selector(banned_domains,domains_to_check).selection(),result);
     }

}
void TestSelector_2(){
    {
    const vector<string> banned_domains = {"b.c","a.b.c"} ;
    const vector<string> domains_to_check ={"d.b.c"};
    vector<string> result = {"Bad"};
    ASSERT_EQUAL(Selector(banned_domains,domains_to_check).selection(),result);
    }
}
void TestSelector_3(){
    {
    const vector<string> banned_domains = { "ya.ya", "ya.ru", "ya.com"};
    const vector<string> domains_to_check ={"haya.ya", "teya.ru", "suya.com","ha.ya.ya", "te.ya.ru", "su.ya.com"};
    vector<string> result = {"Good","Good","Good","Bad","Bad","Bad"};
    ASSERT_EQUAL(Selector(banned_domains,domains_to_check).selection(),result);
    }

}
void TestSelector_4(){
    {
    const vector<string> banned_domains = {"com"};
    const vector<string> domains_to_check ={"com.ru","ru.com.en","ru.com"};
    vector<string> result = {"Good","Good","Bad"};
    ASSERT_EQUAL(Selector(banned_domains,domains_to_check).selection(),result);
    }
}

void TestDomenResp(){
    const vector<string> banned_domains = {"ya.ya"};
    const vector<string> domains_to_check = {"ya","sport.ya.ya","ya.ya.com","teya.ya","ya.yarni"};
    vector<string> result = {"Good", "Bad", "Good","Good", "Good"};
    ASSERT_EQUAL(Selector(banned_domains,domains_to_check).selection(),result);
}
int main(){
//    TestRunner tr;
//    RUN_TEST(tr, TestSelector_1);
//    RUN_TEST(tr, TestSelector_2);
//    RUN_TEST(tr, TestSelector_3);
//    RUN_TEST(tr, TestSelector_4);
//    RUN_TEST(tr, TestDomenResp);
//    return 0;

        const vector<string> banned_domains = ReadDomains();
        const vector<string> domains_to_check = ReadDomains();
        vector<string>result= Selector(banned_domains,domains_to_check).selection();
        for(auto s:result){
                cout<<s<<endl;
        }
    return 0;
}
