#include "test_runner.h"
#include <vector>


using namespace std;
template <typename T>

class LinkedList {
public:
    struct Node {
        T value;
        Node* next = nullptr;
    };
//  Деструктор класса LinkedList освобождает всю память, выделенную для хранения элементов списка.
    ~LinkedList(){
        while(head!=nullptr){
            PopFront();
        }
    }
//  Метод PushFront добавляет новый элемент в голову списка
    void PushFront(const T& value){
        if (head != nullptr){
            Node* tmp = new Node;
            tmp ->value =value;
            tmp ->next = head;
            head = tmp;
        }else{
            head = new Node;
            head->value = value;
        }
    }

//  Метод InsertAfter вставляет новый элемент в список так, чтобы он шёл после узла node.
//  Если node == nullptr, метод эквивалентен PushFront

    void InsertAfter(Node* node, const T& value){
      if( node == nullptr){
         PushFront(value);
      }else{
          Node* tmp = new Node;
          tmp ->value =value;
          tmp ->next = node->next;
          node->next = tmp;
      }
    }
//  Метод RemoveAfter должен удалять из списка элемент, который следует за узлом node, и освобождать выделенную под него память.
//  Если node == nullptr, метод эквивалентен PopFront. Если node->next == nullptr, то метод должен корректно завершаться.
    void RemoveAfter(Node* node){
      if(node == nullptr){
          PopFront();
      }else{

          if(node->next != nullptr){
              Node* tmp = new Node;
              tmp ->next = node->next;
              node->next = node->next->next;
              delete tmp;
          }
      }
    }

//  Метод PopFront удаляет элемент из головы списка и освобождает выделенную под него память.
//  Если список пуст, метод завершается корректно.
//  Если после выполнения метода список стал пустым, метод GetHead должен возвращать nullptr

    void PopFront() {
        Node* n = head;
        if (n != nullptr) {
            head = n->next;
            delete n;
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
