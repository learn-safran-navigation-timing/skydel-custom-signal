#ifndef CUSTOM_B1C_CODE_H
#define CUSTOM_B1C_CODE_H

#include <memory>

#include "custom_signal_interface.h"

class CustomSignalNavMsgFromFile;

class CustomB1CDataCode : public ICustomSignalCode
{
public:
  static constexpr auto xmlCodeName = "B1CData";
  CustomB1CDataCode();
  ~CustomB1CDataCode() override;

  void setNavMessageGenerator(std::shared_ptr<CustomSignalNavMsgFromFile>);

  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;
  void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) override;

private:
  struct Pimpl;
  std::unique_ptr<Pimpl> m;
};

class CustomB1CPilotaCode : public ICustomSignalCode
{
public:
  static constexpr auto xmlCodeName = "B1CPilotA";

  CustomB1CPilotaCode();
  ~CustomB1CPilotaCode() override;

  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;
  void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) override;

private:
  struct Pimpl;
  std::unique_ptr<Pimpl> m;
};

class CustomB1CPilotbCode : public ICustomSignalCode
{
public:
  static constexpr auto xmlCodeName = "B1CPilotB";

  CustomB1CPilotbCode();
  ~CustomB1CPilotbCode() override;

  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;
  void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) override;

private:
  struct Pimpl;
  std::unique_ptr<Pimpl> m;
};

#endif // CUSTOM_B1C_CODE_H
