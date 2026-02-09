#include "Vector.hpp"
#include "externalFunctions.hpp"
#include <cassert>
#include <iostream>

// оформление
void header(const std::string& name) {
    static size_t numberTest = 1;
    std::cout << "Test number "<<numberTest <<". Name test:  "<< name;
    numberTest++;
}

void testPassed() {
    std::cout << "....excellent!" << std::endl;
}

/* ТЕСТЫ ОСНОВНЫХ ОПЕРАЦИЙ */

void testBasicOperations() {
    header("Basic operations and constructors");

    //  Конструктор по умолчанию
    Vector<int> emptyVec;
    assert(emptyVec.size() == 0);
    assert(emptyVec.capacity() == 0);
    assert(emptyVec.empty());

    //  Конструктор с размером 
    Vector<int> sizedVec(15);
    assert(sizedVec.size() == 15);
    assert(sizedVec.capacity() >= 15);
    for (size_t i = 0; i < sizedVec.size(); i++) {
        assert(sizedVec[i] == 0);
    }

    // Конструктор с размером и значением
    Vector<int> filledVec(8, -42);
    assert(filledVec.size() == 8);
    for (size_t i = 0; i < filledVec.size(); i++) {
        assert(filledVec[i] == -42);
    }

    // Конструктор из initializer_list
    Vector<int> initVec = {7, -3, 0, 42, -99, 256};
    assert(initVec.size() == 6);
    assert(initVec[0] == 7);
    assert(initVec[3] == 42);
    assert(initVec[5] == 256);

    //  Конструктор копирования
    Vector<int> copyVec = initVec;
    assert(copyVec.size() == 6);
    assert(copyVec[2] == 0);
    copyVec[1] = 999;
    assert(initVec[1] == -3);  

    // Конструктор перемещения
    Vector<int> moveVec = std::move(copyVec);
    assert(moveVec.size() == 6);
    assert(moveVec[1] == 999);
    assert(copyVec.empty());
    assert(copyVec.size() == 0);

    // Тест 7: Конструктор с нулевым размером
    Vector<int> zeroVec(0);
    assert(zeroVec.size() == 0);
    assert(zeroVec.empty());

    testPassed();
}

/* ТЕСТЫ ДОСТУПА К ЭЛЕМЕНТАМ */

void testElementAccess() {
    header("Element access methods");
    Vector<std::string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    
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
    assert(numbers.size() == 3);
    assert(numbers[0] == 3.14);
    assert(numbers[2] == 1.41);

    // Вставка в начало
    numbers.insert(0, 0.0);
    assert(numbers.size() == 4);
    assert(numbers[0] == 0.0);
    assert(numbers[1] == 3.14);

    // Вставка в середину
    numbers.insert(2, -1.0);
    assert(numbers.size() == 5);
    assert(numbers[2] == -1.0);
    assert(numbers[3] == 2.71);

    // Вставка в конец
    numbers.insert(numbers.size(), 42.0);
    assert(numbers.size() == 6);
    assert(numbers[5] == 42.0);

    Vector<int> growingVec;
    size_t initialCapacity = growingVec.capacity();
    for (int i = 0; i < 1000; ++i) {
        growingVec.push_back(i * i);
    }
    assert(growingVec.size() == 1000);
    assert(growingVec.capacity() > initialCapacity);
    assert(growingVec[0] == 0);
    assert(growingVec[999] == 999 * 999);

    testPassed();
}

/* ТЕСТЫ УДАЛЕНИЯ ЭЛЕМЕНТОВ */

