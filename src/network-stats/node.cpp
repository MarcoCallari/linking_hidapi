#include "node.hpp"

Node::Node(const Type type, const std::string ip, const std::string communityName, std::function<void(std::variant<long, std::string>)> callbackFunc) : m_type{ type }, m_ip{ ip }, m_communityName{ communityName }, m_callbackFunc{ callbackFunc }{
}

std::string Node::getIP() const{
  return m_ip;
}

std::string Node::getCommunityName() const{
 return m_communityName;
}

std::vector<Oid> Node::getOIDS() const{
  return m_type.getOIDS();
}

void Node::execCallback(std::variant<long, std::string> value) const {
  m_callbackFunc(value);
}
