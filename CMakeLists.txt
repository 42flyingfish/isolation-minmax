cmake_minimum_required(VERSION 3.1.0)

project(myapp
	VERSION 1.0
	DESCRIPTION "A game of isolation"
	LANGUAGES CXX)

add_executable(myapp
	src/agent.cpp
	src/agent.h
	src/board.cpp
	src/board.h
	src/interface.cpp
	src/interface.h
	src/log.cpp
	src/log.h
	src/main.cpp
	src/transposition.cpp
	src/transposition.h
	src/zobrist.cpp
	src/zobrist.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(myapp PRIVATE Threads::Threads)

target_compile_features(myapp PRIVATE cxx_std_17)
