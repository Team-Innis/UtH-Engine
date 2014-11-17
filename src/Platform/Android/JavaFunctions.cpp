#include <UtH/Platform/Android/JavaFunctions.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>

#include <UtH/Platform/Debug.hpp>

using namespace uth;

JavaFunctions::JavaFunctions(){}

JavaFunctions::~JavaFunctions(){}

void JavaFunc_JNI_gameActivity()
{
	// Javaenviroment: Loads enviroment from Android activity
	if (uthAndroidEngine.jni == NULL)
		uthAndroidEngine.app->activity->vm->AttachCurrentThread(&uthAndroidEngine.jni, NULL);

	// Loads our java master class GameActivity
	if (uthAndroidEngine.gameActivity == NULL)
	{
		uthAndroidEngine.gameActivity = uthAndroidEngine.jni->GetObjectClass(uthAndroidEngine.app->activity->clazz);
		if (!uthAndroidEngine.gameActivity)
			WriteError("No engine found!");
	}
}

void JavaFunctions::Vibrate(int time_ms)
{
	JavaFunc_JNI_gameActivity();

	// Loading function
	jmethodID vibrationFunc = NULL;
	vibrationFunc = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "Vibrate", "(I)V");
	if (vibrationFunc == NULL)
		WriteError("No Vibrate function found!");

	uthAndroidEngine.jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, vibrationFunc, time_ms);
}

void JavaFunctions::ShowAd(unsigned int origin, pmath::Vec2i off)
{
	JavaFunc_JNI_gameActivity();

	// Loading function
	jmethodID popupFunc = NULL;
	popupFunc = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "ShowAdPopup", "(III)V");
	if (popupFunc == NULL)
		WriteError("No ShowAdPopup function found!");

	uthAndroidEngine.jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, popupFunc, off.x, off.y, origin);
}
void JavaFunctions::CloseAd(unsigned int origin)
{
	JavaFunc_JNI_gameActivity();

	// Loading function
	jmethodID popupFunc = NULL;
	popupFunc = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "CloseAd", "(I)V");
	if (popupFunc == NULL)
		WriteError("No CloseAd function found!");

	uthAndroidEngine.jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, popupFunc, origin);
}