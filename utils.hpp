#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdint>

struct Status
{
  bool carry_flag;
};


class Utils
{
public:
    Utils(){}

    uint8_t asl(uint8_t bit);
    uint8_t rol(uint8_t nibble);
    uint8_t ror(uint8_t bit);
    uint8_t adc(uint8_t val1, uint8_t val2);

    void output_password(const uint8_t password[]);
};

#endif // UTILS_HPP





