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
		WriteError("No vibration function found!");

	jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, vibrationFunc, time_ms);
}

void JavaFunctions::ShowAdBanner(std::string name, unsigned int origin, pmath::Vec2i off)
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
	popupFunc = jni->GetMethodID(gameActivity, "ShowAd", "(IIILjava/lang/String;)V");
	if (popupFunc == NULL)
		WriteError("No adShow function found!");
	jstring jname = jni->NewStringUTF(name.c_str());
	jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, popupFunc, off.x, off.y, origin, jname);
}

void JavaFunctions::ShowAdFull(std::string name)
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
	popupFunc = jni->GetMethodID(gameActivity, "ShowAdFull", "(Ljava/lang/String;)V");
	if (popupFunc == NULL)
		WriteError("No adShowFull function found!");
	jstring jname = jni->NewStringUTF(name.c_str());
	jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, popupFunc, jname);
}

void JavaFunctions::CloseAd(const std::string& name)
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
	popupFunc = jni->GetMethodID(gameActivity, "HideAd", "(Ljava/lang/String;)V");
	if (popupFunc == NULL)
		WriteError("No adHide function found!");
	jstring jname = jni->NewStringUTF(name.c_str());
	jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, popupFunc, jname);
}