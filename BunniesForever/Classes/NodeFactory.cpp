//
//  NodeFactory.cpp
//  NukeGun
//
//  Created by Kiyanov Eugene on 22/06/14.
//
//

#include "NodeFactory.h"
#include "cocos2d.h"
#include "JSONUtils.h"
#include "Profile.h"


using namespace cocos2d;

NodeFactory* NodeFactory::__instance;

NodeFactory* NodeFactory::getInstance()
{
    
    if (__instance==0)__instance=new NodeFactory();
    return __instance;
}


using namespace CSJson;
void NodeUtils::fillTransform(const CSJson::Value& root,Node* spr,Node* parent)
{
    {
        const CSJson::Value& size=root.get("size", CSJson::nullValue);
        if (size.isNull()==false)
        {
            float w=size.get(0u, 0).asFloat();
            float h=size.get(1u, 0).asFloat();
            
            spr->setContentSize(Size(w,h));
        }
    }
    {
        const CSJson::Value& pos=root.get("pos_in_pixels", CSJson::nullValue);
        if (pos.isNull()==false)
        {
            //                float scale=Director::getInstance()->getWinSize().width/1024;
            //          float ss =Director::getInstance()->getContentScaleFactor();
            
            //            log("ss:%f",ss);
            float x=pos.get(0u, 0).asFloat();//photoshop exports real pixels*scale;//Director::getInstance()->getContentScaleFactor();
            float y=pos.get(1, 0).asFloat();//photoshop exports real pixels*scale;//Director::getInstance()->getContentScaleFactor();
            spr->setPosition(x, y);
        }
    }
    
    
    {   //  need to do. pass parent node. and remake NodeFactory for third parameter
        const CSJson::Value& pos=root.get("pos_in_percents", CSJson::nullValue);
        if (pos.isNull()==false)
        {
            float x=0,y=0;
            if (pos.isArray())
            {
                x=pos[0u].asFloat();
                y=pos[1].asFloat();
            }
            if (pos.isObject())
            {
                x=pos.get("x", 0).asFloat();
                y=pos.get("y", 0).asFloat();
            }
            spr->setPosition(x, y);
        }
    }
    
    {
        if (parent)
        {
            const CSJson::Value& ref=root.get("pos_ref", CSJson::nullValue);
            if (ref.isNumeric())
            {
                Node* p=parent->getChildByTag(ref.asInt());
                if (p)
                {
                    spr->setPosition(Point(spr->getPositionX()+p->getPositionX(),
                                           spr->getPositionY()+p->getPositionY()));
                    
                    p->setVisible(!root.get("hide_ref", false).asBool());
                }
            }
            
        }
    }
    
    {
        const CSJson::Value& pos=root.get("scale", CSJson::nullValue);
        if (pos.isNull()==false)
        {
            float x=1,y=0;
            if (pos.isNumeric())
            {
                x=pos.asFloat();
            }
            else if (pos.isObject()){
                x=pos.get("x", 1).asFloat();
                y=pos.get("y", 1).asFloat();
            }else if (pos.isArray())
            {
                x=pos.get(0u, 1).asFloat();
                y=pos.get(1, 1).asFloat();
            }
            
            if (y==0) y=x;
            spr->setScaleX(x);
            spr->setScaleY(y);
        }
    }
    
    {
        const CSJson::Value& pos=root.get("anchor", CSJson::nullValue);
        if (pos.isNull()==false)
        {
            log ("%s %s", __FUNCTION__, StyledWriter().write(pos).c_str());
            float x=0,y=0;
            if (pos.isArray())
            {
                x=pos[0u].asFloat();
                y=pos[1].asFloat();
            }else
            {x=pos.get("x", 0).asFloat();
                y=pos.get("y", 0).asFloat();}
            spr->setAnchorPoint(Point(x,y));
        }
    }
    
    {
        const CSJson::Value& pos=root.get("rotation", 0);
        spr->setRotation(pos.asFloat());
    }
    
    const CSJson::Value& tagnode=root.get("tag", nullValue);
    if(tagnode.isNumeric())   spr->setTag(tagnode.asInt());
}
void downloadFile(std::string src, std::string dst);
void NodeUtils::iterateChilds(const CSJson::Value& root,Node* spr)
{
    const CSJson::Value& childs=root.get("childs", CSJson::objectValue);
    
    log("%s %s",__FUNCTION__, CSJson::StyledWriter().write(childs).c_str());
    
    if (childs.isArray())
    {
        for (int i=0;i<childs.size();++i)
        {log("%i of %i",i,childs.size());
            CSJson::Value v=childs[i];
            CSJson::Value::Members mm=v.getMemberNames();
            for(CSJson::Value::Members::iterator it=mm.begin();it!=mm.end();++it)
            {
                CSJson::Value vv=v.get(it->c_str(), CSJson::nullValue);
                if (strcmp(it->c_str(), "reference")==0 ||
                    strcmp(it->c_str(), "reference_local")==0)
                {
                    CSJson::Value newchilds;
                 //   if (PlatformParams::getInstance()->localResource() || strcmp(it->c_str(), "reference_local")==0){
                        newchilds=JSONUtils::JSONFromFile(vv.asCString());
              /*      }else{
                        std::string ssss=FileUtils::getInstance()->getSearchPaths()[0];//.append("upgrade_base2.json");
                        ssss.append(vv.asCString());
                        std::string url("http://avb.kiyanov.com/get_level.php?level=data/");
                        url.append(ssss);
                        char unchar[32];sprintf(unchar, "&sd=%i",rand());
                        url.append(unchar);
                        downloadFile(url,
                                     FileUtils::getInstance()->getWritablePath().append(vv.asCString()) );
                        
                        newchilds=JSONUtils::JSONFromFile(FileUtils::getInstance()->getWritablePath().append(vv.asCString()).c_str());
               
                    }
               */
                    CSJson::Value newroot;
                    newroot["childs"]=newchilds;
                    
                    log("%s %s",__FUNCTION__,CSJson::StyledWriter().write(newroot).c_str());
                    
                    
                    iterateChilds(newroot, spr);
                    continue;
                }
                
                log ("child: %s",FastWriter().write(vv).c_str());
                Node* n=NodeFactory::getInstance()->ObjectForKey(it->c_str(), vv);
                int z=vv.get("z",0).asInt();
                if (n)
                {
                    spr->addChild(n,z);
                    if (vv.get("pos_in_percents", nullValue).isNull()==false)
                    {
                        n->setPositionX(n->getPositionX()*spr->getContentSize().width);
                        n->setPositionY(n->getPositionY()*spr->getContentSize().height);
                    }
                }
            }
        }
    }else{
        CSJson::Value::Members mm=childs.getMemberNames();
        for(CSJson::Value::Members::iterator it=mm.begin();it!=mm.end();++it)
        {
            CSJson::Value v=childs.get(it->c_str(), CSJson::nullValue);
            Node* n=NodeFactory::getInstance()->ObjectForKey(it->c_str(), v);
            assert(n);
            /*     log("adding %x (%f %f %f %f %f %f %f %f) to %x",n,
             n->getPositionX(),n->getPositionY(),n->getContentSize().width,n->getContentSize().height,
             n->getAnchorPoint().x,n->getAnchorPoint().y,
             n->getScaleX(),n->getScaleY(),
             spr);
             */
            int z=v.get("z",0).asInt();
            if (n) spr->addChild(n,z);
        }
    }
}

