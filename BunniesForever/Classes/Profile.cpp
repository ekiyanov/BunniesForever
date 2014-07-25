//
//  Profile.cpp
//  AvB
//
//  Created by Kiyanov Eugene on 03/12/13.
//
//

#include "Profile.h"

 static Profile*__profile=0;
   void Profile::setIntForKey(int v, const char *key){__keys[key]=v;}
   void Profile::setFloatForKey(float v, const char *key){__keys[key]=v;}
    int Profile::intForKey(const char *key){return __keys.get(key,0).asInt();}
std::string Profile::stringForKey(const char *key){return __keys.get(key, "").asString();}
  float Profile::floatForKey(const char *key){return __keys.get(key, 0).asFloat();}
        Profile*Profile::getInstance(){if(__profile==0)__profile=new Profile();return __profile;}
   void Profile::setStringForKey(cocos2d::String *s, const char *key){__keys[key]=s->getCString();}
        Profile::Profile(){restore();}
CSJson::Value& Profile::nodeForKey(const char *key){return __keys[key];}
const CSJson::Value& Profile::nodeForKey(const char *key)const{return __keys[key];}
   void Profile::restore(){
    std::string path=cocos2d::FileUtils::getInstance()->getWritablePath()+"profile.json";
    ssize_t psize;
    unsigned char* pdata=cocos2d::FileUtils::getInstance()->getFileData(path.c_str(),
                                                                        "rb",&psize);
       if (pdata==0){pdata=cocos2d::FileUtils::getInstance()->getFileData("start_profile.json","rb",&psize);}
       
       
       printf("profile::\n\n%s\n\n",(const char*)pdata);
       
       
    bool r=Reader().parse((const char*)pdata, (const char*)pdata+psize,__keys);
       
       printf("parsed:%s\n\n",r?"dA":"HET");
    delete[]pdata;
    if (!r)__keys=CSJson::Value(objectValue);
   
       int c=__keys.get("item_potion_0", -1).asInt();
       int cc2=intForKey("item_potion_0");
       
       printf("%i vs %i\n\n",c,cc2);
   }
void Profile::store(){
    std::string  path=cocos2d::FileUtils::getInstance()->getWritablePath()+"profile.json";
    std::string  content=FastWriter().write(__keys);
    FILE* f=fopen(path.c_str(),"wb");
    if(f){ fwrite(content.c_str(), content.length(), 1, f); fclose(f);}}
bool Profile::validateKeys(const CSJson::Value &val){
    for (int i=0;i<val.size();++i)
    {
        std::string key;
        int minval=1;
        if (val[i].isString()) key=val[i].asString();
        if (val[i].isObject()) {key=(val[i]).getMemberNames().front(); minval=(val[i])[key].asInt();}
        
        const CSJson::Value& v=__keys.get(key, nullValue);
        if (v.isNull()||(v.isNumeric()&&v.asInt()<minval)) return false;
    }
    return true;}
#if 0
bool Profile::validateRequirements(const std::vector<Requirements> &req,const char* masterkey)const{
    if (masterkey)
    {
        const CSJson::Value& unlocked=__keys["unlocked"].get(masterkey, nullValue);
        if (unlocked.isNumeric() && unlocked.asInt()==1) return true;
    }
    
    for (int i=0;i<req.size();++i)
    {
        const Requirements&r=req[i];
        const CSJson::Value& k=__keys.get(r._key.c_str(),nullValue);
        if (k.isNull() || (k.isNumeric()&&k.asInt()<r._level))return false;
    }
    return true;}
#endif