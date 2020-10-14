#ifndef __NODES_MANAGER_H_
#define __NODES_MANAGER_H_

#include "node.hpp"
#include <thread>
#include <chrono>

class NodesManager{
  public:
  NodesManager() = default;
  NodesManager(std::vector<Node> nodes, std::chrono::seconds pollingRate = 1s);
  void addNode(Node& node);
  private:
  std::chrono:seconds m_pollingRate;
  std::vector<Node> m_nodes;
  std::thread m_childThread;
};

#endif // __NODES_MANAGER_H_
