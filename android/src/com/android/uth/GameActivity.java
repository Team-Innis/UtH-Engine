package com.android.uth;

import android.content.Context;
import android.os.Bundle;
import android.os.Vibrator;
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
	
	public void ShowAdPopup(final int offsetX, final int offsetY, final int origin)
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
					int gravity = Gravity.BOTTOM;
					switch(origin)
					{
					case 1:
						gravity = Gravity.BOTTOM | Gravity.LEFT;
						break;
					case 2:
						gravity = Gravity.BOTTOM;
						break;
					case 3:
						gravity = Gravity.BOTTOM | Gravity.RIGHT;
						break;
					case 4:
						gravity = Gravity.LEFT;
						break;
					case 5:
						gravity = Gravity.CENTER;
						break;
					case 6:
						gravity = Gravity.RIGHT;
						break;
					case 7:
						gravity = Gravity.TOP | Gravity.LEFT;
						break;
					case 8:
						gravity = Gravity.TOP;
						break;
					case 9:
						gravity = Gravity.TOP | Gravity.RIGHT;
						break;
					default:
						gravity = Gravity.BOTTOM;
						break;
					}
					
					Log.v("uth-engine", "adrun");
					adsinited = true;
				
					popUp = new PopupWindow(_activity);
				
					popUp.setWidth(720);
					popUp.setHeight(640);
				
					popUp.setWindowLayoutMode(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
					popUp.setClippingEnabled(false);
				
					layout = new RelativeLayout(_activity);
					mainLayout = new RelativeLayout(_activity);
				
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
					popUp.showAtLocation(mainLayout, gravity, offsetX, offsetY);
					popUp.update();
			
			}});
		}
		else
			Log.v("uth-engine", "adView null");
			
	}
	
}