Node* makeSprite(const CSJson::Value& root, Node* parent)
{
    const CSJson::Value&visual=root.get("visual",nullValue);
    if (visual.isNull())return 0;
    std::string prefix="";
    if (visual.isString())
    {
        prefix=visual.asString();
    }else{
        prefix=visual.get("prefix", "").asString();
        std::string modifier=visual.get("modifier", "").asString();
        int modLevel=0;
        if (modifier.length()>0)
        modLevel=Profile::getInstance()->intForKey(modifier.c_str());
        
        char name[256];
        sprintf(name, prefix.c_str(), modLevel);
        
        prefix=name;
    }
    const CSJson::Value& op=root.get("opacity",nullValue);
    
    
    Sprite*spr=Sprite::create(prefix.c_str());
    if (spr==0){
        SpriteFrame*fr=SpriteFrameCache::getInstance()->getSpriteFrameByName(prefix.c_str()); if (fr)spr=Sprite::createWithSpriteFrame(fr); else log("searching plist got nothing :(");}
    
    if (spr==0)
    {
        
        log("%s \"%s\" failed to load",__FUNCTION__,prefix.c_str());
        
        return NULL;
        assert(spr);
    }
    
    if (op.isNumeric())
    {
        float opVal=op.asFloat()*255;
        spr->setOpacity(opVal);
    }
    
    //   log("%s %s to %x",__FUNCTION__,name,spr);
    NodeUtils::fillTransform(root,spr);
    NodeUtils::iterateChilds(root,spr);
    
    log("%s: %s at %f %f. anchor %f %f. scale: %f %f. rotation: %f size:%f %f",__FUNCTION__,
        prefix.c_str(),spr->getPositionX(),spr->getPositionY(),
        spr->getAnchorPoint().x,spr->getAnchorPoint().y,spr->getScaleX(),
        spr->getScaleY(),spr->getRotation(),
        spr->getContentSize().width,spr->getContentSize().height);
    return spr;
}

