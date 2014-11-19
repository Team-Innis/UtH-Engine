#include <UtH/Platform/Android/GooglePlayGameServices.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>
#include <UtH/Platform/Debug.hpp>

// Android

using namespace uth;

//bool GooglePlayGameServices::is_auth_in_progress = false;
//std::unique_ptr<gpg::GameServices> GooglePlayGameServices::game_services;

GooglePlayGameServices::GooglePlayGameServices()
{
	//init();
}

GooglePlayGameServices::~GooglePlayGameServices()
{
	//deInit();
}

// Public

void JNI_gameActivity()
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


// Achiements
void GooglePlayGameServices::Achievement::UnlockAchievement(std::string achievement_id)
{
	JNI_gameActivity();

	// Loading function
	jmethodID unlockAchFunc = NULL;
	unlockAchFunc = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "UnlockAchievement", "(Ljava/lang/String;)V");
	if (unlockAchFunc == NULL)
		WriteError("No UnlockAchievement function found!");

	jstring stringArg = uthAndroidEngine.jni->NewStringUTF(achievement_id.c_str());

	uthAndroidEngine.jni->CallVoidMethod(uthAndroidEngine.app->activity->clazz, unlockAchFunc, stringArg);
}
void GooglePlayGameServices::Achievement::IncrementAchievement(std::string achievement_id, int steps)
{
	JNI_gameActivity();

	// Loading function
	jmethodID unlockAchFunc = NULL;
	unlockAchFunc = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "IncrementAchievement", "(Ljava/lang/String;I)V");
	if (unlockAchFunc == NULL)
		WriteError("No IncrementAchievement function found!");

	jstring stringArg = uthAndroidEngine.jni->NewStringUTF(achievement_id.c_str());

	uthAndroidEngine.jni->CallVoidMethod(uthAndroidEngine.app->activity->clazz, unlockAchFunc, stringArg, steps);
}
void GooglePlayGameServices::Achievement::ShowAchievements()
{
	JNI_gameActivity();

	// Loading function
	jmethodID showAchFunc = NULL;
	showAchFunc = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "ShowAchievements", "()V");
	if (showAchFunc == NULL)
		WriteError("No ShowAchievements function found!");

	uthAndroidEngine.jni->CallVoidMethod(uthAndroidEngine.app->activity->clazz, showAchFunc);
}

// Leaderboard
void GooglePlayGameServices::LeaderBoard::SubmitHighScore(std::string leaderboard_id, int score)
{
	JNI_gameActivity();

	// Loading function
	jmethodID submitScoreFunc = NULL;
	submitScoreFunc = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "SubmitHighScore", "(Ljava/lang/String;I)V");
	if (submitScoreFunc == NULL)
		WriteError("No SubmitHighScore function found!");

	jstring stringArg = uthAndroidEngine.jni->NewStringUTF(leaderboard_id.c_str());

	uthAndroidEngine.jni->CallVoidMethod(uthAndroidEngine.app->activity->clazz, submitScoreFunc, stringArg, score);
}
void GooglePlayGameServices::LeaderBoard::ShowLeaderboard(std::string leaderboard_id)
{
	JNI_gameActivity();

	// Loading function
	jmethodID showLPFunc = NULL;
	showLPFunc = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "ShowLeaderboard", "(Ljava/lang/String;)V");
	if (showLPFunc == NULL)
		WriteError("No ShowLeaderboard function found!");

	jstring stringArg = uthAndroidEngine.jni->NewStringUTF(leaderboard_id.c_str());

	uthAndroidEngine.jni->CallVoidMethod(uthAndroidEngine.app->activity->clazz, showLPFunc, stringArg);
}

