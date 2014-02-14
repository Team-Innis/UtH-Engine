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

#Platform
LOCAL_SRC_FILES += \
#$(SRC_PATH)Platform/myfile.cpp

include $(BUILD_STATIC_LIBRARY)
