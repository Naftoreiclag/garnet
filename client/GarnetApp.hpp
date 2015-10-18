#ifndef GRT_GARNETAPP_HPP
#define GRT_GARNETAPP_HPP

#include "OgreRoot.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"

namespace grt
{

class GarnetApp
{
public:
    
    static GarnetApp& getSingleton();
public:
    
    Ogre::Root* mOgreRoot;
    Ogre::Camera* mCam;
    Ogre::SceneManager* mSmgr;
    
    void initialize(Ogre::Root* mOgreRoot);
    void onClose();
    void onTick();
    
    GarnetApp();
    ~GarnetApp();
};

}

#endif // GRT_GARNETAPP_HPP
