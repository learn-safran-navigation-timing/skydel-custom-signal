#ifndef E1_CODE_H
#define E1_CODE_H

#include <string>
#include <cstdint>
#include <memory>
#include <vector>

class E1Code
{
public:
  static const size_t E1BChipCount          = 1023*4;
  static const size_t E1CPrimaryChipCount   = 1023*4;
  static const size_t E1CSecondayChipCount  = 25;
  static const size_t E1CChipCount          = 1023*100;
  static const size_t E1MembersCount        = 50;

  E1Code();

  const int8_t* getE1B(const uint32_t memberIdx) { return m_E1B[memberIdx].data(); }
  const int8_t* getE1C(const uint32_t memberIdx) { return m_E1C[memberIdx].data(); }

private:

  std::string m_E1BFile;
  std::vector<std::vector<int8_t>> m_E1B;

  std::string m_E1CFile;
  std::vector<std::vector<int8_t>> m_E1C;

  void loadFiles();
  void createE1BCode();
  void createE1CCode();
  void charToChipsVector(const std::string& c, std::vector<int8_t>& chipsOneChar);
};

#endif // E1_CODE_H
