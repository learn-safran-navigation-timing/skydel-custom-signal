#include "e1_nav_msg_from_file.h"
#include <filesystem>
#include <vector>
#include <sstream>
#include <stdexcept>

E1NavMsgFromFile::E1NavMsgFromFile(const std::string &filename)
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

void E1NavMsgFromFile::prepare(int64_t elapsed, uint32_t /*prn*/)
{
  while (m_file && m_msgs[0].timestamp < elapsed)
    parseBlock();
}

bool E1NavMsgFromFile::getBit(int64_t elapsed, uint32_t prn)
{
  const Msg& msg = m_msgs[prn - 1];
  return msg.bits[(elapsed - msg.timestamp) * 500 / 2000];
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

static void setBits(std::array<bool, 500>& bits, const std::string& str)
{
  std::istringstream iss(str);
  iss >> std::hex;

  uint32_t word;
  int i = 0;
  while (iss >> word)
  {
    for (int j = 0; j < 32; ++j)
    {
      if (i * 32 + j < 500)
        bits[i * 32 + j] = (word & (1 << (31 - j))) != 0;
    }
    ++i;
  }
}

static bool parseLine(const std::string& line, int64_t& out_timestamp, uint32_t& out_prn, std::string& out_bits)
{
  std::vector<std::string> values = split(line, ",");

  if (values.size() < 8)
    return false;
  out_timestamp = toInt64(values[0]);
  out_prn = static_cast<int32_t>(toInt64(values[2]));
  out_bits = values[7];
  return true;
}

void E1NavMsgFromFile::parseBlock()
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
