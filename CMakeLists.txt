cmake_minimum_required(VERSION 3.1.0)
project(Space)

set(CMAKE_CXX_STANDARD 11)

find_package(raylib REQUIRED)
include_directories(${raylib_INCLUDE_DIR})

add_executable(Space_Invaders src/main.cpp src/Enemy.cpp include/Enemy.h src/Game.cpp include/Game.h src/Player.cpp include/Player.h src/Projectile.cpp include/Projectile.h src/ScoreManager.cpp include/ScoreManager.h include/GameObject.h)

target_link_libraries(Space_Invaders ${raylib_LIBRARIES})

