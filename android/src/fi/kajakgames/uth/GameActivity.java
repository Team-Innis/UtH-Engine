package fi.kajakgames.uth;

import java.util.Vector;

import android.content.Context;
import android.content.res.Resources;
import android.os.Bundle;
import android.os.Vibrator;
import android.util.Log;
import android.util.DisplayMetrics;
import android.view.*;
import android.view.ViewGroup.MarginLayoutParams;
import android.view.WindowManager.LayoutParams;
import android.widget.*;
import fi.kajakgames.uth.R;

import com.google.android.gms.ads.*;

public class GameActivity extends android.app.NativeActivity
{
	GameActivity gameActivity;
	Advertisement initialAd = null;
	Vector<Advertisement> adList = new Vector<Advertisement>(32);
	
	//Test Only
	private InterstitialAd interstitial;
	
	static
	{
		System.loadLibrary("sndfile");
		System.loadLibrary("openal");
		System.loadLibrary("uthengine");
	}

	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
		
		if(gameActivity == null)
			gameActivity = this;
		
		int dpi = getResources().getDisplayMetrics().densityDpi;
		float padding = ((dpi / 100.0f) * getResources().getDisplayMetrics().density);
		Log.i("uth-engine", "padding " + padding);
		initialAd = new Advertisement(this, (int)padding);
		
		//Test
		interstitial = new InterstitialAd(this);
		final String adID = this.getString(R.string.AdMobPublisherID) + "/" + "9257920890";
		interstitial.setAdUnitId(adID);
	    AdRequest adRequest = new AdRequest.Builder()
									    .addTestDevice("E69C2A8B1675A10447583C0049DC0D26")
									    .build();
	    
	    interstitial.loadAd(adRequest);
	}
	
	public void Vibrate(int time)
	{
		Vibrator vibra = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);

		if(vibra == null)
			Log.i("uth-engine", "vibra is null");
			
		vibra.vibrate(time);
	}
	
	public void ShowAd(final int offsetX, final int offsetY, final int origin, final String name)
	{
		final String publisher = this.getString(R.string.AdMobPublisherID);
		
		gameActivity.runOnUiThread(new Runnable() 
		{
			@Override
			public void run()
			{
				boolean exists = false;
				int index = 0;
				
				for(int i = 0; i < adList.size(); i++)
				{
					if(adList.get(i).name.equals(name))
					{
						exists = true;
						index = i;
						break;
					}
				}
				
				if(exists == false)
				{
					String adID  = publisher + "/" + name;
					int[] offset = {offsetX, offsetY};
					Advertisement lol = new Advertisement(adID, initialAd, AdSize.BANNER, offset, origin);
					lol.name = name;
					
					adList.add(lol);
					index = adList.indexOf(lol);
				}
				adList.get(index).Toggle();
			}
		});
	}
	
	public void ShowAdFull(final String adID)
	{
		gameActivity.runOnUiThread(new Runnable() 
		{
			@Override
			public void run()
			{
				Log.i("uth-engine","Show fullscreen ad[" + adID + "]");
			    if (interstitial.isLoaded())
			    {
			        interstitial.show();
					Log.i("uth-engine","after show full");
			    }
				Log.i("uth-engine","end of show full");
			}
		});
	}
	
	public void HideAd(final String name)
	{
		gameActivity.runOnUiThread(new Runnable() 
		{
			@Override
			public void run()
			{
				for(int i = 0; i < adList.size(); i++)
				{
					if(adList.get(i).name.equals(name))
					{
						adList.get(i).Toggle();
						break;
					}
				}
			}
		});
	}
}
