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
	
	std::string test = "Location[fused 64,216285,27,714625 acc=20 et=+1m23s12ms]";

	std::string::size_type fused = test.find("fused");
	std::string::size_type acc = test.find("acc=");
	std::string::size_type et = test.find("et=");
	std::string::size_type timeEnd = test.find("]");

	std::string::size_type replacePos;

	std::string fusedString = test.substr(fused + 6, acc - fused - 7);
	std::string::size_type splitPos = fusedString.find(",", 4);


	std::string latitude = fusedString.substr(0, splitPos);
	replacePos = latitude.find(",");
	latitude.replace(replacePos, 1, ".");


	std::string longitude = fusedString.substr(splitPos+1);
	replacePos = longitude.find(",");
	longitude.replace(replacePos, 1, ".");


	std::string accuracy = test.substr(acc + 4, 2);
	std::string time = test.substr(et + 4, timeEnd - et - 4);

	uthGPGS.curLocation.loc_latitude = atof(latitude.c_str());
	uthGPGS.curLocation.loc_longitude = atof(longitude.c_str());
	uthGPGS.curLocation.loc_accuracy = atof(accuracy.c_str());
	uthGPGS.curLocation.device_time_since_reboot = time;
	
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