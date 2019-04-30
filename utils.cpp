#include <iostream>
#include "utils.hpp"

Status status;

uint8_t Utils::rol(uint8_t nibble)
{
  uint8_t retval;
  bool previous_carry = status.carry_flag;

  status.carry_flag = nibble >> 7;
  retval = (nibble << 1) | previous_carry;

  return retval;
}


uint8_t Utils::ror(uint8_t bit)
{
  uint8_t retval;

  bool previous_carry = status.carry_flag;

  status.carry_flag = static_cast<bool>(bit & 0x01);

  retval = bit >> 1;
  retval = static_cast<uint8_t>(previous_carry ? retval | 0x80 : retval);

  return retval;
}


uint8_t Utils::asl(uint8_t bit)
{
  status.carry_flag = bit >> 7;

  return bit << 1;
}


uint8_t Utils::adc(uint8_t val1, uint8_t val2)
{
  uint8_t result = val1 + val2 + status.carry_flag;

  if (result < val1 || result < val2)
    status.carry_flag = true;

  return result;
}


void Utils::output_password(const uint8_t password[])
{
  for (int i = 0; i < 8; ++i)
    std::cout << (int)password[i] << " ";

  std::cout << std::endl;
}
