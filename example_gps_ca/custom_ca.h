#pragma once

#include <fstream>

#include "../common/custom_signal_nav_msg_from_file.h"
#include "../custom_signal_interface.h"
#include "coarse_acquisition_code.h"

class CAData
{
public:
  CAData(const CSInitData& data);

  const uint32_t startWeek;
  const uint32_t startSecondOfWeek;

  const CoarseAcquisitionCode codes;
  CustomSignalNavMsgFromFile navMsg;

  std::ofstream out;
};

class CustomCANavMsg : public ICustomSignalNavMsg
{
public:
  CustomCANavMsg(CAData& data);

  uint32_t getNavMsgDurationMs() override;
  int32_t getTOWOffset() override;
  void buildNavMsg(int64_t elapsedTime, uint32_t prn, const CSConstellation& data) override;

private:
  CAData& m_data;
};

class CustomCACode : public ICustomSignalCode
{
public:
  CustomCACode(CAData& data);

  void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) override;
  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;

private:
  CAData& m_data;
};

class CustomCA : public ICustomSignal
{
public:
  CustomCA(const CSInitData& data);
  ~CustomCA();

  ICustomSignalNavMsg* getNavMsg() override;
  ICustomSignalCode* getCode(const char* name) override;

private:
  CAData m_data;
  CustomCANavMsg m_msg;
  CustomCACode m_code;
};
