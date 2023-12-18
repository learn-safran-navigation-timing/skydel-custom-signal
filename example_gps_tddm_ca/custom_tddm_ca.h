#pragma once

#include <fstream>

#include "../common/coarse_acquisition_code.h"
#include "../common/custom_signal_nav_msg_from_file.h"
#include "../custom_signal_interface.h"

class TddmCAData
{
public:
  TddmCAData(const CSInitData& data);

  const uint32_t startWeek;
  const uint32_t startSecondOfWeek;

  const CoarseAcquisitionCode codes;
  CustomSignalNavMsgFromFile navMsg;
};

class CustomTddmCANavMsg : public ICustomSignalNavMsg
{
public:
  CustomTddmCANavMsg(TddmCAData& data);

  uint32_t getNavMsgDurationMs() override;
  int32_t getTOWOffset() override;
  void buildNavMsg(int64_t elapsedTime, uint32_t prn, const CSConstellation& data) override;

private:
  TddmCAData& m_data;
};

class CustomTddmCACode : public ICustomSignalCode
{
public:
  CustomTddmCACode(TddmCAData& data);

  void getChips(int64_t elapsedMs, uint32_t prn, int8_t* chips) override;
  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;

private:
  TddmCAData& m_data;
};

class CustomTddmCA : public ICustomSignal
{
public:
  CustomTddmCA(const CSInitData& data);
  ~CustomTddmCA();

  ICustomSignalNavMsg* getNavMsg() override;
  ICustomSignalCode* getCode(const char* name) override;

private:
  TddmCAData m_data;
  CustomTddmCANavMsg m_msg;
  CustomTddmCACode m_code;
};
