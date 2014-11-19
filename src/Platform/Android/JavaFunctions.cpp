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

	jni->CallVoidMethod(uthAndroidEngine.app->activity->clazz, vibrationFunc, time_ms);
}

void JavaFunctions::ShowAdBanner(std::string name, unsigned int origin, pmath::Vec2i off)
{
	JavaFunc_JNI_gameActivity();

	// Loading function
	jmethodID popupFunc = NULL;
	popupFunc = jni->GetMethodID(gameActivity, "ShowAd", "(IIILjava/lang/String;)V");
	if (popupFunc == NULL)
		WriteError("No adShow function found!");
	jstring jname = jni->NewStringUTF(name.c_str());
	jni->CallVoidMethod(uthAndroidEngine.app->activity->clazz, popupFunc, off.x, off.y, origin, jname);
}

void JavaFunctions::ShowAdFull(std::string name)
{
	JavaFunc_JNI_gameActivity();

	// Loading function
	jmethodID popupFunc = NULL;
	popupFunc = jni->GetMethodID(gameActivity, "ShowAdFull", "(Ljava/lang/String;)V");
	if (popupFunc == NULL)
		WriteError("No adShowFull function found!");
	jstring jname = jni->NewStringUTF(name.c_str());
	jni->CallVoidMethod(uthAndroidEngine.app->activity->clazz, popupFunc, jname);
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
	jni->CallVoidMethod(uthAndroidEngine.app->activity->clazz, popupFunc, jname);
}