#include <fstream>
#include <array>

class E1NavMsgFromFile
{
public:
  explicit E1NavMsgFromFile(const std::string& filename);

  void prepare(int64_t elapsed, uint32_t prn);
  bool getBit(int64_t elapsed, uint32_t prn);

private:
  std::ifstream m_file;
  std::string m_lastLine;

  void parseBlock();

  struct Msg
  {
    int64_t timestamp;
    std::array<bool, 500> bits;
  };

  std::array<Msg, 36> m_msgs;
};
