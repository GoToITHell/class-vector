#ifndef VECTOR_HPP
#define VECTOR_HPP

#include<iostream>
#include<stdexcept>
#include <type_traits> 

template<typename T>
class Vector {
private:

	T* data_; 
	size_t size_; 
	size_t capacity_;

public:

    // Kонструктор инициализации
	Vector() :data_(nullptr), size_(0),  capacity_(0){ }

    // Кoнструктор инициализации с параметром
	explicit Vector(size_t getSize) : data_(new T[getSize]),  size_(getSize), capacity_(getSize) {
		for (size_t i = 0; i < size_; i++) {
			data_[i] = T();
		}
	}

    // Кoнструктор инициализации с параметрами
	Vector(size_t getSize, const T& value) : data_(new T[getSize]),  size_(getSize), capacity_(getSize)
	{
		for (size_t i = 0; i < size_; i++) {
			data_[i] = value;
		}
	}
    // добавить исключение!!!
    
    // Конструкор копирования
	Vector(const Vector& other) : data_(nullptr), size_(0), capacity_(0)
	{
        try
        {
            if (other.data_){
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new T[capacity_];
            for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
            }
		}
        }
        catch(const std::bad_alloc& e)
        {
            throw ("FATAL ERROR! memory allocation error");
        } 
	}

    // Конструктор перемещения 
	Vector(Vector&& other) noexcept :  data_(nullptr), size_(0), capacity_(0)
	{
        swap(other);
	}

    // Деструктор 
	~Vector() {
		delete[] data_;
	}



    /*  ОПЕРАТОРЫ ПРИСВАИВАНИЯ  */

// Оператор копирования
Vector& operator=(const Vector& other) {
    Vector tmp(other);
    this->swap(tmp);
    return *this;
}

