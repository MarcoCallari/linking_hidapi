#ifndef __RESULT_H_
#define __RESULT_H_

#define HAVE_STDINT_H //Awkward workaround to use net-snmp on windows.
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#undef inline //Another workaround.
#include "oid.hpp"
#include <variant>
#include <string>

//netsnmp_pdu is the data structure that we're given after making a request to a host.
//It could be a string, an int etc...(TODO: add other types from the docs)
//This class takes care of parsing that data.
//Currently, this class only handles ints and strings.

class Result{
  public:
  explicit Result(netsnmp_pdu* response, Oid oidRequested);
  virtual ~Result();
  std::variant<long,std::string> getValue() const;
  Oid getOID() const;
  private:
  std::variant<long,std::string> m_value;
  netsnmp_pdu* m_response{ nullptr };
  Oid m_oidRequested;
  std::variant<long,std::string> parseResult(const netsnmp_pdu * response) const;
};

#endif // __RESULT_H_
