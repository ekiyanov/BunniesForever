//
//  Factory.cpp
//  NukeGun
//
//  Created by Kiyanov Eugene on 1/21/13.
//
//

#include "Factory.h"
using namespace std;
static Factory * __sharedFactory=NULL;


Factory * Factory::sharedInstance()
{
    if (__sharedFactory==NULL) __sharedFactory=new Factory();
    
    return __sharedFactory;
}


CCNode* Factory::productById(const std::string& key,CCDictionary* node)
{
   
    std::map<std::string, SEL_FactoryCreator*>::iterator   it = _factoryReception.find(key);
    
    if (it ==_factoryReception.end()) return NULL;
    
    SEL_FactoryCreator* func = it->second;
    CCNode*  newNode = (*func)(node);
    
    return newNode;
}


bool Factory::registerFabric(const char* key, SEL_FactoryCreator funcPtr)
{
    map<std::string, SEL_FactoryCreator*>::iterator it = _factoryReception.find(key);
    if (it==_factoryReception.end())
    { 
        pair<std::string, SEL_FactoryCreator*> pp  (string(key),funcPtr);
        _factoryReception.insert(pp);
        
        return true;
    }
    
    return false;
}