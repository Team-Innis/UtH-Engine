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
		
		if(gameActivity == null)
			gameActivity = this;
		
		int dpi = getResources().getDisplayMetrics().densityDpi;
		float padding = ((dpi / 100.0f) * getResources().getDisplayMetrics().density);
		
		initialAd = new Advertisement(this, (int)padding);
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
		Log.i("uth-engine", "Show Ad middle");
		
		gameActivity.runOnUiThread(new Runnable() 
		{
			@Override
			public void run()
			{
				String adID  = publisher + "/" + name;
				
				Advertisement lol = new Advertisement(adID, initialAd, AdSize.BANNER);
				lol.name = name;
				
				//TODO: Use gravity
				int gravity = Gravity.BOTTOM;
				switch(origin)
				{
				case 1:
					gravity = Gravity.BOTTOM | Gravity.LEFT; break;
				case 2:
					gravity = Gravity.BOTTOM; break;
				case 3:
					gravity = Gravity.BOTTOM | Gravity.RIGHT; break;
				case 4:
					gravity = Gravity.LEFT; break;
				case 5:
					gravity = Gravity.CENTER; break;
				case 6:
					gravity = Gravity.RIGHT; break;
				case 7:
					gravity = Gravity.TOP | Gravity.LEFT; break;
				case 8:
					gravity = Gravity.TOP; break;
				case 9:
					gravity = Gravity.TOP | Gravity.RIGHT; break;
				default:
					gravity = Gravity.BOTTOM; break;
				}
				Log.i("uth-engine", "Show AdID " + adID);
				
				adList.add(lol);
			
				for(int i = 0; i < adList.size(); i++)
				{
					if(adList.get(i).name == name)
					{
						adList.get(i).Toggle();
						break;
					}
				}
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
