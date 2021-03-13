#include "test_runner.h"
#include <iostream>
#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
// Напишите реализацию функции, не копируя объекты типа Token
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    if (tokens.empty())
    {
        return vector<Sentence<Token>>() ;
    }
    size_t last_element_index = tokens.size() - 1;
    vector<Sentence<Token>> result;
    Sentence<Token> sentence;
    int k1 = 0;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if(tokens[i].IsEndSentencePunctuation()){
            if(i ==  last_element_index ){
                sentence.push_back(move(tokens[i]));
                result.push_back(move(sentence));
                sentence.clear();
            }else{
                sentence.push_back(move(tokens[i]));
                k1++;

            }
        }else{
            if(k1>0){
                result.push_back(move(sentence));
                sentence.clear();
                k1 = 0 ;
            }
            //cout<<"OK"<<endl;
            sentence.push_back(move(tokens[i]));
        }
    }
    if( sentence.size() > 0){
        // cout<<"Suck"<<endl;
        result.push_back(move(sentence));
        sentence.clear();
    }
    return result;
}



ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
  );

  ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
  );
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSplitting);
  return 0;
}
