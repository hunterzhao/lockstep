set(SOURCE_FILES
             event_poll.cc
             game_server.cc
             socket_event.cc
             game_socket_event.cc
             game_server.cc
             game_unit.cc
             notify_event.cc
             timer_event.cc
             reactor.cc
             log.cc
             game.pb.cc
             player.cc
             )

add_library(game STATIC ${SOURCE_FILES})
target_link_libraries(game)
add_library(game_so SHARED ${SOURCE_FILES})
set_target_properties(game_so PROPERTIES OUTPUT_NAME "game")
