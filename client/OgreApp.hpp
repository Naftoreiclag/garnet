#ifndef GRT_OGREAPP_HPP
#define GRT_OGREAPP_HPP

#include "OgreRoot.h"
#include "OgreCamera.h"
#include "OgreSceneManager.h"
#include "OgreRenderWindow.h"

namespace grt
{

class OgreApp {
public:
    OgreApp();
    virtual ~OgreApp();
    void run();
private:
    Ogre::Root* m_ogreRoot;
    Ogre::Camera* m_cam;
    Ogre::SceneManager* m_smgr;
    Ogre::RenderWindow* m_window;

};

}

#endif // GRT_OGREAPP_HPP
