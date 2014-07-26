#include "AndroidJni.h"
#include "platform/android/jni/JniHelper.h" //vem do projeto principal - pasta cocos2dx

#include <jni.h>

using namespace cocos2d;

extern "C"
{

	void rateus()
	{
		JniMethodInfo t;
				if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.cpp/AppActivity"
								,"rateus"
								,"()V"))
				{
					t.env->CallStaticVoidMethod(t.classID,t.methodID);
				}
	}

	void significantEvent()
	{
		JniMethodInfo t;
				if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.cpp/AppActivity"
								,"significantEvent"
								,"()V"))
				{
					t.env->CallStaticVoidMethod(t.classID,t.methodID);
				}
	}

    void hideAdmobJNI(){
    	JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.cpp/AppActivity"
						,"hideAdmobJNI"
						,"()V"))
		{
			t.env->CallStaticVoidMethod(t.classID,t.methodID);
		}
    }

    void showAdmobJNI(){
        	JniMethodInfo t;
    		if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.cpp/AppActivity"
    						,"showAdmobJNI"
    						,"()V"))
    		{
    			t.env->CallStaticVoidMethod(t.classID,t.methodID);
    		}
        }

    void setAdmobVisibleJNI(int number){
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.cpp/AppActivity"
						,"setAdmobVisibleJNI"
						,"(I)V"))
		{
			t.env->CallStaticVoidMethod(t.classID,t.methodID,number);
		}
    }
    void setVisibleAdmobJNI(bool visible){
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.cpp/AppActivity"
						,"setVisibleAdmobJNI"
						,"(Z)V"))
		{
			t.env->CallStaticVoidMethod(t.classID,t.methodID,visible);
		}
    }
    void setAdmobVisibilityJNI(const char* name){
        JniMethodInfo t;
        if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.cpp/AppActivity"
                        ,"setAdmobVisibilityJNI"
                        ,"(Ljava/lang/String;)V"))
        {
            jstring StringArg1 = t.env->NewStringUTF(name);
            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
        }
    }

    void shareFBText(const char* name)
    {
    	JniMethodInfo t;
    	        if (JniHelper::getStaticMethodInfo(t, "org.cocos2dx.cpp/AppActivity"
    	                        ,"onShareFacebook"
    	                        ,"(Ljava/lang/String;)V"))
    	        {
    	            jstring StringArg1 = t.env->NewStringUTF(name);
    	            t.env->CallStaticVoidMethod(t.classID,t.methodID, StringArg1);
    	        }
    }
}
