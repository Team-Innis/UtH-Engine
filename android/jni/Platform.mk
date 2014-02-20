LOCAL_PATH := $(call my-dir)
SRC_PATH := ../../src/

include $(CLEAR_VARS)

LOCAL_MODULE    := engine
LOCAL_STATIC_LIBRARIES := android_native_app_glue engine
LOCAL_SHARED_LIBRARIES := libopenal
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../extlibs/openal/include/

#Math
LOCAL_SRC_FILES := \
$(SRC_PATH)Math/Matrix3.cpp \
$(SRC_PATH)Math/Matrix4.cpp \
$(SRC_PATH)Math/Vector2.cpp \
$(SRC_PATH)Math/Vector3.cpp \
$(SRC_PATH)Math/Vector4.cpp \
$(SRC_PATH)Math/Rectangle.cpp

#Audio
LOCAL_SRC_FILES += \
$(SRC_PATH)Audio/Audio.cpp \
$(SRC_PATH)Audio/Sound.cpp \
$(SRC_PATH)Audio/SoundManager.cpp

#Platform
LOCAL_SRC_FILES += \
$(SRC_PATH)Platform/FileReader.cpp \
$(SRC_PATH)Platform/Graphics.cpp \
$(SRC_PATH)Platform/HiResTimer.cpp \
$(SRC_PATH)Platform/OGLCheck.cpp

#Core
LOCAL_SRC_FILES += \
$(SRC_PATH)Core/Shader.cpp \
$(SRC_PATH)Core/VertexBuffer.cpp

include $(BUILD_STATIC_LIBRARY)