// GPS
std::string GooglePlayGameServices::GPS::GetCurrentLocation()
{
	JNI_gameActivity();

	// Loading function
	jmethodID getCurLoc = NULL;
	getCurLoc = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "GetCurrentLocation", "()Ljava/lang/String;");
	if (getCurLoc == NULL)
		WriteError("No GetCurrentLocation function found!");


	jstring location = (jstring)uthAndroidEngine.jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, getCurLoc);

	std::string returnable = uthAndroidEngine.jni->GetStringUTFChars( location, 0);

	return returnable;
}
float GooglePlayGameServices::GPS::GetDistanceTo(double latitude, double longitude)
{
	JNI_gameActivity();

	// Loading function
	jmethodID getDistance = NULL;
	getDistance = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "DistanceTo", "(DD)F");
	if (getDistance == NULL)
		WriteError("No GetDistanceTo function found!");
		
	float result = 0;

	result = uthAndroidEngine.jni->CallFloatMethod(uthAndroidEngine.app->activity->clazz, getDistance, latitude, longitude);

	return result;
}
float GooglePlayGameServices::GPS::GetDistanceBetween(double sLatitude, double sLongitude, double eLatitude, double eLongitude)
{
	JNI_gameActivity();

	// Loading function
	jmethodID getDistance = NULL;
	getDistance = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "DistanceBetween", "(DDDD)F");
	if (getDistance == NULL)
		WriteError("No DistanceBetween function found!");

	float result = 0;

	result = uthAndroidEngine.jni->CallFloatMethod(uthAndroidEngine.app->activity->clazz, getDistance,
		sLatitude, sLongitude, eLatitude, eLongitude);

	return result;
}
double GooglePlayGameServices::GPS::GetLatitude()
{
	JNI_gameActivity();

	// Loading function
	jmethodID getLatitude = NULL;
	getLatitude = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "GetLatitude", "()D");
	if (getLatitude == NULL)
		WriteError("No GetLatitude function found!");

	double result = 0;

	result = uthAndroidEngine.jni->CallDoubleMethod(uthAndroidEngine.app->activity->clazz, getLatitude);

	return result;
}
double GooglePlayGameServices::GPS::GetLongitude()
{
	JNI_gameActivity();

	// Loading function
	jmethodID getLongitude = NULL;
	getLongitude = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "GetLongitude", "()D");
	if (getLongitude == NULL)
		WriteError("No GetLongitude function found!");

	double result = 0;

	result = uthAndroidEngine.jni->CallDoubleMethod(uthAndroidEngine.app->activity->clazz, getLongitude);

	return result;
}
float GooglePlayGameServices::GPS::GetAccuracy()
{
	JNI_gameActivity();

	// Loading function
	jmethodID getAccuracy = NULL;
	getAccuracy = uthAndroidEngine.jni->GetMethodID(uthAndroidEngine.gameActivity, "GetAccuracy", "()F");
	if (getAccuracy == NULL)
		WriteError("No GetAccuracy function found!");

	float result = 0;

	result = uthAndroidEngine.jni->CallFloatMethod(uthAndroidEngine.app->activity->clazz, getAccuracy);
	
	return result;
}

// Private
/*
// Callback functions for game_services
void OnAuthFinished(gpg::AuthOperation op, gpg::AuthStatus status) 
{
	WriteLog("OnAuthActionFinished");
}
void OnAuthStarted(gpg::AuthOperation op)
{
	WriteLog("OnAuthActionStarted");
	switch (op)
	{
	case gpg::AuthOperation::SIGN_IN:
		WriteLog("Signing In");
		break;
	case gpg::AuthOperation::SIGN_OUT:
		WriteLog("Signing Out");
		break;
	}
}

void GooglePlayGameServices::init()
{
	//platform_config->SetActivity(uthAndroidEngine.app->activity->clazz);
	
	initServices(*platform_config,
		[](gpg::AuthOperation op){ OnAuthStarted(op); },
		[](gpg::AuthOperation op, gpg::AuthStatus status)
		{ OnAuthFinished(op, status); });
}

void GooglePlayGameServices::initServices(gpg::PlatformConfiguration const &pc,
	gpg::GameServices::Builder::OnAuthActionStartedCallback started_callback,
	gpg::GameServices::Builder::OnAuthActionFinishedCallback finished_callback)
{
	//game_services = gpg::GameServices::Builder()
	//	.SetDefaultOnLog(gpg::LogLevel::VERBOSE)
	//	.SetOnAuthActionStarted([started_callback](gpg::AuthOperation op){
	//	is_auth_in_progress = true;
	//	started_callback(op);
	//})
	//	.SetOnAuthActionFinished([finished_callback](gpg::AuthOperation op,
	//	gpg::AuthStatus status){
	//	WriteLog("Sign in finished with a result of %d", status);
	//	is_auth_in_progress = false;
	//	finished_callback(op, status);
	//})
	//	.Create(pc);
}

void GooglePlayGameServices::deInit()
{
}
*/