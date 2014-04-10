#pragma once
#ifndef WINDOWSETTINGS_H_UTH
#define WINDOWSETTINGS_H_UTH

#include <string>
#include <UtH/Platform/Configuration.hpp>
#include <UtH/Math/Vector2.hpp>


namespace uth
{
	struct WindowSettings
	{
		WindowSettings()
			: useDepthBuffer(false),
			useStencilBuffer(false),
			useBlending(true),
			useVsync(false),
			fullScreen(false),

#if defined(UTH_SYSTEM_WINDOWS) || defined(UTH_SYSTEM_LINUX)
			contextVersionMajor(3),
			contextVersionMinor(3),
#else
			contextVersionMajor(2),
			contextVersionMinor(0),
#endif

			antialiasingSamples(0),

			position(0, 0),
			size(800, 600),

			title("Generic window title")
		{}


		bool useDepthBuffer,
			useStencilBuffer,
			useBlending,
			useVsync,
			fullScreen;

		int contextVersionMajor,
			contextVersionMinor;

		int antialiasingSamples;

		umath::vector2 position;
		umath::vector2 size;

		std::string title;
	};
}

#endif