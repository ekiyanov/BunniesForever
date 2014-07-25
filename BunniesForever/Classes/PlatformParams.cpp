//
//  PlatformParams.cpp
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#include "PlatformParams.h"
#include "JSONUtils.h"

class PlatformParams
{
public:
    
    CSJson::Value root;
    static PlatformParams* getInstance();
    
    bool init();
};

static PlatformParams* ppinstance=0;

PlatformParams* PlatformParams::getInstance()
{
    if (ppinstance==0)
    {
        ppinstance=new PlatformParams();
        ppinstance->init();
    }
    
    return ppinstance;
}

bool PlatformParams::init()
{
    root = JSONUtils::JSONFromFile("settings.json");

    return true;
}

int PPIntForKey(const char* key){
    return PlatformParams::getInstance()->root.get(key, 0).asInt();
}