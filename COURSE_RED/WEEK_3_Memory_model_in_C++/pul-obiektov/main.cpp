#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
/*
 * если есть хотя бы один освобождённый объект,
 * о его надо перенести в множество выделенных и вернуть указатель на него в качестве результата функции
 * если же освобождённых объектов нет, то создаётся новый объект,
 * помещается в множество выделенных, и указатель на него возвращается в качестве результата функции
*/
  T* Allocate(){

    if(obj_pool_free.size()!=0){
        T* str = obj_pool_free[0];
        obj_pool_free.pop_front();
        obj_pool_line.insert(str);
        return str;

    }else{

        T* str = new T;
        obj_pool_line.insert(str);
        return str;
    }

  }
/*
 * Метод TryAllocate работает аналогично, однако если освобождённых объектов нет, он должен просто возвращать nullptr.
*/
  T* TryAllocate(){

      if(obj_pool_free.size()!=0){
          T* str = obj_pool_free[0];
          obj_pool_free.pop_front();
          obj_pool_line.insert(str);
          return str;
      }else{
          return nullptr;
      }
  }

/*
 * Метод Deallocate переносит объект из множества выделенных в множество освобождённых;
 * если переданный объект не содержится в множестве выделенных, метод Deallocate должен бросать исключение invalid_argument.
*/
  void Deallocate(T* object){
      if(obj_pool_line.count(object)!=0){
          obj_pool_line.erase(obj_pool_line.find(object));
          obj_pool_free.push_back(object);
      }else{
          throw(invalid_argument("invalid_arg"));
      }

  }
  ~ObjectPool(){
      for (auto i: obj_pool_line) { //удаляем выделенный сет
          delete i;
      }
      for (auto i:obj_pool_free){
          delete i;
      }
  }

private:
  set< T* > obj_pool_line;
  deque< T* >obj_pool_free;

  // Добавьте сюда поля
};


void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");
  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
