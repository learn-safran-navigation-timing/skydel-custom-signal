#include "custom_e1.h"

#include <cstring>
#include <sstream>

#ifndef DOWNLINK_PATH
#define DOWNLINK_PATH "./custom_e1_downlink.csv"
#endif

namespace
{

void setBits(std::array<bool, 500>& bits, const std::string& str)
{
  std::istringstream iss(str);
  iss >> std::hex;

  uint32_t word;
  int i = 0;
  while (iss >> word)
  {
    for (int j = 0; j < 32; ++j)
    {
      if (i * 32 + j < 500)
        bits[i * 32 + j] = (word & (1 << (31 - j))) != 0;
    }
    ++i;
  }
}

} // namespace

E1Data::E1Data(const CSInitData& data) :
  startWeek(data.startWeek),
  startSecondOfWeek(data.startSecondOfWeek),
  navMsg(std::string {data.pathToXml} + '/' + DOWNLINK_PATH,
         std::make_unique<NavMessageBlock<36, 500, 2000>>(&setBits)),
  out("custom_e1.log")
{
}

CustomE1NavMsg::CustomE1NavMsg(E1Data& data) : m_data(data)
{
}

uint32_t CustomE1NavMsg::getNavMsgDurationMs()
{
  return 2000;
}

int32_t CustomE1NavMsg::getTOWOffset()
{
  return 1;
}

void CustomE1NavMsg::buildNavMsg(int64_t elapsedTime, uint32_t prn, const CSConstellation& /*data*/)
{
  m_data.out << "buildNavMsg(" << elapsedTime << ", " << prn << ")\n";
  m_data.navMsg.prepare(elapsedTime, prn);
}

CustomE1BCode::CustomE1BCode(E1Data& data) : m_data(data)
{
}

void CustomE1BCode::getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips)
{
  const int8_t* fullCode = m_data.code.getE1B(prn - 1);
  const int8_t* curMs = fullCode + (elapsedTime % 4) * 1023;

  int8_t navBit = m_data.navMsg.getBit(elapsedTime, prn) ? -1 : 1;

  for (int i = 0; i < 1023; ++i)
    chips[i] = navBit * curMs[i];
}

uint32_t CustomE1BCode::getNumberOfChipsPerMSec()
{
  return 1023;
}

uint32_t CustomE1BCode::getExtraAllocSize()
{
  return 0;
}

CustomE1CCode::CustomE1CCode(E1Data& data) : m_data(data)
{
}

void CustomE1CCode::getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips)
{
  const int8_t* fullCode = m_data.code.getE1C(prn - 1);
  const int8_t* curMs = fullCode + (elapsedTime % 100) * 1023;
  std::memcpy(chips, curMs, 1023);
}

uint32_t CustomE1CCode::getNumberOfChipsPerMSec()
{
  return 1023;
}

uint32_t CustomE1CCode::getExtraAllocSize()
{
  return 0;
}

CustomE1::CustomE1(const CSInitData& data) :
  ICustomSignal(data),
  m_data(data),
  m_msg(m_data),
  m_e1bCode(m_data),
  m_e1cCode(m_data)
{
  m_data.out << "ctor(" << m_data.startWeek << ", " << m_data.startSecondOfWeek << ")\n";
}

CustomE1::~CustomE1()
{
  m_data.out << "dtor()\n";
}

ICustomSignalNavMsg* CustomE1::getNavMsg()
{
  m_data.out << "getNavMsg()\n";
  return &m_msg;
}

ICustomSignalCode* CustomE1::getCode(const char* name)
{
  m_data.out << "getCode(\"" << name << "\")\n";
  if (name == std::string {"E1B"})
    return &m_e1bCode;
  if (name == std::string {"E1C"})
    return &m_e1cCode;
  return nullptr;
}

DEFINE_CUSTOM_SIGNAL(CustomE1)
