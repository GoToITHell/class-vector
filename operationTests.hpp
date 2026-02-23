#ifndef OPERATION_TESTS_HPP
#define OPERATION_TESTS_HPP


#include <iostream>
#include <cassert>
#include "Vector.hpp"
#include "decor.hpp"

/* ТЕСТЫ ОСНОВНЫХ ОПЕРАЦИЙ */

void testBasicOperations() {
    header("Basic operations and constructors");

    //  Конструктор по умолчанию
    Vector<int> emptyVec;
    assert(emptyVec.getSize() == 0);
    assert(emptyVec.getCapacity() == 0);
    assert(emptyVec.isEmpty());

    //  Конструктор с размером 
    Vector<int> sizedVec(15);
    assert(sizedVec.getSize() == 15);
    assert(sizedVec.getCapacity() >= 15);
    for (size_t i = 0; i < sizedVec.getSize(); i++) {
        assert(sizedVec[i] == 0);
    }

    // Конструктор с размером и значением
    Vector<int> filledVec(8, -42);
    assert(filledVec.getSize() == 8);
    for (size_t i = 0; i < filledVec.getSize(); i++) {
        assert(filledVec[i] == -42);
    }

    //  Конструктор копирования
    Vector<int> copyVec = filledVec;
    assert(copyVec.getSize() == 8);
    assert(copyVec[2] == -42);
    copyVec[1] = 999;
    assert(filledVec[1] == -42);  

    // Конструктор перемещения
    Vector<int> moveVec = std::move(copyVec);
    assert(moveVec.getSize() == 8);
    assert(moveVec[1] == 999);
    assert(copyVec.isEmpty());
    assert(copyVec.getSize() == 0);

    // Тест 7: Конструктор с нулевым размером
    Vector<int> zeroVec(0);
    assert(zeroVec.getSize() == 0);
    assert(zeroVec.isEmpty());

    testPassed();
}

/* ТЕСТЫ ИЗМЕНЕНИЯ РАЗМЕРА  */

void testSizeManagement() {
    header("getSize management (resize, reserve, shrink_to_fit)");
    Vector<int> vec;
    for (size_t i =0; i<5; i++) vec.push_back(i*10);
    
    // Увеличение размера 
    vec.resize(8);
    assert(vec.getSize() == 8);
    assert(vec[0] == 0);
    assert(vec[4] == 40);
    assert(vec[5] == 0);  
    assert(vec[7] == 0);

    // Уменьшение размера
    vec.resize(3);
    assert(vec.getSize() == 3);
    assert(vec[0] == 0);
    assert(vec[2] == 20);

    // Увеличение размера с значением
    vec.resize(6, -1);
    assert(vec.getSize() == 6);
    assert(vec[3] == -1);
    assert(vec[4] == -1);
    assert(vec[5] == -1);

    // reserve()
    size_t oldSize = vec.getSize();
    size_t oldCapacity = vec.getCapacity();
    vec.reserve(100);
    assert(vec.getSize() == oldSize);
    assert(vec.getCapacity() >= 100);
    size_t currentCapacity = vec.getCapacity();
    vec.reserve(10);
    assert(vec.getCapacity() == currentCapacity);

    testPassed();
}

/* ТЕСТЫ ОПЕРАТОРОВ ПРИСВАИВАНИЯ */

void testAssignmentOperators() {
    header("Assignment operators");

    Vector<int> source;
    for (size_t i =0; i<=5; i++) source.push_back(i*100);
    Vector<int> target;
    
    target = source;
    assert(target.getSize() == 6);
    assert(target[1] == 100);
    assert(target[3] == 300);
    
    target[1] = 999;
    assert(source[1] == 100);

    // Присваивание string
    Vector<std::string> strings;
        const char* values[] = {"one", "two", "three", "four"};
    for (const auto& val : values) {
        strings.push_back(val);
    }
    assert(strings.getSize() == 4);
    assert(strings[0] == "one");
    assert(strings[3] == "four");

    testPassed();
}

/* ТЕСТЫ ОПЕРАТОРОВ СРАВНЕНИЯ */

void testComparisonOperators() {
    header("Comparison operators");

    // Равные векторы
    Vector<int> v1;
     for (size_t i =0; i<=5; i++) v1.push_back(i);
    Vector<int> v2;
    for (size_t i =0; i<=5; i++) v2.push_back(i);
    Vector<int> v3;
    for (size_t i =0; i<=3; i++) v3.push_back(i);
    Vector<int> v4; 
    for (size_t i =0; i<=3; i++) v4.push_back(i*2);
    Vector<int> v5; 
    for (size_t i =0; i<=3; i++) v5.push_back(2);
    Vector<int> v6;
    for (size_t i =0; i<=6; i++) v6.push_back(i);  

    assert(v1 == v2);
    assert(!(v1 == v3));
    
    assert(v1 != v3);
    assert(!(v1 != v2));
    
    assert(v3 < v1);          
    assert(v1 < v6);     
    
    assert(v1 > v3);    
    assert(v4 > v3);     
    assert(v6 > v1);    
    

    assert(v1 <= v2);    
    assert(v3 <= v1);   
    assert(v1 >= v2);   

    // Пустые векторы
    Vector<int> empty1, empty2;
    assert(empty1 == empty2);
    assert(!(empty1 != empty2));
    assert(!(empty1 < empty2));
    assert(!(empty1 > empty2));
    assert(empty1 <= empty2);
    assert(empty1 >= empty2);

    // Векторы с отрицательными числами
    Vector<int> neg1;
    for (size_t i =0; i<=3; i++) neg1.push_back(-1*i);
    Vector<int> neg2;
    for (size_t i =0; i<=3; i++) neg2.push_back(-2*i);
    assert(neg1 > neg2);
    assert(neg2 < neg1);

    // Строки
    Vector<std::string> words1;
    const char* values[] = {"apple", "banana"};
    for (const auto& val : values) {
        words1.push_back(val);
    }

    Vector<std::string> words2;
    const char* values1[] =  {"apple", "cherry"};
    for (const auto& val : values1) {
        words2.push_back(val);
    }

    assert(words1 < words2);  
    assert(words2 > words1);

    testPassed();
}

#endif