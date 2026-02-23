#ifndef DECOR_HPP
#define DECOR_HPP
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
#endif 

