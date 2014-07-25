//
//  Profile.h
//  AvB
//
//  Created by Kiyanov Eugene on 03/12/13.
//
//

#ifndef __AvB__Profile__
#define __AvB__Profile__

#include <iostream>
#include "cocos2d.h"
#include "Json/lib_json/json_lib.h"
//#include "jsonmodels.h"
using namespace CSJson;



class Profile{
    CSJson::Value       __keys;
public:
    Profile();
    static Profile*getInstance();
    std::string stringForKey(const char*key);
    int intForKey(const char* key);
    float floatForKey(const char*key);
    void setIntForKey(int, const char* key);
    void setFloatForKey(float, const char* key);
    void setStringForKey(cocos2d::String*, const char* key);
    const CSJson::Value&nodeForKey(const char*key)const;
    CSJson::Value&nodeForKey(const char*key);
    void restore();
    void store();
    
    bool validateKeys(const CSJson::Value& val);
//    bool validateRequirements(const std::vector<Requirements>& req,const char* masterkey=0)const;
};

#endif /* defined(__AvB__Profile__) */
