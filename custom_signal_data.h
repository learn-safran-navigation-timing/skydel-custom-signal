#pragma once

#include <cstdint>
#include <vector>

//
// CUSTOM SIGNAL Data Structure
//
extern "C"
{

  struct CSInitData
  {
    /*
     * startWeek and startSecondOfWeek are defining the simulation start time
     * startWeek is the week number relative to the epoch of the attached constellation
     * startSecondOfWeek is the second number in that week, between 0 and 604799.
     */
    uint32_t startWeek;
    uint32_t startSecondOfWeek;
    char pathToXml[512];   // NULL terminated string
    char xmlFileName[512]; // NULL terminated string
  };

  enum CSConstellationEnum
  {
    GPS,
    GALILEO,
    BEIDOU,
    CONSTELLATION_COUNT
  };

  struct CSGpsEphemeris
  {
    double gpsTgd; // gps time group delay // seconds

    std::uint32_t iodc; // Issue of Data, Clock

    std::uint32_t codesOnL2;
    std::uint32_t l2PDataFlag;

    std::uint32_t svSignalHealth; // 0..31  (0 all signals ok)
    std::uint32_t svDataHealth;   // 0..7   (0 data data ok)

    std::uint32_t fitInterval;

    std::uint32_t uraIndex;
    std::uint32_t integrityStatusFlag; // bit (0 = ok)
    std::uint32_t l2CPhasing;          // bit

    double uraEdIndex;
    double uraNed0Index;
    double uraNed1Index;
    double uraNed2Index;

    bool iscL1CaAvailable;
    bool iscL2CAvailable;
    bool iscL5I5Available;
    bool iscL5Q5Available;
    bool iscL1CPAvailable;
    bool iscL1CDAvailable;
    double iscL1Ca; // seconds
    double iscL2C;  // seconds
    double iscL5I5; // seconds
    double iscL5Q5; // seconds
    double iscL1CP; // seconds
    double iscL1CD; // seconds

    std::uint8_t signalHealth;
    std::uint8_t dataHealth;
    int svConfig;
    bool l1Health;
    bool l2Health;
    bool l5Health;
    bool l1cHealth;
    bool navAlertFlag;
    bool cNavAlertFlag;
  };

  struct CSGalileoEphemeris
  {
    double galileoBgdE5a; // galileo broadcast group delay E5a  // seconds
    double galileoBgdE5b; // galileo broadcast group delay E5b // seconds

    std::uint32_t sisaE5a;
    std::uint32_t sisaE5b;

    std::uint32_t signalHealthE5a;
    std::uint32_t signalHealthE5b;
    std::uint32_t signalHealthE1B;
    bool dataHealthE5a;
    bool dataHealthE5b;
    bool dataHealthE1B;
  };

  struct CSBeiDouEphemeris
  {
    double beiDouTgd1;    // beidou time group delay 1 // seconds
    double beiDouTgd2;    // beidou time group delay 2 // seconds
    double beiDouTgdb1cp; // beiDou time group delay B1Cp // seconds
    double beiDouTgdb2ap; // beiDou time group delay B2ap // seconds

    std::uint32_t aodc;  // Age of Data, Clock
    std::uint32_t aode;  // Age of Data, Ephemeris
    std::uint32_t iodc;  // Issue of Data, Clock
    std::uint32_t satH2; // Satellite Health Flag for Integrity and Differential Correction Information
    bool iscB1CdAvailable;
    double iscB1Cd; // seconds
                    //  (2020/05) to add to the next version of the interface:
                    //  bool iscB2adAvailable;
                    //  double iscB2ad;          // seconds
    std::uint32_t uraIndex;

    std::uint16_t healthInfo;
    bool autonomousHealth;
    std::uint8_t cnavHealthInfo;
    std::uint8_t healthStatus;
  };

  struct CSEphemeris
  {
    uint32_t prn;

    std::uint32_t iod; // iode (Issue of Data, Ephemeris) or iodnav (Issue of Data of the nav batch)

    uint32_t wnop; // week num of prediction // gps weeks
    uint32_t top;  // time of predicition // seconds

    uint32_t wnoc; // week num of clock // gps weeks
    uint32_t toc;  // time of clock // seconds
    double af0;    // sv cock bias // seconds
    double af1;    // sv cock drift // sec/sec
    double af2;    // sv cock drift rate // sec/sec^2

    uint32_t wnoe; // week num of ephemeris // gps weeks
    uint32_t toe;  // time of ephemeris // seconds

    double sqrtA;             // square root semi major axis // sqrt(meters)
    double eccentricity;      // eccentricity // unitless
    double inclination;       // inclination angle // semi-circles
    double lonAscendNode;     // longitude of ascending node // semi-circles
    double rateOfRightAscen;  // rate of right ascension (bigOmegaDot) // semi-circles/sec^2
    double meanAnomaly;       // mean anomaly // semi-circles
    double argumentOfPerigee; // argument of perigee
    double meanMotionDiff;    // mean motion difference // semi-circles/sec

    double iDot;       // rate of inclination angle // semi-circles/sec
    double aDot;       // change rate in semi-major axis // meters/sec
    double deltaN0Dot; // rate of mean motion difference  // semi-circles/sec^2

    double crs; // correction radius sine // meters
    double crc; // correction radius cosine // meters
    double cuc; // correction argument lat sine // radians
    double cus; // correction argument lat sine // radians
    double cic; // correction inclination sine // radians
    double cis; // correction inclination sine // radians

    CSConstellationEnum constellation;

    CSGpsEphemeris gpsEphemeris;
    CSGalileoEphemeris galileoEphemeris;
    CSBeiDouEphemeris beidouEphemeris;
  };

  ///
  /// Terms for ionospheric corrections
  ///
  struct CSIonosphereTerms
  {
    double alpha0; // seconds
    double alpha1; // seconds/semi-circle
    double alpha2; // seconds/semi-circle^2
    double alpha3; // seconds/semi-circle^3
    double beta0;  // seconds
    double beta1;  // seconds/semi-circle
    double beta2;  // seconds/semi-circle^2
    double beta3;  // seconds/semi-circle^3
  };

  ///
  /// Terms for UTC calculation
  ///
  struct CSUtcTerms
  {
    uint32_t tot;      // Time data reference TOW
    uint32_t wnot;     // time data reference week number
    double a0;         // bias coefficient of GPS to UTC
    double a1;         // drift coefficient of GPS to UTC
    double a2;         // drift rate coefficient of GPS to UTC
    uint32_t deltaTLS; // leap second count
    uint32_t wnLSF;    // week number of future leap second
    uint32_t dn;       // day of future leap second
    int32_t deltaTLSF; // current or future leap second count
  };

  ///
  /// Earth orientation parameters for ECEF-to-ECI coordinate transformation
  ///
  struct CSPolarMotionTerms
  {
    double pmx;         // X-Axis polar motion     arc-seconds
    double pmxDot;      // Polar motion drift (X)  arc-seconds/day
    double pmy;         // Y-Axis polar motion     arc-seconds
    double pmyDot;      // polar motion drift (Y)  arc-seconds/day
    double deltaUT1;    // UT1-UTV, seconds
    double deltaUT1Dot; // UT1-UTV Drift, seconds/day
  };

  ///
  /// This struct is to contain all pertinent information regarding the CS
  /// constellation, including SV ephemeris, configuration and more in future
  /// versions of this library.
  ///
  /// "config" and "ephemeris" are vectors to contain prnCount number of their respective
  /// structs, and are zero based, with index 0 corresponding to PRN 1.
  ///
  struct CSConstellation
  {
    uint32_t prnCount;
    std::vector<CSEphemeris> ephemeris;
    CSIonosphereTerms ionosphere;
    CSUtcTerms utc;
    CSPolarMotionTerms polarMotion;
  };
}
