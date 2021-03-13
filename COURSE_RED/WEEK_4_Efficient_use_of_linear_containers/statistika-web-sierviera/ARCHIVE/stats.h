#pragma once
#include "http_request.h"
#include <string_view>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

class Stats {
public:
  void AddMethod(const string_view& method);
  void AddUri(const string_view& uri);
  const map<string_view, int>& GetMethodStats() const;
  const map<string_view, int>& GetUriStats() const;
private:
//Таким образом, наш web-сервер поддерживает 4 метода: GET, POST, PUT, DELETE и 5 URI: «/», «/order», «/product», «/basket», «/help».
map<string_view, int> MethodStats = {{"GET",0},{"POST",0},{"PUT",0},{"DELETE",0},{"UNKNOWN",0}};
map<string_view, int> UriStats = {{"/",0},{"/order",0},{"/product",0},{"/basket",0},{"/help",0},{"unknown",0}};
};

HttpRequest ParseRequest(string_view line);
