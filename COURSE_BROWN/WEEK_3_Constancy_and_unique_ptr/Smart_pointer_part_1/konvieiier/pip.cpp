#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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
  virtual void Run() {
    throw logic_error("Unimplemented");
  }

protected:
  void PassOn(unique_ptr<Email> email) const;

public:
  void SetNext(unique_ptr<Worker> next);
};
class Reader : public Worker {
public:
	explicit Reader(istream& in):in_(){
	
	}
	void Run() {
	   //выписать обработку из Zoo	
    	throw logic_error("Unimplemented");
    }
private:
	istream& in_;
};
class Filter : public Worker {
public:
  using Function = function<bool(const Email&)>;
  
  explicit Filter(Function func):func_(func){
  	
  }
  void Process(unique_ptr<Email> email){

	}

private:
	Function func_;
};


class Copier : public Worker {
public:
	explicit Copier(string& recipient):recipient_(recipient){
		
	}
	void Process(){
		
	}
private:
	string recipient;
};


class Sender : public Worker {
public:
	Sender(ostream& out):out_(out){
	}
	void Process(unique_ptr<Email> email){
		out_>>*email;
	}
private:
	ostream& out_	

};


class PipelineBuilder {
public:

  explicit PipelineBuilder(istream& in){
  	Reader x(in);
  }

  PipelineBuilder& FilterBy(Filter::Function filter){
  	return;
  
  }

  PipelineBuilder& CopyTo(string recipient){
  	return;
  }

  PipelineBuilder& Send(ostream& out){
  	return;
  }
  unique_ptr<Worker> Build();
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

  pipeline->Run();

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

  ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSanity);
  return 0;
}