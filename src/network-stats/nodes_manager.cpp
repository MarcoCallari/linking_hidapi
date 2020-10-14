#include "nodes_manager.hpp"
#include "session.hpp"
#include <variant>

NodesManager::NodesManager(std::vector<Node> nodes, std::chrono::seconds pollingRate) : m_nodes{nodes}, m_pollingRate{pollingRate}{

}

void NodesManager::addNode(Node& node){
  m_nodes.emplace_back(node);
}

void NodesManager::start(){
  for(const auto& node : m_nodes){
    Session session(node);
    Result result = session.getAllOIDS();
    auto value = result.getValue();
  }
}
