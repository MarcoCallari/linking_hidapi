#include "node.hpp"

Node::Node(const Type type, const std::string ip, const std::string communityName) : m_type{type} , m_ip{ip} , m_communityName{communityName}{
}

std::string Node::getIP() const{
  return m_ip;
}

std::string Node::getCommunityName() const{
 return m_communityName;
}

std::map<std::string, std::string> Node::getOIDS() const{
  return m_type.getOIDS();
}
