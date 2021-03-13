#include "test_runner.h"
#include <algorithm>
#include <list>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>


using namespace std;
template <typename T>
class PriorityCollection {
public:
  struct elem{
        T object;
        int num = 0;
        int64_t timestep;
  };
  using Id = typename list<elem>::iterator;  /* тип, используемый для идентификаторов */
  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object){
     elem a = { move(object),0,count};
     collection.push_back(move(a));
     Id id = prev(collection.end());
     database[0].push_back(id);
     count++;
     return id;

  }
  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,IdOutputIt ids_begin){
      while (range_begin !=range_end) {
          *ids_begin = Add(move(*range_begin));
          ++ids_begin;
          ++range_begin;
      }
  }
  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const{
      return (find(collection.begin(),collection.end(),*id)!=collection.end());
  }
  // Получить объект по идентификатору
  const T& Get(Id id) const{
    return ref(id->object);
  }
  // Увеличить приоритет объекта на 1

  void Promote(Id id){
      database.at(id->num).erase(find(database[id->num].begin(),database[id->num].end(),id));
      id->num++;
      database[id->num].push_back(id);

  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const{
    int timestep =0;
    Id result;
    for(Id a:database.at(database.rbegin()->first)){
        if(a->timestep >= timestep){
            timestep = a->timestep;
            result =  a;
        }
    }
    pair<const T&, int> obj = {ref(result->object),result->num};
    return  obj;
  }
  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax(){
      auto it =database.begin();
      while(it !=database.end()){
          if(it->second.empty()){
            database.erase(it);
          }
          it++;
      }
      int key = database.rbegin()->first;
      int timestep = 0;
      Id result;
      for(Id& a: database.at(database.rbegin()->first)){
          if(a->timestep >= timestep){
              timestep = a->timestep;
              result =  a;
          }
       }
    pair<T, int> ans = {move(result->object),result->num};
    database.at(key).erase(find(database.at(key).begin(),database.at(key).end(),result));
    collection.erase(result);
    return ans;
  }
private:
  int64_t count = 0;
  map < int,  list<Id>> database;
  list<elem> collection;
};
class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
   ASSERT_EQUAL (item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
