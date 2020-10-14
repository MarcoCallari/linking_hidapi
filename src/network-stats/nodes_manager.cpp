#include "nodes_manager.hpp"


NodesManager::NodesManager(std::vector<Node> nodes, std::chrono::seconds pollingRate = 1s) m_nodes{nodes}, m_pollingRate{pollingRate}{

}

void NodesManager::addNode(Node& node){
  m_nodes.emplace_back(node);
}

void NodesManager::start(){
  for(const auto& node : m_nodes){
    Session session(node);
    Result result = session.getAllOIDS();
    std::variant<int,std::string> value = result.getValue();
  }
}
