#include <UtH/Platform/Android/JavaFunctions.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>

#include <UtH/Platform/Debug.hpp>

using namespace uth;

JavaFunctions::JavaFunctions(){}

JavaFunctions::~JavaFunctions(){}

void JavaFunctions::Vibrate(int time_ms)
{
	JNIEnv* jni;
	uthAndroidEngine.app->activity->vm->AttachCurrentThread(&jni, NULL);
	
	jclass vibrationClass = jni->GetObjectClass(uthAndroidEngine.app->activity->clazz);
	if (!vibrationClass)
		WriteError("No engine found!");
	jmethodID vibrationFunc = jni->GetMethodID(vibrationClass, "Vibrate", "(I)V");
	if (!vibrationFunc)
		WriteError("No vibration function found!");
	jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, vibrationFunc, time_ms);
}