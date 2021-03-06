#ifndef IO_H
#define IO_H

// Multi inheritance is bad, but whatever :(
// Private inheritance means the functions inherited can only be used internally
#include <string>
#include <sstream>
#include <iomanip>
#include <mbed.h>

#include "Printable.h"

class IO: public Printable{
private:
  string __name;
  Mutex mu;
public:
  //constructor
  IO(string name)
  {
    mu.lock();
    this->__name = name;
    mu.unlock();
  };

  void set_name(string name)
  {
    mu.lock();
    this->__name = name;
    mu.unlock();
  };

  string get_name()
  {
    return this->__name;
  };

  void lock()
  {
    mu.lock();
  };

  void unlock()
  {
    mu.unlock();
  };

  string toString()
  {
    return this->get_name();
  };

  string toStringInfo()
  {
    return this->get_name();
  };

  string toStringHeader()
  {
    return this->get_name();
  };

  string toJsonObject()
  {
    return "";
  };
};

#endif
