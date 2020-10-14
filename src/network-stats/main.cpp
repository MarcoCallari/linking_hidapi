#include <iostream>
#include <unordered_map>
#include "nodes_manager.hpp"

void printResult(const std::variant<long, std::string> result, const Oid oidRequested) {
  if (auto intResult = std::get_if<long>(&result)) {
    std::cout << oidRequested.getName() << ": " << *intResult << std::endl;
  }
  else if (auto strResult = std::get_if<std::string>(&result)) {
    std::cout << oidRequested.getName() << ": " << *strResult << std::endl;
  }
}

int main(int argc, char ** argv)
{
    //std::unordered_map<Oid, int> resultFormat;
    //resultFormat[Oid("1", "Temperature (C)")] = 10;
    std::cout << (Oid("1", "2") == Oid("1", "2"));
    Type PDU;
    PDU.addOID("1.3.6.1.4.1.318.1.1.26.10.2.2.1.8.1", "Temperature (C)");
    PDU.addOID("1.3.6.1.4.1.318.1.1.26.6.3.1.5.1", "Current (A)");
    PDU.addOID("1.3.6.1.4.1.318.1.1.26.6.3.1.6.1", "Voltage (V)");
    PDU.addOID("1.3.6.1.4.1.318.1.1.26.6.3.1.7.1", "Power consumption (KW)");
    Node firstPDU(PDU, "192.168.1.200", "public", printResult);
    Node secondPDU(PDU, "192.168.1.201", "public", printResult);
    Type Server;
    NodesManager manager;
    manager.addNode(firstPDU);
    manager.addNode(secondPDU);
    manager.start();
    return (0);
}
