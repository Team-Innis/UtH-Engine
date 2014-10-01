package com.android.uth;

import android.content.Context;
import android.os.Vibrator;

public class GameActivity extends android.app.NativeActivity
{
	static
	{
		System.loadLibrary("sndfile");
		System.loadLibrary("openal");
		System.loadLibrary("uthengine");
	}
	
	public void Vibrate(int time)
	{
		Vibrator v = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
		v.vibrate(time);
	}
}
