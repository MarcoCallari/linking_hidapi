#ifndef __NODE_H_
#define __NODE_H_
#include <type.hpp>
#include <functional>
#include <variant>
#include <string>

class Node{
  public:
  Node(const Type type, const std::string ip, const std::string communityName, std::function<void(std::variant<long, std::string>, Oid oidRequested) > );
  virtual ~Node() = default;
  std::string getIP() const;
  std::string getCommunityName() const;
  std::vector<Oid> getOIDS() const;
  void execCallback(std::variant<long, std::string> value, Oid oidRequested) const;

  private:
  const std::string m_ip;
  const std::string m_communityName;
  const Type m_type;
  const std::function<void(std::variant<long, std::string>, Oid oidRequested)> m_callbackFunc;
};

#endif // __NODE_H_
