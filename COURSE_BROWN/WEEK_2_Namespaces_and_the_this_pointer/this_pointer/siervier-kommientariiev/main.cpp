#include "test_runner.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
//#include <optional>
#include <unordered_set>

using namespace std;
struct HttpRequest {
  string method, path, body;
  map<string, string> get_params;
};
enum class HttpCode {
  Ok = 200,
  NotFound = 404,
  Found = 302,
};

pair<string, string> SplitBy(const string& what, const string& by) {
  size_t pos = what.find(by);
  if (by.size() < what.size() && pos < what.size() - by.size()) {
    return {what.substr(0, pos), what.substr(pos + by.size())};
  } else {
    return {what, {}};
  }
}

template<typename T>
T FromString(const string& s) {
  T x;
  istringstream is(s);
  is >> x;
  return x;
}

pair<size_t, string> ParseIdAndContent(const string& body) {
  auto [id_string, content] = SplitBy(body, " ");
  return {FromString<size_t>(id_string), content};
}

struct LastCommentInfo {
  size_t user_id, consecutive_count;
};

class HttpResponse {
public:
  explicit HttpResponse(HttpCode code):code(code){

  }
  HttpResponse& AddHeader(string name, string value){
      headers.insert(make_pair(name,value));
      return *this;
  }
  HttpResponse& SetContent(string a_content){
      content = a_content;
      return *this;
  }
  HttpResponse& SetCode(HttpCode a_code){
      code = a_code;
      return *this;
  }

  friend ostream& operator << (ostream& output, const HttpResponse& resp){
      if(resp.code == HttpCode::Ok){
          output<<"HTTP/1.1 200 OK\n";
          if(resp.headers.size()!=0){
              for(auto &i :resp.headers){
                   output<<i.first<<": "<<i.second<<"\n";
              }
          }
          if(resp.content.size()!=0){
              output<<"Content-Length: "<<resp.content.size()<< "\n" << "\n";
              output<<resp.content;
          }else{
              output<<"\n";
          }

      }else if(resp.code == HttpCode::Found){
          output<<"HTTP/1.1 302 Found\n";
          if(resp.headers.size()!=0){
              for(auto &i :resp.headers){
                  output<<i.first<<": "<<i.second<<"\n";
              }
          }
          if(resp.content.size()!=0){
              output<<"Content-Length: "<<resp.content.size()<< "\n" << "\n";
              output<<resp.content;
          }else{
              output<<"\n";
          }


      }else if(resp.code == HttpCode::NotFound){
           output<<"HTTP/1.1 404 Not found\n";
           if(resp.headers.size()!=0){
               for(auto &i :resp.headers){
                   output<<i.first<<": "<<i.second<<"\n";
               }
           }
           if(resp.content.size()!=0){
               output<<"Content-Length: "<<resp.content.size()<< "\n" << "\n";
               output<<resp.content;
           }else{
               output<<"\n";
           }
      }
      return output;
  }

private:
  multimap<string, string> headers;
  string content;
  HttpCode code;
};

class CommentServer {
private:
  vector<vector<string>> comments_;
  std::optional<LastCommentInfo> last_comment;
  unordered_set<size_t> banned_users;

  //POST /add_user — добавляет нового пользователя и возвращает ответ 200 OK, в теле которого содержится идентификатор вновь
  //добавленного пользователя (см. реализацию в заготовке решения)
  HttpResponse post_add_user(){
      comments_.emplace_back();
      auto response = to_string(comments_.size()-1);
      return HttpResponse(HttpCode::Ok).SetContent(move(response));
  }
//POST /add_comment — извлекает из тела запроса идентификатор пользователя и новый комментарий; если пользователь признаётся спамером,
//возвращает 302 Found c заголовком Location: /captcha, переводя пользователя на страницу капчи,
//в противном случае сохраняет комментарий и возвращает 200 OK
  HttpResponse  post_add_comment(const HttpRequest& req){
      auto [user_id, comment] = ParseIdAndContent(req.body);
      if (!last_comment || last_comment->user_id != user_id) {
        last_comment = LastCommentInfo {user_id, 1};
      } else if (++last_comment->consecutive_count > 3) {
        banned_users.insert(user_id);
      }

      if (banned_users.count(user_id) == 0) {
        comments_[user_id].push_back(string(comment));
        return HttpResponse(HttpCode::Ok);
      } else {
        return HttpResponse(HttpCode::Found).AddHeader("Location","/captcha");
      }
        return HttpResponse(HttpCode::Ok);
  }

//POST /checkcaptcha — извлекает из тела запроса ответ на вопрос капчи; если он верен, разблокирует пользователя и возвращает 200 OK,
//если нет — возвращает 302 Found c заголовком Location: /captcha
  HttpResponse post_checkcaptcha(const HttpRequest& req){
      if (auto [id, response] = ParseIdAndContent(req.body); response == "42") {
        banned_users.erase(id);
        if (last_comment && last_comment->user_id == id) {
          last_comment.reset();
        }
        return HttpResponse(HttpCode::Ok);
      }
      return HttpResponse(HttpCode::Found).AddHeader("Location","/captcha");;
  }
//если метод запроса не POST и не GET или путь запроса не совпадает
//ни с одним из вышеперечисленных, сервер отвечает 404 Not found.
  HttpResponse not_found(){
      return HttpResponse(HttpCode::NotFound);
      //os << "HTTP/1.1 404 Not found\n\n";
  }
//GET /user_comments?user_id=[id] — возвращает ответ 200 OK, в теле которого содержатся все комментарии пользователя id, разделённые переводом строки
  HttpResponse get_user_comments(const HttpRequest& req){
      auto user_id = FromString<size_t>(req.get_params.at("user_id"));
      string response;
      for (const string& c : comments_[user_id]) {
        response += c + '\n';
      }
      //return HttpResponse(HttpCode::Ok).AddHeader("Content-Length",to_string(response.size())).SetContent(move(response));
      return HttpResponse(HttpCode::Ok).SetContent(move(response));
  }

//GET /captcha — возвращает ответ 200 OK, в теле которого содержится страница капчи
//(для простоты в этой задаче мы просто возвращаем вопрос, на который надо ответить пользователю, на практике это может быть полноценная HTML-страница)
  HttpResponse get_captcha(){
       return HttpResponse(HttpCode::Ok).SetContent( "What's the answer for The Ultimate Question of Life, the Universe, and Everything?");
  }

public:
      HttpResponse ServeRequest(const HttpRequest& req){
          HttpResponse result(HttpCode::NotFound);
          if(req.method == "POST") {
              if (req.path == "/add_user"){
                  result = post_add_user();
              }else if (req.path == "/add_comment"){
                  result = post_add_comment(req);
              } else if (req.path == "/checkcaptcha") {
                      result = post_checkcaptcha(req);
              }else{
                  result = not_found();
              }
          }else if (req.method == "GET") {
              if (req.path == "/user_comments") {
                  result = get_user_comments(req);
              }else if (req.path == "/captcha") {
                  result = get_captcha();
              } else {
                  result = not_found();
              }
          }
          return result;
      }    
      void ServeRequest(const HttpRequest& req, ostream& os) {
          os<<ServeRequest(req);
      }
};

