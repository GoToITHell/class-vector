// #include <iostream>
// #include <initializer_list>
// #ifndef VECTOR_HPP
// #define VECTOR_HPP
// template<typename dataType>
// class Vector {
// private:
//     dataType* data_;
//     size_t size_;
//     size_t capacity_;

// public:
//     /*  КОНСТРУКТОРЫ  */
    
//     // Конструктор инициализации
//     Vector() noexcept : data_(nullptr), size_(0), capacity_(0) {}
    
//     // Конструктор инициализации с параметром size
//      Vector(size_t n) : data_(nullptr), size_(n), capacity_(n * 2) {
//         if (n > 0) {
//             try {
//                 data_ = new dataType[capacity_];
//                 for (size_t i = 0; i < size_; i++) {
//                     data_[i] = dataType{};
//                 }
//             } catch (const std::bad_alloc& e) {
//                 throw std::runtime_error("Memory allocation failed");
//             }
//         }
//     }
    
//     // Конструктор инициализации с параметрами
//     Vector(size_t n, const dataType& value) : data_(nullptr), size_(n), capacity_(n*2) {
//         if (n > 0) {
//             try {
//                 data_ = new dataType[capacity_];
//                 for (size_t i = 0; i < size_; i++) {
//                     data_[i] = value;
//                 }
//             } catch (const std::bad_alloc& e) {
//                 throw std::runtime_error("Memory allocation failed");
//             }
//         }
//     }
    
//     // Конструктор valueializer_list
//  Vector(std::initializer_list<dataType> value) : data_(nullptr), size_(value.size()), capacity_(value.size()*2) {  
//     if (value.size() > 0) {
//         size_ = value.size();
//         capacity_ = value.size() * 2;  
//         try {
//             data_ = new dataType[capacity_];
//             size_t i = 0;
//             for (const auto& item : value) {
//                 data_[i] = item; 
//                 i++;
//             }
//         } catch (const std::exception& e) {
//             delete[] data_;
//             data_ = nullptr;
//             size_ = 0;
//             capacity_ = 0;
//             throw std::runtime_error("Memory allocation failed");
//         }
//     }
// }
  
//     // Конструктор копирования
//     Vector(const Vector& other) : data_(nullptr), size_(0), capacity_(0) {
//         if (other.data_ && other.size_ > 0) {
//             size_ = other.size_;
//             capacity_ = other.capacity_;
//             try {
//                 data_ = new dataType[capacity_];
//                 for (size_t i = 0; i < size_; i++) {
//                     data_[i] = other.data_[i];
//                 }
//             } catch (const std::bad_alloc& e) {
//                 throw std::runtime_error("Memory allocation failed");
//             }
//         }
//     }
    
//     // Конструктор перемещения через swap
//     Vector(Vector&& other) noexcept : Vector() { 
//         swap(other);
//     }
    
//     // Деструктор
//     ~Vector() noexcept {
//         delete[] data_;
//     }
    
//     /*  ГЕТТЕРЫ  */
    
//     dataType* getData() { return data_; }
//     const dataType* getData() const { return data_; }
//     size_t getSize() const { return size_; }
//     size_t getCapacity() const { return capacity_; }
//     bool empty() const noexcept { return size_ == 0; }
    

//     /*  ОПЕРАТОРЫ ПРИСВАИВАНИЯ  */
    
//     // Оператор копирующего присваивания
//     Vector& operator=(const Vector& other) {
//         if (this != &other) {
//             Vector temp(other);
//             swap(temp);
//         }
//         return *this;
//     }
    
//     // Оператор перемещающего присваивания
//     Vector& operator=(Vector&& other) noexcept {
//         if (this != &other) {
//             swap(other);  
//         }
//         return *this;
//     }
    
//     // Оператор присваивания из valueializer
//     Vector& operator=(std::initializer_list<dataType> value) {
//         Vector temp(value);
//         swap(temp);
//         return *this;
//     }
    
//     /*  МЕТОД SWAP  */
    
//     void swap(Vector& other) noexcept {
//         std::swap(data_, other.data_);
//         std::swap(size_, other.size_);
//         std::swap(capacity_, other.capacity_);
//     }
    
//     /*  ДОСТУП К ЭЛЕМЕНТАМ  */
    
//     // Доступ без проверки границ
//     dataType& operator[](size_t index) {
//         return data_[index];
//     }
    
//     const dataType& operator[](size_t index) const {
//         return data_[index];
//     }
    