void testRemovingElements() {
    header("Removing elements (pop_back, erase, clear)");
    Vector<char> letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    
    // pop_back()
    letters.pop_back();
    assert(letters.size() == 7);
    assert(letters.back() == 'g');

    // Удаление из середины
    letters.erase(2);
    assert(letters.size() == 6);
    assert(letters[2] == 'd');
    assert(letters[5] == 'g');

    // Удаление первого элемента
    letters.erase(0);
    assert(letters.size() == 5);
    assert(letters[0] == 'b');

    // Удаление диапазона
    letters.erase(1, 4);
    assert(letters.size() == 2);
    assert(letters[0] == 'b');
    assert(letters[1] == 'g');

    // Очистка вектора
    letters.clear();
    assert(letters.empty());
    assert(letters.size() == 0);

    // исключение при попытке удаления из пустого вектора
    bool exceptionCaught = false;
    try {
        letters.pop_back();
    } catch (const std::runtime_error&) {
        exceptionCaught = true;
    }
    assert(exceptionCaught);

    // Удаление с неправильными индексами
    Vector<int> nums = {1, 2, 3};
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

    testPassed();
}

/* ТЕСТЫ ИЗМЕНЕНИЯ РАЗМЕРА  */

void testSizeManagement() {
    header("Size management (resize, reserve, shrink_to_fit)");
    Vector<int> vec = {10, 20, 30, 40, 50};
    
    // Увеличение размера 
    vec.resize(8);
    assert(vec.size() == 8);
    assert(vec[0] == 10);
    assert(vec[4] == 50);
    assert(vec[5] == 0);  
    assert(vec[7] == 0);

    // Уменьшение размера
    vec.resize(3);
    assert(vec.size() == 3);
    assert(vec[0] == 10);
    assert(vec[2] == 30);

    // Увеличение размера с значением
    vec.resize(6, -1);
    assert(vec.size() == 6);
    assert(vec[3] == -1);
    assert(vec[4] == -1);
    assert(vec[5] == -1);

    // reserve()
    size_t oldSize = vec.size();
    size_t oldCapacity = vec.capacity();
    vec.reserve(100);
    assert(vec.size() == oldSize);
    assert(vec.capacity() >= 100);
    for (size_t i = 0; i < oldSize; ++i) {
        if (i < 3) assert(vec[i] == 10 + i * 10);
        else assert(vec[i] == -1);
    }

    size_t currentCapacity = vec.capacity();
    vec.reserve(10);
    assert(vec.capacity() == currentCapacity);

    testPassed();
}

/* ТЕСТЫ ОПЕРАТОРОВ ПРИСВАИВАНИЯ */

void testAssignmentOperators() {
    header("Assignment operators");

    Vector<int> source = {100, 200, 300, 400};
    Vector<int> target;
    
    target = source;
    assert(target.size() == 4);
    assert(target[0] == 100);
    assert(target[3] == 400);
    
    target[1] = 999;
    assert(source[1] == 200);

    Vector<int> mover = {1, 2, 3};
    Vector<int> receiver;
    receiver = std::move(mover);
    assert(receiver.size() == 3);
    assert(receiver[2] == 3);
    assert(mover.empty());

    // Присваивание из initializer_list
    Vector<std::string> strings;
    strings = {"one", "two", "three", "four"};
    assert(strings.size() == 4);
    assert(strings[0] == "one");
    assert(strings[3] == "four");

    // Цепочка присваиваний
    Vector<int> a, b, c;
    a = b = c = {7, 8, 9};
    assert(a.size() == 3);
    assert(b.size() == 3);
    assert(c.size() == 3);
    assert(a[2] == 9);
    assert(b[1] == 8);
    assert(c[0] == 7);

    testPassed();
}

/* ТЕСТЫ ОПЕРАТОРОВ СРАВНЕНИЯ */

