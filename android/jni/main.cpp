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
#include <UtH/UtHEngine.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>
#include <Uth/Platform/Input.hpp>
#include <UtH/Platform/Android/InputController.hpp>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#define NEWSCENEFUNC
#include <Scenes.hpp>

void handle_cmd(android_app* app, int cmd)
{
	uthAndroidEngine.message = cmd;
	((uth::Window*)app->userData)->processMessages();
}

int handle_input(android_app* app, AInputEvent* inputEvent)
{
    // Returning 1 seems to tell android that we handled
    // the event and android ignores it

    int32_t eventType = AInputEvent_getType(inputEvent);

    if (eventType == AINPUT_EVENT_TYPE_KEY)
    {
        int handledInput = uthInput.Controller.HandleInput(inputEvent);

		if (AKeyEvent_getKeyCode(inputEvent) == AKEYCODE_BACK)
		{
            handledInput = static_cast<int>(uthInput.RunBackButton());
		}

        return handledInput;
    }
    else if (eventType == AINPUT_EVENT_TYPE_MOTION)
    {
        int32_t source = AInputEvent_getSource(inputEvent);
        if (source == AINPUT_SOURCE_JOYSTICK)
        {
            uthInput.Controller.HandleInput(inputEvent);
        }
        else if (source == AINPUT_SOURCE_TOUCHSCREEN)
        {
            uth::TouchInput::DroidMessage(app, inputEvent);
        }

        return 1;
    }

    return 0;
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
	uth::FileManager::m_manager = state->activity->assetManager;

	state->onAppCmd = handle_cmd;
	state->onInputEvent = handle_input;

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
	ANativeActivity* natAct = state->activity;
	uthAndroidEngine.internalPath = natAct->internalDataPath;
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
			//Instead of these two 'if' statement proper exit should be placed
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