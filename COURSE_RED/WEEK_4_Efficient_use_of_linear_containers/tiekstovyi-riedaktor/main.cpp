#include "test_runner.h"
#include <vector>
#include <array>
#include <list>
using namespace std;

class Editor {
private:
  void destructor(){
      for(int i = 0; i<pos;i++){
          first_part.push_back(GAP_BUFFER[i]);
      }
      pos = 0;
  }
  void Left_private(){
      if(pos == 0){
          if(!first_part.empty()){
              last_part.push_front(first_part.back());
              first_part.pop_back();
          }
      }else{
          pos--;
          last_part.push_front(GAP_BUFFER[pos]);

      }
  }
  void Right_private(){
      if(pos < 100){
          if(!last_part.empty()){
          GAP_BUFFER[pos]= last_part.front();
          last_part.pop_front();
          pos++;
          }
      }else{
          destructor();
          first_part.push_back(last_part.front());
          last_part.pop_front();
      }

  }

  vector<char> BUFFER;
  list<char> first_part;
  list<char> last_part;
  array<char,100> GAP_BUFFER;
  int pos = 0;

public:
  // Реализуйте конструктор по умолчанию и объявленные методы
  Editor(){
  }
  //Вырезание фрагмента текста аналогично копированию с последующим удалением скопированных символов из текста (Cut).
  void Cut(size_t tokens = 1){
      BUFFER.clear();
      //destructor();
      for(size_t i = 0; i <tokens; i++){
          if(!last_part.empty()){
              BUFFER.push_back(last_part.front());
              last_part.pop_front();
          }
      }
  }

  //Ввод символа в текущую позицию курсора (Insert).
  void Insert(char token){
      if(pos == 100){
          destructor();
      }
      GAP_BUFFER[pos] = token;
      pos++;
  }
  //Копирование фрагмента текста, начинающегося в текущей позиции курсора, в буфер обмена (Copy).
  void Copy(size_t tokens = 1){
     BUFFER.clear();
     destructor();
     if(!last_part.empty()){
         list<char>::iterator it = last_part.begin();
         for(size_t i = 0; i < tokens; i++){
             BUFFER.push_back(*it);
             it = next(it);
         }
     }
  }
  //Вставка содержимого буфера обмена в текущую позицию курсора (Paste).
  void Paste(){
      destructor();
      for(auto i:BUFFER){
          first_part.push_back(i);
      }
  }

  string GetText() const  {
      string a;
      //destructor();
      for(auto i :first_part){
          a.push_back(i);
      }
      for(int i=0;i < pos;i++){
          a.push_back(GAP_BUFFER[i]);
      }
      for(auto i :last_part){
          a.push_back(i);
      }
      return a;
  }

  //Перемещение курсора влево (Left) и вправо (Right) на одну позицию.
  void Left(){
      Left_private();
  }
  void Right(){
      Right_private();
  }
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
   {
    Editor editor;
    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }

}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}
void Test_spec() {
    Editor editor;
    TypeText(editor, "1234567");
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Paste();
    editor.Paste();
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "123456667");
}

void TestCut()
{
    Editor editor;
    //1
    editor.Cut(10);
    editor.Insert('a');
    editor.Left();
    //2
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "a");
    //3
    editor.Cut(0);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "a");
    TypeText(editor, "bcde");
    editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
    //4
    editor.Cut(10);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "abcde");
    editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
    //5
    editor.Cut(5);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    //6
    editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "bcde");
    editor.Right();
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "bde");
    editor.Cut(1);
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "b");
}

void TestCopy()
{
    Editor editor;
    //1
    editor.Copy(10);
    editor.Insert('a');
    editor.Paste();
    editor.Left();
    ASSERT_EQUAL(editor.GetText(), "a");
    //2
    editor.Copy(1);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "aa");//between a
    //3
    editor.Copy(0);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "aa");
    TypeText(editor, "bcde");
    editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();editor.Left();
    //4
    editor.Cut(10);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "abcdea");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  RUN_TEST(tr, Test_spec);
  RUN_TEST(tr, TestCut);
  RUN_TEST(tr, TestCopy);
  return 0;
}

