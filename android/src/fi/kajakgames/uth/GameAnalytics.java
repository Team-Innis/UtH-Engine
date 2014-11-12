package fi.kajakgames.uth;

import android.app.Application;

import com.google.android.gms.analytics.GoogleAnalytics;
import com.google.android.gms.analytics.Tracker;

import java.util.HashMap;

public class GameAnalytics extends Application
{
	// The following line should be changed to include the correct id
	private static final String PROPERTY_ID = "UA-56465161-1";
	
	// Logging TAG
	private static final String TAG = "GameAnalytics";

	public static int GENERAL_TRACKER = 0;
	
	public enum TrackerName
	{
		APP_TRACKER,	// Tracker used only in this app
		GLOBAL_TRACKER,	// Tracker used by all apps from a company
		ECOMMERCE_TRACKER,// Tracker used by all ecommerce transactions from a company
	}
	
	HashMap<TrackerName, Tracker> mTrackers = new HashMap<TrackerName, Tracker>();
	
	public GameAnalytics(){super();}
	
	public synchronized Tracker getTracker(TrackerName trackerId)
	{
		if(!mTrackers.containsKey(trackerId))
		{
			GoogleAnalytics analytics = GoogleAnalytics.getInstance(this);
			/*Tracker t = (trackerId == TrackerName.APP_TRACKER) ? analytics.newTracker(R.xml.app_tracker)
					: (trackerId == TrackerName.GLOBAL_TRACKER) ? analytics.newTracker(PROPERTY_ID)
					: analytics.newTracker(R.xml.ecommerce_tracker);*/
			Tracker t = analytics.newTracker(R.xml.app_tracker);
					mTrackers.put(trackerId, t);
		}
		return mTrackers.get(trackerId);
	}	
}
