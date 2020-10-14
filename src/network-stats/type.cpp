#include "type.hpp"

Type::Type(std::map<std::string , std::string> oids) : m_oids{oids}{
}

Type::Type(const Type& rhs){
  m_oids = rhs.getOIDS();
}

void Type::operator=(const Type& rhs){
  m_oids = rhs.getOIDS();
}

std::map<std::string,std::string> Type::getOIDS() const{
  return m_oids;
}

bool Type::addOID(std::string oid, std::string name){
  auto result = m_oids.insert(std::make_pair(oid,name));
  return result.second;
}
