#ifndef __SESSION_H_
#define __SESSION_H_
#include <memory>
#include <string>
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>


class Session{
  private:
  netsnmp_session m_request;
  netsnmp_session* m_activeSession;
  public:
  Session(const std::string peername, const std::string community);
  virtual ~Session() = default;
  void request(const std::string oid);
};

#endif // __SESSION_H_
