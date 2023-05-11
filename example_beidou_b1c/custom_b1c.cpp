#include "custom_b1c.h"

#include <filesystem>
#include <string>

#include "custom_b1c_codes.h"
#include "custom_b1c_nav_message.h"

namespace
{
constexpr auto DOWNLINK_FILENAME = "custom_b1c_downlink.csv";
}

struct CustomB1C::Pimpl
{
  CustomB1CDataCode csDataCode;
  CustomB1CPilotaCode csPilotaCode;
  CustomB1CPilotbCode csPilotbCode;
  CustomB1CNavMsg csNavMsg;
};

CustomB1C::CustomB1C(const CSInitData& csInitData) : ICustomSignal(csInitData), m(std::make_unique<Pimpl>())
{
  auto navGenPtr = CustomB1CNavMsg::makeSharedB1CNavMsgFromFile(
    (std::filesystem::path(csInitData.pathToXml) / DOWNLINK_FILENAME).string());
  m->csDataCode.setNavMessageGenerator(navGenPtr);
  m->csNavMsg.setNavMessageGenerator(navGenPtr);
}

CustomB1C::~CustomB1C()
{
}

ICustomSignalNavMsg* CustomB1C::getNavMsg()
{
  return &m->csNavMsg;
}

ICustomSignalCode* CustomB1C::getCode(const char* name)
{
  if (name == std::string(CustomB1CDataCode::xmlCodeName))
  {
    return &m->csDataCode;
  }
  else if (name == std::string(CustomB1CPilotaCode::xmlCodeName))
  {
    return &m->csPilotaCode;
  }
  else if (name == std::string(CustomB1CPilotbCode::xmlCodeName))
  {
    return &m->csPilotbCode;
  }
  return nullptr;
}

DEFINE_CUSTOM_SIGNAL(CustomB1C)
