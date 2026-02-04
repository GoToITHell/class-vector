#include <iostream>
#ifndef VECTOR_H
#define VECTOR_H

template<typename dataType>
class Vector{

private:

dataType* data_;
size_t size_;
size_t capacity_;

public:

/* КОНСТРУКТОРЫ */

// Конструктор инициализации 
Vector () : data_(nullptr), size_(0), capacity_(0) {}

// геттеры

dataType* getData(){ return data_; }
size_t getSize() { return size_; }
size_t getCapacity(){ return capacity_; }


};

#endif