//     // Доступ с проверкой границ
//     dataType& at(size_t index) {
//         if (index >= size_) {
//             throw std::out_of_range("Index out of range");
//         }
//         return data_[index];
//     }
    
//     const dataType& at(size_t index) const {
//         if (index >= size_) {
//             throw std::out_of_range("Index out of range");
//         }
//         return data_[index];
//     }
    
//     // Ссылка на первый элемент
//     dataType& front() {
//         if (empty()) {
//             throw std::out_of_range("Vector is empty");
//         }
//         return data_[0];
//     }
    
//     const dataType& front() const {
//         if (empty()) {
//             throw std::out_of_range("Vector is empty");
//         }
//         return data_[0];
//     }
    
//     // Ссылка на последний элемент
//     dataType& back() {
//         if (empty()) {
//             throw std::out_of_range("Vector is empty");
//         }
//         return data_[size_ - 1];
//     }
    
//     const dataType& back() const {
//         if (empty()) {
//             throw std::out_of_range("Vector is empty");
//         }
//         return data_[size_ - 1];
//     }
    
//     /*  ВСТАВКА ЭЛЕМЕНТОВ  */
    
//     // Копирующая вставка
//     void push_back(const dataType& value) {
//         if (size_ >= capacity_) {
//             reserve(capacity_ * 2);
//         }
//         data_[size_] = value;
//         size_++;
//     }
    
//     // Перемещающая вставка
//     void push_back(dataType&& value) {
//         if (size_ >= capacity_) {
//             reserve(capacity_ * 2);
//         }
//         data_[size_] = std::move(value);
//         size_++;
//     }
    
//     // Вставка в произвольную позицию
//     void insert(size_t index, const dataType& value) {
//         if (index > size_) {
//             throw std::out_of_range("Index out of range");
//         }
//         if (size_ >= capacity_) {
//             reserve(capacity_ * 2);
//         }
//         for (size_t i = size_; i > index; --i) {
//             data_[i] = std::move(data_[i - 1]);
//         }
//         data_[index] = value;
//         size_++;
//     }
    
//     // Вставка в произвольную позицию (перемещающая)
//     void insert(size_t index, dataType&& value) {
//         if (index > size_) {
//             throw std::out_of_range("Index out of range");
//         }
//         if (size_ >= capacity_) {
//             reserve(capacity_ * 2);
//         }
//         for (size_t i = size_; i > index; --i) {
//             data_[i] = std::move(data_[i - 1]);
//         }
//         data_[index] = std::move(value);
//         size_++;
//     }
    
//     /*  УДАЛЕНИЕ ЭЛЕМЕНТОВ  */
    
//     // Удаление последнего элемента
//     void pop_back() {
//         if (empty()) {
//             throw std::runtime_error("Vector is empty");
//         }
//         data_[size_ - 1].~dataType();
//         size_--;
//     }
    
//     // Удаление всех элементов
//     void clear() {
//         for (size_t i = 0; i < size_; i++) {
//             data_[i].~dataType();
//         }
//         size_ = 0;
//     }
    
//     // Удаление элемента по индексу
//     void erase(size_t index) {
//         if (index >= size_) {
//             throw std::out_of_range("Index out of range");
//         }
//         data_[index].~dataType();
//         for (size_t i = index; i < size_ - 1; i++) {
//             data_[i] = std::move(data_[i + 1]);
//         }
//         if (size_ > 0) {
//             data_[size_ - 1].~dataType();
//         }
//         size_--;
//     }
    
//     // Удаление диапазона [first, last)
//     void erase(size_t first, size_t last) {
//         if (first > last || last > size_) {
//             throw std::out_of_range("Invalid range");
//         }
        
//         size_t count = last - first;
//         if (count == 0) return;

//         for (size_t i = first; i < last; i++) {
//             data_[i].~dataType();
//         }
        
//         for (size_t i = first; i < size_ - count; i++) {
//             data_[i] = std::move(data_[i + count]);
//         }

//         for (size_t i = size_ - count; i < size_; i++) {
//             data_[i].~dataType();
//         }
        
//         size_ -= count;
//     }
    
//     /*  ИЗМЕНЕНИЕ РАЗМЕРА  */
    
