#pragma once
#ifndef WINDOWSETTINGS_H_UTH
#define WINDOWSETTINGS_H_UTH

#include <string>
#include <UtH/Platform/Configuration.hpp>
#include <pmath/Vector2.hpp>


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

			contextVersionMajor(0),
			contextVersionMinor(0),

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

		pmath::Vec2 position;
		pmath::Vec2 size;

		std::string title;
	};
}

#endif