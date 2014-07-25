/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.annotation.TargetApi;
import android.app.Activity;
import android.graphics.Color;
import android.graphics.Point;
import android.os.Build;
import android.os.Bundle;
import android.view.Display;
import android.view.View;
import android.widget.LinearLayout;

import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;

public class AppActivity extends Cocos2dxActivity {
	static AdView adView;
	static Activity me;
	final String ADMOB_ID="ca-app-pub-8430244079488991/3538408247";

	// Helper get display screen to avoid deprecated function use
	private Point getDisplaySize(Display d)
	    {
	        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB)
	        {
	            return getDisplaySizeGE11(d);
	        }
	        return getDisplaySizeLT11(d);
	    }

	    @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
	    private Point getDisplaySizeGE11(Display d)
	    {
	        Point p = new Point(0, 0);
	        d.getSize(p);
	        return p;
	    }
	    private Point getDisplaySizeLT11(Display d)
	    {
	        try
	        {
	            Method getWidth = Display.class.getMethod("getWidth", new Class[] {});
	            Method getHeight = Display.class.getMethod("getHeight", new Class[] {});
	            return new Point(((Integer) getWidth.invoke(d, (Object[]) null)).intValue(), ((Integer) getHeight.invoke(d, (Object[]) null)).intValue());
	        }
	        catch (NoSuchMethodException e2) // None of these exceptions should ever occur.
	        {
	            return new Point(-1, -1);
	        }
	        catch (IllegalArgumentException e2)
	        {
	            return new Point(-2, -2);
	        }
	        catch (IllegalAccessException e2)
	        {
	            return new Point(-3, -3);
	        }
	        catch (InvocationTargetException e2)
	        {
	            return new Point(-4, -4);
	        }
	    }

	    @Override
	    protected void onCreate(Bundle savedInstanceState){
	    	super.onCreate(savedInstanceState);
	    	

adView = new AdView(this);
adView.setAdSize(AdSize.BANNER);
adView.setAdUnitId(ADMOB_ID);


int width = getDisplaySize(getWindowManager().getDefaultDisplay()).x;


LinearLayout.LayoutParams adParams = new LinearLayout.LayoutParams(
width,
LinearLayout.LayoutParams.WRAP_CONTENT);


AdRequest adRequest = new AdRequest.Builder()
.addTestDevice(AdRequest.DEVICE_ID_EMULATOR)
.addTestDevice("HASH_DEVICE_ID")
.build();

adView.loadAd(adRequest);
            adView.setBackgroundColor(Color.BLACK);
            adView.setBackgroundColor(0);
            addContentView(adView,adParams);

            me = this;
            
            adView.setVisibility(View.VISIBLE);
	    }
	    
	static void showAdmobJNI(){
		me.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				adView.setVisibility(View.VISIBLE);
			}
		});
	}

	static void hideAdmobJNI(){
		me.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				adView.setVisibility(View.INVISIBLE);
			}
		});
    }
	
	static void setAdmobVisibleJNI(final int number){
		me.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if(number==0){
		    		adView.setVisibility(View.INVISIBLE);
		    	} else {
		    		adView.setVisibility(View.VISIBLE);
		    	}
			}
		});

    }
	
	static void setVisibleAdmobJNI(final boolean visible){

		me.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if(visible){
		    		adView.setVisibility(View.VISIBLE);
		    	} else {
		    		adView.setVisibility(View.INVISIBLE);
		    	}
			}
		});
    }
	
	 static void setAdmobVisibilityJNI(final String name){
	    	me.runOnUiThread(new Runnable() {
				@Override
				public void run() {
			    	if(name.equals("show")||name=="show"){
			    		adView.setVisibility(View.VISIBLE);
			    	} else {
			    		adView.setVisibility(View.INVISIBLE);
			    	}
				}
			});
	    }
}
