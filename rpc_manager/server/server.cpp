#include <iostream>
#include "RpcServer.hpp"
#include <string>
using grpc::ServerBuilder;
using grpc::Server;

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  monitor::RpcServer service;
 
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());  // 绑定端口（无加密）
  builder.RegisterService(&service);  // 注册服务
 
  std::unique_ptr<Server> server(builder.BuildAndStart());  // 构建并启动
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();  // 阻塞等待请求
}
 
int main(int argc, char** argv) {
  RunServer();
  return 0;
}
