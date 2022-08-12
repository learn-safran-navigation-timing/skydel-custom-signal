#pragma once

#include "e1_code.h"
#include "custom_signal_interface.h"
#include "e1_nav_msg_from_file.h"
#include <fstream>

class E1Data
{
public:
  E1Data(const CSInitData& data);

  const uint32_t startWeek;
  const uint32_t startSecondOfWeek;

  E1Code code;
  E1NavMsgFromFile navMsg;

};

class CustomE1NavMsg : public ICustomSignalNavMsg
{
public:
  CustomE1NavMsg(E1Data& data);

  uint32_t getNavMsgDurationMs() override;
  int32_t getTOWOffset() override;
  void buildNavMsg(int64_t elapsedTime, uint32_t prn, const CSConstellation &data) override;

private:
  E1Data& m_data;
};

class CustomE1BCode : public ICustomSignalCode
{
public:
  CustomE1BCode(E1Data& data);

  void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) override;
  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;

private:
  E1Data& m_data;
};

class CustomE1CCode : public ICustomSignalCode
{
public:
  CustomE1CCode(E1Data& data);

  void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) override;
  uint32_t getNumberOfChipsPerMSec() override;
  uint32_t getExtraAllocSize() override;

private:
  E1Data& m_data;
};

class CustomE1 : public ICustomSignal
{
public:
  CustomE1(const CSInitData& data);

  ICustomSignalNavMsg *getNavMsg() override;
  ICustomSignalCode* getCode(const char* name) override;

private:
  E1Data m_data;
  CustomE1NavMsg m_msg;
  CustomE1BCode m_e1bCode;
  CustomE1CCode m_e1cCode;
};
