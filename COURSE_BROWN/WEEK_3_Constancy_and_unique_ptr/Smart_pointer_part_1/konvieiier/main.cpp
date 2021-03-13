#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include <iterator>

using namespace std;
struct Email {
  string from;
  string to;
  string body;
};

class Worker {
public:
  virtual ~Worker() = default;
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run(){
      throw logic_error("Unimplemented");
  }
  void SetNext(unique_ptr<Worker> next_other){
      if(next == nullptr ){
        next = move(next_other);
      }else{
          next.get()->SetNext(move(next_other));
      }
  }
protected:
  void PassOn(unique_ptr<Email> email) const {
      if(next!=nullptr){
         next.get()->Process(move(email));
      }
  }

private:
  unique_ptr<Worker> next = nullptr;
};

class Reader : public Worker {
public:
    explicit Reader(istream& in):in_(in){
    }
    void Process(unique_ptr<Email> email)override{
          this->PassOn(move(email));
    }
    virtual void Run() override {
        string str;
        vector<string> data;

        while (getline(in_, str)){
            data.push_back(str);
            if(data.size() == 3){
                this-> Process(make_unique<Email>(Email({data[0],data[1],data[2]})));
                data.clear();
            }
        }
    }
private:
    istream& in_;
};

class Filter : public Worker {
public:
//    конструктор должен принимать предикат типа function<bool(const Email&)>
//    метод Process должен передавать дальше только сообщения, удовлетворяющие предикату
  using Function = function<bool(const Email&)>;

  explicit Filter(Function func ):func_(func){
  }
  virtual void Process(unique_ptr<Email> email){
    if(func_(*email.get())){
        PassOn(move(email));
    }
  }
private:
	Function func_;
};


class Copier : public Worker {
public:
    explicit Copier(const string& recipient ):recipient_(recipient){
	}
    virtual void Process(unique_ptr<Email> email){
        string from_ = email.get()->from;
        string body_ = email.get()->body;
        string to_ = email.get()->to;
        this->PassOn(move(email));
        if(recipient_!= to_){
            this->PassOn(make_unique<Email>(Email({from_, recipient_, body_ })));
        }
    }
private:
    string recipient_;
};

class Sender : public Worker {
public:
    // должен принимать поток для записи сообщений
    //метод Process должен записывать сообщения в поток в том же формате, в котором они были прочитаны
    Sender(ostream& out):out_(out){
	}
    void Process(unique_ptr<Email> email) override {
        out_<<email.get()->from<<"\n"<<email.get()->to<<"\n"<<email.get()->body<<"\n";
        this->PassOn(move(email));
    }
private:
    ostream& out_;
};

//Конструктор должен инициализировать цепочку обработчиков обработчиком Reader с переданным потоком.
//Методы с типом возврата PipelineBuilder& должны возвращать ссылку на экземпляр класса,
//для которого они были вызваны, а также добавлять в конец цепочки новый обработчик,
//соответствующий вызванному методу (Filter для метода FilterBy, Sender для метода Send и т.д.).
//Метод Build должен возвращать готовую цепочку обработчиков; подразумевается,
//что после его завершения экземпляр PipelineBuilder больше использоваться не будет

class PipelineBuilder {
public:
  explicit PipelineBuilder(istream& in):worker(make_unique<Reader>(in)){
  }

  PipelineBuilder& FilterBy(Filter::Function filter){
      worker.get()->SetNext(make_unique<Filter>(filter));
      return *this;
  }
  PipelineBuilder& CopyTo(string recipient){
      worker.get()->SetNext(make_unique<Copier>(recipient));
      return *this;
  }
  PipelineBuilder& Send(ostream& out){
      worker.get()->SetNext(make_unique<Sender>(out));
      return *this;
  }

  unique_ptr<Worker> Build(){
      return move(worker);
  }
private:
  unique_ptr<Reader> worker;
};

void TestSanity() {
  string input = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"
    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"
    "ralph@example.com\n"
    "erich@example.com\n"
    "I do not make mistakes of that kind\n"
  );
  istringstream inStream(input);
  ostringstream outStream;
  PipelineBuilder builder(inStream);
  builder.FilterBy([](const Email& email) {
     return email.from == "erich@example.com";
  });
  builder.CopyTo("richard@example.com");
  builder.Send(outStream);
  auto pipeline = builder.Build();
  pipeline -> Run();
  string expectedOutput = (
    "erich@example.com\n"
    "richard@example.com\n"
    "Hello there\n"
    "erich@example.com\n"
    "ralph@example.com\n"
    "Are you sure you pressed the right button?\n"
    "erich@example.com\n"
    "richard@example.com\n"
    "Are you sure you pressed the right button?\n"
  );
//  cout<<"TEST\n"<<outStream.str()<<"TEST\n"<<endl;
  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}
