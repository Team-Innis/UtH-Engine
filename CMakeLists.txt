cmake_minimum_required(VERSION 2.8)

project(UtH-Engine CXX)

set(INCLUDE_DIRS include/
extlibs/glew/include/
extlibs/glfw/include/
extlibs/openal/include/
extlibs/freetype/include/
extlibs/freetype-gl/include/
extlibs/physfs/include/
extlibs/tinyxml2/include/
extlibs/Box2D/include/)

include_directories(${INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")



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

add_library(resources STATIC
src/Resources/ResourceManager.cpp
src/Resources/Image.cpp
src/Resources/SoundBuffer.cpp
src/Resources/Font.cpp)

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
target_link_libraries(renderer resources math)

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
    target_link_libraries(platform ${PROJECT_SOURCE_DIR}/extlibs/glew/lib/linux/libGLEW.a)

    # GLFW
    pkg_search_module(GLFW REQUIRED glfw3)
    target_link_libraries(platform ${GLFW_STATIC_LIBRARIES})

    # PhysFs
    find_library(PHYSFS_LOCATION physfs)
    target_link_libraries(platform ${PHYSFS_LOCATION})

    #FreeType
    pkg_search_module(FREETYPE2 REQUIRED freetype2)
    target_link_libraries(engine ${FREETYPE_STATIC_LIBRARIES})
    target_link_libraries(engine ${CMAKE_SOURCE_DIR}/extlibs/freetype-gl/lib/Linux/libfreetype-gl.a)

    #TinyXML2
    target_link_libraries(renderer ${CMAKE_SOURCE_DIR}/extlibs/tinyxml2/lib/Linux/libtinyxml2.a)

    #Box2D
    target_link_libraries(engine ${CMAKE_SOURCE_DIR}/extlibs/Box2D/lib/Linux/libBox2D.a)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

target_link_libraries(engine math platform core resources audio renderer)

add_executable(testproject vs2010/TestProject/main.cpp)
target_link_libraries(testproject engine)