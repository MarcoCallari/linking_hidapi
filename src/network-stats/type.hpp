#ifndef __TYPE_H_
#define __TYPE_H_

#include "oid.hpp"
#include <vector>

class Type{
  public:
  Type() = default;
  explicit Type(std::vector<Oid> oids);
  virtual ~Type() = default;
  Type(const Type& rhs);
  void operator=(const Type& rhs);
  std::vector<Oid> getOIDS() const;
  void addOID(const std::string& oidToAdd, const std::string& name);
  void addOID(const Oid& oid);
  private:
  std::vector<Oid> m_oids;
};

#endif // __TYPE_H_
