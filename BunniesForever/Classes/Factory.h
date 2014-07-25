//
//  Factory.h
//  NukeGun
//
//  Created by Kiyanov Eugene on 1/21/13.
//
//

#ifndef __NukeGun__Factory__
#define __NukeGun__Factory__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;
typedef Node*(SEL_FactoryCreator)(Dictionary*);
class Factory
{
    map<string,SEL_FactoryCreator*> _factoryReception;
public:
    static Factory* sharedInstance();
    Node* productById(const std::string& key,Dictionary* dict);
    bool registerFabric(const char* key,SEL_FactoryCreator);
};
#endif /* defined(__NukeGun__Factory__) */