void testComparisonOperators() {
    header("Comparison operators");

    // Равные векторы
    Vector<int> v1 = {1, 2, 3, 4, 5};
    Vector<int> v2 = {1, 2, 3, 4, 5};
    Vector<int> v3 = {1, 2, 3};
    Vector<int> v4 = {1, 2, 4}; 
    Vector<int> v5 = {1, 2, 2};  
    Vector<int> v6 = {1, 2, 3, 4, 5, 6};  

    assert(v1 == v2);
    assert(!(v1 == v3));
    
    assert(v1 != v3);
    assert(!(v1 != v2));
    
    assert(v3 < v1);     
    assert(v5 < v3);     
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
    Vector<int> neg1 = {-5, -3, -1};
    Vector<int> neg2 = {-5, -3, 0};
    assert(neg1 < neg2);
    assert(neg2 > neg1);

    // Строки
    Vector<std::string> words1 = {"apple", "banana"};
    Vector<std::string> words2 = {"apple", "cherry"};
    assert(words1 < words2);  
    assert(words2 > words1);

    testPassed();
}

/* ТЕСТЫ SWAP  */

void testSwapAndIterators() {
    header("Swap method and iterators");

    // swap между векторами разного размера
    Vector<int> first = {1, 2, 3};
    Vector<int> second = {4, 5, 6, 7, 8};
    
    size_t firstSize = first.size();
    size_t secondSize = second.size();
    
    first.swap(second);
    
    assert(first.size() == secondSize);
    assert(second.size() == firstSize);
    assert(first[0] == 4);
    assert(first[4] == 8);
    assert(second[0] == 1);
    assert(second[2] == 3);

    // swap через свободную функцию
    swap(first, second);
    assert(first.size() == firstSize);
    assert(second.size() == secondSize);
    assert(first[0] == 1);
    assert(second[0] == 4);

    // swap пустых векторов
    Vector<int> empty1, empty2;
    empty1.swap(empty2);
    assert(empty1.empty());
    assert(empty2.empty());

    testPassed();
}

/* ТЕСТЫ СОРТИРОВКИ */

void testSortingAlgorithms() {
    header("Sorting algorithms (selection)");
    
        Vector<int> unsorted = {64, 34, 25, 12, 22, 11, 90};
        Vector<int> sorted = {11, 12, 22, 25, 34, 64, 90};
        
        selectionSort(unsorted);
        assert(unsorted == sorted);
    

    
        Vector<int> v1 = { 5, 4, 3, 2, 1 };
        selectionSort(v1);
        for (size_t i = 0; i < v1.size(); i++) {
            assert(v1[i] == static_cast<int>(i + 1));
        }
    

    // отрицательные числа
    
        Vector<int> v2 = { -5, -1, -10, 0, 5, -3 };
        selectionSort(v2);
        assert(v2[0] == -10);
        assert(v2.back() == 5);
        for (size_t i = 0; i < v2.size() - 1; i++) {
            assert(v2[i] <= v2[i + 1]);
        }
    
    // string
        Vector<std::string> vec = { "banana", "apple", "cherry", "date" };
        selectionSort(vec);
        assert(vec[0] == "apple");
        assert(vec[1] == "banana");
        assert(vec[2] == "cherry");
        assert(vec[3] == "date");

    // Сортировка уже отсортированного массива
    
        Vector<int> alreadySorted = {1, 2, 3, 4, 5};
        Vector<int> copy = alreadySorted;
        selectionSort(copy);
        assert(copy == alreadySorted);
    
    // Сортировка массива с дубликатами
    
        Vector<int> withDuplicates = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
        selectionSort(withDuplicates);
        
        for (size_t i = 0; i < withDuplicates.size() - 1; i++) {
            assert(withDuplicates[i] <= withDuplicates[i + 1]);
        }
    
    // Сортировка пустого и одноэлементного вектора
    
        Vector<int> empty;
        selectionSort(empty);
        assert(empty.empty());
    
    testPassed();
}


/* ТЕСТЫ ДЛЯ ТИПОВ БЕЗ КОНСТРУКТОРА ПО УМОЛЧАНИЮ */

class NoDefaultConstructor {
private:
    int value_;

public:
    NoDefaultConstructor() = delete;
    NoDefaultConstructor(int n) : value_(n) {}
    int get() const { return value_; }
    bool operator==(const NoDefaultConstructor& other) const {
        return value_ == other.value_;
    }
    bool operator<(const NoDefaultConstructor& other) const {
        return value_ < other.value_;
    }
};

