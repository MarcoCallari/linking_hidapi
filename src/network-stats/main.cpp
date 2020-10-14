#include <iostream>
#include <string>
#include <variant>
#include "node.hpp"
#include "nodes_manager.hpp"

void printResult(const std::variant<long, std::string> result) {
  if (auto intResult = std::get_if<long>(&result)) {
    std::cout << " " << *intResult << std::endl;
  }
  else if (auto strResult = std::get_if<std::string>(&result)) {
    std::cout << " " << *strResult << std::endl;
  }
}

int main(int argc, char ** argv)
{
    Type PDU;
    PDU.addOID("1.3.6.1.4.1.318.1.1.26.10.2.2.1.8.1", "Temperature(C)");
    PDU.addOID("1.3.6.1.4.1.318.1.1.26.6.3.1.5.1", "Current(A)");
    PDU.addOID("1.3.6.1.4.1.318.1.1.26.6.3.1.6.1", "Voltage(V)");
    PDU.addOID("1.3.6.1.4.1.318.1.1.26.6.3.1.7.1", "Power consumption(KW)");
    Node firstPDU(PDU, "192.168.1.200", "public", printResult);
    Node secondPDU(PDU, "192.168.1.201", "public", printResult);
    Type Server;
    NodesManager manager;
    manager.addNode(firstPDU);
    manager.addNode(secondPDU);
    manager.start();
    return (0);
}
