cmake_minimum_required(VERSION 2.8)

project(UtH-Engine CXX)

set(INCLUDE_DIRS include/
ext/include/
ext/include/freetype_include/
vs2013/TestProject/include)

include_directories(${INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_library(platform STATIC
src/Platform/Graphics.cpp
src/Platform/OGLCheck.cpp
src/Platform/HiResTimer.cpp
src/Platform/Window.cpp
src/Platform/Common/FileReader.cpp
src/Platform/Common/CommonWindowImpl.cpp
src/Platform/Input.cpp
src/Platform/Common/InputTouch.cpp
src/Platform/Common/InputMouse.cpp
src/Platform/Common/InputKeyboard.cpp
src/Platform/Common/InputCommon.cpp
src/Platform/Common/InputBase.cpp)

add_library(core STATIC
src/Core/Shader.cpp
src/Core/VertexBuffer.cpp)
target_link_libraries(core platform)

add_library(tinyxml2 STATIC
${CMAKE_SOURCE_DIR}/ext/lib/tinyxml2/src/tinyxml2.cpp)

add_library(resources STATIC
src/Resources/ResourceManager.cpp
src/Resources/Image.cpp
src/Resources/SoundBuffer.cpp
src/Resources/Font.cpp)
target_link_libraries(resources tinyxml2)

add_library(audio STATIC
src/Audio/SoundManager.cpp
src/Audio/Sound.cpp
src/Audio/Audio.cpp)
#target_link_libraries(audio resources)

add_library(renderer STATIC
src/Renderer/Texture.cpp
src/Renderer/Camera.cpp
src/Renderer/TextureAtlas.cpp
src/Renderer/SpriteBatch.cpp
src/Renderer/RenderTarget.cpp
src/Renderer/RenderTexture.cpp)
target_link_libraries(renderer resources)

add_library(engine STATIC
src/Engine/UtHEngine.cpp
src/Engine/Transform.cpp
src/Engine/Sprite.cpp
src/Engine/SceneManager.cpp
src/Engine/Scene.cpp
src/Engine/GameObject.cpp
src/Engine/Component.cpp
src/Engine/DefaultScene.cpp
src/Engine/Layer.cpp
src/Engine/Text.cpp
src/Engine/AnimatedSprite.cpp
src/Engine/Rigidbody.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(PkgConfig REQUIRED)

    # OpenAL
    find_library(OPENAL_LOCATION openal)
    target_link_libraries(audio ${OPENAL_LOCATION})

    # GLEW
    target_link_libraries(platform GL)
    target_link_libraries(platform ${PROJECT_SOURCE_DIR}/ext/lib/glew/lib/linux/libGLEW.a)

    # GLFW
    pkg_search_module(GLFW REQUIRED glfw3)
    target_link_libraries(platform ${GLFW_STATIC_LIBRARIES})

    # PhysFs
    find_library(PHYSFS_LOCATION physfs)
    target_link_libraries(platform ${PHYSFS_LOCATION})

    #FreeType
    pkg_search_module(FREETYPE2 REQUIRED freetype2)
    target_link_libraries(engine ${FREETYPE_STATIC_LIBRARIES})
    target_link_libraries(engine ${CMAKE_SOURCE_DIR}/ext/lib/freetype-gl/lib/Linux/libfreetype-gl.a)

    #Box2D
    target_link_libraries(engine ${CMAKE_SOURCE_DIR}/ext/lib/Box2D/lib/Linux/libBox2D.a)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

target_link_libraries(engine platform core resources audio renderer)

add_executable(testproject
vs2013/TestProject/source/main.cpp
vs2013/TestProject/source/TestScene.cpp)
target_link_libraries(testproject engine)