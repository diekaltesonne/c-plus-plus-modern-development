#pragma once

#include <cstdlib>
#include <algorithm>

using namespace std;

// Реализуйте шаблон SimpleVector
template <typename T>

class SimpleVector {
public:
  SimpleVector(): data(nullptr), _end(nullptr), capacity(0), _size(0){}


  explicit SimpleVector(size_t size){
      data = new T[size];
      _end = data + size;
      capacity = size;
      _size = size;
  }

  ~SimpleVector(){
      delete[] data;
  }

  T& operator[](size_t index){
      return data[index];
  }
  const T& operator[](size_t index) const {
        return data[index];
  }
  const T* begin()const{return data;}
  const T* end()  const{return _end;}
  T* begin(){return data;}
  T* end(){return _end;}


  size_t Size() const {
        return _size;
  }
  size_t Capacity() const {
        return capacity;
  }

  void PushBack(const T& value){
      if(capacity == 0) {
          data = new T[1];
          _end = data + 1;
          capacity = 1;
          _size = 1;
          *data = value;
        }else{

          if(Size() == Capacity()) {
              capacity *= 2;
              T* copy_data = new T[capacity];
              copy(data,_end, copy_data);
              delete[] data;
              data = copy_data;
            }
            data[_size] = value;
            _size++;
            _end = data + _size;
        }
    }
private:
  T* data;
  T* _end;
  size_t capacity;
  size_t _size;
};
