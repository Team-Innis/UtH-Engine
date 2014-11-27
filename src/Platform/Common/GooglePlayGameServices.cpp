#include <UtH/Platform/Common/GooglePlayGameServices.hpp>
#include <UtH/Platform/Debug.hpp>

// Windows

using namespace uth;


GooglePlayGameServices::GooglePlayGameServices()
{
}

GooglePlayGameServices::~GooglePlayGameServices()
{
}

// Public
// Achiements
void GooglePlayGameServices::Achievement::UnlockAchievement(std::string achievement_id)
{

}
void IncrementAchievement(std::string achievement_id, int steps)
{

}
void GooglePlayGameServices::Achievement::ShowAchievements()
{

}
// Leaderboard
void GooglePlayGameServices::LeaderBoard::SubmitHighScore(std::string leaderboard_id, int score)
{

}
void GooglePlayGameServices::LeaderBoard::ShowLeaderboard(std::string leaderboard_id)
{

}
// GPS
GooglePlayGameServices::Location GooglePlayGameServices::GPS::GetCurrentLocation()
{
	uthGPGS.curLocation.loc_latitude = 0;
	uthGPGS.curLocation.loc_longitude = 0;
	uthGPGS.curLocation.loc_accuracy = 0;
	uthGPGS.curLocation.device_time_since_reboot = "+88m88s88ms";
	
	return uthGPGS.curLocation;
}
float GooglePlayGameServices::GPS::GetDistanceTo(double latitude, double longitude)
{
	return 0;
}
float GooglePlayGameServices::GPS::GetDistanceBetween(double sLatitude, double sLongitude, double eLatitude, double eLongitude)
{
	return 0;
}
double GooglePlayGameServices::GPS::GetLatitude()
{
	return 0;
}
double GooglePlayGameServices::GPS::GetLongitude()
{
	return 0;
}
float GooglePlayGameServices::GPS::GetAccuracy()
{
	return 0;
}