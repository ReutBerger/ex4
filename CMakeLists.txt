cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(ex4 server_side.h MySerialServer.cpp MySerialServer.h ClientHandler.h MyTestClientHandler.cpp MyTestClientHandler.h Solver.h StringReverse.cpp StringReverse.h CacheManager.h FileCacheManager.cpp FileCacheManager.h main.cpp Searchable.h Searcher.h State.cpp State.h MyClientHandler.cpp MyClientHandler.h SearchSolver.cpp SearchSolver.h Matrix.cpp Matrix.h Point.cpp Point.h BFS.cpp BFS.h BestFS.cpp BestFS.h MyParallelServer.cpp MyParallelServer.h DFS.cpp DFS.h AStar.cpp AStar.h)