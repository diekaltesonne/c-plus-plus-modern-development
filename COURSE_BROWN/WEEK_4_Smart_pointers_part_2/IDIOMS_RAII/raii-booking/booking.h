#include <stdexcept>
namespace RAII
{

template <class Provider>
class Booking
{
public:
  Booking(Provider * prov , int )
    : p(std::move(prov))
  {
  }
  Booking() = delete;
  Booking(const Booking & other) = delete;
  Booking(Booking && other): p(std::move(other.p)){
    other.p = nullptr;
  }
  Booking& operator=(const Booking& other) = delete;
  Booking& operator=(Booking && other){
    if (p != nullptr){
        p->CancelOrComplete(*this);
    }
    p = (std::move(other.p));//adasdasdasd
    other.p = nullptr;
    return *    this;

  }

  ~Booking(){
    if (p != nullptr){
      p->CancelOrComplete(*this);
    }
  }

private:
  Provider * p;
};

}


//template <typename T>
//class Booking{
//public:
//    Booking() = delete;
//    Booking(const Booking & other) = delete;
//    Booking& operator=(const Booking& other) = delete;

//    Booking(T* provider,int counter):provider_(provider),counter_(counter){
//        if(provider_->capacity<= counter_){
//            if(counter_!=0){
//            provider_->CancelOrComplete(*this);}
//            throw std::runtime_error("Hotel overbooking");
//        }
//    }

//    Booking(Booking && other):provider_(std::move(other.provider_)){
//        other.provider_=nullptr;
//    }

//    Booking& operator=(Booking && other){
//        if (provider_ != nullptr){
//            provider_->CancelOrComplete(*this);
//        }
//        provider_ =(std::move(other.provider_));
//        other.provider_ = nullptr;
//        return *this;
//    }

//    ~Booking(){
//        if(provider_->counter!=0){
//        provider_->CancelOrComplete(*this);
//        }
//    }

//private:
//    T* provider_;
//    int counter_;

//};
