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
import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.R;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.Point;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;


import com.sbstrm.appirater.Appirater;
import com.flurry.android.FlurryAgent;

import com.facebook.*;
import com.facebook.model.*;
import com.facebook.widget.FacebookDialog;
import com.facebook.widget.WebDialog;
import com.facebook.widget.WebDialog.OnCompleteListener;

public class AppActivity extends Cocos2dxActivity {
	static AdView adView;
	static AppActivity me;
	final String ADMOB_ID="ca-app-pub-8430244079488991/3538408247";
	
	final String FBAPP_ID="654394264657097";

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

	    static void significantEvent() 
	    {
	    	me.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					Appirater.significantEvent(me);
				}
			});
	    	
	    	
	    }
	    
	    static void rateus()
	    {
	    	
	    	me.runOnUiThread(new Runnable() {
				@Override
				public void run() {
					Appirater.rateApp(me);
				}
			});
	    	
	    	
	    }
	    
	    @Override
	    protected void onStart()
	    {
		    super.onStart();
		    FlurryAgent.onStartSession(this, "QC2BSN8DH4GM74MDBZXJ");
	    }
	    
	    @Override
	    protected void onStop()
	    {
		    super.onStop();	
		    FlurryAgent.onEndSession(this);
	    }
	    
	    @Override
	    protected void onCreate(Bundle savedInstanceState){
	    	super.onCreate(savedInstanceState);
	    	
	    	
	    	Appirater.appLaunched(this);
	    	
			
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
			
			RelativeLayout relativeLayout=new RelativeLayout(this);
			
				mFramelayout.addView(relativeLayout);
			
			
			RelativeLayout.LayoutParams adViewParams = new RelativeLayout.LayoutParams(
				    AdView.LayoutParams.WRAP_CONTENT,
				    AdView.LayoutParams.WRAP_CONTENT);
	//important
	adViewParams.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);


relativeLayout.addView(adView, adViewParams);


			adView.loadAd(adRequest);
            adView.setBackgroundColor(Color.BLACK);
            adView.setBackgroundColor(0);
            
            me = this;
            
            adView.setVisibility(View.VISIBLE);
            
            
            // Facebook
            uiHelper = new UiLifecycleHelper(this, null);
            uiHelper.onCreate(savedInstanceState);
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
	 
	 
	 // FB
	 
	 private UiLifecycleHelper uiHelper;
	 
	 @Override
	 protected void onResume() {
	     super.onResume();
	     uiHelper.onResume();
	 }

	 @Override
	 protected void onSaveInstanceState(Bundle outState) {
	     super.onSaveInstanceState(outState);
	     uiHelper.onSaveInstanceState(outState);
	 }

	 @Override
	 public void onPause() {
	     super.onPause();
	     uiHelper.onPause();
	 }

	 @Override
	 public void onDestroy() {
	     super.onDestroy();
	     uiHelper.onDestroy();
	 }
	 
	 @Override
	 protected void onActivityResult(int requestCode, int resultCode, Intent data) {
	     super.onActivityResult(requestCode, resultCode, data);

	     uiHelper.onActivityResult(requestCode, resultCode, data, new FacebookDialog.Callback() {
	         @Override
	         public void onError(FacebookDialog.PendingCall pendingCall, Exception error, Bundle data) {
	             Log.e("Activity", String.format("Error: %s", error.toString()));
	         }

	         @Override
	         public void onComplete(FacebookDialog.PendingCall pendingCall, Bundle data) {
	             Log.i("Activity", "Success!");
	         }
	     });
	 }
	 
	 private void publishFeedDialog(final String text) {
		 
		 Session session = Session.getActiveSession();
		 
		 if (session==null)
		 {
			 // start Facebook Login
			    Session.openActiveSession(me, true, new Session.StatusCallback() {

			      // callback when session changes state
			      @Override
			      public void call(Session session, SessionState state, Exception exception) {
			        if (session.isOpened()) {

			        	me.publishFeedDialog(text);
			        }
			      }
			    });
			    
			    return;
		 }

		 if (session.isOpened()==false)
		 {
			 Session.openActiveSession(me, true, new Session.StatusCallback() {

			      // callback when session changes state
			      @Override
			      public void call(Session session, SessionState state, Exception exception) {
			        if (session.isOpened()) {

			        	me.publishFeedDialog(text);
			        }
			      }
			    });
			 
			 return;
		 }
		 
		    if (session != null){
		    	
		    	 // Check for publish permissions    
		        List<String> permissions = session.getPermissions();
		        if (!permissions.contains("publish_actions")) {
//		            pendingPublishReauthorization = true;
		            Session.NewPermissionsRequest newPermissionsRequest = new Session
		                    .NewPermissionsRequest(me, "publish_actions");
		            session.requestNewPublishPermissions(newPermissionsRequest);
		        
		        
		            return;
		        }
		        
		        
		    	Bundle params = new Bundle();
			    params.putString("name", "Bunnies Forever");
			    params.putString("caption", "Check out my score");
			    params.putString("description", text);
			    params.putString("link", String.format("market://details?id=%s", me.getPackageName()));

			    WebDialog feedDialog = (
			        new WebDialog.FeedDialogBuilder(me,
			            Session.getActiveSession(),
			            params)).setOnCompleteListener
			        (new OnCompleteListener() {

			            @Override
			            public void onComplete(Bundle values,
			                FacebookException error) {

			                if (error == null) {
			                    // When the story is posted, echo the success
			                    // and the post Id.
			                    final String postId = values.getString("post_id");
			                    if (postId != null) {
			                        Toast.makeText(me,
			                            "Posted story, id: "+postId,
			                            Toast.LENGTH_SHORT).show();
			                    } else {
			                        // User clicked the Cancel button
			                        Toast.makeText(me.getApplicationContext(), 
			                            "Publish cancelled", 
			                            Toast.LENGTH_SHORT).show();
			                    }
			                } else if (error instanceof FacebookOperationCanceledException) {
			                    // User clicked the "x" button
			                    Toast.makeText(me.getApplicationContext(), 
			                        "Publish cancelled", 
			                        Toast.LENGTH_SHORT).show();
			                } else {
			                    // Generic, ex: network error
			                    Toast.makeText(me.getApplicationContext(), 
			                        "Error posting story", 
			                        Toast.LENGTH_SHORT).show();
			                }
			            }

			        })
			        .build();
			    feedDialog.show();		    	
		    }
		    
		}
	 
	 static void onShareFacebook(final String shareText)
	 {
		 me.runOnUiThread(new Runnable(){
		 @Override 
		 public void run(){
	         
			 if (FacebookDialog.canPresentShareDialog(me.getApplicationContext(), 
                     FacebookDialog.ShareDialogFeature.SHARE_DIALOG)) 
			 {
				 // Publish the post using the Share Dialog
				 FacebookDialog shareDialog = new FacebookDialog.ShareDialogBuilder(me)
				 .setLink(String.format("market://details?id=%s", me.getPackageName())).setDescription(shareText)
				 .build();
				 me.uiHelper.trackPendingDialogCall(shareDialog.present());
				 
			 } else {
				 me.publishFeedDialog(shareText);
			 }
		 }
		 });
	 }
	 
}
