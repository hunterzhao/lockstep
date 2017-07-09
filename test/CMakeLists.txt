set(SERVER_SOURCE server.cc)
set(CLIENT_SOURCE client.cc game.pb.cc)

add_executable(server ${SERVER_SOURCE})
target_link_libraries(server game protobuf glog)
# profiler tcmalloc)

add_executable(client ${CLIENT_SOURCE})
target_link_libraries(client protobuf)

