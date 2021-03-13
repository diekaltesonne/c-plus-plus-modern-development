#include <node.h>

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}

bool DateComparisonNode::Evaluate(const Date &date, const string& event) const  {
        if (_cmp == Comparison::Less) {return _date > date;
        } else if (_cmp == Comparison::LessOrEqual){return _date >= date;
        } else if (_cmp == Comparison::Greater) {return _date < date;
        } else if (_cmp == Comparison::GreaterOrEqual) {return _date <= date;
        } else if (_cmp == Comparison::Equal) {return _date == date;
        } else if (_cmp == Comparison::NotEqual){return _date != date;}
        return false;
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const  {
        if (_cmp == Comparison::Less) {
            return _event > event;

        } else if (_cmp == Comparison::LessOrEqual){
            return _event >= event;

        } else if (_cmp == Comparison::Greater){
            return _event <event;

        } else if (_cmp == Comparison::GreaterOrEqual){
            return _event <= event;
        } else if (_cmp == Comparison::Equal) {
            return _event == event;

        } else if (_cmp == Comparison::NotEqual){
            return _event != event;
        }
        return false;
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const  {
        if (_logicaloperation == LogicalOperation::Or) {
            return _left->Evaluate(date, event) || _parseexpression->Evaluate(date, event);
        } else if (_logicaloperation == LogicalOperation::And) {
            return _left->Evaluate(date, event) && _parseexpression->Evaluate(date, event);
        }
        return false;
}
