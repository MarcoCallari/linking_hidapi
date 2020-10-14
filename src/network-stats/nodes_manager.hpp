#ifndef __NODES_MANAGER_H_
#define __NODES_MANAGER_H_

#include "node.hpp"
#include <vector>
#include <thread>
#include <chrono>

class NodesManager{
  public:
  NodesManager() = default;
  NodesManager(std::vector<Node> nodes, std::chrono::seconds pollingRate);
  void addNode(Node& node);
  void start();
  private:
  std::chrono::seconds m_pollingRate = std::chrono::seconds(1);
  std::vector<Node> m_nodes;
  std::thread m_childThread;
};

#endif // __NODES_MANAGER_H_
