#ifndef __SESSION_H_
#define __SESSION_H_

#define HAVE_STDINT_H //Awkward workaround to use net-snmp on windows.
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#undef inline //Another workaround.

#include "node.hpp"
#include "result.hpp"

class Session{
  public:
  Session(const Node& node);
  Result getAllOIDS();
  private:
  Node m_node;
  netsnmp_session* m_session;
  void connectSession();
};

#endif // __SESSION_H_