// Оператор перемещения
Vector& operator=(Vector&& other) noexcept {
    if (this != &other) {
        Vector tmp(std::move(other)); 
        this->swap(tmp);
    }
    return *this;
}

    // геттеры
	size_t getSize() const  {return size_;}
	size_t getCapacity() const  {return capacity_;}
	bool isEmpty() const noexcept {return size_ == 0;}

    /*  ДОСТУП К ЭЛЕМЕНТАМ  */

    // индексирование
	T& operator[](size_t index) {
		return data_[index];
	}

    // константное индексирование
	const T& operator[] (size_t index) const {
		return data_[index];
	}

    // индексирование с проверкой
	T& at(size_t index) {
		if (index >= size_) {
			 throw std::out_of_range("Index out of range");
		}
		return data_[index];
		
	}

    // константное индексирование с проверкой
	const T& at(size_t index) const {
		if (index >= size_) {
			throw std::out_of_range("Index out of range");
		}
        return data_[index];
	}

    // return первый элемент
	T& front() {
         if (isEmpty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[0];
    }

    // return последний элемент
	T& back() {
         if (isEmpty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[size_ - 1];
    }

    // return первый элемент константно 
	const T& front() const {
         if (isEmpty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[0]; 
    }

    // return последний элемент константно
	const T& back() const { 
         if (isEmpty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[size_ - 1]; 
    }

      /*  ВСТАВКА ЭЛЕМЕНТОВ  */

    //Копирующая вставка ищмен
	void push_back(const T& value) {
        size_t oldCapacity = capacity_;
        size_t oldSize = size_;
        try
        {
            oldCapacity = capacity_;
            setNewCapacity();
		    data_[size_] = value;  
		    size_++;
        }
        catch(const std::exception& e)
        {
            reserve(oldCapacity);
            if (size_ != oldSize) {
                data_[oldSize].~T();
                size_ = oldSize;
            }
            throw std::runtime_error("Error in push_back method!");
        }      
	}

    // Перемещающая вставка
	void push_back(T&& value) {
        size_t oldCapacity = capacity_;
        size_t oldSize = size_;
        try
        {
            setNewCapacity();
		    data_[size_] = std::move(value);  
		    size_++;
        }
        catch(const std::exception& e)
        {
            reserve(oldCapacity);
            if (size_ != oldSize) {
                data_[oldSize].~T();
                size_ = oldSize;
            }
            throw std::runtime_error("Error in push_back method!");
        }
	}

    // Вставка в произвольную позицию
	void insert(size_t index, const T& value) {
       
		if (index >= size_) { 
            throw std::out_of_range("Index out of range!");
        }
         try
        {
			setNewCapacity();
			for (size_t i = size_; i > index; i--) {
				data_[i] = std::move(data_[i - 1]);
			}
			data_[index] = value;
			size_++;
        }
        catch(const std::exception& e)
        {
            throw std::runtime_error("Error in insert method!");
        }
	}

    // Перемещающая вставка
	void insert(size_t index, T&& value) {
        
        if (index > size_) { 
            throw std::out_of_range("Index out of range!");
        }
        try
        {
		setNewCapacity();
		for (size_t i = size_; i > index; --i) {
			data_[i] = std::move((data_[i - 1]));
		}
		    data_[index] = std::move(value);
		    size_++;	
        }
        catch(const std::exception& e)
        {
            throw std::runtime_error("Error in insert method!");
        }
        
			
	}

   /*  УДАЛЕНИЕ ЭЛЕМЕНТОВ  */

    // удаление последнего элемента
    void pop_back() {
        if (isEmpty()) {
            throw std::out_of_range("Vector is empty");
        }
        if  (!std::is_trivially_destructible<T>::value) {
        data_[size_ - 1].~T();
    }
        size_--;
    }

    // удаление всех элементов
	void clear() {
        if (isEmpty()) {
            throw std::out_of_range("Vector is empty");
        }
        if  (!std::is_trivially_destructible<T>::value){
        for (size_t i = 0; i < size_; i++) {
            data_[i].~T();
        }
    }
        size_ = 0;
    }



    //  удаление элемента по индексу
	void erase(size_t index) {
        
		if (index >= size_) { 
            throw std::out_of_range("Index out of range!");
        }
        try
        {
			for (size_t i = index+1; i < size_; i++) {
				data_[i-1] = std::move(data_[i]);
			}
			if  (!std::is_trivially_destructible<T>::value) {
        data_[size_ - 1].~T();
        }
        size_--;          
        }
        catch(const std::exception& e)
        {
            throw std::runtime_error("Error in erase method!");
        }
        

	}

    // удаление промежутка
	void erase(size_t first, size_t last) {
        
		if (first > last || last > size_) {
            throw std::out_of_range("Index out of range!");}
         
        try
        {
			size_t count = last - first;
			if (count == 0) {
				return;
			}
			for (size_t i = last; i < size_; i++) {
				data_[i - count] = std::move(data_[i]);
                
		} 
        if  (!std::is_trivially_destructible<T>::value) {
            for (size_t i = size_ - count; i < size_; i++) {
            data_[i].~T();
            }
        }
			size_ -= count;
         }
         catch(const std::exception& e)
         {
            throw std::runtime_error("Error in erase method!");
         }
         
	}

    /*  ИЗМЕНЕНИЕ РАЗМЕРА  */

    // изменение размера
	void resize(size_t newSize) {
		if (newSize == size_) {
			return;
		}
		if (newSize < size_) {
			size_ = newSize;
		}
		if (newSize > size_) {
			reserve(newSize);
			for (size_t i = size_; i < newSize; i++) {
				data_[i] = T();
			}
			size_ = newSize;
		}
	}

    // Изменение размера с указанием значения
	void resize(size_t new_size, const T& value) {
		if (new_size == size_) {
			return;
		}
		if (new_size < size_) {
			size_ = new_size;
		}
		if (new_size > size_) {
			reserve(new_size);
			for (size_t i = size_; i < new_size; i++) {
				data_[i] = value;
			}
			size_ = new_size;
		}

	}

    // Резервирование памяти
	void reserve(size_t newCapacity) {

		if (newCapacity <= capacity_) {
			return;
		}
        try
        {
            T* temp = new T[newCapacity];
			for (size_t i = 0; i < size_; i++) {
				temp[i] = std::move(data_[i]);
			}
            capacity_ = newCapacity;
			delete[] data_;
			data_ = temp;  
        }
        catch(const std::bad_alloc& e)
        {
            throw ("memory allocation error!");
        }
	}

    // Уменьшение capacity до size
	void shrink_to_fit() {
		if (capacity_ > size_) {
            try
            {
                T* temp = new T[size_];
			    for (size_t i = 0; i < size_; i++) {
				    temp[i] = std::move(data_[i]);
			    }
                capacity_ = size_;
			    delete[] data_;
			    data_ = temp;
            }
            catch(const std::bad_alloc& e)
            {
                throw ("memory allocation error!");
            }
        }
	}


    /*  ОПЕРАТОРЫ СРАВНЕНИЯ  */

    bool operator==(const Vector& other) const {
        if (size_ != other.size_) return false;
        for (size_t i = 0; i < size_; i++) {
            if (data_[i] != other.data_[i]) return false;
        }
        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    bool operator<(const Vector& other) const {
        size_t minSize = std::min(size_, other.size_);
        for (size_t i = 0; i < minSize; i++) {
            if (data_[i] < other.data_[i]) return true;
            if (other.data_[i] < data_[i]) return false;
        }
        return size_ < other.size_;
    }

    bool operator<=(const Vector& other) const {
        return !(other < *this);
    }
    
    bool operator>(const Vector& other) const {
        return other < *this;
    }

    bool operator>=(const Vector& other) const {
        return !(*this < other);
    }


	//swap
	void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
		std::swap(capacity_, other.capacity_);
	}

    // проверка на корректное capacity
    void setNewCapacity(){
    	if (size_ == capacity_) {
		size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
		reserve(new_capacity);
	}
}
};


#endif







//     //  оператор присваения
// Vector& operator=(Vector&& other) noexcept {
//     if (this != &other) {
//         Vector tmp(std::move(other));  // Создаем временный объект из other
//         swap(tmp);                      // Обмениваемся с временным объектом
//         // tmp удалится автоматически с нашими старыми данными
//     }
//     return *this;
// }