#include "type.hpp"

Type::Type(std::vector<Oid> oids) : m_oids{oids}{
}

Type::Type(const Type& rhs){
  m_oids = rhs.getOIDS();
}

void Type::operator=(const Type& rhs){
  m_oids = rhs.getOIDS();
}

std::vector<Oid> Type::getOIDS() const{
  return m_oids;
}

void Type::addOID(const std::string& oidToAdd, const std::string& name){
  m_oids.emplace_back(oidToAdd,name);
}

/*void Type::addOID(const Oid& oid){
  m_oids.emplace_back(oid);
}*/ //TODO: oid needs a copy constructor
