#include "test_runner.h"
#include <vector>


using namespace std;
template <typename T>
class LinkedList {
public:

    struct Node {
       Node(const T& v)
            : value(v)
            {}
       T value;
       Node* next = nullptr;
     };


     ~LinkedList(){
        while (head) {
            PopFront();
        }
    }

//  Метод PushFront добавляет новый элемент в голову списка
    void PushFront(const T& value){
            Node* tmp = head;
            head = new Node(value);
            head ->next =tmp;
    }
//  Метод InsertAfter вставляет новый элемент в список так, чтобы он шёл после узла node.
//  Если node == nullptr, метод эквивалентен PushFront
    void InsertAfter(Node* node, const T& value){
      if( node == nullptr){
         return PushFront(value);
      }else{
          Node* tmp = node->next;
          node->next = new Node(value);
          node->next->next = tmp;
      }
    }
//  Метод RemoveAfter должен удалять из списка элемент, который следует за узлом node, и освобождать выделенную под него память.
//  Если node == nullptr, метод эквивалентен PopFront. Если node->next == nullptr, то метод должен корректно завершаться.
    void RemoveAfter(Node* node){
      if(node == nullptr){
          return PopFront();
      }else{
          if(node->next != nullptr){
              Node* tmp = node->next;
              node->next = tmp->next;
              delete tmp;
          }else{
              return;
          }
      }
    }
//  Метод PopFront удаляет элемент из головы списка и освобождает выделенную под него память.
//  Если список пуст, метод завершается корректно.
//  Если после выполнения метода список стал пустым, метод GetHead должен возвращать nullptr
    void PopFront() {
      if (head != nullptr) {
        Node* temp = head;
        head = temp->next;
        delete temp;
      }
    }

//  Метод GetHead возвращает указатель на голову списка,
//  он используется для перебора элементов списка (см. шаблон ToVector в заготовке решения)
    Node* GetHead(){return head;}
    const Node* GetHead() const { return head; }

private:
    Node* head = nullptr;
};


template <typename T>
vector<T> ToVector(const LinkedList<T>& list) {
    vector<T> result;
    for (auto node = list.GetHead(); node; node = node->next) {
        result.push_back(node->value);
    }
    return result;
}



void TestPushFront() {
    LinkedList<int> list;
    list.PushFront(1);

    ASSERT_EQUAL(list.GetHead()->value, 1);
    list.PushFront(2);
    ASSERT_EQUAL(list.GetHead()->value, 2);
    list.PushFront(3);

    ASSERT_EQUAL(list.GetHead()->value, 3);
    const vector<int> expected = {3, 2, 1};
    ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
  LinkedList<string> list;

  list.PushFront("a");
  auto head = list.GetHead();
  ASSERT(head);
  ASSERT_EQUAL(head->value, "a");

  list.InsertAfter(head, "b");
  const vector<string> expected1 = {"a", "b"};
  ASSERT_EQUAL(ToVector(list), expected1);

  list.InsertAfter(head, "c");
  const vector<string> expected2 = {"a", "c", "b"};
  ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
  LinkedList<int> list;
  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }

  const vector<int> expected = {5, 4, 3, 2, 1};
  ASSERT_EQUAL(ToVector(list), expected);

  auto next_to_head = list.GetHead()->next;
  list.RemoveAfter(next_to_head); // удаляем 3
  list.RemoveAfter(next_to_head); // удаляем 2

  const vector<int> expected1 = {5, 4, 1};
  ASSERT_EQUAL(ToVector(list), expected1);

  while (list.GetHead()->next) {
    list.RemoveAfter(list.GetHead());
  }
  ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
  LinkedList<int> list;

  for (int i = 1; i <= 5; ++i) {
    list.PushFront(i);
  }
  for (int i = 1; i <= 5; ++i) {
    list.PopFront();
  }

  ASSERT(list.GetHead() == nullptr);
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestPushFront);
  RUN_TEST(tr, TestInsertAfter);
  RUN_TEST(tr, TestRemoveAfter);
  RUN_TEST(tr, TestPopFront);
  return 0;
}
