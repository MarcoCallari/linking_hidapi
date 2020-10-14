#include "oid.hpp"

Oid::Oid(std::string code, std::string name) : m_code{code} , m_name{name}{

}

bool Oid::operator==(const Oid& rhs){
  return (m_name == rhs.getName() &&
          m_code == rhs.getCode()); 
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
