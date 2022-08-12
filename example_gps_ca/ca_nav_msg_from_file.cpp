#include "ca_nav_msg_from_file.h"
#include <filesystem>
#include <vector>
#include <sstream>
#include <stdexcept>

CANavMsgFromFile::CANavMsgFromFile(const std::string &filename)
  : m_file(std::filesystem::u8path(filename))
{
  if (!m_file)
    throw std::runtime_error{"Couldn't open file " + filename};

  // skip header
  std::string headerLine;
  std::getline(m_file, headerLine);

  // get the first line
  std::getline(m_file, m_lastLine);

  parseBlock();
}

void CANavMsgFromFile::prepare(int64_t elapsed, uint32_t /*prn*/)
{
  while (m_file && m_msgs[0].timestamp < elapsed)
    parseBlock();
}

bool CANavMsgFromFile::getBit(int64_t elapsed, uint32_t prn)
{
  return m_msgs[prn - 1].bits[(elapsed % 6000) * 300 / 6000];
}

static std::vector<std::string> split(const std::string& str, const std::string& delim)
{
  std::vector<std::string> sent;
  std::string::size_type pos = 0;

  while (true)
  {
    std::string::size_type delimPos = str.find(delim, pos);
    sent.push_back(str.substr(pos, delimPos - pos));
    if (delimPos == std::string::npos)
      break;
    pos = delimPos + delim.size();
  }
  return sent;
}

int64_t toInt64(const std::string& str)
{
  int64_t sent = 0;
  std::istringstream iss(str);
  iss >> sent;
  return sent;
}

static void setBits(std::array<bool, 300>& bits, const std::string& str)
{
  std::istringstream iss(str);
  iss >> std::hex;

  for (int i = 0; i < 10; ++i)
  {
    uint32_t word = 0;
    iss >> word;

    for (int j = 0; j < 30; ++j)
      bits[i * 30 + j] = word & (1 << (29 - j));
  }
}

static bool parseLine(const std::string& line, int64_t& out_timestamp, uint32_t& out_prn, std::string& out_bits)
{
  std::vector<std::string> values = split(line, ",");

  if (values.size() < 7)
    return false;
  out_timestamp = toInt64(values[0]);
  out_prn = static_cast<int32_t>(toInt64(values[1]));
  out_bits = values[6];
  return true;
}

void CANavMsgFromFile::parseBlock()
{
  int64_t timestamp;
  int64_t firstTimestamp;
  uint32_t prn;
  std::string bits;

  if (!parseLine(m_lastLine, timestamp, prn, bits))
    return ;

  firstTimestamp = timestamp;

  do
  {
    m_msgs[prn - 1].timestamp = timestamp;
    setBits(m_msgs[prn - 1].bits, bits);
  } while (std::getline(m_file, m_lastLine)
           && parseLine(m_lastLine, timestamp, prn, bits)
           && timestamp == firstTimestamp);
}
