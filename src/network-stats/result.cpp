#include "result.hpp"
#include <iostream> //TODO: use another logger?

Result::Result(netsnmp_pdu* response) : m_response{response} {
  m_value = parseResult(m_response);
}

Result::~Result() {
//  delete m_response;
}

std::variant<long,std::string> Result::getValue() const{
  return m_value;
}

std::variant<long ,std::string> Result::parseResult(const netsnmp_pdu* response) const{
  netsnmp_variable_list *vars;
  std::variant<long,std::string> value;
  int count = 0;
  for (vars = response->variables; vars; vars = vars->next_variable)
    {
      if (vars->type == ASN_OCTET_STR)
        {
          std::cout << "Received a string: \"" << std::endl;
          std::cout << *(vars->val.string) <<"\"" << std::endl;
          value = std::string(reinterpret_cast<char*>(vars->val.string));
        }
      else if (vars->type == ASN_INTEGER)
        {
          std::cout << "Received an integer: \"";
          std::cout << *(vars->val.integer) <<"\"" << std::endl;
          value = *(vars->val.integer);
        }
      else
        std::cout << "Received a data type that hasn't been implemented yet." << std::endl;
    }
  delete vars;
  return value;
}
