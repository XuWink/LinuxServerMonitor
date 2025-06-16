#include "RpcClient.hpp"

namespace monitor {

RpcClient::RpcClient() {
  auto channel = grpc::CreateChannel("localhost:50051",
                                     grpc::InsecureChannelCredentials());
  stub_ptr_ = monitor::proto::GrpcManager::NewStub(channel);
}

RpcClient::~RpcClient() {}

}  // namespace monitor