#ifndef COARSE_ACQUISITION_CODE_H
#define COARSE_ACQUISITION_CODE_H

#include <cstdint>
#include <vector>
#include <array>

class CoarseAcquisitionCode
{
public:
  CoarseAcquisitionCode();

  // prn for GPS : 1..32
  // prn for EGNOS and WAAS : 33..51 --> Note in this case, true_prn = prn + 87
  // bit_index is zero based : 0..1022
  const std::int8_t* code(std::uint32_t prn) const; // returns the entire code for a prn

private:
  std::vector<std::array<int8_t, 1023>> ca_codes;
};

#endif // COARSE_ACQUISITION_CODE_H
