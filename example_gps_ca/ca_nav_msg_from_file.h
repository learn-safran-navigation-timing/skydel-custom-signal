#include <fstream>
#include <array>

class CANavMsgFromFile
{
public:
  explicit CANavMsgFromFile(const std::string& filename);

  void prepare(int64_t elapsed, uint32_t prn);
  bool getBit(int64_t elapsed, uint32_t prn);

private:
  std::ifstream m_file;
  std::string m_lastLine;

  void parseBlock();

  struct Msg
  {
    int64_t timestamp;
    std::array<bool, 300> bits;
  };

  std::array<Msg, 32> m_msgs;
};
