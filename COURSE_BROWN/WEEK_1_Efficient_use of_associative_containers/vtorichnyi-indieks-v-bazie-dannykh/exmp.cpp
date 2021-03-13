struct Record {
  string id;
  string title;
  string user;
  int timestamp;
  int karma;
};
struct IntWithRecordId {
    int index;
    string record_id = "O";
    bool operator < (const IntWithRecordId & other) const{
        return index < other.index;
    }

};
struct StringtWithRecordId {
    string index;
    string record_id = "O";
    bool operator < (const  StringtWithRecordId & other) const {
        return index < other.index;
    }
};

class Database {
public:

  bool Put(const Record& record){
      if(database.count(record.id) == 0){
          database[record.id] = record;
          map<string,Record>::iterator it = database.find(record.id);
          user_base.insert(pair<StringtWithRecordId,map<string,Record>::iterator>({record.user,record.id},it));
          karma_range.insert(pair<IntWithRecordId,map<string,Record>::iterator>({record.karma,record.id},it));
          timestamp_range.insert(pair<IntWithRecordId,map<string,Record>::iterator>({record.timestamp,record.id},it));
          return true;
      }else{
          return false;
      }
  }
  const Record* GetById(const string& id) const{
      if(database.count(id) == 0){
          return nullptr;
      }else{
          return &database.at(id);
      }
  }

  bool Erase(const string& id){
      if(database.count(id) == 0){
          return false;
      }else{
         const Record* a = GetById(id);
         karma_range.erase({a->karma,id});
         timestamp_range.erase({a->timestamp,id});
         user_base.erase({a->user,id});
         database.erase(id);
         return true;
      }
  }
  template <typename Callback>
  void RangeByTimestamp(int low, int high, Callback callback) const{
      auto range_begin = timestamp_range.lower_bound({low});
      auto range_end = timestamp_range.upper_bound({high});
      IterateThroughRange(range_begin,range_end,callback);
  }
  template <typename Callback>
  void RangeByKarma(int low, int high, Callback callback) const{
      auto range_begin = karma_range.lower_bound({low});
      auto range_end = karma_range.upper_bound({high});
      IterateThroughRange(range_begin,range_end,callback);
  }
  template <typename Callback>
  void AllByUser(const string& user, Callback callback) const{
      auto [it_begin, it_end] = user_base.equal_range({user});
      for (auto it = it_begin; it != it_end; ++it){
          if (!callback(it->second->second)) {
              break;
          }
      }
  }
private:
  template <typename InputIt, typename Callback>
      void IterateThroughRange(InputIt range_begin, InputIt range_end, Callback callback) const {
          for (InputIt it = range_begin; it != range_end; ++it) {
              if(callback(it->second->second)==false){
                  break;
              }
          }
  }
 map<string,Record> database;
 multimap<StringtWithRecordId,map<string,Record>::iterator> user_base;
 multimap<IntWithRecordId,map<string,Record>::iterator> karma_range;
 multimap<IntWithRecordId,map<string,Record>::iterator> timestamp_range;
};
