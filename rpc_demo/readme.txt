sudo apt-get update
sudo apt-get install protobuf-compiler libprotobuf-dev
sudo apt install protobuf-compiler-grpc
sudo apt-get install libgrpc++-dev

which proto
which grpc_cpp_plugin


# First generate the protobuf code
protoc --cpp_out=. hello.proto

# Then generate the gRPC code
protoc --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` hello.proto
