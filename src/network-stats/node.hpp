#ifndef __NODE_H_
#define __NODE_H_
#include <type.hpp>
#include <string>

class Node{
  public:
  Node(const Type type, const std::string ip, const std::string communityName);
  virtual ~Node() = default;
  std::string getIP() const;
  std::string getCommunityName() const;
  std::map<std::string, std::string> getOIDS() const;
  private:
  const std::string m_ip;
  const std::string m_communityName;
  const Type m_type;
};

#endif // __NODE_H_
