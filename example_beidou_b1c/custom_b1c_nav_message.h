#ifndef CUSTOM_B1C_NAV_MESSAGE_H
#define CUSTOM_B1C_NAV_MESSAGE_H

#include <memory>
#include <string>

#include "custom_signal_interface.h"

class CustomSignalNavMsgFromFile;

class CustomB1CNavMsg : public ICustomSignalNavMsg
{
public:
  CustomB1CNavMsg();
  ~CustomB1CNavMsg() override;
  uint32_t getNavMsgDurationMs() override;
  int32_t getTOWOffset() override;
  void buildNavMsg(int64_t elapsedTime, uint32_t prn, const CSConstellation& data) override;
  void setNavMessageGenerator(std::shared_ptr<CustomSignalNavMsgFromFile>);
  static std::shared_ptr<CustomSignalNavMsgFromFile> makeSharedB1CNavMsgFromFile(std::string downlinkPath);

private:
  struct Pimpl;
  std::unique_ptr<Pimpl> m;
};

#endif // CUSTOM_B1C_NAV_MESSAGE_H
