#include <iostream>
#include <variant>
#include "node.hpp"
#include "nodes_manager.hpp"

void printResult(std::variant<long, std::string> result) {
  if (auto intResult = std::get_if<long>(&result)) {
    std::cout << *intResult << std::endl;
  }
  else if (auto strResult = std::get_if<std::string>(&result)) {
    std::cout << *strResult << std::endl;
  }
}

int main(int argc, char ** argv)
{
    Type PDU;
    PDU.addOID("1.3.6.1.4.1.318.1.1.26.10.2.2.1.8.1", "Temperature");
    Node firstPDU(PDU, "192.168.1.200", "public", printResult);
    Node secondPDU(PDU, "192.168.1.201", "public", printResult);
    NodesManager manager;
    manager.addNode(firstPDU);
    manager.addNode(secondPDU);
    manager.start();
    return (0);
}
