#!bin/bash
protoc game.proto -I=. --cpp_out=. &&
cp -f game.pb.h include/ && 
cp -f game.pb.cc src/ && 
cp -f game.pb.cc test/
