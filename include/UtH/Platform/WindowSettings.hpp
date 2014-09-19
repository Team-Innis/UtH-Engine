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
			useVsync(true),
			fullScreen(false),

			contextVersionMajor(3),
			contextVersionMinor(3),

			antialiasingSamples(0),

			position(100, 100),
			size(1280, 720),

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