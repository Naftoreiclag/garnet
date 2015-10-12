#ifndef GRT_DOLLOP_HPP
#define GRT_DOLLOP_HPP

#include <stdint.h>

#include "OgreManualObject.h"
#include "OgreMeshManager.h"

#include "Nugget.hpp"

namespace grt {

class Dollop {
public:
    static const uint32_t sSize = 60;
    static const uint32_t sVolume = 216000;
public:
    Nugget::Id_t mStaticData[sVolume];
private:
    Ogre::MeshPtr mMeshPtr;
public:
    Dollop();
    ~Dollop();
    
    static inline uint32_t toIndex(uint32_t x, uint32_t y, uint32_t z);
    
    void updateMesh();
    

};

}

#endif // GRT_DOLLOP_HPP
