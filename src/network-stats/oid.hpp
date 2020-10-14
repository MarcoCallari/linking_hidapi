#ifndef __OID_H_
#define __OID_H_
#include <string>

class Oid{
  public:
  Oid(std::string code, std::string name);
  Oid(const Oid& rhs);
  virtual ~Oid() = default;
  bool operator==(const Oid& rhs);
  void setCode(const std::string& code);
  void setName(const std::string& name);
  std::string getCode() const;
  std::string getName() const;
  private:
  std::string m_code;
  std::string m_name;
};

#endif // __OID_H_
