package com.android.uth;

public class GameActivity extends android.app.NativeActivity
{
	static
	{
		System.loadLibrary("sndfile");
		System.loadLibrary("openal");
		System.loadLibrary("uthengine");
	}
}




