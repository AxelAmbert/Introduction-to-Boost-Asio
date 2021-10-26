//
// Created by axela on 26/10/2021.
//

#include "UsefulClass.hpp"

UsefulClass::UsefulClass() {
    useless_strings_.reserve(10000);
    for (int i = 0; i < 10000; i++) {
        std::string m;

        m.reserve(1000);
        for (int t = 0; t < 1000; t++) {
            m.push_back((char)(65 + rand() % 26));
        }
        useless_strings_.push_back(m);
    }
}

template<typename T>
T UsefulClass::clamp(const T &val, const T &min, const T &max) {
    if (val > max)
        return max;
    else if (val < min) {
        return min;
    }
    return val;
}

void UsefulClass::modify_a_string(std::string &str) {
    if (str.length() > 10) {
        str = str.substr(0, str.length() - 10);
    }
    for (char & i : str) {
        char r = (char)(rand() % 52);

        r = r < 26 ? r : -(r - (char)26);
        i += r;
        i = clamp<char>(i, 65, 90);
    }
    for (int i = 0; i < 10; i++) {
        str.push_back(rand() % 26 + 65);
    }
}

void UsefulClass::modify_strings() {
    std::cout << "[start]" << std::endl;
    std::for_each(useless_strings_.begin(), useless_strings_.end(), boost::bind(&UsefulClass::modify_a_string, this, boost::placeholders::_1));
    std::cout << "[end]" << std::endl;
}
