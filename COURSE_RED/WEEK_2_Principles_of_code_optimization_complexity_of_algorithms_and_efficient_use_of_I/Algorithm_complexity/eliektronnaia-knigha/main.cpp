#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include "test_runner.h"
#include "profile.h"

using namespace std;

class ReadingManager {
private:

    // Статическое поле не принадлежит какому-то конкретному
    // объекту класса. По сути это глобальная переменная,
    // в данном случае константная.
    // Будь она публичной, к ней можно было бы обратиться снаружи
    // следующим образом: ReadingManager::MAX_USER_COUNT.

    static const int MAX_USER_COUNT_ = 100000;
    vector<int> user_page_counts_;
    vector<vector<int>>sorted_on_page_and_user_id;

    void AddUser(int user_id){
      sorted_on_page_and_user_id[0].push_back(user_id);
    }

    int GetUserCount() const {
      return sorted_on_page_and_user_id[0].size();
    }

public:

    ReadingManager(): user_page_counts_(MAX_USER_COUNT_+1, 0),sorted_on_page_and_user_id(1001){}
    /*
     * READ user page — сохранить факт того, что пользователь под номером user дочитал книгу до 1 page.
     * Если ранее такой пользователь не встречался, необходимо его добавить.
     * Гарантируется, что в рамках одного пользователя номера страниц в соответствующих ему событиях возрастают.
     */
    void Read(int user_id, int page_count){
      int last_achivment = 0;
      if (user_page_counts_[user_id] == 0){
          AddUser(user_id);
          user_page_counts_[user_id] = page_count;
          for(int i = last_achivment+1;i<=page_count;i++){
              sorted_on_page_and_user_id[i].push_back(user_id);
          }

      }else {
          last_achivment =user_page_counts_[user_id];
          user_page_counts_[user_id] = page_count;
          for(int i = last_achivment+1;i<=page_count;i++){
              sorted_on_page_and_user_id[i].push_back(user_id);
          }
      }
    }

    /*
     *CHEER user — сообщить пользователю user, какая доля существующих пользователей (не считая его самого) прочитала меньшую часть книги, чем он.
     * Если этот пользователь на данный момент единственный, доля считается равной 1.
     * Если для данного пользователя пока не было ни одного события READ, доля считается равной 0,
     * а сам пользователь не учитывается при вычислении долей для других пользователей до тех пор, пока для него не случится событие READ.
    */

    double Cheer(int user_id) const {
        int check_sum = 0;
        if (user_page_counts_[user_id] == 0) {
            return 0;
        }
        const int user_count = GetUserCount();
        if (user_count == 1) {
            return 1;
        }
        check_sum =  sorted_on_page_and_user_id[user_page_counts_[user_id]].size();
        double check = (user_count - check_sum) *1.0/(user_count-1);
        return check;
  }
};
void TestReadPage();
void Run_check();

int main(){
    //TestRunner tr;
    //RUN_TEST(tr,TestReadPage);
    Run_check();
  return 0;
}

