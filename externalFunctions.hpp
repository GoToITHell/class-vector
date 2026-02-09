#ifndef EXTERNAL_FUNCTIONS_HPP
#define  EXTERNAL_FUNCTIONS_HPP
#include "Vector.hpp"

template<typename dataType>
void selectionSort(Vector<dataType>& vector) {
    size_t n = vector.size();
    if (n <= 1) return;

    for (size_t i = 0; i < n - 1; i++) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < n; j++) {
            if (vector[j] < vector[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            std::swap(vector[i], vector[minIdx]);
        }
    }
}

template<typename dataType, typename Compare>
void selectionSort(Vector<dataType>& vector, Compare comp) {
    size_t n = vector.size();
    if (n <= 1) return;

    for (size_t i = 0; i < n - 1; ++i) {
        size_t bestIdx = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (comp(vector[j], vector[bestIdx])) {
                bestIdx = j;
            }
        }
        if (bestIdx != i) {
            std::swap(vector[i], vector[bestIdx]);
        }
    }
}
// глобальный swap
template<typename dataType>
void swap(Vector<dataType>& value1, Vector<dataType>& value2) noexcept {
    value1.swap(value2);
}

// перегрузка вывода
template<typename dataType>
std::ostream& operator<<(std::ostream& output, const Vector<dataType>& vector) {
    output << "[";
    for (size_t i = 0; i < vector.size(); i++) {
        output << vector[i];
        if (i < vector.size() - 1) output << ", ";
    }
    output << "]";
    return output;
}


#endif

