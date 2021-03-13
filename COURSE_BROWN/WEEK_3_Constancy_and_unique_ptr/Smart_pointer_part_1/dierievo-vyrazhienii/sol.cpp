#include "Common.h"
#include <iostream>


class Real_Expression:public Expression{
public:
    Real_Expression(int value):value(std::move(value)){
    }
    int Evaluate()const{
        return value;
    }
    std::string ToString() const{
        return std::to_string(value);

    }
private:
    int value;

};

class Sum_Expression:public Expression{
public:
    Sum_Expression(ExpressionPtr left, ExpressionPtr right):left_(std::move(left)),right_(std::move(right)){

    }
    int Evaluate()const{
        return left_.get()->Evaluate()+right_.get()->Evaluate();
    }


    std::string ToString() const{
            return "("+left_.get()->ToString()+")"+"+"+"("+right_.get()->ToString()+")";



    }
private:
    ExpressionPtr left_;
    ExpressionPtr right_;
};

class Product_Expression:public Expression{
public:
    Product_Expression(ExpressionPtr left, ExpressionPtr right):left_(std::move(left)),right_(std::move(right)){
    }
    int Evaluate()const{
        return left_.get()->Evaluate()*right_.get()->Evaluate();

    }
    std::string ToString() const{
            return  "("+left_.get()->ToString()+")"+"*"+"("+right_.get()->ToString()+")";

    }
private:
    ExpressionPtr left_;
    ExpressionPtr right_;
};


// Функции для формирования выражения
ExpressionPtr Value(int value){
    return std::make_unique<Real_Expression>(value);
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right){
    return  std::make_unique<Sum_Expression>(std::move(left),std::move(right));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right){
    ExpressionPtr x = std::make_unique<Product_Expression>(std::move(left),std::move(right));
    return  std::move(x);
}
