LOCAL_PATH := $(call my-dir)
SRC_PATH := ../../src/

include $(CLEAR_VARS)

include $(CLEAR_VARS)
LOCAL_MODULE := freetype
LOCAL_SRC_FILES := ../../ext/lib/android/libfreetype.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libfreetypegl
LOCAL_SRC_FILES := ../../ext/lib/android/libfreetypegl_static.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libbox2d
LOCAL_SRC_FILES := ../../ext/lib/android/libbox2d_static.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_MODULE    := engine
LOCAL_STATIC_LIBRARIES := android_native_app_glue engine libbox2d libfreetypegl freetype
LOCAL_SHARED_LIBRARIES := libopenal libsndfile
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../ext/include/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../ext/include/freetype_include/

#Renderer
LOCAL_SRC_FILES += \
$(SRC_PATH)Renderer/Camera.cpp \
$(SRC_PATH)Renderer/RenderTarget.cpp \
$(SRC_PATH)Renderer/RenderTexture.cpp \
$(SRC_PATH)Renderer/TextureAtlas.cpp \
$(SRC_PATH)Renderer/VertexBuffer.cpp


#Resources
LOCAL_SRC_FILES += \
$(SRC_PATH)Resources/ResourceManager.cpp \
$(SRC_PATH)Resources/Shader.cpp \
$(SRC_PATH)Resources/Texture.cpp \
$(SRC_PATH)Resources/Font.cpp \
$(SRC_PATH)Resources/Image.cpp \
$(SRC_PATH)Resources/Sound.cpp \
$(SRC_PATH)Resources/Resource.cpp


#Platform
LOCAL_SRC_FILES += \
$(SRC_PATH)Platform/Android/FileManager.cpp \
$(SRC_PATH)Platform/SoundDevice.cpp \
$(SRC_PATH)Platform/Graphics.cpp \
$(SRC_PATH)Platform/Debug.cpp \
$(SRC_PATH)Platform/HiResTimer.cpp \
$(SRC_PATH)Platform/OGLCheck.cpp \
$(SRC_PATH)Platform/Window.cpp \
$(SRC_PATH)Platform/Android/AndroidWindowImpl.cpp \
$(SRC_PATH)Platform/Input.cpp \
$(SRC_PATH)Platform/Common/InputBase.cpp \
$(SRC_PATH)Platform/Android/InputTouch.cpp \
$(SRC_PATH)Platform/Android/InputSensor.cpp \
$(SRC_PATH)Platform/Android/InputController.cpp \
$(SRC_PATH)Platform/Android/InputCommon.cpp \
$(SRC_PATH)Platform/Android/InputMouse.cpp \
$(SRC_PATH)Platform/Android/InputKeyboard.cpp \
$(SRC_PATH)Platform/Android/JavaFunctions.cpp

#Engine
LOCAL_SRC_FILES += \
$(SRC_PATH)Engine/Object.cpp \
$(SRC_PATH)Engine/Component.cpp \
$(SRC_PATH)Engine/GameObject.cpp \
$(SRC_PATH)Engine/DefaultScene.cpp \
$(SRC_PATH)Engine/Scene.cpp \
$(SRC_PATH)Engine/SceneManager.cpp \
$(SRC_PATH)Engine/Sprite.cpp \
$(SRC_PATH)Engine/Engine.cpp \
$(SRC_PATH)Engine/Transform.cpp \
$(SRC_PATH)Engine/Physics/Rigidbody.cpp \
$(SRC_PATH)Engine/Physics/PhysicsContactListener.cpp \
$(SRC_PATH)Engine/Physics/PhysicsWorld.cpp \
$(SRC_PATH)Engine/Text.cpp \
$(SRC_PATH)Engine/SpriteBatch.cpp \
$(SRC_PATH)Engine/Particles/ParticleTemplate.cpp \
$(SRC_PATH)Engine/Particles/ParticleSystem.cpp \
$(SRC_PATH)Engine/Particles/Affector.cpp \
$(SRC_PATH)Engine/Randomizer.cpp \
$(SRC_PATH)Engine/TMX/Map.cpp \
$(SRC_PATH)Engine/TMX/Tile.cpp \
$(SRC_PATH)Engine/TMX/TileLayer.cpp \
$(SRC_PATH)Engine/TMX/Tileset.cpp \
$(SRC_PATH)Engine/AnimatedSprite.cpp \

#TinyXML2
LOCAL_SRC_FILES += \
$(SRC_PATH)../ext/lib/tinyxml2/src/tinyxml2.cpp

include $(BUILD_STATIC_LIBRARY)
