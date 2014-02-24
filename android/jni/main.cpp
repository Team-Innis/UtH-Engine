/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/Debug.hpp>

#include <UtH/Math/Math.hpp>

#include <UtH/Platform/Android/AndroidEngine.hpp>
#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/WindowSettings.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/FileReader.h>

//After input manager 
//int handle_input(android_app* app, AInputEvent* event)			
//{
//	//AndroidEngine* androidengine = (AndroidEngine*)app->userData;
//	//Input should be places here
//	return 0;
//}

//This is sort of state manager. Checks is Activity on top or not and does it have saved state
//void handle_cmd(android_app* app, int cmd)														///EVENT MANAGER
//{
//	//AndroidEngine* androidengine = (AndroidEngine*)app->userData;
//
//	switch (cmd)
//	{
//	case APP_CMD_SAVE_STATE:
//		break;
//	case APP_CMD_INIT_WINDOW:
//		if (androidengine->app->window != NULL)
//		{
//			displayInit(androidengine);
//			draw_frame(androidengine);
//		}
//		break;
//	case APP_CMD_TERM_WINDOW:
//		displayDestroy(androidengine);
//		break;
//	case APP_CMD_LOST_FOCUS:
//		draw_frame(androidengine);
//		break;
//	}
//}

void android_main(android_app* state)
{
	app_dummy();

	uth::FileReader::m_manager = state->activity->assetManager;

	uth::AndroidEngine& androidengine = uth::AndroidEngine::getInstance();
    uthGraphics.getInstance();

    androidengine.settings.position = umath::vector2(0, 0);
	androidengine.settings.contextVersionMajor = 2;
	androidengine.settings.contextVersionMinor = 1;
    androidengine.settings.fullScreen = true;
	
    uth::Window wndw(androidengine.settings);
	uthGraphics.setBlendFunction(true, uth::SRC_ALPHA, uth::ONE_MINUS_SRC_ALPHA);

	androidengine.app = state;

	while(1)
	{
		int ident;
		int events;
		android_poll_source* source;

		while ((ident=ALooper_pollAll(0, NULL, &events,(void**)&source)) >= 0)
		{
			//Insteads of these two 'if' statement proper exit should be placed
			if (source != NULL)
			{
				source->process(state, source);
			}
			if (state->destroyRequested != 0)
			{
				wndw.destroy();
				return;
			}
		}

		if(androidengine.display == NULL)
		{
			;//Do nothing
		}
		else
		{
			wndw.clear(0.0f, 0.0f, 0.0f);
			//engine->Update();
		}
	}
}