#ifndef __SESSION_H_
#define __SESSION_H_

#define HAVE_STDINT_H //Awkward workaround to get net-snmp to compile on windows.
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include "node.hpp"
#include "result.hpp"

class Session{
  public:
  Session(const Node& node);
  Result getAllOIDS();
  private:
  Node m_node;
};

#endif // __SESSION_H_
