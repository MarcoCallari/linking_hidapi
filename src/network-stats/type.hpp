#ifndef __TYPE_H_
#define __TYPE_H_

#include <string>
#include <map>

class Type{
  public:
  Type() = default;
  explicit Type(std::map<std::string, std::string> oids); //The first string will be the oid itself,
                                                //the 2nd string will be the name assigned to it.
  virtual ~Type() = default;
  Type(const Type& rhs);
  std::map<std::string,std::string> getOIDS() const;
  bool addOID(std::string oid, std::string name);
  void operator=(const Type& rhs);
  private:
  std::map<std::string, std:: string> m_oids;
};

#endif // __TYPE_H_
