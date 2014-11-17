package fi.kajakgames.uth;

import android.content.Context;
import android.content.Intent;
import android.location.Location;
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
import com.google.android.gms.games.Games;
import com.google.android.gms.plus.Plus;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.analytics.*;
import com.google.android.gms.location.*;

import fi.kajakgames.uth.BaseGameUtils;

public class GameActivity extends android.app.NativeActivity
implements LocationListener, 
GoogleApiClient.ConnectionCallbacks, 
GoogleApiClient.OnConnectionFailedListener
{
	GameActivity gameActivity;
	AdView	gAdView;
	
	private boolean useGoogleAnalytics = false;
	private boolean usePlayServices = true;
	
	GoogleApiClient mClient;
	Location mCurLocation;
	LocationRequest locationRequest;
	
	private static final long INTERVAL = 1000 * 30;
    private static final long FASTEST_INTERVAL = 1000 * 5;
	
	
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

		if(usePlayServices){
		mClient = new GoogleApiClient.Builder(this)
		.addApi(Games.API).addScope(Games.SCOPE_GAMES)
		.addApi(Plus.API).addScope(Plus.SCOPE_PLUS_LOGIN)
		.addApi(LocationServices.API)
		.addOnConnectionFailedListener(this)
		.addConnectionCallbacks(this)
		.build(); }
		
		//((GameAnalytics) getApplication()).getTracker(GameAnalytics.TrackerName.APP_TRACKER); // doesn't work
		if(useGoogleAnalytics){	GoogleAnalytics.getInstance(this).newTracker(R.xml.app_tracker); }
		
		locationRequest = LocationRequest.create();
		locationRequest.setPriority(LocationRequest.PRIORITY_HIGH_ACCURACY);
		locationRequest.setInterval(INTERVAL);
		locationRequest.setFastestInterval(FASTEST_INTERVAL);
	}
	
	public void onStart()
	 {
	 	super.onStart();
	 	if(usePlayServices){ mClient.connect(); }
	 	
	 	if(useGoogleAnalytics){ GoogleAnalytics.getInstance(this).reportActivityStart(this); }
	 }
	  
	 public void onStop()
	 {
		if(usePlayServices){ mClient.disconnect(); }
			
		if(useGoogleAnalytics){ GoogleAnalytics.getInstance(this).reportActivityStop(this); }
		
		super.onStop();	
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
		if(usePlayServices)
		{
			if(!mClient.isConnected())
				mClient.connect();	
			
			Games.Achievements.unlock(mClient, achievement_id);
		}
		else
		{
			Log.d("uth-engine", "GooglePlayGameServices is disabled.");
		}
	}
	public void IncrementAchievement(String achievement_id, int steps)
	{	
		if(usePlayServices)
		{
			if(!mClient.isConnected())
				mClient.connect();	
			
			Games.Achievements.increment(mClient, achievement_id, steps);
		}
		else
		{
			Log.d("uth-engine", "GooglePlayGameServices is disabled.");
		}
	}
	
	public void ShowAchievements()
	{	
		if(usePlayServices)
		{
			if(!mClient.isConnected())
				mClient.connect();
			
			startActivityForResult(Games.Achievements.getAchievementsIntent(mClient), 5001);
		}
		else
		{
			Log.d("uth-engine", "GooglePlayGameServices is disabled.");
		}
	}
	
	public void SubmitHighScore(String leaderboard_id, int score)
	{	
		if(usePlayServices)
		{
			if(!mClient.isConnected())
				mClient.connect();
			
			Games.Leaderboards.submitScore(mClient, leaderboard_id, score);
		}
		else
		{
			Log.d("uth-engine", "GooglePlayGameServices is disabled.");
		}
	}
	
	public void ShowLeaderboard(String leaderboard_id)
	{	
		if(usePlayServices)
		{
			if(!mClient.isConnected())
				mClient.connect();
			
			startActivityForResult(Games.Leaderboards.getLeaderboardIntent(mClient, leaderboard_id), 5002);
		}
		else
		{
			Log.d("uth-engine", "GooglePlayGameServices is disabled.");
		}
	}
	

	public String GetCurrentLocation()
	{
		mCurLocation = LocationServices.FusedLocationApi.getLastLocation(mClient);
		
		//Log.d("location test", "" + mCurLocation); 
		
		//Log.d("location string", "" + mCurLocation.toString());
	
		return mCurLocation.toString();
	}
	public float DistanceTo(double endLatitude, double endLongitude)
	{
		float[] result = {0};
		
		//GetCurrentLocation();
		//double startLatitude = mCurLocation.getLatitude();
		//double startLongitude = mCurLocation.getLongitude();
		double startLatitude = LocationServices.FusedLocationApi.getLastLocation(mClient).getLatitude();
		double startLongitude = LocationServices.FusedLocationApi.getLastLocation(mClient).getLongitude();
		
		Location.distanceBetween(startLatitude, startLongitude, endLatitude, endLongitude, result);
		
		return result[0];
	}
	public float DistanceBetween(double startLatitude, double startLongitude, double endLatitude, double endLongitude)
	{
		float[] result = {0, 0, 0 };
		
		Location.distanceBetween(startLatitude, startLongitude, endLatitude, endLongitude, result);
		
		return result[0];
	}
	public double GetLatitude()
	{
		double result = 0;

		//GetCurrentLocation();
		result = LocationServices.FusedLocationApi.getLastLocation(mClient).getLatitude();
		
		return result;
	}
	public double GetLongitude()
	{
		double result = 0;
		
		//GetCurrentLocation();
		result = LocationServices.FusedLocationApi.getLastLocation(mClient).getLongitude();
		
		return result;
	}
	public float GetAccuracy()
	{
		float result = 0;
		
		//GetCurrentLocation();
		result = LocationServices.FusedLocationApi.getLastLocation(mClient).getAccuracy();
		
		return result;
	}
	
	private static int RC_SIGN_IN = 9001;
	private boolean mResolvingConnectionFailure = false;
	private boolean mAutoStartSignInFlow = true;
	private boolean mSignInClicked = false;

	@Override
	public void onConnectionFailed(ConnectionResult arg0) 
	{
		Log.d("uth-engine", "Connection failed, result: " + arg0);
		
		if (mResolvingConnectionFailure)
		{
			return;
		}
		
		if(mSignInClicked || mAutoStartSignInFlow)
		{
			mAutoStartSignInFlow = false;
			mSignInClicked = false;
			mResolvingConnectionFailure = true;		
			
			
			if(!BaseGameUtils.resolveConnectionFailure(this, mClient, arg0, RC_SIGN_IN, "Error message"))
			{
				mResolvingConnectionFailure = false;
			}
		}
	}

	@Override
	public void onConnected(Bundle arg0) 
	{
		Log.d("uth-engine", "OnConnected, bundle: " + arg0);
		//Toast.makeText(this, "Connected", Toast.LENGTH_SHORT).show();
		
		LocationServices.FusedLocationApi.requestLocationUpdates(mClient, locationRequest, gameActivity);
	}
	@Override
	public void onConnectionSuspended(int arg0) 
	{
		Log.d("uth-engine", "onConnectionSuspended, arg: " + arg0);
	}
	@Override
	protected void onActivityResult(int requestCode, int responseCode, Intent intent)
	 {
		 if(requestCode == RC_SIGN_IN)
		 {
			 mSignInClicked = false;
			 Log.d("uth-engine", "onActivityResult with requestCode == 9001, responseCode=" + responseCode + ", intent=" + intent);
		 
			 if(responseCode == RESULT_OK)
			 {
				 mClient.connect();
			 }
			 else
			 {
				 BaseGameUtils.showActivityResultError(this, requestCode, responseCode, R.string.signin_failure, R.string.signin_other_error);
			 }
		 }
	 }

	@Override
	public void onLocationChanged(Location arg0) {
		// TODO Auto-generated method stub
		Log.d("location", "changed");
	}

	
	public void onDisconnected() 
	{
		//Toast.makeText(this, "Disconnected.", Toast.LENGTH_SHORT).show();
		Log.d("uth-engine", "Disconnected");
		
	}
	
	
}
