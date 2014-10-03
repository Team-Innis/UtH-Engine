package com.android.uth;

import android.content.Context;
import android.os.Bundle;
import android.os.Vibrator;
import android.support.annotation.StringRes;
import android.util.Log;
import android.view.*;
import android.view.ViewGroup.MarginLayoutParams;
import android.view.WindowManager.LayoutParams;
import android.widget.*;

import com.google.android.gms.ads.*;

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
		Vibrator vibra = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);

		if(vibra == null)
			Log.v("uth-engine", "vibra is null");
			
		vibra.vibrate(time);
	}
	
	AdView adView = null;

	PopupWindow popUp;
	GameActivity _activity;
	RelativeLayout layout;
	RelativeLayout mainLayout;
	boolean adsinited = false;
	
	public void onCreate(Bundle savedInstanceState)
	{

		super.onCreate(savedInstanceState);

		// Make your custom init here
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		_activity = this;

		// Create our ad view here
		adView = new AdView(_activity);
		adView.setAdSize(AdSize.BANNER);
		adView.setAdUnitId(this.getString(R.string.banner_ad_unit_id));
	}
	
	public void ShowAdPopup()
	{
		if(adsinited)
		{
			Log.v("uth-engine", "adsinited");
			return;
		}
		
		if(adView != null)
		{
			Log.v("uth-engine", "adView not null");
			_activity.runOnUiThread(new Runnable() 
			{
		
				@Override
				public void run()
				{

					Log.v("uth-engine", "adrun");
					adsinited = true;
				
					// Out popup window
					popUp = new PopupWindow(_activity);
					// This is the minimum size for AdMob, we need to set this in case our target device run at 320x480 resolution (Otherwise no ad will be shown, see the padding kill below)
				
					popUp.setWidth(720);
					popUp.setHeight(640);
				
					popUp.setWindowLayoutMode(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
					popUp.setClippingEnabled(false);
				
					layout = new RelativeLayout(_activity);
					mainLayout = new RelativeLayout(_activity);
				
					// The layout system for the PopupWindow will kill some pixels due to margins/paddings etc… (No way to remove it), so padd it to adjust
					layout.setPadding(-12, -12, -12, -12);
					Log.v("uth-engine", "Adview " + adView.getAdSize().getWidth() + " " + adView.getAdSize().getHeight());
					
					MarginLayoutParams params = new MarginLayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
					params.setMargins(0, 0, 0, 0);
					//layout.setOrientation(LinearLayout.VERTICAL);
					layout.addView(adView, params);
				
					popUp.setContentView(layout);
					_activity.setContentView(mainLayout, params);
				
					AdRequest adRequest = new AdRequest.Builder()
				    .addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
				    .addTestDevice("9DACB2219B50B6E9F596041151E63E12")
				    .addTestDevice("1B5A8F52DE892FF3954B698A84CBCC87")
				    .build();
					
					_activity.adView.loadAd(adRequest);
					popUp.showAtLocation(mainLayout, Gravity.BOTTOM, 0, 10);
					popUp.update();
			
			}});
		}
		else
			Log.v("uth-engine", "adView null");
			
	}
	
}