struct HttpHeader {
  string name, value;
};

ostream& operator<<(ostream& output, const HttpHeader& h) {
  return output << h.name << ": " << h.value;
}

bool operator==(const HttpHeader& lhs, const HttpHeader& rhs) {
  return lhs.name == rhs.name && lhs.value == rhs.value;
}


struct ParsedResponse {
      int code;
      vector<HttpHeader> headers;
      string content;
};

istream& operator >>(istream& input, ParsedResponse& r) {
      string line;
      getline(input, line);

      {
        istringstream code_input(line);
        string dummy;
        code_input >> dummy >> r.code;
      }

      size_t content_length = 0;

      r.headers.clear();
      while (getline(input, line) && !line.empty()) {
        if (auto [name, value] = SplitBy(line, ": "); name == "Content-Length") {
          istringstream length_input(value);
          length_input >> content_length;
        } else {
          r.headers.push_back( {std::move(name), std::move(value)});
        }
      }

      r.content.resize(content_length);
      input.read(r.content.data(), r.content.size());
      return input;
}

void Test(CommentServer& srv, const HttpRequest& request, const ParsedResponse& expected) {
  stringstream ss;
  srv.ServeRequest(request, ss);
  ParsedResponse resp;
  ss >> resp;
  cout<<ss.str();
  ASSERT_EQUAL(resp.code, expected.code);
  ASSERT_EQUAL(resp.headers, expected.headers);
  ASSERT_EQUAL(resp.content, expected.content);
}

template <typename CommentServer>
void TestServer() {
  CommentServer cs;
  const ParsedResponse ok{200};
  const ParsedResponse redirect_to_captcha{302, {{"Location", "/captcha"}}, {}};
  const ParsedResponse not_found{404};
  Test(cs, {"POST", "/add_user"}, {200, {}, "0"});
  Test(cs, {"POST", "/add_user"}, {200, {}, "1"});
  Test(cs, {"POST", "/add_comment", "0 Hello"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Hi"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Enlarge"}, ok);

  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);
  Test(cs, {"POST", "/add_comment", "0 What are you selling?"}, ok);
  Test(cs, {"POST", "/add_comment", "1 Buy my goods"}, redirect_to_captcha);

  Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "0"}}},
    {200, {}, "Hello\nWhat are you selling?\n"}
  );

  Test(
    cs,
    {"GET", "/user_comments", "", {{"user_id", "1"}}},
    {200, {}, "Hi\nBuy my goods\nEnlarge\n"}
  );

//  Test(
//    cs,
//    {"GET", "/captcha"},
//    {200, {}, {"What's the answer for The Ultimate Question of Life, the Universe, and Everything?"}}
//  );
//  Test(cs, {"POST", "/checkcaptcha", "1 24"}, redirect_to_captcha);
//  Test(cs, {"POST", "/checkcaptcha", "1 42"}, ok);
//  Test(cs, {"POST", "/add_comment", "1 Sorry! No spam any more"}, ok);
//  Test(
//    cs,
//    {"GET", "/user_comments", "", {{"user_id", "1"}}},
//    {200, {}, "Hi\nBuy my goods\nEnlarge\nSorry! No spam any more\n"}
//  );

//  Test(cs, {"GET", "/user_commntes"}, not_found);
//  Test(cs, {"POST", "/add_uesr"}, not_found);
//
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestServer<CommentServer>);
}


