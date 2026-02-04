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

/* конструкторы */

// Конструктор инициализации 
Vector (): data_(nullptr), size_(0), capacity_(0) {}

// Конструктор инициализации с параметрами
Vector (const  dataType& data): data_(nullptr), size_(0), capacity_(0) {
    try
    {
        if (data){
          size_ = 1;// функция нахождения длины
          capacity_ = size_*2 + 1;
          data_ = new dataType[capacity_];
          (data_, data) // процедура передачи данных 

        }
    }
    catch(const std::bad_alloc& e)
    {
        throw std::runtime_error("Memory allocation failed in array (constructor)::reallocate");
    }
    

}

// Конструктор копирования
Vector (const Vector& other) : data_(nullptr), size_(0), capacity_(0){
    try
    {
        if (other.data_){
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new dataType[capacity_];
            (data_, other.data_) // процкедура передачи данных


        }
    }
    catch(const std::bad_alloc& e){

        throw std::runtime_error("Memory allocation failed in array (constructor)::reallocate");
    }
    
}


// Конструктор перемещения 
Vector(Vector&& other) noexcept : data_(nullptr), size_(0), capacity_(0){
    swap(other); // процедура swap
    
}

// Десктруктор 
~Vector() noexcept {
    delete[] data_;
}

// геттеры

dataType* getData(){ return data_; }
size_t getSize() { return size_; }
size_t getCapacity(){ return capacity_; }


};

#endif