#include "Dollop.hpp"

#include <stdint.h>
#include <iostream>

#include "OgreApp.hpp"

namespace grt
{

Dollop::Dollop() {
    for(uint32_t i = 0; i < sVolume; ++ i) {
        mStaticData[i] = 200;
    }
}

Dollop::~Dollop()
{
}

void Dollop::updateMesh() {
    Ogre::SceneManager* smgr = OgreApp::getSingleton().mSmgr;
    Ogre::ManualObject* man = smgr->createManualObject("manual obj");
    
    man->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
    
    man->position(100, 100, 100);
    man->position(-100, -100, -100);
    man->end();
    
    smgr->getRootSceneNode()->attachObject(man);
    
    
    /*
    mMeshPtr = Ogre::MeshManager::getSingleton().createManual("Something", "Or another");
    
    Ogre::SubMesh* sub = mMeshPtr->createSubMesh();
    
    // Worst possible rendering method
    
    uint32_t nVerts = 0;
    uint32_t nTris = 0;
    for(uint32_t x = 0; x < sSize; ++ x) {
        for(uint32_t y = 0; y < sSize; ++ y) {
            for(uint32_t z = 0; z < sSize; ++ z) {
                Nugget::Id_t id = mStaticData[toIndex(x, y, z)];
                
                if(id > 200) {
                    nVerts += 24;
                    nTris += 12;
                }
            }
        }
    }
    
    float verts[nVerts];
    
    uint32_t iVerts = 0;
    for(uint32_t x = 0; x < sSize; ++ x) {
        for(uint32_t y = 0; y < sSize; ++ y) {
            for(uint32_t z = 0; z < sSize; ++ z) {
                Nugget::Id_t id = mStaticData[toIndex(x, y, z)];
                
                if(id > 200) {
                    
                }
            }
        }
    }
    
    
    Ogre::RenderSystem* rendSys = OgreApp::getSingleton().m_ogreRoot->getRenderSystem();
    */
    
    
}

inline uint32_t Dollop::toIndex(uint32_t x, uint32_t y, uint32_t z) {
    return x + (y * sSize) + (z * sSize * sSize);
}


}

