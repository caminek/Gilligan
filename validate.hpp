#ifndef VALIDATE_HPP
#define VALIDATE_HPP

#include <QObject>
#include <cstdint>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include "utils.hpp"

extern Status status;

struct Results
{
    bool is_valid;
    int level;
    std::string score;
};

class validate : public QObject
{
    Q_OBJECT
public:
    explicit validate();
    Results validator(const std::string &pwd);

private:
    Utils util;
    Results results;
    uint8_t password[8];

    void populate_password(const std::string &pwd);
    void decompose_password();
    void calculate_score_and_level();

    bool calculate_bits_1_and_8(uint8_t var_18);

    uint8_t seed_value();


};


#endif // VALIDATE_HPP