//     // Изменение размера
//     void resize(size_t newSize) {
//         if (newSize < size_) {
//             for (size_t i = newSize; i < size_; i++) {
//                 data_[i].~dataType();
//             }
//             size_ = newSize;
//         } else if (newSize > size_) {
//             if (newSize > capacity_) {
//                 reserve(newSize);
//             }
//             for (size_t i = size_; i < newSize; i++) {
//                 data_[i] = dataType{};
//             }
//             size_ = newSize;
//         }
//     }
    
//     // Изменение размера с указанием значения
//     void resize(size_t newSize, const dataType& value) {
//         if (newSize < size_) {
//             for (size_t i = newSize; i < size_; i++) {
//                 data_[i].~dataType();
//             }
//             size_ = newSize;
//         } else if (newSize > size_) {
//             if (newSize > capacity_) {
//                 reserve(newSize);
//             }
//             for (size_t i = size_; i < newSize; i++) {
//                 data_[i] = value;
//             }
//             size_ = newSize;
//         }
//     }
    
//     // Резервирование памяти
//     void reserve(size_t newCapacity) {
//     if (newCapacity <= capacity_) return;


//     Vector<dataType> temp;
//     temp.data_ = new dataType[newCapacity];
//     temp.capacity_ = newCapacity;
    
//     try {
//         for (size_t i = 0; i < size_; i++) {
//             temp.data_[i] = std::move(data_[i]);
//         }
//         temp.size_ = size_;
//     } catch (const std::exception& e)  {
//         delete[] temp.data_;
//         throw std::runtime_error("Memory allocation failed");
//     }
//     swap(temp);
// }
//     // Уменьшение capacity до size
//     void shrink_to_fit() {
//         if (capacity_ > size_) {
//             Vector temp(*this);
//             swap(temp);
//         }
//     }
    
//     /*  ОПЕРАТОРЫ СРАВНЕНИЯ  */

//     // оператор ==
//     bool operator==(const Vector& other) const {
//         if (size_ != other.size_) return false;
//         for (size_t i = 0; i < size_; i++) {
//             if (data_[i] != other.data_[i]) return false;
//         }
//         return true;
//     }

//     // оператор !=
//     bool operator!=(const Vector& other) const {
//         return !(*this == other);
//     }

//     // оператор <
//     bool operator<(const Vector& other) const {
//         size_t minSize = std::min(size_, other.size_);
//         for (size_t i = 0; i < minSize; i++) {
//             if (data_[i] < other.data_[i]) return true;
//             if (other.data_[i] < data_[i]) return false;
//         }
//         return size_ < other.size_;
//     }

//     // оператор <=
//     bool operator<=(const Vector& other) const {
//         return !(other < *this);
//     }
    
//     // оператор >
//     bool operator>(const Vector& other) const {
//         return other < *this;
//     }

//     // jgthfnjh >=
//     bool operator>=(const Vector& other) const {
//         return !(*this < other);
//     }
// };

// template<typename dataType>
// void swap(Vector<dataType>& value1, Vector<dataType>& value2) noexcept {
//     value1.swap(value2);
// }
// #endif


#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>
#include <string>
#include <iostream>

template<typename dataType>
class Vector {

private:

    dataType* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
    std::allocator<dataType> alloc_;

    /*  функции безопасного копирования/перемещения */

    template<typename U>
    void saveCopy(U* dest, const U* src, size_t count) {
        size_t i = 0;
        try {
            for (; i < count; ++i) {
                alloc_.construct(dest + i, src[i]);
            }
        }
        catch (...) {
            for (size_t j = 0; j < i; ++j) {
                alloc_.destroy(dest + j);
            }
            throw;
        }
    }

    template<typename U>
    void safe_move(U* dest, U* src, size_t count) {
        size_t i = 0;
        try {
            for (; i < count; ++i) {
                alloc_.construct(dest + i, std::move(src[i]));
            }
        }
        catch (...) {
            for (size_t j = 0; j < i; ++j) {
                alloc_.destroy(dest + j);
            }
            throw;
        }
    }

    void destroyAll() {
        for (size_t i = 0; i < size_; ++i) {
            alloc_.destroy(data_ + i);
        }
    }

public:

     /*  КОНСТРУКТОРЫ  */

    // Конструктор инициализации
   Vector() noexcept : data_(nullptr), size_(0), capacity_(0) {}


