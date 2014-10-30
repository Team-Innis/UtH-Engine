#include <UtH/Platform/Android/GooglePlayGameServices.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>
#include <UtH/Platform/Debug.hpp>


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
// Achiements
void GooglePlayGameServices::Achievement::UnlockAchievement(std::string achievement_id)
{
	// Javaenviroment: Loads enviroment from Android activity
	JNIEnv* jni;
	uthAndroidEngine.app->activity->vm->AttachCurrentThread(&jni, NULL);

	// Loads our java master class GameActivity
	jclass gameActivity = jni->GetObjectClass(uthAndroidEngine.app->activity->clazz);
	if (!gameActivity)
		WriteError("No engine found!");

	// Loading function
	jmethodID unlockAchFunc = NULL;
	unlockAchFunc = jni->GetMethodID(gameActivity, "UnlockAchievement", "(Ljava/lang/String;)V");
	if (unlockAchFunc == NULL)
		WriteError("No UnlockAchievement function found!");

	jstring stringArg = jni->NewStringUTF(achievement_id.c_str());

	jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, unlockAchFunc, stringArg);
}
void GooglePlayGameServices::Achievement::IncrementAchievement(std::string achievement_id, int steps)
{
	// Javaenviroment: Loads enviroment from Android activity
	JNIEnv* jni;
	uthAndroidEngine.app->activity->vm->AttachCurrentThread(&jni, NULL);

	// Loads our java master class GameActivity
	jclass gameActivity = jni->GetObjectClass(uthAndroidEngine.app->activity->clazz);
	if (!gameActivity)
		WriteError("No engine found!");

	// Loading function
	jmethodID unlockAchFunc = NULL;
	unlockAchFunc = jni->GetMethodID(gameActivity, "IncrementAchievement", "(Ljava/lang/String;I)V");
	if (unlockAchFunc == NULL)
		WriteError("No IncrementAchievement function found!");

	jstring stringArg = jni->NewStringUTF(achievement_id.c_str());

	jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, unlockAchFunc, stringArg, steps);
}
void GooglePlayGameServices::Achievement::ShowAchievements()
{
	// Javaenviroment: Loads enviroment from Android activity
	JNIEnv* jni;
	uthAndroidEngine.app->activity->vm->AttachCurrentThread(&jni, NULL);

	// Loads our java master class GameActivity
	jclass gameActivity = jni->GetObjectClass(uthAndroidEngine.app->activity->clazz);
	if (!gameActivity)
		WriteError("No engine found!");

	// Loading function
	jmethodID showAchFunc = NULL;
	showAchFunc = jni->GetMethodID(gameActivity, "ShowAchievements", "()V");
	if (showAchFunc == NULL)
		WriteError("No ShowAchievements function found!");

	jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, showAchFunc);
}
// Leaderboard
void GooglePlayGameServices::LeaderBoard::SubmitHighScore(std::string leaderboard_id, int score)
{
	//if (game_services->IsAuthorized())
		//game_services->Leaderboards().SubmitScore(leaderboard_id, score);

	// Javaenviroment: Loads enviroment from Android activity
	JNIEnv* jni;
	uthAndroidEngine.app->activity->vm->AttachCurrentThread(&jni, NULL);

	// Loads our java master class GameActivity
	jclass gameActivity = jni->GetObjectClass(uthAndroidEngine.app->activity->clazz);
	if (!gameActivity)
		WriteError("No engine found!");

	// Loading function
	jmethodID submitScoreFunc = NULL;
	submitScoreFunc = jni->GetMethodID(gameActivity, "SubmitHighScore", "(Ljava/lang/String;I)V");
	if (submitScoreFunc == NULL)
		WriteError("No SubmitHighScore function found!");

	jstring stringArg = jni->NewStringUTF(leaderboard_id.c_str());

	jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, submitScoreFunc, stringArg, score);
}
void GooglePlayGameServices::LeaderBoard::ShowLeaderboard(std::string leaderboard_id)
{
	// Javaenviroment: Loads enviroment from Android activity
	JNIEnv* jni;
	uthAndroidEngine.app->activity->vm->AttachCurrentThread(&jni, NULL);

	// Loads our java master class GameActivity
	jclass gameActivity = jni->GetObjectClass(uthAndroidEngine.app->activity->clazz);
	if (!gameActivity)
		WriteError("No engine found!");

	// Loading function
	jmethodID showLPFunc = NULL;
	showLPFunc = jni->GetMethodID(gameActivity, "ShowLeaderboard", "(Ljava/lang/String;)V");
	if (showLPFunc == NULL)
		WriteError("No ShowLeaderboard function found!");

	jstring stringArg = jni->NewStringUTF(leaderboard_id.c_str());

	jni->CallObjectMethod(uthAndroidEngine.app->activity->clazz, showLPFunc, stringArg);
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