Node* makeMenuItemSprite(const CSJson::Value& root, Node* parent)
{
    Sprite*normal=(Sprite*)makeSprite(root.get("normal", nullValue),parent);
    Sprite*on=(Sprite*)makeSprite(root.get("on", nullValue),parent);
    
    log("%s %x %x",__FUNCTION__,normal,on);
    MenuItemSprite*item=MenuItemSprite::create(normal, on);
    NodeUtils::fillTransform(root, item,parent);
    NodeUtils::iterateChilds(root, item);
    
    return item;
}
/*
Node* makeMenuItemTab(const CSJson::Value& root, Node* parent)
{
    Sprite*normal=(Sprite*)makeSprite(root.get("normal", nullValue),parent);
    Sprite*on=(Sprite*)makeSprite(root.get("on", nullValue),parent);
    
    log("%s %x %x",__FUNCTION__,normal,on);
    MenuItemTab*item=new MenuItemTab();
    item->initWithNormalSprite(normal, on,0, (const ccMenuCallback&)nullptr);
    NodeUtils::fillTransform(root, item);
    item->autorelease();
    return item;
}
*/
Node* makeLabelBMFont(const CSJson::Value& root, Node* parent)
{
    LabelBMFont*item=LabelBMFont::create(root.get("content", "").asCString(),
                                         root.get("font","").asCString(),root.get("width",0).asInt(),(TextHAlignment)root.get("alignment", 0).asInt());
    NodeUtils::fillTransform(root, item);
    return item;
}

Node* makelabelTTF(const CSJson::Value& root, Node* parent)
{
    LabelTTF*item=LabelTTF::create(root.get("content","").asCString(), root.get("font","Arial").asCString(),
                                   root.get("fontsize",12).asInt(),Size(root.get("width",0).asInt(),
                                                                        root.get("height",0).asInt()),
                                   (TextHAlignment)root.get("alignment", 0).asInt()
                                   );
    
    NodeUtils::fillTransform(root, item);
    return item;
}

Node* makeNode(const CSJson::Value& root, Node* parent)
{
    Node* n = Node::create();
    NodeUtils::fillTransform(root, n);
    NodeUtils::iterateChilds(root, n);
    return n;
}

namespace  {
    const static bool regSprite=NodeFactory::getInstance()->RegisterConstructorForKey("sprite",makeSprite);
    const static bool regMenuItemSprite=NodeFactory::getInstance()->RegisterConstructorForKey("menuitemsprite", makeMenuItemSprite);
//    const static bool regMenuItemTab=NodeFactory::getInstance()->RegisterConstructorForKey("menuitemtab", makeMenuItemTab);
    const static bool regLabelbmfont=NodeFactory::getInstance()->RegisterConstructorForKey("labelbmfont", makeLabelBMFont);
    const static bool regLabelttffont=NodeFactory::getInstance()->RegisterConstructorForKey("labelttf", makelabelTTF);
    const static bool regNode=NodeFactory::getInstance()->RegisterConstructorForKey("node", makeNode);
}