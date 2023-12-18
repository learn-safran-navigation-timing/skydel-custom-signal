#pragma once

#include <fstream>

#include "../common/coarse_acquisition_code.h"
#include "../common/custom_signal_nav_msg_from_file.h"
#include "../custom_signal_interface.h"

class QzssCAData
{
public:
  QzssCAData(const CSInitData& data);

  const uint32_t startWeek;
  const uint32_t startSecondOfWeek;

  const CoarseAcquisitionCode codes;
  CustomSignalNavMsgFromFile navMsg;
};

class CustomQzssCANavMsg : public ICustomSignalNavMsg
{
public:
  CustomQzssCANavMsg(QzssCAData& data);

  uint32_t getNavMsgDurationMs() override;
  int32_t getTOWOffset() override;
  void buildNavMsg(int64_t elapsedTime, uint32_t prn, const CSConstellation& data) override;

private:
  QzssCAData& m_data;
};

class CustomQzssCACode : public ICustomSignalCode
{
public:
  CustomQzssCACode(QzssCAData& data);

  void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) override;
  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;

private:
  QzssCAData& m_data;
};

class CustomQzssCA : public ICustomSignal
{
public:
  CustomQzssCA(const CSInitData& data);
  ~CustomQzssCA();

  ICustomSignalNavMsg* getNavMsg() override;
  ICustomSignalCode* getCode(const char* name) override;

private:
  QzssCAData m_data;
  CustomQzssCANavMsg m_msg;
  CustomQzssCACode m_code;
};
