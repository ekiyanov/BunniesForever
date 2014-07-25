//
//  NodeFactory.h
//  NukeGun
//
//  Created by Kiyanov Eugene on 22/06/14.
//
//

#ifndef __NukeGun__NodeFactory__
#define __NukeGun__NodeFactory__

#include <iostream>

#include "StringFactory.h"
#include "cocos2d.h"
using namespace cocos2d;

class NodeFactory
{
protected:
    static NodeFactory* __instance;
    
    typedef Node* (*funcConstructor)(const CSJson::Value& value, cocos2d::Node*);
    
    std::map<std::string, funcConstructor> _factories;
public:
    
    Node* ObjectForKey(const char* key, const CSJson::Value value, Node* parent=0)
    {
        typename std::map<std::string, funcConstructor>::iterator i=_factories.find(key);
        if (i==_factories.end())return 0;return i->second(value,parent);
    }
    bool RegisterConstructorForKey(const char* key, funcConstructor ctr)
    {
        typename std::map<std::string, funcConstructor>::iterator i=_factories.find(key);
        if (i==_factories.end()==false)return false;_factories[key]=ctr;
        return true;
    }
    
    static NodeFactory* getInstance();
};



class NodeUtils
{
public:
    static void fillTransform(const CSJson::Value& root, Node* spr, Node* parent=0);
    static void iterateChilds(const CSJson::Value& root, Node* spr);
};


#endif /* defined(__NukeGun__NodeFactory__) */
