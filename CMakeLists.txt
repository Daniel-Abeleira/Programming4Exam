cmake_minimum_required(VERSION 3.26)
project(Pacman_DanielAbeleira)
include(FetchContent)

set(TARGET_NAME Pacman)

# add glm
FetchContent_Declare(
  glm
  URL https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
  DOWNLOAD_NO_PROGRESS ON
  DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
)

FetchContent_MakeAvailable(glm)

# add SDL2
if (WIN32)
  FetchContent_Declare(
    SDL2
    URL https://www.libsdl.org/release/SDL2-devel-2.30.10-VC.zip 
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads 
  )
  FetchContent_MakeAvailable(SDL2)
  set(SDL2_INCLUDE_DIR ${sdl2_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x64/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x64/SDL2main.lib")
    set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x64/SDL2.dll")
  else()
    set(SDL2_LIBRARIES "${sdl2_SOURCE_DIR}/lib/x86/SDL2.lib;${sdl2_SOURCE_DIR}/lib/x86/SDL2main.lib")
    set(SDL2_LIBRARY_DLL "${sdl2_SOURCE_DIR}/lib/x86/SDL2.dll")
  endif()

  # add SDL2_image
  FetchContent_Declare(
    SDL2_image
    URL https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.8.3-VC.zip 
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_MakeAvailable(SDL2_image)
  set(SDL2_IMAGE_INCLUDE_DIR ${sdl2_image_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.lib")
    set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x64/SDL2_image.dll")
  else()
    set(SDL2_IMAGE_LIBRARIES "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.lib")
    set(SDL2_IMAGE_LIBRARY_DLL "${sdl2_image_SOURCE_DIR}/lib/x86/SDL2_image.dll")
  endif()

  # add SDL2_ttf
  FetchContent_Declare(
    SDL2_ttf
    URL https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.22.0-VC.zip
    DOWNLOAD_NO_PROGRESS ON
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_MakeAvailable(SDL2_ttf)
  set(SDL2_TTF_INCLUDE_DIR ${sdl2_ttf_SOURCE_DIR}/include)
  if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.lib)
    set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x64/SDL2_ttf.dll")
  else()
    set(SDL2_TTF_LIBRARIES ${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.lib)
    set(SDL2_TTF_LIBRARY_DLL "${sdl2_ttf_SOURCE_DIR}/lib/x86/SDL2_ttf.dll")
  endif()

  find_package(VLD CONFIG)

elseif(NOT EMSCRIPTEN)

  FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.10
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  FetchContent_MakeAvailable(SDL2)
  
  FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.3
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL2IMAGE_INSTALL OFF)
  FetchContent_MakeAvailable(SDL2_image)

  FetchContent_Declare(
    SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG release-2.22.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )
  set(SDL2TTF_INSTALL OFF)
  FetchContent_MakeAvailable(SDL2_ttf)

endif()

# Add Engine static library
add_library(Engine STATIC
  Engine/src/Game.cpp
  Engine/inc/Game.h
 "Engine/inc/Singleton.h" "Engine/inc/SceneManager.h" "Engine/src/SceneManager.cpp" "Engine/inc/Scene.h" "Engine/src/Scene.cpp" "Engine/inc/GameObject.h" "Engine/src/GameObject.cpp" "Engine/inc/Component.h" "Engine/src/Component.cpp" "Engine/inc/ResourceManager.h" "Engine/inc/Renderer.h" "Engine/inc/InputManager.h" "Engine/inc/Font.h" "Engine/inc/RenderComponent.h" "Engine/inc/TextComponent.h" "Engine/inc/Texture2D.h" "Engine/inc/Transform.h" "Engine/src/Font.cpp" "Engine/src/InputManager.cpp" "Engine/src/RenderComponent.cpp" "Engine/src/Renderer.cpp" "Engine/src/TextComponent.cpp" "Engine/src/Texture2D.cpp" "Engine/src/Transform.cpp" "Engine/src/ResourceManager.cpp" "Engine/inc/Command.h")

# enable c++20 features for Engine
target_compile_features(Engine PUBLIC cxx_std_20)

# set include directories for Engine
target_include_directories(Engine PRIVATE
  ${CMAKE_SOURCE_DIR}/Engine/src
  ${CMAKE_SOURCE_DIR}/Engine/inc
  ${SDL2_INCLUDE_DIR}
  ${SDL2_IMAGE_INCLUDE_DIR}
  ${SDL2_TTF_INCLUDE_DIR}
  ${glm_SOURCE_DIR}
)

# compile at max warning level + treat warnings as errors for Engine
target_compile_options(Engine PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

# Add Pacman executable
add_executable(Pacman
  Pacman/main.cpp
   "Pacman/inc/PacmanGame.h" "Pacman/src/PacmanGame.cpp" "Pacman/inc/Pacman.h" "Pacman/src/Pacman.cpp" "Pacman/src/MainMenuManager.cpp" "Pacman/inc/GameMode.h" "Pacman/src/MainMenuManager.cpp")

# enable c++20 features for Pacman
target_compile_features(Pacman PUBLIC cxx_std_20)

# compile at max warning level + treat warnings as errors for Engine
target_compile_options(Pacman PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

# set include directories for Pacman
target_include_directories(Pacman PRIVATE
  ${CMAKE_SOURCE_DIR}/Pacman/inc
  ${CMAKE_SOURCE_DIR}/Engine/inc
  ${SDL2_INCLUDE_DIR}
  ${SDL2_IMAGE_INCLUDE_DIR}
  ${SDL2_TTF_INCLUDE_DIR}
  ${glm_SOURCE_DIR}
)

# link Pacman with Engine and SDL2 libraries
target_link_libraries(Pacman PUBLIC
  Engine
  ${SDL2_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
)

if(WIN32)
  set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${TARGET_NAME}>")

  # add post build commands
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_IMAGE_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_TTF_LIBRARY_DLL}" "$<TARGET_FILE_DIR:${TARGET_NAME}>"
  )
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Data" "$<TARGET_FILE_DIR:${TARGET_NAME}>/Data"
  )
endif()

# set Pacman as the default startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Pacman)
