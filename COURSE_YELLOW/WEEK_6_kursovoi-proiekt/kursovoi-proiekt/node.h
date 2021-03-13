#pragma once
#include <token.h>
#include <date.h>
#include <memory>


enum class Comparison {
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  PAREN_LEFT,
  NotEqual,
};

enum class LogicalOperation{
    Or,
    And,
};



class Node{
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;

private:

};

//UNDONE
class EmptyNode: public Node{
public:
    EmptyNode(){}
    bool Evaluate(const Date& date, const string& event) const override;
private:
};


class DateComparisonNode:public Node {
public:
    DateComparisonNode(const Comparison &cmp, const Date &date):_cmp(cmp),_date(date){}

    bool Evaluate(const Date &date, const string& event) const override;
private:
    const Comparison _cmp;
    const Date _date;
};


class EventComparisonNode: public Node{
public:
    EventComparisonNode(const Comparison &cmp, const string &event):_cmp(cmp),_event(event){}
    bool Evaluate(const Date& date, const string& event) const override;

private:
    const Comparison _cmp;
    const string _event;
};

//какая то херозина
class LogicalOperationNode: public Node{
public:

    LogicalOperationNode(const LogicalOperation &logicaloperation, shared_ptr < const Node> left,
                          shared_ptr< const Node> parseexpression):_logicaloperation(logicaloperation),
    _left(left), _parseexpression(parseexpression){}
    bool Evaluate(const Date& date, const string& event) const override;

private:
    const LogicalOperation _logicaloperation;
    shared_ptr<const Node> _left, _parseexpression;
};


