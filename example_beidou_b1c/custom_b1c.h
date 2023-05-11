#ifndef CUSTOM_B1C_H
#define CUSTOM_B1C_H

#include <memory>

#include "custom_signal_interface.h"

class CustomB1C final : public ICustomSignal
{
public:
  CustomB1C(const CSInitData&);

  ~CustomB1C() override;

  ICustomSignalNavMsg* getNavMsg() override;

  ICustomSignalCode* getCode(const char* name) override;

private:
  struct Pimpl;
  std::unique_ptr<Pimpl> m;
};

#endif // CUSTOM_B1C_H
