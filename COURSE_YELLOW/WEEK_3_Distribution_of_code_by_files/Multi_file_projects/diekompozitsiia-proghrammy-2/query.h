#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#ifndef QUERY_H
#define QUERY_H
enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};
struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};
istream& operator >> (istream& is, Query& q);
#endif // QUERY_H

