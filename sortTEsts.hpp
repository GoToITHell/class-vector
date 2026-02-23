#ifndef SORT_TESTS_HPP
#define SORT_TESTS_HPP


#include <iostream>
#include <cassert>

#include "Vector.hpp"
#include "decor.hpp"
#include "externalFunctions.hpp"

/* ТЕСТЫ СОРТИРОВКИ */

void testSortingAlgorithms() {
    header("Sorting algorithms (selection)");
    
        Vector<int> unsorted; 
        const int values[] = {64, 34, 25, 12, 22, 11, 90};
        for (const auto& val : values) {
        unsorted.push_back(val);}

        Vector<int> sorted; 
        const int values2[] = {11, 12, 22, 25, 34, 64, 90};
        for (const auto& val : values2) {
        sorted.push_back(val);}
        
        selectionSort(unsorted);
        assert(unsorted == sorted);
    

    // отрицательные числа
    
        Vector<int> v2;
        const int values3[] = { -5, -1, -10, 0, 5, -3 };
        for (const auto& val : values3) {
        v2.push_back(val);}
        selectionSort(v2);
        assert(v2[0] == -10);
        assert(v2.back() == 5);

    // string
        Vector<std::string> vec;
         const char* values4[] =  { "banana", "apple", "cherry", "date" };
    for (const auto& val : values4) {
        vec.push_back(val);
    }

        selectionSort(vec);
        assert(vec[0] == "apple");
        assert(vec[1] == "banana");
        assert(vec[2] == "cherry");
        assert(vec[3] == "date");

    // Сортировка уже отсортированного массива
    
        Vector<int> alreadySorted;
        for (int i = 1; i <= 10; i++) alreadySorted.push_back(i);
        Vector<int> copy = alreadySorted;
        selectionSort(copy);
        assert(copy == alreadySorted);
    
    // Сортировка массива с дубликатами
    
        Vector<int> withDuplicates;
        const int values5[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
        for (const auto& val : values5) {
        withDuplicates.push_back(val);
    }
        selectionSort(withDuplicates);
        
        for (size_t i = 0; i < withDuplicates.getSize() - 1; i++) {
            assert(withDuplicates[i] <= withDuplicates[i + 1]);
        }
    
    // Сортировка пустого и одноэлементного вектора
    
        Vector<int> empty;
        selectionSort(empty);
        assert(empty.isEmpty());
    
    testPassed();
}


#endif