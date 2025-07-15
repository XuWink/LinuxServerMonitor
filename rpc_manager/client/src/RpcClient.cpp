#include "RpcClient.hpp"

namespace monitor {

RpcClient::RpcClient() {
  auto channel = grpc::CreateChannel("localhost:50051",
                                     grpc::InsecureChannelCredentials());
  stub_ptr_ = monitor::proto::GrpcManager::NewStub(channel);
}

RpcClient::~RpcClient() {}

// 服务端调用gRPC方法把数据传给服务器，const & 传入参数
void RpcClient::SetMonitorInfo(const monitor::proto::MonitorInfo& monito_info) {
  // 用于管理一个gRPC调用的生命周期和状态，使用&传递，任何修改都能反映到原始对象上
  ::grpc::ClientContext context;
  // 用来接收服务器响应（这里是空消息类型）
  ::google::protobuf::Empty response;
  // 通过stub调用服务端的RPC方法，stub->(调用RPC服务)，(&context, request,
  // &reply)
  ::grpc::Status status =
      stub_ptr_->SetMonitorInfo(&context, monito_info, &response);
  // 判断响应消息
  if (status.ok()) {
  } else {
    std::cout << status.error_details() << std::endl;
    std::cout << "status.error_message: " << status.error_message()
              << std::endl;
    std::cout << "falied to connect !!!" << std::endl;
  }
}

// 从服务器中获取数据，* monito_info是传出参数
void RpcClient::GetMonitorInfo(monitor::proto::MonitorInfo* monito_info) {
  ::grpc::ClientContext context;
  ::google::protobuf::Empty request;
  ::grpc::Status status =
      stub_ptr_->GetMonitorInfo(&context, request, monito_info);
  if (status.ok()) {
    std::cout << "monitor_info: " << monito_info << std::endl;
  } else {
    std::cout << status.error_details() << std::endl;
    std::cout << "status.error_message: " << status.error_message()
              << std::endl;
    std::cout << "falied to connect !!!" << std::endl;
  }
}

}  // namespace monitor