#ifndef __NODE_H_
#define __NODE_H_
#include <type.hpp>
#include <string>

class Node{
  public:
  Node(const Type type, const std::string ip, const std::string communityName);
  virtual ~Node() = default;
  private:
  const std::string m_ip;
  const std::string m_communityName;
  const Type m_type;
};

#endif // __NODE_H_
