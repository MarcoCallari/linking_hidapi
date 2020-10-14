#include "result.hpp"

Result::Result(std::variant<int,std::string> value) : m_value{value} {

}

std::variant<int,std::string> getValue() const{
  return m_value;
}
