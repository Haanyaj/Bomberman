cmake_minimum_required(VERSION 3.11)
project (OOP_indie_studio_2018)

IF (NOT Irrlicht_INCLUDE_DIRS OR NOT Irrlicht_LIBRARIES)
  FIND_PATH(Irrlicht_INCLUDE_DIRS
    NAMES
      irrlicht.h
    PATHS
      /usr/include/irrlicht/        # Default Fedora28 system include path
      /usr/local/include/irrlicht/  # Default Fedora28 local include path
      ${CMAKE_MODULE_PATH}/include/ # Expected to contain the path to this file for Windows10
      ${Irrlicht_DIR}/include/      # Irrlicht root directory (if provided)
  )

  IF (MSVC)     # Windows
    SET(CMAKE_FIND_LIBRARY_PREFIXES "")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  ELSE (MSVC)   # Linux
    SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
  ENDIF(MSVC)

  FIND_LIBRARY(Irrlicht_LIBRARIES
    NAMES
      Irrlicht
    PATHS
      /usr/lib64/                   # Default Fedora28 library path
      /usr/lib/                     # Some more Linux library path
      /usr/lib/x86_64-linux-gnu/    # Some more Linux library path
      /usr/local/lib/               # Some more Linux library path
      /usr/local/lib64/             # Some more Linux library path
      ${CMAKE_MODULE_PATH}/         # Expected to contain the path to this file for Windows10
      ${Irrlicht_DIR}/              # Irrlicht root directory (if provided)
  )
ENDIF (NOT Irrlicht_INCLUDE_DIRS OR NOT Irrlicht_LIBRARIES)

IF (Irrlicht_INCLUDE_DIRS AND Irrlicht_LIBRARIES)
  SET(Irrlicht_FOUND TRUE)
ELSE (Irrlicht_INCLUDE_DIRS AND Irrlicht_LIBRARIES)
  SET(Irrlicht_FOUND FALSE)
ENDIF (Irrlicht_INCLUDE_DIRS AND Irrlicht_LIBRARIES)

IF (Irrlicht_FIND_REQUIRED AND NOT Irrlicht_FOUND)
  MESSAGE(FATAL_ERROR
    "  Irrlicht not found.\n"
    "      Windows: Fill CMake variable CMAKE_MODULE_PATH to the provided directory.\n"
    "      Linux: Install Irrlicht using your package manager ($> sudo dnf install irrlicht-devel).\n"
  )
ENDIF (Irrlicht_FIND_REQUIRED AND NOT Irrlicht_FOUND)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/Player.cpp
    src/PlayerControls.cpp
    src/Bomberman.cpp
    src/Menu.cpp
    src/Explosion.cpp
    src/Bomb.cpp
    src/WorldMap.cpp
    src/Crate.cpp
    src/EventHandler.cpp
    src/Screen.cpp
    src/Jukebox.cpp
    src/PowerUp.cpp
    src/AI.cpp
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Weffc++ -O3")

add_executable(bomberman ${SOURCES})

target_link_libraries(bomberman Irrlicht)
target_link_libraries(bomberman sfml-audio)
target_link_libraries(bomberman GL)
target_link_libraries(bomberman Xxf86vm)
target_link_libraries(bomberman Xext)
target_link_libraries(bomberman X11)
