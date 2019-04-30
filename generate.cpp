#include "generate.hpp"


std::string generate::generator(uint8_t level, const std::string &score_string)
{
  std::string result;
  std::string score = std::string(6 - score_string.length(), '0').append(score_string);

  memset(password, 0, 8 * sizeof(uint8_t));

  encode_score(password, score, level);
  calculate_bits_1_and_8(password, seed_value(password));
  calculate_password(password);

  return std::string(password, std::find(password, password + 8, '\0'));
}


void generate::encode_score(uint8_t password[], const std::string &score_str, uint8_t level)
{
  uint8_t result = 0x00;
  uint8_t score_pos = 0x04;

  auto acc = static_cast<uint8_t>(level - 1);

  for (int j = 1; j < 7; ++j)
  {
    for (uint8_t i = 0; i < 2; ++i)
    {
      acc = util.ror(acc);
      result = util.rol(result);
    }

    if (j < 6)
    {
      acc = static_cast<uint8_t>(score_str[score_pos] - 0x30);

      for (uint8_t i = 0; i < 2; ++i)
      {
        acc = util.ror(acc);
        result = util.rol(result);
      }

      score_pos--;
    }

    password[j] = result;
    result = 0x00;
  }
}


uint8_t generate::seed_value(const uint8_t password[])
{
  uint8_t var_18 = 0x00;
  uint8_t var_f;
  uint8_t var_a;
  uint8_t var_b;

  for (uint8_t i = 6; i > 0 ; --i)
  {
    var_f = password[i];
    var_a = 0x00;
    var_b = 0x00;

    status.carry_flag = false;

    for (int j = 0; j < 16 - (6-i); ++j)
    {
      var_a = util.adc(var_a, var_f);
      var_b = util.adc(var_b, 0x00);
      status.carry_flag = false;
    }

    var_18 = util.adc(var_a, var_18);
  }

  return var_18;
}


void generate::calculate_bits_1_and_8(uint8_t password[], uint8_t var_18)
{
  password[0] = static_cast<uint8_t>(var_18 & 0x0F);

  for (int i = 0; i < 2; ++i)
  {
    var_18 = util.asl(var_18);
    password[7] = util.rol(password[7]);
  }

  password[7] &= 0x0F;
}


void generate::calculate_password(uint8_t password[])
{
  std::cout << std::endl;
  auto var_e = static_cast<uint8_t>(password[0] | 0x10);
  uint8_t a = 0x00;

  for (int i = 6; i > 0; --i)
  {
    for (int k = 0; k < 2; ++k)
    {
      a = var_e;

      for (int j = 0; j < 4; ++j)
        a = util.rol(a);

      a ^= var_e;

      for (int j = 0; j < 2; ++j)
        a = util.ror(a);

      a = var_e;
      a = util.rol(a);
      var_e = a;
    }

    status.carry_flag = false;
    password[i] = static_cast<uint8_t>(util.adc(a, password[i]) & 0x0F);
  }

  for (int i = 0; i < 8; ++i)
      password[i] += 0x41;
}
