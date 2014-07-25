//
//  JSONUtils.h
//  AvB
//
//  Created by Kiyanov Eugene on 15/01/14.
//
//

#ifndef __AvB__JSONUtils__
#define __AvB__JSONUtils__

#include <iostream>
#include "Json/lib_json/json_lib.h"
using namespace CSJson;


namespace JSONUtils
{
    const CSJson::Value JSONFromFile(const char*,bool checkwebfirst=false,bool fromshared=false);
    template <class T> bool fetchArray(std::vector<T>&outVector,const char* file){CSJson::Value root=JSONFromFile(file); if (root.isArray()==false) return false;for (int i=0;i<root.size();++i){outVector.push_back(T());T&lastone=outVector.back(); if (lastone.loadFromJSON(root[i])==false) outVector.pop_back();}return true;}
    template <class T> bool fetchArray(std::vector<T>&outVector,const CSJson::Value& root)    {   if (root.isArray()==false) return false;        for (int i=0;i<root.size();++i)        {            outVector.push_back(T());            T&lastone=outVector.back();            if (lastone.loadFromJSON(root[i])==false)            outVector.pop_back();        }        return true;    }
    inline bool fetchArrayString(std::vector<std::string>&outVector,const CSJson::Value&node){if (node.isArray()==false)return false;for (int i=0;i<node.size();++i)if (node[i].isString())outVector.push_back(node[i].asString());return true;}
};

#endif /* defined(__AvB__JSONUtils__) */
