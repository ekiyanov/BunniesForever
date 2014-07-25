//
//  StringFactory.h
//  AvB
//
//  Created by Kiyanov Eugene on 25/11/13.
//
//

#ifndef AvB_StringFactory_h
#define AvB_StringFactory_h

#include "Json/lib_json/json_lib.h"
#include <map>
#include <functional>

#define FACTORY_GET_INSTANCE(a) template<>a*a::__instance=0;template<> a* a::getInstance(){if(__instance==0)__instance=new a();return __instance;}

template <class T, class T2>
class StringFactory
{
protected:
    static StringFactory* __instance;
    std::map<std::string, std::function<T (T2)> > _factories;
public:
    
    T ObjectForKey(const char* key, T2 value)
    {
        auto i=_factories.find(key);
        if (i==_factories.end())return 0;return i->second(value);
    }
    bool RegisterConstructorForKey(const char* key, std::function<T (T2)> ctr)
    {
        auto i=_factories.find(key);
        if (i==_factories.end()==false)return false;_factories[key]=ctr;
        return true;
    }

    static StringFactory* getInstance();
};

#endif
