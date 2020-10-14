#ifndef __RESULT_H_
#define __RESULT_H_

#define HAVE_STDINT_H //Awkward workaround to use net-snmp on windows.
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#undef inline //Another workaround.
#include <variant>
#include <string>

//netsnmp_pdu is the data structure that we're given after making a request to a host.
//It could be a string, an int etc...(TODO: add other types from the docs)
//Currently, this class only handles ints and strings.

class Result{
  public:
  explicit Result(netsnmp_pdu* response);
  virtual ~Result() = default;
  std::variant<int,std::string> getValue() const;
  private:
  void parseResult();
  netsnmp_pdu* m_response;
};

#endif // __RESULT_H_
