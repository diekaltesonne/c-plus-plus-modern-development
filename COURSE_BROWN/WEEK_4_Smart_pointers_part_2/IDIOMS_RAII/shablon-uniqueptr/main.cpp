#include "test_runner.h"

#include <cstddef>
#include <utility>
using namespace std;

// Реализуйте шаблон класса UniquePtr
template <typename T>
class UniquePtr {
private:
    T* item;
public:
  UniquePtr(){
      item = nullptr;
  }
  UniquePtr(T * ptr):item(ptr){
  }
  UniquePtr(const UniquePtr&) =delete;
  UniquePtr(UniquePtr&& other){
      item = other.Release();
  }
  UniquePtr& operator = (const UniquePtr&) = delete;
  UniquePtr& operator = (std::nullptr_t){
    Reset(nullptr);
    return *this;
  }
  UniquePtr& operator = (UniquePtr&& other){
      Reset(other.item);
      other.item = nullptr;
      return *this;
  }
  ~UniquePtr(){
      delete item;
  }
  T& operator * () const{
      return *item;
  }
  T* operator -> () const{
      return item;
  }
  T* Release(){
      T* x = item;
      item = nullptr;
      return x;
  }
  void Reset(T* ptr){
      T* old = item;
      item = ptr;
      delete old;
  }

  void Swap(UniquePtr& other){
      std::swap(item, other.item);
  }

  T* Get() const{
      return item;
  }
};


struct Item {
  static int counter;
  int value;
  Item(int v = 0): value(v) {
    ++counter;
  }
  Item(const Item& other): value(other.value) {
    ++counter;
  }
  ~Item() {
    --counter;
  }
};

int Item::counter = 0;


void TestLifetime() {
  Item::counter = 0;
  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);
    ptr.Reset(new Item);
    ASSERT_EQUAL(Item::counter, 1);
  }
  ASSERT_EQUAL(Item::counter, 0);

  {
    UniquePtr<Item> ptr(new Item);
    ASSERT_EQUAL(Item::counter, 1);

    auto rawPtr = ptr.Release();
    ASSERT_EQUAL(Item::counter, 1);

    delete rawPtr;
    ASSERT_EQUAL(Item::counter, 0);
  }
  ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
    UniquePtr<Item> ptr(new Item(42));
    ASSERT_EQUAL(ptr.Get()->value, 42);
    ASSERT_EQUAL((*ptr).value, 42);
    ASSERT_EQUAL(ptr->value, 42);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestLifetime);
  RUN_TEST(tr, TestGetters);
}
