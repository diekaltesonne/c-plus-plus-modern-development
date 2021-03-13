#pragma once
#include <istream>
#include <string>
#include <unordered_map>
using namespace std;
namespace Ini {
using Section = unordered_map<string, string>;

class Document {
public:
  Section& AddSection(string name);
  const Section& GetSection(const string& name) const;
  size_t SectionCount() const;
  unordered_map<string, Section> sections;


private:
};
Document Load(istream& input);
}
