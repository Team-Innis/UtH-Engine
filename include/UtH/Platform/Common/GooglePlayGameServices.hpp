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

	public:
		GooglePlayGameServices();
		~GooglePlayGameServices();

		Achievement achievement;
		LeaderBoard leaderboard;

	private:
	
	};
}

#endif