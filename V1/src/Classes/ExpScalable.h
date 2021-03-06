#ifndef EXPSCALABLE_H
#define EXPSCALABLE_H

#include "Scalable.h"

//Class for applying exponential transform to data
//y = a*exp(x) + b
//Derived from Scalable.h
template <class T>
class ExpScalable: public Scalable<T>{
private:
  T a;
  T b;

public:
  //class constructors
  ExpScalable(){this->set_params();};
  ExpScalable(T a){this->set_params(a);}; //b defaults to 0
  ExpScalable(T a, T b){this->set_params(a, b);};

  //applies Scale
  T scale(T value) {
    return (a*exp(value)) + b;
  };

  //for changing the parameters
  void set_params(T a=1, T b=0) {
    this->a = a;
    this->b = b;
  };
};

#endif
