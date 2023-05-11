#include "custom_ca.h"

#include <cstring>
#include <sstream>

#ifndef DOWNLINK_PATH
#define DOWNLINK_PATH "./custom_ca_downlink.csv"
#endif

namespace
{

void setBits(std::array<bool, 300>& bits, const std::string& str)
{
  std::istringstream iss(str);
  iss >> std::hex;

  for (int i = 0; i < 10; ++i)
  {
    uint32_t word = 0;
    iss >> word;

    for (int j = 0; j < 30; ++j)
      bits[i * 30 + j] = word & (1 << (29 - j));
  }
}

} // namespace

CAData::CAData(const CSInitData& data) :
  startWeek(data.startWeek),
  startSecondOfWeek(data.startSecondOfWeek),
  navMsg(std::string {data.pathToXml} + '/' + DOWNLINK_PATH,
         std::make_unique<NavMessageBlock<32, 300, 6000>>(&setBits)),
  out("custom_ca.log")
{
}

CustomCANavMsg::CustomCANavMsg(CAData& data) : m_data(data)
{
}

uint32_t CustomCANavMsg::getNavMsgDurationMs()
{
  return 6000;
}

int32_t CustomCANavMsg::getTOWOffset()
{
  return 0;
}

void CustomCANavMsg::buildNavMsg(int64_t elapsedTime, uint32_t prn, const CSConstellation& /*data*/)
{
  m_data.out << "buildNavMsg(" << elapsedTime << ", " << prn << ")\n";
  m_data.navMsg.prepare(elapsedTime, prn);
}

CustomCACode::CustomCACode(CAData& data) : m_data(data)
{
}

void CustomCACode::getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips)
{
  int8_t sign = m_data.navMsg.getBit(elapsedTime, prn) ? -1 : 1;
  for (int i = 0; i < 1023; ++i)
    chips[i] = m_data.codes.code(prn)[i] * sign;
}

uint32_t CustomCACode::getNumberOfChipsPerMSec()
{
  return 1023;
}

uint32_t CustomCACode::getExtraAllocSize()
{
  return 0;
}

CustomCA::CustomCA(const CSInitData& data) : ICustomSignal(data), m_data(data), m_msg(m_data), m_code(m_data)
{
  m_data.out << "ctor(" << m_data.startWeek << ", " << m_data.startSecondOfWeek << ")\n";
}

CustomCA::~CustomCA()
{
  m_data.out << "dtor()\n";
}

ICustomSignalNavMsg* CustomCA::getNavMsg()
{
  m_data.out << "getNavMsg()\n";
  return &m_msg;
}

ICustomSignalCode* CustomCA::getCode(const char* name)
{
  m_data.out << "getCode(\"" << name << "\")\n";
  if (std::strcmp(name, "L1CA") == 0)
    return &m_code;
  return nullptr;
}

DEFINE_CUSTOM_SIGNAL(CustomCA)
