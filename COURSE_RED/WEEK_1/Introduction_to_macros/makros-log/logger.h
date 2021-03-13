#ifndef LOGGER_H
#define LOGGER_H
#include <sstream>
#include <string>

#include <iostream>
using namespace std;

class Logger {
public:
  explicit Logger(ostream& output_stream) : os(output_stream) {
  }
  void SetLogLine(bool value);
  void SetLogFile(bool value);

  bool GetLogLine()const;
  bool GetLogFile()const;

  void Log(const string& message);

private:
  ostream& os;
  bool log_line = false;
  bool log_file = false;
};

void TestLog();



#endif // LOGGER_H

