#include <stats.h>

void Stats::AddMethod(const string_view& method){
    if(MethodStats.count(method)!=0){
        MethodStats.at(method)+=1;
    }else{
        MethodStats.at("UNKNOWN")+=1;
    }
}

void Stats::AddUri(const string_view& uri){
    if(UriStats.count(uri) != 0){
        UriStats.at(uri)+=1;
    }else{
        UriStats.at("unknown")+=1;
    }
}
const map<string_view, int>& Stats::GetMethodStats() const{
    return MethodStats;
}
const map<string_view, int>& Stats::GetUriStats() const{
    return UriStats;
}
//GET /order HTTP/1.1

//HttpRequest ParseRequest(string_view line){
//    size_t token_0 = 0;
//    if(line.find_first_of(" ")==0){
//        token_0 = 4;
//    }
//    size_t token_1 = line.find(" /"); //+
//    string_view a  = line.substr(token_0,token_1-token_0); //+
//    cout<< a<< endl;
//    //cout<< token_1<<endl;
//    size_t token_2 = line.find(" HTTP/");
//    //cout<< token_2<<endl;
//    string_view b  = line.substr(token_1+1,(token_2-token_1-1));
//    size_t token_3 = line.find_first_of("\n");
//    string_view c  = line.substr(token_2+1,(token_3-token_2));
//    //cout<< c<< endl;
//    return{a,b,c};
//}

HttpRequest ParseRequest(string_view line) {
  HttpRequest request;

  size_t pos = 0;
  while (line[pos] == ' ' && pos != line.npos) {
    ++pos;
  }
  line.remove_prefix(pos);

  size_t delimiter = line.find(' ');
  request.method = line.substr(0, delimiter);

  line.remove_prefix(++delimiter);
  delimiter = line.find(' ');
  request.uri = line.substr(0, delimiter);

  line.remove_prefix(++delimiter);
  request.protocol = line;

  return request;
}
