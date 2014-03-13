cmake_minimum_required(VERSION 2.8)

project(UtH-Engine CXX)

include_directories(include/ extlibs/glew/include/ extlibs/glfw/include/ extlibs/openal/include/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")



add_library(math STATIC
src/Math/Matrix3.cpp
src/Math/Matrix4.cpp
src/Math/Rectangle.cpp
src/Math/Vector2.cpp
src/Math/Vector3.cpp
src/Math/Vector4.cpp)

add_library(platform STATIC
src/Platform/Graphics.cpp
src/Platform/OGLCheck.cpp
src/Platform/HiResTimer.cpp
src/Platform/Window.cpp
src/Platform/Common/FileReader.cpp
src/Platform/Linux/LinuxWindowImpl.cpp)

add_library(core STATIC
src/Core/Shader.cpp
src/Core/VertexBuffer.cpp)
target_link_libraries(core platform)

add_library(resources STATIC
src/Resources/ResourceManager.cpp)

add_library(audio STATIC
src/Audio/SoundManager.cpp
src/Audio/Sound.cpp
src/Audio/Audio.cpp)
#target_link_libraries(audio resources)

add_library(renderer STATIC
src/Renderer/Texture.cpp
src/Renderer/Camera.cpp)
target_link_libraries(renderer resources)

add_library(engine STATIC
src/Engine/UtHEngine.cpp
src/Engine/Transform.cpp
src/Engine/Sprite.cpp
src/Engine/SceneManager.cpp
src/Engine/Scene.cpp
src/Engine/GameObject.cpp
src/Engine/Component.cpp
src/Engine/DefaultScene.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # OpenAL
    find_library(OPENAL_LOCATION openal)
    target_link_libraries(audio ${OPENAL_LOCATION})

    # GLEW
    target_link_libraries(platform GL)
    target_link_libraries(platform ${PROJECT_SOURCE_DIR}/extlibs/glew/lib/linux/libGLEW.a)

    # GLFW
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    target_link_libraries(platform ${GLFW_STATIC_LIBRARIES})
endif()

target_link_libraries(engine math platform core resources audio renderer)

add_executable(testproject vs2010/TestProject/main.cpp)
target_link_libraries(testproject engine)