void TestReadPage() {

    {// add user
        LOG_DURATION("add user");
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(1), 0.0);//done
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
    }

    {// add user but cheer not existed
        LOG_DURATION("add user but cheer not existed");
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(2), 0.0);
    }

    {// read twice
        LOG_DURATION("read twice");
        ReadingManager manager;
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        manager.Read(1, 2);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
    }

    {// better than third
        LOG_DURATION("better than third")

        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(2, 2);
        manager.Read(3, 3);

        ASSERT_EQUAL(manager.Cheer(2), 0.5);
        manager.Read(4, 4);
        ASSERT_EQUAL(manager.Cheer(2), 1.0 / 3.0);
    }

    {// better than 2 third
        LOG_DURATION("better than third");
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(2, 2);
        manager.Read(3, 3);
        ASSERT_EQUAL(manager.Cheer(2), 0.5);
        manager.Read(4, 4);
        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
    }

    {// read zero
        LOG_DURATION("read zero");
        ReadingManager manager;
        manager.Read(1, 0);
        manager.Read(2, 0);
        manager.Read(3, 1);
        manager.Read(4, 2);
        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
    }

    {// all read the same
        LOG_DURATION("all read the same");
        ReadingManager manager;
        manager.Read(1, 5);
        manager.Read(2, 5);
        manager.Read(3, 5);
        manager.Read(4, 5);
        ASSERT_EQUAL(manager.Cheer(3), 0.0);
    }
    {// reverse order
        LOG_DURATION("reverse order");
        ReadingManager manager;
        manager.Read(4, 5);
        manager.Read(3, 4);
        manager.Read(2, 3);
        manager.Read(1, 2);
        ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
    }
    {// two users read two times
        LOG_DURATION("two users read two times");
        ReadingManager manager;
        manager.Read(4, 5);
        manager.Read(3, 4);
        manager.Read(4, 6);
        manager.Read(3, 5);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        ASSERT_EQUAL(manager.Cheer(3), 0.0);
        manager.Read(10, 2);
        ASSERT_EQUAL(manager.Cheer(3), 0.5);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
    }
    {// only one user
        LOG_DURATION("only one user");
        ReadingManager manager;
        manager.Read(4, 5);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        manager.Read(4, 6);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        manager.Read(4, 100);
        ASSERT_EQUAL(manager.Cheer(4), 1.0);
        ASSERT_EQUAL(manager.Cheer(3), 0.0);
        ASSERT_EQUAL(manager.Cheer(5), 0.0);
    }
    {// ten users
        LOG_DURATION("ten users");
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(2, 2);
        manager.Read(3, 3);
        manager.Read(4, 4);
        manager.Read(5, 5);
        manager.Read(6, 6);
        manager.Read(7, 7);
        manager.Read(8, 8);
        manager.Read(9, 9);
        manager.Read(100, 10);
        manager.Read(111, 11);

        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        ASSERT_EQUAL(manager.Cheer(2), 0.1);
        ASSERT_EQUAL(manager.Cheer(3), 0.2);
        ASSERT_EQUAL(manager.Cheer(4), 0.3);
        ASSERT_EQUAL(manager.Cheer(5), 0.4);
        ASSERT_EQUAL(manager.Cheer(6), 0.5);
        ASSERT_EQUAL(manager.Cheer(7), 0.6);
        ASSERT_EQUAL(manager.Cheer(8), 0.7);
        ASSERT_EQUAL(manager.Cheer(9), 0.8);
        ASSERT_EQUAL(manager.Cheer(100), 0.9);
        ASSERT_EQUAL(manager.Cheer(111), 1.0);
        ASSERT_EQUAL(manager.Cheer(12), 0.0);
    }
    {// cheer twice
        LOG_DURATION("cheer twice");
        ReadingManager manager;

        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);

        ASSERT_EQUAL(manager.Cheer(2), 0);
    }

    {// max ID
        LOG_DURATION("max ID");
        const int MAX_USER_COUNT = 100000;
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 0.0);
        manager.Read(MAX_USER_COUNT, 1);
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 1.0);
    }
    {// max page
        LOG_DURATION("max page");
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(1), 0.0);
        manager.Read(1, 1000);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
    }
    {// max ID and max page
        LOG_DURATION("max ID and max page");
        const int MAX_USER_COUNT = 100000;
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 0.0);
        manager.Read(MAX_USER_COUNT, 1000);
        ASSERT_EQUAL(manager.Cheer(MAX_USER_COUNT), 1.0);
    }
    {// zero ID
        LOG_DURATION("zero ID");
        ReadingManager manager;
        ASSERT_EQUAL(manager.Cheer(0), 0.0);
        manager.Read(0, 1000);
        ASSERT_EQUAL(manager.Cheer(0), 1.0);
    }
    {// from coursera (https://www.coursera.org/learn/c-plus-plus-red/programming/e72ST/eliektronnaia-knigha/discussions/threads/hLK3cT0AEemHtRKqiMW_lA)
        LOG_DURATION("last");
        ReadingManager manager;
        manager.Read(1, 1);
        manager.Read(1, 3);
        manager.Read(2, 2);
        ASSERT_EQUAL(manager.Cheer(1), 1.0);
        ASSERT_EQUAL(manager.Cheer(2), 0.0);
    }
}

void Run_check(){

      // Для ускорения чтения данных отключается синхронизация
      // cin и cout с stdio,
      // а также выполняется отвязка cin от cout

      ios::sync_with_stdio(false);
      cin.tie(nullptr);

      ReadingManager manager;

      int query_count;
      cin >> query_count;

      for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
          int page_count;
          cin >> page_count;
          manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
          cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
      }
}
