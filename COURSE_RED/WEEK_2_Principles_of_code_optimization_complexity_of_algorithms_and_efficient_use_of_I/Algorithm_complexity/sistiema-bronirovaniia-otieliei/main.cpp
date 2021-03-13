#include <iostream>
#include <map>
#include <utility>
#include "test_runner.h"
#include "profile.h"
#include <stdint.h>
#include "manager.h"
using namespace std;
void test() {
    BookingManager manager;

    // Test empty bookings
    ASSERT_EQUAL(manager.getClients("mariott"), 0);
    ASSERT_EQUAL(manager.getRooms("mariott"), 0);

    manager.Book(0, "mariott", 1, 10);
    manager.Book(0, "mariott", 2, 1);
    manager.Book(0, "mariott", 3, 1);
    manager.Book(0, "mariott", 4, 1);
    manager.Book(0, "hilton", 1, 1);
    manager.Book(1, "hilton", 2, 1);

    // Test correctness
    ASSERT_EQUAL(manager.getClients("mariott"), 4);
    ASSERT_EQUAL(manager.getRooms("mariott"), 13);
    ASSERT_EQUAL(manager.getRooms("hilton"), 2);
    ASSERT_EQUAL(manager.getClients("hilton"), 2);


    // Test event past 1 day resets statics
    manager.Book(86400, "mariott", 1, 1);
    ASSERT_EQUAL(manager.getClients("mariott"), 1);
    ASSERT_EQUAL(manager.getRooms("mariott"), 1);
    ASSERT_EQUAL(manager.getClients("hilton"), 1);
    ASSERT_EQUAL(manager.getRooms("hilton"), 1);

    // Test no clients and room for the last day
    manager.Book(86401, "mariott", 5, 1);
    ASSERT_EQUAL(manager.getClients("mariott"), 2);
    ASSERT_EQUAL(manager.getRooms("mariott"), 2);
    ASSERT_EQUAL(manager.getClients("hilton"), 0);
    ASSERT_EQUAL(manager.getRooms("hilton"), 0);
}

void Run_check(){
      // Для ускорения чтения данных отключается синхронизация
      // cin и cout с stdio,
      // а также выполняется отвязка cin от cout
      ios::sync_with_stdio(false);
      cin.tie(nullptr);
      BookingManager manager;
      int query_count;
      cin >> query_count;
      for (int query_id = 0; query_id < query_count; ++query_id){
        string query_type;
        cin >> query_type;
        if (query_type == "BOOK") {
          int64_t time;
          int64_t client_id;
          int room_count;
          string hotel_name;
          cin >> time >> hotel_name >> client_id >>room_count;
          manager.Book(time,hotel_name,client_id,room_count);
        }else if (query_type == "CLIENTS") {
          string hotel_name;
          cin >> hotel_name;
          cout<<manager.getClients(hotel_name)<<"\n";
        }else if (query_type == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout<<manager.getRooms(hotel_name)<<"\n";
        }
      }
}
int main(){
    TestRunner tr;
    RUN_TEST(tr, test);
    //Run_check();
    return 0;
}
