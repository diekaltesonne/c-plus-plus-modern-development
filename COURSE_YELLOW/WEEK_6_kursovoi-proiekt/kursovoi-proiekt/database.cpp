#include <database.h>
#include <date.h>
using namespace std;

void Database::Add(const Date &date, const string &event) {
    if (storage.count(date) == 0 || storage_Set.at(date).count(event) == 0) {
        storage[date].push_back(event);
        storage_Set[date].insert(event);
    }
}

void Database::Print(ostream &stream) const {
    for (const auto &date : storage) {
        for (const auto &event : date.second) {
            stream << date.first << " " << event << endl;
        }
    }
}

pair<Date, string> Database::Last(const Date &date) const {
    if (date < storage.begin()->first || storage.empty()) {
        throw invalid_argument("");
    };
    auto it = --(storage.upper_bound(date));
    return {it->first, it->second.back()};
}

ostream &operator << (ostream &stream, const pair<Date, string> &p) {
    return stream << p.first << " " << p.second;
}