    // Конструктор инициализации с параметром size
    Vector(size_t n) : size_(n), capacity_(n * 2) {
        if (n > 0) {
            data_ = alloc_.allocate(capacity_);
            size_t i = 0;
            try {
                for (size_t i=0; i < size_; i++) {
                    alloc_.construct(data_ + i);  
                }
            } catch (const std::bad_alloc& e) {
                {
                for (size_t j = 0; j < i; j++) {
                    alloc_.destroy(data_ + j);
                }
                alloc_.deallocate(data_, capacity_);     
                throw std::runtime_error("Memory allocation failed"); 

                }
            }
        }       
    }

    // Конструктор инициализации с параметрами
    Vector(size_t n, const dataType& value) {
        if (n > 0) {
        size_ = n;
        capacity_ = n * 2;
        data_ = alloc_.allocate(capacity_);
        size_t i = 0;
        try {
            for (; i < n; i++) {
                alloc_.construct(data_ + i, value);
            }
        } catch (const std::bad_alloc& e) {
            for (size_t j = 0; j < i; j++) {
                alloc_.destroy(data_ + j);
            }
            alloc_.deallocate(data_, capacity_);
            throw std::runtime_error("Memory allocation failed");
        }
    }
    }

    // Конструктор valueializer_list
    Vector(std::initializer_list<dataType> value) {
        if (value.size() > 0){
            capacity_ = value.size() * 2;
            auto iter = value.begin();
            data_ = alloc_.allocate(capacity_);
            size_t i = 0;
            try {
                for (; iter != value.end(); iter++, i++) {
                    alloc_.construct(data_ + i, *iter);
                }
                size_ = value.size();
            }
            catch (const std::bad_alloc& e)  {
                for (size_t j = 0; j < i; j++) {
                    alloc_.destroy(data_ + j);
                }
                alloc_.deallocate(data_, capacity_);
                throw std::runtime_error("Memory allocation failed");
            }
        }
    }

    // Конструктор копирования
    Vector(const Vector& other) {
        if (other.data_ && other.size_ > 0) {
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = alloc_.allocate(capacity_);
        try {
            saveCopy(data_, other.data_, other.size_);
        }
        catch (...) {
            if (data_) {
                alloc_.deallocate(data_, capacity_);
            }
            throw std::runtime_error("Fatal error");
        }
    }
    }

    // Конструктор перемещения через swap
    Vector(Vector&& other) noexcept : Vector() { 
        swap(other);
    }

    // Деструктор
    ~Vector() {
        destroyAll();
        if (data_) {
            alloc_.deallocate(data_, capacity_);
        }
    }


    /* ГЕТТЕРЫ */

    size_t size() const noexcept {
        return size_;
    }

    size_t capacity() const noexcept {
        return capacity_;
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    dataType* data() noexcept {
        return data_;
    }

    /* SWAP  */

    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(alloc_, other.alloc_);
    }

    /*  ОПЕРАТОРЫ ПРИСВОЕНИЯ */
    
