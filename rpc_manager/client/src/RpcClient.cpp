#include "RpcClient.hpp"

namespace monitor {

RpcClient::RpcClient() {
  auto channel = grpc::CreateChannel("localhost:50051",
                                     grpc::InsecureChannelCredentials());
  stub_ptr_ = monitor::proto::GrpcManager::NewStub(channel);
}

RpcClient::RpcClient(const std::string& server_address) {
  auto channel =
      grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
  stub_ptr_ = monitor::proto::GrpcManager::NewStub(channel);
}

RpcClient::~RpcClient() {}

// 服务端调用gRPC方法把数据传给服务器，const & 传入参数
bool RpcClient::SetMonitorInfo(
    const monitor::proto::MonitorInfo& monitor_info) {
  // 用于管理 gRPC 调用的生命周期
  ::grpc::ClientContext context;
  // 空响应对象（SetMonitorInfo 是单向通知，无需返回数据）
  ::google::protobuf::Empty response;

  // 调用 RPC 方法
  ::grpc::Status status =
      stub_ptr_->SetMonitorInfo(&context, monitor_info, &response);

  // 检查状态并处理错误
  if (!status.ok()) {
    std::stringstream ss;
    ss << "gRPC SetMonitorInfo failed! "
       << "Error Code: " << status.error_code() << ", "
       << "Error Message: " << status.error_message() << ", "
       << "Error Details: " << status.error_details();

    Logger::getInstance().error(ss.str());  // 一次性记录完整错误信息
    return false;
  }

  return true;  // 成功时返回 true
}

// 从服务器中获取数据，* monito_info是传出参数
bool RpcClient::GetMonitorInfo(monitor::proto::MonitorInfo* monitor_info) {
  // 检查输出参数是否有效
  if (!monitor_info) {
    Logger::getInstance().error("Invalid argument: monitor_info is nullptr!");
    return false;
  }

  // 用于管理 gRPC 调用的生命周期
  ::grpc::ClientContext context;
  // 空请求对象（GetMonitorInfo 不需要请求参数）
  ::google::protobuf::Empty request;

  // 调用 RPC 方法
  ::grpc::Status status =
      stub_ptr_->GetMonitorInfo(&context, request, monitor_info);

  // 检查状态并处理错误
  if (!status.ok()) {
    std::stringstream ss;
    ss << "gRPC SetMonitorInfo failed! "
       << "Error Code: " << status.error_code() << ", "
       << "Error Message: " << status.error_message() << ", "
       << "Error Details: " << status.error_details();
    Logger::getInstance().error(ss.str());  // 一次性记录完整错误信息
    return false;
  }

  return true;
}

bool RpcClient::GetAllMonitorInfo(AllMonitorInfo* all_monitor_info) {
  // 检查输出参数是否有效
  if (!all_monitor_info) {
    Logger::getInstance().error("Invalid argument: monitor_info is nullptr!");
    return false;
  }

  // 用于管理 gRPC 调用的生命周期
  ::grpc::ClientContext context;
  // 空请求对象（GetMonitorInfo 不需要请求参数）
  ::google::protobuf::Empty request;

  // 调用 RPC 方法
  ::grpc::Status status =
      stub_ptr_->GetAllMonitorInfo(&context, request, all_monitor_info);

  // 检查状态并处理错误
  if (!status.ok()) {
    std::stringstream ss;
    ss << "gRPC SetMonitorInfo failed! "
       << "Error Code: " << status.error_code() << ", "
       << "Error Message: " << status.error_message() << ", "
       << "Error Details: " << status.error_details();
    Logger::getInstance().error(ss.str());  // 一次性记录完整错误信息
    return false;
  }

  return true;
}

}  // namespace monitor