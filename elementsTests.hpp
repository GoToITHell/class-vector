#ifndef ELEMENTS_TESTS_HPP
#define ELEMENTS_TESTS_HPP

#include <iostream>
#include "decor.hpp"
#include "Vector.hpp"
#include <cassert>

/* ТЕСТЫ ДОСТУПА К ЭЛЕМЕНТАМ */

void testElementAccess() {
    header("Element access methods");

    Vector<std::string> words;
    const char* values[] =  {"apple", "banana", "cherry", "date", "elderberry"};
    for (const auto& val : values) {
        words.push_back(val);
    }
    
    // Оператор []
    assert(words[0] == "apple");
    assert(words[2] == "cherry");
    words[1] = "blueberry";
    assert(words[1] == "blueberry");

    // Метод at()
    assert(words.at(3) == "date");
    words.at(4) = "fig";
    assert(words[4] == "fig");

    bool exceptionCaught = false;
    try {
        words.at(100);
    } catch (const std::out_of_range&) {
        exceptionCaught = true;
    }
    assert(exceptionCaught);

    // front() и back()
    assert(words.front() == "apple");
    assert(words.back() == "fig");
    words.front() = "apricot";
    words.back() = "grape";
    assert(words[0] == "apricot");
    assert(words[4] == "grape");

    // Проверка const методов
    const Vector<std::string>& constWords = words;
    assert(constWords[0] == "apricot");
    assert(constWords.at(1) == "blueberry");
    assert(constWords.front() == "apricot");
    assert(constWords.back() == "grape");

    testPassed();
}

/*  ТЕСТЫ ДОБАВЛЕНИЯ ЭЛЕМЕНТОВ */

void testAddingElements() {
    header("Adding elements (push_back and insert)");

    Vector<double> numbers;
    
    numbers.push_back(3.14);
    numbers.push_back(2.71);
    numbers.push_back(1.41);
    assert(numbers.getSize() == 3);
    assert(numbers[0] == 3.14);
    assert(numbers[2] == 1.41);
    // Вставка в начало
    numbers.insert(0, 0.0);
    assert(numbers.getSize() == 4);
    assert(numbers[0] == 0.0);
    assert(numbers[1] == 3.14);

    // Вставка в середину
    numbers.insert(2, -1.0);
    assert(numbers.getSize() == 5);
    assert(numbers[2] == -1.0);
    assert(numbers[3] == 2.71);
    
    // Вставка в конец
    numbers.insert(numbers.getSize(), 42);
    assert(numbers.getSize() == 6);
    assert(numbers[5] == 42.0);
    
    Vector<int> growingVec;
    size_t initialCapacity = growingVec.getCapacity();
    for (int i = 0; i < 1000; ++i) {
        growingVec.push_back(i * i);
    }
    assert(growingVec.getSize() == 1000);
    assert(growingVec.getCapacity() > initialCapacity);
    assert(growingVec[0] == 0);
    assert(growingVec[999] == 999 * 999);
    
    testPassed();
}

/* ТЕСТЫ УДАЛЕНИЯ ЭЛЕМЕНТОВ */

void testRemovingElements() {
    header("Removing elements (pop_back, erase, clear)");
    Vector<char> letters;
    const char values[] =  {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    for (const auto& val : values) {
        letters.push_back(val);
    }
    
    // pop_back()
    letters.pop_back();
    assert(letters.getSize() == 7);
    assert(letters.back() == 'g');

    // Удаление из середины
    letters.erase(2);
    assert(letters.getSize() == 6);
    assert(letters[2] == 'd');
    assert(letters[5] == 'g');

    // Удаление первого элемента
    letters.erase(0);
    assert(letters.getSize() == 5);
    assert(letters[0] == 'b');

    // Удаление диапазона
    letters.erase(1, 4);
    assert(letters.getSize() == 2);
    assert(letters[0] == 'b');
    assert(letters[1] == 'g');

    // Очистка вектора
    letters.clear();
    assert(letters.isEmpty());
    assert(letters.getSize() == 0);

    
    // исключение при попытке удаления из пустого вектора
    bool exceptionCaught = false;
    try {
        letters.pop_back();
    } catch (const std::out_of_range&) {
        exceptionCaught = true;
    }
    assert(exceptionCaught);

    // Удаление с неправильными индексами
    Vector<int> nums;
    for (size_t i =0; i<=3; i++) nums.push_back(i);
    exceptionCaught = false;
    try {
        nums.erase(5);
    } catch (const std::out_of_range&) {
        exceptionCaught = true;
    }
    assert(exceptionCaught);

    exceptionCaught = false;
    try {
        nums.erase(2, 1); 
    } catch (const std::out_of_range&) {
        exceptionCaught = true;
    }
    assert(exceptionCaught);


    // тест перемещения
    Vector<int> a;
    a.push_back(10);
    a.push_back(20);
    
    Vector<int> b = std::move(a);  
    assert(a.isEmpty());  
    
    Vector<int> c;
    c = std::move(b);     
    assert(b.isEmpty());  
    assert(c.getSize() == 2);
    

    testPassed();
}
#endif
