#include <cassert>
#include <iostream>

#include "Vector.hpp"
#include "externalFunctions.hpp"
#include "decor.hpp"
#include "elementsTests.hpp"
#include "sortTEsts.hpp"
#include "operationTests.hpp"
#include "securityTests.hpp"
#include "otherTests.hpp"


int main() {
    std::cout << "##########################################" << std::endl;
    std::cout << "           TESTS VECTOR          "          << std::endl;
    std::cout << "##########################################" << std::endl;
    std::cout << std::endl;

    try {
        //
        testBasicOperations();
        testElementAccess();
        testAssignmentOperators();
        testComparisonOperators();
        testSizeManagement();
        //
        testAddingElements();
        testRemovingElements();
        //
        testSortingAlgorithms();
        //
        testSafetyAndExceptions(); 
        //
        testSwapAndIterators();
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