#include "validate.hpp"


validate::validate()
{
    status.carry_flag = false;
    results.is_valid = true;
    results.level = -1;

    memset(password, 0, 8 * sizeof(uint8_t));
}


Results validate::validator(const std::string &pwd)
{
  uint8_t temp = 0;

  populate_password(pwd);

  decompose_password();
  temp = seed_value();
  results.is_valid = calculate_bits_1_and_8(temp);

  if (!results.is_valid) return results;

  calculate_score_and_level();

  return results;
}


void validate::populate_password(const std::string &pwd)
{
  for (int i = 0; i < 8; ++i)
    password[i] = static_cast<uint8_t>(pwd[i] - 0x41);
}


void validate::decompose_password()
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
    password[i] = static_cast<uint8_t>((password[i] - a) & 0x0F);
  }

  status.carry_flag = false;
}


uint8_t validate::seed_value()
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

bool validate::calculate_bits_1_and_8(uint8_t var_18)
{
  uint8_t a = 0x00;

  if (password[0] != (var_18 & 0x0F))
  {
    std::cerr << "Error: Bit 1 failed validation.  "
              << "Got " << (var_18 & 0x0F)
              << ", Expected "<< (int)password[0] << std::endl;

    return false;
  }

  password[0] = static_cast<uint8_t>(var_18 & 0x0F);

  for (int i = 0; i < 2; ++i)
  {
    var_18 = util.asl(var_18);
    a = util.rol(a);
  }

  if (password[7] != (a & 0x0F))
  {
    std::cerr << "Error: Bit 8 failed validation.  "
              << "Got " << (int)a
              << ", Expected "<< (int)password[7] << std::endl;

    return false;
  }

  password[7] &= 0x0F;
  return true;
}

void validate::calculate_score_and_level()
{
  uint8_t a = 0x00;
  status.carry_flag = false;
  int score[6] = {0,0,0,0,0,0};

  for (int i = 6; i > 0; --i)
  {
    for (int j = 0; j < 2; ++j)
    {
      password[i] = util.ror(password[i]);
      a = util.rol(a);
    }

    if (i < 6)
    {
      score[5-i] = a;
      a = 0x00;

      for (int j = 0; j < 2; ++j)
      {
        password[i] = util.ror(password[i]);
        a = util.rol(a);
      }
    }
  }

  for (int i = 6; i > 1; --i)
  {
      if (password[i] != 0)
      {
          results.is_valid = false;
          std::cerr << "Error with score.  This shouldn't happen..." << std::endl;
      }
  }

  std::ostringstream oss("");
    for (int i = 0; i < 6; ++i)
      oss << score[i];

  results.level = (int) a + 1;
  results.score = oss.str();
}



















