cmake_minimum_required(VERSION 3.17)
project(testinput)

set(CMAKE_CXX_STANDARD 14)

add_executable(testinput main.cpp GameWindow.cpp GameWindow.h Animation.cpp Animation.h GeneralSound.cpp GeneralSound.h Input.cpp Input.h Player.cpp Player.h
                Physics.cpp Physics.h SFMLDebugDraw.cpp SFMLDebugDraw.h ContactListener.cpp ContactListener.h Menu.cpp Menu.h Arrow.cpp Arrow.h Enemy1.cpp Enemy1.h createPhysical.h GlobalVariables.cpp GlobalVariables.h Enemy2.cpp Enemy2.h Enemy3.cpp Enemy3.h NecroBall.cpp NecroBall.h)
target_link_libraries (testinput sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries (testinput ${CMAKE_SOURCE_DIR}/libbox2d.a)