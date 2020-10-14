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
    std::vector<Result> results = session.getAllOIDS();
    for (const auto& result : results) {
      auto value = result.getValue();
      node.execCallback(value);
    }
  }
}
