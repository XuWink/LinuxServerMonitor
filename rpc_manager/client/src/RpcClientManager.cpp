#include "RpcClientManager.hpp"

namespace monitor {

std::shared_ptr<RpcClient> RpcClientManager::GetClient(const std::string& target) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (clients_.find(target) == clients_.end()) {
    clients_[target] = std::make_shared<RpcClient>(target);
  }
  return clients_[target];
}


}  // namespace monitor