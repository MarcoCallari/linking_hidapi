#include "oid.hpp"

Oid::Oid(std::string code, std::string name) : m_code{code} , m_name{name}{

}

void Oid::setCode(const std::string& code){
  m_code = code;
}

void Oid::setName(const std::string& name){
  m_name = name;
}

std::string Oid::getCode() const{
  return m_code;
}

std::string Oid::getName() const{
  return m_name;
}
