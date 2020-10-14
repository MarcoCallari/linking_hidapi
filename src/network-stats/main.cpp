#include <iostream>
#include <map>
#include "nodes_manager.hpp"

struct cmpOid 
{
   bool operator() (const Oid& lhs, const Oid& rhs) const
   {
       return lhs.getName() < rhs.getName();
   }
};

std::map< Oid, double, cmpOid> resultFormat;

void printResult(const std::variant<long, std::string> result, const Oid oidRequested) {
  double format = resultFormat[oidRequested];
  if (auto intResult = std::get_if<long>(&result)) {
    const double formattedResult = (*intResult) / format;
    std::cout << oidRequested.getName() << ": " << formattedResult << std::endl;
  }
  else if (auto strResult = std::get_if<std::string>(&result)) {
    std::cout << oidRequested.getName() << ": " << *strResult << std::endl;
  }
}


int main(int argc, char ** argv)
{
    resultFormat[Oid("1.3.6.1.4.1.318.1.1.26.10.2.2.1.8.1", "Temperature (C)")] = 10.0;
    resultFormat[Oid("1.3.6.1.4.1.318.1.1.26.6.3.1.5.1", "Current (A)")] = 10.0;
    resultFormat[Oid("1.3.6.1.4.1.318.1.1.26.6.3.1.6.1", "Voltage (V)")] = 1.0;
    resultFormat[Oid("1.3.6.1.4.1.318.1.1.26.6.3.1.7.1", "Power consumption (kW)")] = 100.0;
    Type PDU;
    for (const auto& currOid : resultFormat)
      PDU.addOID(currOid.first);
    Node firstPDU(PDU, "192.168.1.200", "public", printResult);
    Node secondPDU(PDU, "192.168.1.201", "public", printResult);
    Type Server;
    NodesManager manager;
    manager.addNode(firstPDU);
    manager.addNode(secondPDU);
    manager.start();
    return (0);
}
