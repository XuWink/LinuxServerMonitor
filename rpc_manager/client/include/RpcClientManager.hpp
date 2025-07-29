#include "Logger.hpp"
#include "RpcClient.hpp"

#include <algorithm>
#include <memory>
#include <mutex>
#include <unordered_map>

namespace monitor {

class RpcClientManager {
  public:
    RpcClientManager() {}

    ~RpcClientManager() {}

    std::shared_ptr<RpcClient> GetClient(const std::string & target);

  private:
    std::unordered_map<std::string, std::shared_ptr<RpcClient>> clients_;
    std::mutex                                                  mutex_;
};

}  // namespace monitor
