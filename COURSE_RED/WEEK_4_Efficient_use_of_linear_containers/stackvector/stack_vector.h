#pragma once
#include <array>
#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0) : _size(a_size){
    if (_size > N) {
        throw invalid_argument("Too much");
    }
  }
  T& operator[](size_t index){
    return data[index];
  }
  const T& operator[](size_t index) const {
        return data[index];
  }
  const T& begin()const{return data.begin();}//?
  const T& end()  const{return data.begin()+_size;}//?
  T& begin(){return data;}//?
  T& end(){return data.begin()+_size;;}//?
  size_t Size() const {
        return _size;
  }
  size_t Capacity() const {
        return N;
  }

  void PushBack(const T& value) {
      if (_size >= N) {
        throw overflow_error("Full");
      } else {
        data[_size++] = value;
      }
    }

    T PopBack() {
      if (_size == 0) {
        throw underflow_error("Empty");
      } else {
        --_size;
        return data[_size];
      }
    }

private:
  array<T,N> data;
  size_t _size;
};