void testDefaultConstructor() {
    header("Types without default constructor");

    Vector<NoDefaultConstructor> vectorWithoutCons;

    // push_back работает
    vectorWithoutCons.push_back(NoDefaultConstructor(1));
    vectorWithoutCons.push_back(NoDefaultConstructor(2));
    vectorWithoutCons.push_back(NoDefaultConstructor(5));

    assert(vectorWithoutCons.size() == 3);
    assert(vectorWithoutCons[0].get() == 1);
    assert(vectorWithoutCons[1].get() == 2);
    assert(vectorWithoutCons[2].get() == 5);

    vectorWithoutCons.resize(5, NoDefaultConstructor(99));
    assert(vectorWithoutCons.size() == 5);
    assert(vectorWithoutCons[3].get() == 99);
    assert(vectorWithoutCons[4].get() == 99);

    // тест сортировки 
    selectionSort(vectorWithoutCons, [](const NoDefaultConstructor& value1, const NoDefaultConstructor& value2) {
        return value1.get() < value2.get();
        });

    for (size_t i = 0; i < vectorWithoutCons.size() - 1; i++) {
        assert(vectorWithoutCons[i].get() <= vectorWithoutCons[i + 1].get());
    }

    testPassed();
}

/* ТЕСТЫ САМОПРИСВАИВАНИЯ */

void testAssignment() {
    header("Self assignment");

    Vector<int> v = { 1, 2, 3, 4, 5 };
    size_t oldSize = v.size();

    // Самоприсваивание через copy
    v = v;
    assert(v.size() == oldSize);
    assert(v[0] == 1);
    assert(v[4] == 5);

    // Самоприсваивание через move 
    v = std::move(v);
    assert(v.size() == oldSize);

    // Самоприсваивание через swap
    v.swap(v);
    assert(v.size() == oldSize);
    assert(v[0] == 1);

    testPassed();
}

/* ТЕСТЫ ПЕРЕМЕЩАЮЩЕЙ СЕМАНТИКИ */

class MoveOnly {
private:
    int* data_;

public:
    MoveOnly(int value = 0) : data_(new int(value)) {}

    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete;

    MoveOnly(MoveOnly&& other) noexcept : data_(other.data_) {
        other.data_ = nullptr;
    }

    MoveOnly& operator=(MoveOnly&& other) noexcept {
        if (this != &other) {
            delete data_;
            data_ = other.data_;
            other.data_ = nullptr;
        }
        return *this;
    }

    ~MoveOnly() {
        delete data_;
    }

    int get() const { return data_ ? *data_ : -1; }
};

void testMove() {
    header("Move semantics");

    Vector<MoveOnly> v;

    // Добавляем элементы через перемещение
    v.push_back(MoveOnly(1));
    v.push_back(MoveOnly(2));
    v.push_back(MoveOnly(3));

    assert(v.size() == 3);
    assert(v[0].get() == 1);
    assert(v[1].get() == 2);
    assert(v[2].get() == 3);

    Vector<MoveOnly> v3;
    v3 = std::move(v);
    assert(v.empty());
    assert(v3.size() == 3);

    testPassed();
}



int main() {
    std::cout << "##########################################" << std::endl;
    std::cout << "           TESTS VECTOR          " << std::endl;
    std::cout << "##########################################" << std::endl;
    std::cout << std::endl;

    try {

        testBasicOperations();
        testElementAccess();
        testAssignmentOperators();
        testComparisonOperators();
        testSwapAndIterators();
        testAddingElements();
        testRemovingElements();
        testSizeManagement();
        testSortingAlgorithms();
        testDefaultConstructor();
        testMove();
        testAssignment();


         std::cout << std::endl;
        std::cout << " All tests passed! " << std::endl;

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return -1;
    }
    catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return -1;
    }
}