LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := engine
LOCAL_SRC_FILES := ../../src/Math/Matrix3.cpp \
../../src/Math/Matrix4.cpp \
../../src/Math/Vector2.cpp \
../../src/Math/Vector3.cpp \
../../src/Math/Vector4.cpp \
../../src/Math/Rectangle.cpp
LOCAL_STATIC_LIBRARIES := android_native_app_glue engine
LOCAL_SHARED_LIBRARIES := libopenal
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../extlibs/openal/include/

include $(BUILD_STATIC_LIBRARY)
