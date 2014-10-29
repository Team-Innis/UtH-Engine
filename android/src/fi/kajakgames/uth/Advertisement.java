package fi.kajakgames.uth;

import android.util.Log;
import android.view.Gravity;
import android.view.ViewGroup.MarginLayoutParams;
import android.view.WindowManager.LayoutParams;
import android.widget.LinearLayout;
import android.widget.PopupWindow;

import com.google.android.gms.ads.*;

public class Advertisement
{
	boolean toggled = false;
	int[] offset = {0,0};
	int[] size = {320,50};
	int gravity = Gravity.BOTTOM;
	
	AdRequest adRequest = null;
	AdView adView = null;
	MarginLayoutParams mLParams = null;
	PopupWindow window = null;
	LinearLayout layout = null;
	LinearLayout mainLayout = null;
	String adUnitID = null;
	String name = null;
	
	public Advertisement(final GameActivity gameActivity, final int padding)
	{
		adView = new AdView(gameActivity);
		window = new PopupWindow(gameActivity);
		window.setWindowLayoutMode(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		window.setClippingEnabled(false);
		
		layout = new LinearLayout(gameActivity);
		mainLayout = new LinearLayout(gameActivity);
		
		layout.setPadding(-padding-1, -padding-1, -padding-1, -padding-1);
		mLParams = new MarginLayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		mLParams.setMargins(0, 0, 0, 0);
		layout.addView(adView, mLParams);
		
		window.setContentView(layout);
		gameActivity.setContentView(mainLayout, mLParams);

		adRequest = new AdRequest.Builder()
						     .addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
						     .addTestDevice("E69C2A8B1675A10447583C0049DC0D26")
						     .addTestDevice("9DACB2219B50B6E9F596041151E63E12")
						     .build();
	}
	
	public Advertisement(final String adUnitID_, final Advertisement init, final AdSize adsize, final int[] Offset, final int origin)
	{
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
		
		adRequest = init.adRequest;
		adView = init.adView;
		mLParams = init.mLParams;
		window = init.window;
		layout = init.layout;
		mainLayout = init.mainLayout;
		adUnitID = init.adUnitID;

		adUnitID = adUnitID_;
		adView.setAdUnitId(adUnitID);
		adView.setAdSize(adsize);
		size[0] = adsize.getWidth();
		size[1] = adsize.getHeight();
		window.setWidth(size[0]);
		window.setHeight(size[0]);
		offset = Offset;
	}
	
	public void Toggle()
	{
		if(toggled)
		{
			Hide();
			toggled = false;
		}
		else
		{
			Show();
			toggled = true;
		}
	}
	
	private void Show()
	{
		adView.loadAd(adRequest);
		window.showAtLocation(mainLayout, gravity, offset[0], offset[1]);
		window.update(offset[0], offset[1], size[0], size[1]);
	}
	
	private void Hide()
	{
		window.dismiss();
		adView.pause();
	}
}
