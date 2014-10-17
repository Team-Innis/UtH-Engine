package fi.kajakgames.uth;

import android.content.Context;
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
import com.google.android.gms.games.achievement.*;
import com.google.android.gms.games.leaderboard.*;
import com.google.android.gms.common.api.GoogleApiClient;

public class GameActivity extends android.app.NativeActivity
{

	GameActivity gameActivity;
	AdView	gAdView;
	GoogleApiClient client;
	Achievement achievement;
	Leaderboard leaderboard;
	
	public class AdStruct
	{
		public AdRequest adRequest = null;
		public AdView adView = null;
		public MarginLayoutParams mLParams = null;
		public PopupWindow window = null;
		//public RelativeLayout layout = null;
		//public RelativeLayout mainLayout = null;
		public LinearLayout layout = null;
		public LinearLayout mainLayout = null;
		public String adUnitID = null;
		
		public AdStruct(String adID)
		{
			if(adView == null)
				adView = new AdView(gameActivity);
			adView.setAdSize(AdSize.BANNER);
			adView.setAdUnitId(adID);
			
			if(window == null)
				window = new PopupWindow(gameActivity);
			window.setWidth(320);
			window.setHeight(50);
			window.setWindowLayoutMode(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
			window.setClippingEnabled(false);
			
			if(layout == null)
				layout = new LinearLayout(gameActivity);
			if(mainLayout == null)
				mainLayout = new LinearLayout(gameActivity);
			
			layout.setPadding(-12, -12, -12, -12);
			mLParams = new MarginLayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
			mLParams.setMargins(0, 0, 0, 0);
			layout.addView(adView, mLParams);
			
			window.setContentView(layout);
			gameActivity.setContentView(mainLayout, mLParams);

			if(adRequest == null)
				adRequest = new AdRequest.Builder()
								     .addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
								     .addTestDevice("9DACB2219B50B6E9F596041151E63E12") // my Nexus 5
								     .addTestDevice("1B5A8F52DE892FF3954B698A84CBCC87") // jani Xperia
								     .addTestDevice("E69C2A8B1675A10447583C0049DC0D26") // my Tab2
								     .build();
		}
		
		public void onDestroy()
		{
			adRequest = null;
			adView = null;
			mLParams = null;
			window = null;
			layout = null;
			mainLayout = null;
			adUnitID = null;
		}
	}
	
	AdStruct[] adS = {null, null, null, null, null, null, null, null, null, null};
	
	static
	{
		System.loadLibrary("sndfile");
		System.loadLibrary("openal");
		System.loadLibrary("uthengine");
	}

	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		// Make your custom init here
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		
		if(gameActivity == null)
			gameActivity = this;
		
		adS[0] = new AdStruct(this.getString(R.string.banner_ad_unit_id));
		gAdView = new AdView(gameActivity);
		
		DisplayMetrics metrics = getResources().getDisplayMetrics();
		Log.i("uth-engine", "dpi:" + metrics.densityDpi);
	}
	
	
	 public void onStart()
	 {
	 	super.onStart();
	  	client.connect();
	 }
	  
	 public void onStop()
	 {
		super.onStop();
		client.disconnect();
	 }
	 
	
	public void Vibrate(final int time)
	{
		Vibrator vibra = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);

		if(vibra == null)
			Log.i("uth-engine", "vibra is null");
			
		vibra.vibrate(time);
	}
	
	public void ShowAdPopup(final int offsetX, final int offsetY, final int origin)
	{
		if(adS[origin] == null)
		{
			adS[origin] = adS[0];
		}
		
		if(adS[origin] != null)
		{
			gameActivity.runOnUiThread(new Runnable() 
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
					gameActivity.adS[origin].adView.loadAd(adS[origin].adRequest);
					adS[origin].window.showAtLocation(adS[origin].mainLayout, gravity, offsetX, offsetY);
					adS[origin].window.update(offsetX, offsetY, 320, 50);
			}});
		}
		else
			Log.e("uth-engine", "adS[" + (origin-1) + "] is null");
	}
	
	public void CloseAd(final int origin)
	{
		if(origin == 0)
		{
			gameActivity.runOnUiThread(new Runnable() 
			{
				@Override
				public void run()
				{
					for(int i = 1; i < 10; i++)
					{
						if(adS[i] != null)
							if(adS[i].window.isShowing())
							{
								adS[i].window.dismiss();
							}
					}
				}
			});
		}
		else if(adS[origin].window.isShowing())
		{
			gameActivity.runOnUiThread(new Runnable() 
			{
				@Override
				public void run()
				{
					adS[origin].window.dismiss();
				}
			});
		}		
	}

	
	public void UnlockAchievement(String achievement_id)
	{
		Log.i("uth-engine", "received string: " + achievement_id);
		
		if(!client.isConnected())
			client.connect();
		
		//Games.Achievements.unlock(getApiClient(), achievement_id);
	}
	
	public void ShowAchievements()
	{
		if(!client.isConnected())
			client.connect();
	}
	
	public void SubmitHighScore(String leaderboard_id, int score)
	{
		if(!client.isConnected())
			client.connect();
	}
	
	public void ShowLeaderboard(String leaderboard_id)
	{
		if(!client.isConnected())
			client.connect();
	}
}
