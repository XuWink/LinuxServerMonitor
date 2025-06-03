'''
 该脚本实现调用grpc和protobuf编译monitor.proto生成对应的 monitor.pb.h、monitor.pb.cc、monitor.grpc.pb.h 和 monitor.grpc.pb.cc 文件
'''
import subprocess
import sys

def generate_grpc_cpp_code(proto_file, output_dir):
    try:
        # 使用 protoc 生成 C++ 代码
        command = [
            'protoc',
            f'--grpc_out={output_dir}',
            f'--cpp_out={output_dir}',
            f'--plugin=protoc-gen-grpc=$(which grpc_cpp_plugin)',
            proto_file
        ]
        subprocess.run(command, check=True, shell=True)
        print(f"Successfully generated gRPC and Protocol Buffers C++ code for {proto_file} in {output_dir}")
    except subprocess.CalledProcessError as e:
        print(f"Error generating gRPC and Protocol Buffers C++ code: {e}")
        sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python generate_grpc_cpp.py <proto_file> <output_directory>")
        sys.exit(1)

    proto_file = sys.argv[1]
    output_dir = sys.argv[2]
    generate_grpc_cpp_code(proto_file, output_dir)