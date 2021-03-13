#include "ini.h"
#include <string_view>
#include <iostream>
using namespace std;

pair<string_view, string_view> Split(string_view line, char by) {
  size_t pos = line.find(by);
  string_view left = line.substr(0, pos);
  if (pos < line.size() && pos + 1 < line.size()) {
    return {left, line.substr(pos + 1)};
  } else {
    return {left, string_view()};
  }
}

string_view Lstrip(string_view line) {
  while (!line.empty() && isspace(line[0])) {
    line.remove_prefix(1);
  }
  return line;
}

string_view Unquote(string_view value) {
    if (!value.empty() && value.front() =='[') {
    value.remove_prefix(1);
  }
  if (!value.empty() && value.back() == ']') {
    value.remove_suffix(1);
  }
  return value;
}

namespace Ini {
Section& Document::AddSection(string name){
    return sections[name];
}
Document Load(istream& input){
    Document result;
      Section* current_section = nullptr;
      for (string line; getline(input, line); ) {
        if (!line.empty()) {
          if (line[0] == '[') {
            current_section = &result.AddSection(line.substr(1, line.size() - 2));
          } else {
            size_t eq_pos = line.find('=');
            current_section->insert({line.substr(0, eq_pos), line.substr(eq_pos + 1)});
          }
        }
      }
      return result;
}
size_t Document::SectionCount() const{
    return sections.size();
}
const Section& Document::GetSection(const string& name) const{
    return sections.at(name);
}
}
