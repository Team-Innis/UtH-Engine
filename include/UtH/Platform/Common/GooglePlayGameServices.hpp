#pragma once
#ifndef GOOGLEPLAYGAMESERVICES_H_UTH
#define GOOGLEPLAYGAMESERVICES_H_UTH

#include <UtH/Platform/Singleton.hpp>
#include <string>

#define uthGPGS uth::GooglePlayGameServices().getInstance() 

namespace uth
{
	class GooglePlayGameServices : public Singleton < GooglePlayGameServices >
	{
		friend class Singleton < GooglePlayGameServices > ;

		struct Location;

		class Achievement
		{
		public:
			void UnlockAchievement(std::string achievement_id);
			void IncrementAchievement(std::string achievement_id, int steps);
			void ShowAchievements();
		};
		class LeaderBoard
		{
		public:
			void SubmitHighScore(std::string leaderboard_id, int score);
			void ShowLeaderboard(std::string leaderboard_id);
		};
		class GPS
		{
		public:
			Location GetCurrentLocation();
			float GetDistanceTo(double latitude, double longitude);
			float GetDistanceBetween(double sLatitude, double sLongitude, double eLatitude, double eLongitude);
			double GetLatitude();
			double GetLongitude();
			float GetAccuracy();
		};

	public:
		GooglePlayGameServices();
		~GooglePlayGameServices();

		Achievement achievement;
		LeaderBoard leaderboard;
		GPS gps;

		struct Location
		{
			double loc_latitude;
			double loc_longitude;
			float loc_accuracy;
			std::string device_time_since_reboot;
		}curLocation;
		

	private:
	
	};
}

#endif