#pragma once
#ifndef GOOGLEPLAYGAMESERVICES_H_UTH
#define GOOGLEPLAYGAMESERVICES_H_UTH

#include <UtH/Platform/Singleton.hpp>
#include <string>

//#include <gpg/gpg.h>


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
		/*
		void init();
		void initServices(gpg::PlatformConfiguration const &pc,
			gpg::GameServices::Builder::OnAuthActionStartedCallback started_callback,
			gpg::GameServices::Builder::OnAuthActionFinishedCallback finished_callback);

		void deInit();

		gpg::AndroidPlatformConfiguration *platform_config;
		static bool is_auth_in_progress;
		static std::unique_ptr<gpg::GameServices> game_services;
		*/
	};
}

#endif