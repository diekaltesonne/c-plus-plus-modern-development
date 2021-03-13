#include "test_runner.h"
#include "logger.h"

using namespace std;

void  Logger:: SetLogLine(bool value) { log_line = value;}
void  Logger:: SetLogFile(bool value) { log_file = value;}
bool  Logger:: GetLogLine()const{
return log_line;
}
bool Logger:: GetLogFile()const{
return log_file;
}
void Logger:: Log(const string& message){
    os<<message+"\n";

}

#define LOG(logger, message){\
    \
    const string file = __FILE__ ;\
    const int line = __LINE__ ;\
    const string SpecLine ="Line";\
    if(!logger.GetLogFile()&&logger.GetLogLine()){\
        logger.Log(SpecLine+" "+to_string(line)+" "+message);\
    }else if(logger.GetLogFile()&&!logger.GetLogLine()){\
        logger.Log(file+" "+message);\
    \
    }else if(logger.GetLogFile()&&logger.GetLogLine()){\
        logger.Log(file+":"+to_string(line)+" "+message);\
    }else if(!logger.GetLogFile()&&!logger.GetLogLine()){\
        logger.Log(message);\
    }\
}

void TestLog() {
/* Для написания юнит-тестов в этой задаче нам нужно фиксировать конкретные
 * номера строк в ожидаемом значении (см. переменную expected ниже). Если
 * мы добавляем какой-то код выше функции TestLog, то эти номера строк меняются,
 * и наш тест начинает падать. Это неудобно.
 *
 * Чтобы этого избежать, мы используем специальный макрос #line
 * (http://en.cppreference.com/w/cpp/preprocessor/line), который позволяет
 * переопределить номер строки, а также имя файла. Благодаря ему, номера
 * строк внутри функции TestLog будут фиксированы независимо от того, какой
 * код мы добавляем перед ней*/
#line 1 "logger.cpp"

  ostringstream logs;
  Logger l(logs);
  LOG(l, "hello");

  l.SetLogFile(true);
  LOG(l, "hello");

  l.SetLogLine(true);
  LOG(l, "hello");

  l.SetLogFile(false);
  LOG(l, "hello");

  string expected = "hello\n";
  expected += "logger.cpp hello\n";
  expected += "logger.cpp:10 hello\n";
  expected += "Line 13 hello\n";
  ASSERT_EQUAL(logs.str(), expected);
}
