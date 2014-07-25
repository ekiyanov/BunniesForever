//
//  JSONUtils.cpp
//  AvB
//
//  Created by Kiyanov Eugene on 15/01/14.
//
//

#include "JSONUtils.h"
#include "cocos2d.h"
//#include "PlatformParams.h"
void downloadFile(std::string src,std::string dst);
namespace JSONUtils
{
    const CSJson::Value JSONFromFile(const char* fname,bool checkwebfirst,bool fromshared)
    {
        /*
        if (checkwebfirst && fname && fname[0]!='/')
        {
            if (!PlatformParams::getInstance()->localResource())
            {
                if (!fromshared)
                    downloadFile(std::string("http://avb.kiyanov.com/get_level.php?level=data/").append(FileUtils::getInstance()->getSearchPaths().front())
                                 .append(fname),FileUtils::getInstance()->getWritablePath().append(fname));
                else
                    downloadFile(std::string("http://avb.kiyanov.com/get_level.php?level=data/shared/")
                                 .append(fname),FileUtils::getInstance()->getWritablePath().append(fname));
                
                    CSJson::Value val=JSONUtils::JSONFromFile(FileUtils::getInstance()->getWritablePath().append(fname).c_str());
                    return val;
            }
        }
        */
        cocos2d::log("%s: %s",__FUNCTION__,fname);
        unsigned char * data=0;
        ssize_t psize=0;
        
        
        data=cocos2d::FileUtils::getInstance()->getFileData(fname, "rb", &psize  );
        if (!data) return CSJson::Value();
        
        
        CSJson::Value ff;
        bool parsed=Reader().parse((const char*)data,(const char*)data+psize, ff);
        
        delete[] data;
        if (!parsed)
        {
            cocos2d::log("%s:%s FAILED",__FUNCTION__ ,fname);
            return CSJson::Value();
        }
        
#ifdef COCOS2D_DEBUG
        cocos2d::log("%s:done:\n%s\n\n",__FUNCTION__,CSJson::StyledWriter().write(ff).c_str());
#endif
        return ff;
    }
}