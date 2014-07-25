LOCAL_PATH := $(call my-dir)
CLASSES:=../../Classes

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp


LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
       	           ../../Classes/Json/lib_json/json_reader.cpp\
					../../Classes/Json/lib_json/json_value.cpp \
					../../Classes/Json/lib_json/json_writer.cpp \
					$(CLASSES)/Explode.cpp \
					$(CLASSES)/Factory.cpp \
                    /Users/EKiyanov/Documents/BunniesForever/BunniesForever/Classes/IngameScene.cpp \
/Users/EKiyanov/Documents/BunniesForever/BunniesForever/Classes/RunRow.cpp \
/Users/EKiyanov/Documents/BunniesForever/BunniesForever/Classes/Character.cpp \
/Users/EKiyanov/Documents/BunniesForever/BunniesForever/Classes/RowObject.cpp \
/Users/EKiyanov/Documents/BunniesForever/BunniesForever/Classes/ObjectFactory.cpp \
/Users/EKiyanov/Documents/BunniesForever/BunniesForever/Classes/MenuPause.cpp \
/Users/EKiyanov/Documents/BunniesForever/BunniesForever/Classes/MenuGameover.cpp \
/Users/EKiyanov/Documents/BunniesForever/BunniesForever/Classes/JSONUtils.cpp \
/Users/EKiyanov/Documents/BunniesForever/BunniesForever/Classes/Profile.cpp \
/Users/EKiyanov/Documents/BunniesForever/BunniesForever/Classes/NodeFactory.cpp \
/Users/EKiyanov/Documents/BunniesForever/BunniesForever/Classes/PlatformParams.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes\
                    $(LOCAL_PATH)/../../cocos2d/ \
                    $(LOCAL_PATH)/../../cocos2d/extensions \
					$(LOCAL_PATH)/../../cocos2d/cocos \
					$(LOCAL_PATH)/../../cocos2d/cocos/physics \
					$(LOCAL_PATH)/../../cocos2d/cocos/base \
					$(LOCAL_PATH)/../../cocos2d/cocos/math/kazmath \
					$(LOCAL_PATH)/../../cocos2d/cocos/2d \
					$(LOCAL_PATH)/../../cocos2d/cocos/ui \
					$(LOCAL_PATH)/../../cocos2d/cocos/network \
					$(LOCAL_PATH)/../../cocos2d/cocos/audio/include \
					$(LOCAL_PATH)/../../cocos2d/cocos/editor-support \
					$(LOCAL_PATH)/../../cocos2d/extensions \
					$(LOCAL_PATH)/../../cocos2d/external \
					$(LOCAL_PATH)/../../cocos2d/external\chipmunk\include\chipmunk

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,editor-support/cocostudio)
$(call import-module,audio/android)
$(call import-module,Box2D)
$(call import-module,network)