    // Оператор копирующего присваивания
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }

    // Оператор перемещающего присваивания
    Vector& operator=(Vector&& other) noexcept {
       if (this != &other) {
            swap(other);  
        }
        return *this;
    }

    // Оператор присваивания из valueializer
    Vector& operator=(std::initializer_list<dataType> init) {
        Vector temp(init);
        swap(temp);
        return *this;
    }

    /*  ДОСТУП К ЭЛЕМЕНТАМ  */

    // Доступ без проверки границ
    dataType& operator[](size_t index) noexcept {
        return data_[index];
    }

    const dataType& operator[](size_t index) const noexcept {
        return data_[index];
    }

    // Доступ с проверкой границ
    dataType& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const dataType& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Ссылка на первый элемент
    dataType& front() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[0];
    }

    // Ссылка на первый элемент
    dataType& front() const {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[0];
    }

    // ссылка на последний элемент
    dataType& back() {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[size_ - 1];
    }

    const dataType& back() const {
        if (empty()) {
            throw std::out_of_range("Vector is empty");
        }
        return data_[size_ - 1];
    }

    // Копирующая вставка
    void push_back(const dataType& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ * 2);
        }
        data_[size_] = value;
        size_++;
    }
    
    // Перемещающая вставка
    void push_back(dataType&& value) {
        if (size_ >= capacity_) {
            size_t newCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
            dataType* newData = alloc_.allocate(newCapacity);
            size_t i = 0;
            try {
                for (; i < size_; i++) {
                    alloc_.construct(newData + i, std::move(data_[i]));
                }
                alloc_.construct(newData + i, std::move(value));
            }
            catch (...) {
                for (size_t j = 0; j < i; j++) {
                    alloc_.destroy(newData + j);
                }
                alloc_.deallocate(newData, newCapacity);
                throw std::runtime_error("Fatal error");
            }
            destroyAll();
            if (data_) {
                alloc_.deallocate(data_, capacity_);
            }
            data_ = newData;
            capacity_ = newCapacity;
            size_++;
        }
        else {
            alloc_.construct(data_ + size_, std::move(value));
            size_++;
        }
    }


    // Вставка в произвольную позицию
    void insert(size_t index, const dataType& value) {
    if (index > size_) {
        throw std::out_of_range("Index out of range");
    }

    if (size_ >= capacity_) {
        reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
        
    if (index < size_) {
        alloc_.construct(data_ + size_, std::move(data_[size_ - 1]));    
            for (size_t i = size_ - 1; i > index; --i) {
                data_[i] = std::move(data_[i - 1]);
            }
        data_[index] = value;
    } else {
        alloc_.construct(data_ + size_, value);
    }
    size_++;
    }

    // Вставка в произвольную позицию (перемещающая)
    void insert(size_t index, dataType&& value) {
        if (index > size_) {
            throw std::out_of_range("Index out of range");
        }
        if (size_ >= capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        if (index < size_) {
            alloc_.construct(data_ + size_, std::move(data_[size_ - 1]));
            for (size_t i = size_ - 1; i > index; --i) {
                data_[i] = std::move(data_[i - 1]);
            }
            data_[index] = std::move(value);
        } else {
            alloc_.construct(data_ + size_, std::move(value));
        }
        size_++;
    }

     /*  УДАЛЕНИЕ ЭЛЕМЕНТОВ  */

    // удаление последнего элемента
    void pop_back() {
       if (empty()) {
            throw std::runtime_error("Vector is empty");
        }

        alloc_.destroy(data_ + size_ - 1);
        size_--;
    }

    // Удаления всех элементов
    void clear() noexcept {
        destroyAll();
        size_ = 0;
    }

    // Удаление элемента по индексу
    void erase(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        alloc_.destroy(data_ + index);
        for (size_t i = index; i < size_ - 1; i++) {
            data_[i] = std::move(data_[i + 1]);
        }
        
        alloc_.destroy(data_ + size_ - 1);
        size_--;
    }

    // удаление диапозона
    void erase(size_t first, size_t last) {
        if (first > last || last > size_) {
            throw std::out_of_range("Invalid range");
        }

        size_t range_size = last - first;
        if (range_size == 0) return;

        for (size_t i = first; i < last; i++) {
            alloc_.destroy(data_ + i);
        }
        for (size_t i = first; i < size_ - range_size; i++) {
            data_[i] = std::move(data_[i + range_size]);
        }

        for (size_t i = size_ - range_size; i < size_; i++) {
            alloc_.destroy(data_ + i);
        }
        size_ -= range_size;
    }

     /*  ИЗМЕНЕНИЕ РАЗМЕРА  */

    // Изменение размера
    void resize(size_t newSize) {
        if (newSize == size_) return;

        if (newSize > capacity_) {
            size_t newCapacity = std::max(newSize, capacity_ * 2);
            dataType* newData = alloc_.allocate(newCapacity);
            size_t i = 0;

            try {
                for (; i < size_; ++i) {
                    alloc_.construct(newData + i, data_[i]);
                }
                for (; i < newSize; ++i) {
                    alloc_.construct(newData + i);
                }
            }
            catch (...) {
                for (size_t j = 0; j < i; j++) {
                    alloc_.destroy(newData + j);
                }
                alloc_.deallocate(newData, newCapacity);
                throw std::runtime_error("Fatal error");
            }

            destroyAll();
            if (data_) {
                alloc_.deallocate(data_, capacity_);
            }

            data_ = newData;
            size_ = newSize;
            capacity_ = newCapacity;
        }
        else if (newSize > size_) {
            size_t i = size_;
            try {
                for (; i < newSize; i++) {
                    alloc_.construct(data_ + i);
                }
                size_ = newSize;
            }
            catch (...) {
                for (size_t j = size_; j < i; j++) {
                    alloc_.destroy(data_ + j);
                }
                throw std::runtime_error("Fatal error");
            }
        }
        else {
            for (size_t i = newSize; i < size_; i++) {
                alloc_.destroy(data_ + i);
            }
            size_ = newSize;
        }
    }

    // Изменение размера с указанием значения
    void resize(size_t newSize, const dataType& value) {
        if (newSize == size_) return;
        if (newSize > capacity_) {
            size_t newCapacity = std::max(newSize, capacity_ * 2);
            dataType* newData = alloc_.allocate(newCapacity);

            size_t i = 0;
            try {
                for (; i < size_; i++) {
                    alloc_.construct(newData + i, data_[i]);
                }
                for (; i < newSize; i++) {
                    alloc_.construct(newData + i, value);
                }
            }
            catch (...) {
                for (size_t j = 0; j < i; j++) {
                    alloc_.destroy(newData + j);
                }
                alloc_.deallocate(newData, newCapacity);
                throw std::runtime_error("Fatal error");
                
            }

            destroyAll();
            if (data_) {
                alloc_.deallocate(data_, capacity_);
            }

            data_ = newData;
            size_ = newSize;
            capacity_ = newCapacity;
        }
        else if (newSize > size_) {
            size_t i = size_;
            try {
                for (; i < newSize; i++) {
                    alloc_.construct(data_ + i, value);
                }
                size_ = newSize;
            }
            catch (...) {
                for (size_t j = size_; j < i; j++) {
                    alloc_.destroy(data_ + j);
                }
                throw std::runtime_error("Fatal error");
            }
        }
        else {
            for (size_t i = newSize; i < size_; i++) {
                alloc_.destroy(data_ + i);
            }
            size_ = newSize;
        }
    }

    // резервирования памяти
    void reserve(size_t newCapacity) {
        if (newCapacity > capacity_) {
            dataType* newData = alloc_.allocate(newCapacity);
            size_t i = 0;
            try {
                if (noexcept(dataType(std::declval<dataType&&>()))) {
                    for (; i < size_; i++) {
                        alloc_.construct(newData + i, std::move(data_[i]));
                    }
                } else {
                    for (; i < size_; i++) {
                        alloc_.construct(newData + i, data_[i]);
                    }
                }
            }
            catch (...) {
                for (size_t j = 0; j < i; j++) {
                    alloc_.destroy(newData + j);
                }
                alloc_.deallocate(newData, newCapacity);
                throw std::runtime_error("Fatal error");
            }
            destroyAll();
            if (data_) {
                alloc_.deallocate(data_, capacity_);
            }
            data_ = newData;
            capacity_ = newCapacity;
        }
    }

    // уменьшение саpacity до size
    void shrink_to_fit() {
        if (capacity_ > size_) {
            if (size_ == 0) {
                destroyAll();
                data_ = nullptr;
                capacity_ = 0;
                if (data_) {
                    alloc_.deallocate(data_, capacity_);
                }
            }
            else {
                dataType* newData = alloc_.allocate(size_);
                size_t i = 0;
                try {
                    if (noexcept(dataType(std::declval<dataType&&>()))) {
                        for (; i < size_; i++) {
                            alloc_.construct(newData + i, std::move(data_[i]));
                        }
                    } else {
                        for (; i < size_; i++) {
                            alloc_.construct(newData + i, data_[i]);
                        }
                    }
                }
                catch (...) {
                    for (size_t j = 0; j < i; j++) {
                        alloc_.destroy(newData + j);
                    }
                    alloc_.deallocate(newData, size_);
                    throw std::runtime_error("Fatal error");
                }
                destroyAll();
                if (data_) {
                    alloc_.deallocate(data_, capacity_);
                }
                data_ = newData;
                capacity_ = size_;
            }
        }
    }

     /*  ОПЕРАТОРЫ СРАВНЕНИЯ  */

    // оператор ==
    bool operator==(const Vector& other) const {
        if (size_ != other.size_) return false;
        for (size_t i = 0; i < size_; i++) {
            if (data_[i] != other.data_[i]) return false;
        }
        return true;
    }

    // оператор !
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    // оператор <
    bool operator<(const Vector& other) const {
        size_t minSize = std::min(size_, other.size_);
        for (size_t i = 0; i < minSize; i++) {
            if (data_[i] < other.data_[i]) return true;
            if (other.data_[i] < data_[i]) return false;
        }
        return size_ < other.size_;
    }

    // оператор <=
    bool operator<=(const Vector& other) const {
        return !(other < *this);
    }

    // оператор >
    bool operator>(const Vector& other) const {
        return other < *this;
    }

    // оператор >=
    bool operator>=(const Vector& other) const {
        return !(*this < other);
    }

};


#endif