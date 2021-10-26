//
// Created by axela on 26/10/2021.
//

#ifndef UNTITLED_USEFULCLASS_HPP
#define UNTITLED_USEFULCLASS_HPP


#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <boost/bind.hpp>

class UsefulClass {
public:
    UsefulClass();

    template<typename T>
    T clamp(const T& val, const T& min, const T& max);

    void modify_a_string(std::string &str);

    void modify_strings();
private:
    std::vector<std::string> useless_strings_;
};


#endif //UNTITLED_USEFULCLASS_HPP
