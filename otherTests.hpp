#ifndef OTHER_TESTS_HPP
#define OTHER_TESTS_HPP


#include <iostream>
#include <cassert>

#include "Vector.hpp"
#include "decor.hpp"
#include "externalFunctions.hpp"

/* ТЕСТЫ SWAP  */

void testSwapAndIterators() {
    header("Swap method and iterators");

    // swap между векторами разного размера
    Vector<int> first;
    for (int i = 0; i <= 5; i++) first.push_back(i);

    Vector<int> second;
    for (int i = 0; i <= 10; i++) second.push_back(i*2);

    
    size_t firstSize = first.getSize();
    size_t secondSize = second.getSize();
    
    first.swap(second);
    
    assert(first.getSize() == secondSize);
    assert(second.getSize() == firstSize);
    assert(first[0] == 0);   
    assert(first[1] == 2);   
    assert(first[3] == 6);   
    assert(first[4] == 8);   

    // swap через свободную функцию
    swap(first, second);
    assert(first.getSize() == firstSize);
    assert(second.getSize() == secondSize);
    assert(first[2] == 2);
    assert(second[4] == 8);

    // swap пустых векторов4
    Vector<int> empty1, empty2;
    empty1.swap(empty2);
    assert(empty1.isEmpty());
    assert(empty2.isEmpty());

    testPassed();
}

/* ТЕСТЫ САМОПРИСВАИВАНИЯ */

void testAssignment() {
    header("Self assignment");

    Vector<int> v;
    for (int i = 0; i <= 5; i++) v.push_back(i);
    size_t oldSize = v.getSize();

    // Самоприсваивание через copy
    v = v;
    assert(v.getSize() == oldSize);
    assert(v[0] == 0);
    assert(v[4] == 4);

    testPassed();
}

// /* ТЕСТЫ ПЕРЕМЕЩАЮЩЕЙ СЕМАНТИКИ */

// class Move {
// private:
//     int* data_;

// public:

//         void swap(Move& other) noexcept {
//         std::swap(data_, other.data_);
//     }

//     Move(int value = 0) : data_(new int(value)) {}

//     Move(const Move&) = delete;
//     Move& operator=(const Move&) = delete;

//     Move(Move&& other) noexcept : Move()  {
//         swap(other);
//     }

//     Move& operator=(Move&& other) noexcept {
//         if (this != &other) {
//             delete data_;
//             data_ = other.data_;
//             other.data_ = nullptr;
//         }
//         return *this;
//     }

//     ~Move() {
//         delete data_;
//     }

//     int get() const { return data_ ? *data_ : -1; }
// };

// void testMove() {
//     header("Move semantics");

//     Vector<Move> v;

//     // Добавляем элементы через перемещение
//     v.push_back(Move(1));
//     v.push_back(Move(2));
//     v.push_back(Move(3));

//     assert(v.getSize() == 3);
//     assert(v[0].get() == 1);
//     assert(v[1].get() == 2);
//     assert(v[2].get() == 3);

//     Vector<Move> v3;
//     v3 = std::move(v);
//     assert(v.isEmpty());
//     assert(v3.getSize() == 3);

//     testPassed();
// }

#endif