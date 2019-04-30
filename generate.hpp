#ifndef GENERATE_HPP
#define GENERATE_HPP

#include <QObject>
#include <iostream>
#include <sstream>
#include <ctime>
#include <random>
#include <cstring>
#include "utils.hpp"

extern Status status;

class generate : public QObject
{
    Q_OBJECT
public:
    explicit generate() {status.carry_flag = false;}
    std::string generator(uint8_t level, const std::string &score_string);
    uint8_t seed_value(const uint8_t password[]);

private:
    Utils util;
    uint8_t password[8];

    void calculate_password(uint8_t password[]);
    void calculate_bits_1_and_8(uint8_t password[], uint8_t var_18);
    void encode_score(uint8_t password[], const std::string &score_str, uint8_t level);
};

#endif // GENERATE_HPP
