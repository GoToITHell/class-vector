#ifndef SECURITY_TESTS_HPP
#define SECURITY_TESTS_HPP



#include <iostream>
#include <cassert>

#include "Vector.hpp"
#include "decor.hpp"

/* ТЕСТЫ БЕЗОПАСНОСТИ */

void testSafetyAndExceptions() {
    header("Safety and exception handling");

    // Исключения при выходе за границы
    Vector<int> vec;
    for (int i = 1; i <= 3; i++) vec.push_back(i);

    bool exceptionThrown = false;
    try {
        vec.at(9);
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    exceptionThrown = false;
    try {
        vec.insert(10, 42);
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    exceptionThrown = false;
    try {
        vec.erase(10);
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    exceptionThrown = false;
    try {
        vec.erase(2, 1);  // first > last
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    
    // Исключения при работе с пустым вектором
    Vector<int> empty;
    
    exceptionThrown = false;
    try {
        empty.front();
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    exceptionThrown = false;
    try {
        empty.back();
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    exceptionThrown = false;
    try {
        empty.pop_back();
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);


    // Самоприсваивание
    Vector<int> self;
    for (int i = 0; i <= 3; i++) self.push_back(i);
    size_t oldSize = self.getSize();
    self = self; 
    assert(self.getSize() == oldSize);
    assert(self[0] == 0);
    assert(self[2] == 2);

    testPassed();
}

#endif