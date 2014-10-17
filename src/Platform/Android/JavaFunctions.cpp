#include <UtH/Platform/Android/JavaFunctions.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>

#include <UtH/Platform/Debug.hpp>

using namespace uth;

JavaFunctions::JavaFunctions(){}

JavaFunctions::~JavaFunctions(){}

void JavaFunctions::Vibrate(int time_ms)
{
	// Javaenviroment: Loads enviroment from Android activity
	JNIEnv* jni;
	uthAndroidEngine.app->activity->vm->AttachCurrentThread(&jni, NULL);
	
	// Loads our java master class GameActivity
	jclass gameActivity = jni->GetObjectClass(uthAndroidEngine.app->activity->clazz);
	if (!gameActivity)
		WriteError("No engine found!");

	// Loading function
	jmethodID vibrationFunc = NULL;
	vibrationFunc = jni->GetMethodID(gameActivity, "Vibrate", "(I)V");
	if (vibrationFunc == NULL)
		WriteError("No Vibrate function found!");

	jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, vibrationFunc, time_ms);
}

void JavaFunctions::ShowAd(unsigned int origin, pmath::Vec2i off)
{
	// Javaenviroment: Loads enviroment from Android activity
	JNIEnv* jni;
	uthAndroidEngine.app->activity->vm->AttachCurrentThread(&jni, NULL);

	// Loads our java master class GameActivity
	jclass gameActivity = jni->GetObjectClass(uthAndroidEngine.app->activity->clazz);
	if (!gameActivity)
		WriteError("No engine found!");

	// Loading function
	jmethodID popupFunc = NULL;
	popupFunc = jni->GetMethodID(gameActivity, "ShowAdPopup", "(III)V");
	if (popupFunc == NULL)
		WriteError("No ShowAdPopup function found!");

	jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, popupFunc, off.x, off.y, origin);
}
void JavaFunctions::CloseAd(unsigned int origin)
{
	// Javaenviroment: Loads enviroment from Android activity
	JNIEnv* jni;
	uthAndroidEngine.app->activity->vm->AttachCurrentThread(&jni, NULL);

	// Loads our java master class GameActivity
	jclass gameActivity = jni->GetObjectClass(uthAndroidEngine.app->activity->clazz);
	if (!gameActivity)
		WriteError("No engine found!");

	// Loading function
	jmethodID popupFunc = NULL;
	popupFunc = jni->GetMethodID(gameActivity, "CloseAd", "(I)V");
	if (popupFunc == NULL)
		WriteError("No CloseAd function found!");

	jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, popupFunc, origin);
}