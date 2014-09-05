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
#include <pmath/PMath.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>
#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/WindowSettings.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/FileReader.h>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Input.hpp>
#include <UtH/Platform/Android/InputSensor.hpp>

#include <UtH/Engine/DefaultScene.hpp>
#include "TestScene.hpp"

// Enumeration of scenes, giving name for each scene number
enum SceneName
{
    DEFAULT = UTHDefaultScene,
    MENU = 0,
    GAME = 1,
    CREDITS,
    COUNT // Keep this last, it tells how many scenes there are
};

// Create function for a new scene, having a case for every user made scene
void NewSceneFunc(int SceneID, uth::Scene* &CurScene)
{
    switch (SceneID)
    {
    case MENU:
        CurScene = new /*Menu*/uth::TestScene();
        break;
    case GAME:
        CurScene = new /*Game*/uth::TestScene();
        break;
    case CREDITS:
        CurScene = new /*Credits*/uth::TestScene();
        break;
    default:
        CurScene = new /*Menu*/uth::DefaultScene();
        break;
    }
}


void handle_cmd(android_app* app, int cmd)
{
	uthAndroidEngine.message = cmd;
	((uth::Window*)app->userData)->processMessages();
}

void handle_input(android_app* app, AInputEvent* inputEvent)
{
    switch (AInputEvent_getType(inputEvent))
    {
    case AINPUT_EVENT_TYPE_KEY:
        break;
    case AINPUT_EVENT_TYPE_MOTION:
        switch (AInputEvent_getSource(inputEvent))
        {
        case AINPUT_SOURCE_DPAD:
        case AINPUT_SOURCE_JOYSTICK:

            break;
        case AINPUT_SOURCE_TOUCHSCREEN:
            uth::TouchInput::DroidMessage(app, inputEvent);
            break;
        default:
            // Not supported
            break;
        }
        break;
    }
}

void windowEventHandler(void* handle)
{
	uthEngine.SetWindow((uth::Window*)handle);
}

void android_main(android_app* state)
{
	app_dummy();

    ALooper* looper = ALooper_forThread();
    if (looper == NULL)
        looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);

	uthAndroidEngine.initialized = false;

	uth::Window wndw;
	uth::FileReader::m_manager = state->activity->assetManager;

	state->onAppCmd = handle_cmd;
	state->onInputEvent = uth::TouchInput::DroidMessage;

    uth::SensorInput::sensorManager = ASensorManager_getInstance();
    uth::SensorInput::sensorEventQueue = ASensorManager_createEventQueue(
        uth::SensorInput::sensorManager,
        looper, LOOPER_ID_USER, uth::SensorInput::getSensorEvents, NULL);
    uth::SensorInput::accelerometer = ASensorManager_getDefaultSensor(
        uth::SensorInput::sensorManager, ASENSOR_TYPE_ACCELEROMETER);
    uth::SensorInput::gyroscope = ASensorManager_getDefaultSensor(
        uth::SensorInput::sensorManager, ASENSOR_TYPE_GYROSCOPE);

	uthAndroidEngine.app = state;

    uthAndroidEngine.settings.position = pmath::Vec2(0, 0);
	uthAndroidEngine.settings.contextVersionMajor = 2;
	uthAndroidEngine.settings.contextVersionMinor = 0;
    uthAndroidEngine.settings.fullScreen = true;

	state->userData = &wndw;

	uthAndroidEngine.winEveHand = windowEventHandler;


    uthSceneM.registerNewSceneFunc(NewSceneFunc, COUNT);

	while(1)
	{
		int ident;
		int events;
		android_poll_source* source;

		while ((ident=ALooper_pollAll(0, nullptr, &events,(void**)&source)) >= 0)
		{
			//Insteads of these two 'if' statement proper exit should be placed
			if (source != nullptr)
			{
				source->process(state, source);
			}
			if (state->destroyRequested != 0)
			{
				wndw.destroy();
				return;
			}
		}

		if(uthAndroidEngine.initialized && uthAndroidEngine.display != nullptr)
		{
			uthEngine.Update();
			uthEngine.Draw();
		}
	}
}