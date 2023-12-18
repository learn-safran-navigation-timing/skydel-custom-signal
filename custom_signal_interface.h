#ifndef CUSTOM_SIGNAL_INTERFACE_H
#define CUSTOM_SIGNAL_INTERFACE_H

#include <cstdint>

#include "custom_signal_data.h"

#if _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __attribute__((visibility("default")))
#endif

#define CS_INTERFACE_VERSION 3

class ICustomSignalNavMsg
{
public:
  virtual ~ICustomSignalNavMsg() = default;

  // Return the navigation message duration, in millisecond
  virtual uint32_t getNavMsgDurationMs() = 0;

  // Return the offset between the message beginning and the time of week 0, in seconds
  virtual int32_t getTOWOffset() = 0;

  // Called every navMsgDuration
  // elapsedTime is an offset to the start time in millisecond
  // prn is the PRN transmitted by legacy signals on the same space vehicle
  virtual void buildNavMsg(int64_t elapsedTime, uint32_t prn, const CSConstellation& data) = 0;
};

class ICustomSignalCode
{
public:
  virtual ~ICustomSignalCode() = default;

  // Return the number of chips per ms
  virtual uint32_t getNumberOfChipsPerMSec() = 0;

  // Return the extra chips to allocate for the chips buffer
  virtual uint32_t getExtraAllocSize() = 0;

  // Called every millisecond
  // elapsedTime is an offset to the start time in millisecond
  // prn is the PRN transmitted by legacy signals on the same space vehicle
  // chips is a chip buffer allocated for <codeRate> / 1000 + extraAllocSize chips
  virtual void getChips(int64_t elapsedTime, uint32_t prn, int8_t* chips) = 0;
};

class ICustomSignal
{
public:
  /*
   * Your implementation should define a constructor like so:
   * MySignal(const CSInitData& data);
   */
  ICustomSignal(const CSInitData&) {}

  virtual ~ICustomSignal() = default;

  // Can be null in the case of a signal without navigation message
  virtual ICustomSignalNavMsg* getNavMsg() = 0;

  // Name is a null terminated string identifying the code
  virtual ICustomSignalCode* getCode(const char* name) = 0;
};

#ifndef IS_STATIC
#define DEFINE_CUSTOM_SIGNAL(className)                                                            \
  extern "C"                                                                                       \
  {                                                                                                \
    DLL_EXPORT extern const uint32_t csInterfaceVersion;                                           \
    const uint32_t csInterfaceVersion = CS_INTERFACE_VERSION;                                      \
    DLL_EXPORT ICustomSignal* createSignal(const CSInitData& data) { return new className(data); } \
  }
#else
#define DEFINE_CUSTOM_SIGNAL(className)
#endif // IS_STATIC

#endif // CUSTOM_SIGNAL_INTERFACE_H
