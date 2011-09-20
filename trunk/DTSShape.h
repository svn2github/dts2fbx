/*
 * dts2fbx
 * Copyright (c) 2011 Charlie Duhor. All rights reserved.
 *
 * @DTS2FBX_LICENSE_HEADER_START@
 * 
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA, or see the FSF site: http://www.fsf.org.
 * 
 * @DTS2FBX_LICENSE_HEADER_START@
 */

#ifndef DTSConverter_DTSShape_h
#define DTSConverter_DTSShape_h

#include "DTSBase.h"

#include <string>

class DTSNode
{
public:
    int name;
    int parent;
    int firstObject;
    int child;
    int sibling;
};

class DTSObject
{
public:
    int name;
    int numMeshes;
    int firstMesh;
    int node;
    int sibling;
    int firstDecal;
};

class DTSDecal
{
public:
    int name;
    int numMeshes;
    int firstMesh;
    int object;
    int sibling;
};

class DTSIFLMaterial
{
public:
    int name;
    int slot;
    int firstFrame;
    int time;
    int numFrames;
};

class DTSSubshape
{
public:
    int firstNode;
    int firstObject;
    int firstDecal;
    int numNodes;
    int numObjects;
    int numDecals;
    int firstTranslucent;
};

class DTSObjectState
{
public:
    float vis;
    int   frame;
    int   matFrame;
};

class DTSDetailLevel
{
public:
    int   name;
    int   subshape;
    int   objectDetail;
    float size;
    float avgError;
    float maxError;
    int   polyCount;
};

class DTSTrigger
{
public:
    int   state;
    float pos;
};

class DTSDecalState
{
public:
    int frame;
};

class DTSPrimitive
{
public:
    short firstElement;
    short numElements;
    int   type;
};

class DTSCluster
{
public:
    int     startPrimitive;
    int     endPrimitive;
    Point   normal;
    float   k;
    int     frontCluster;
    int     backCluster;
};

class DTSMesh
{
public:
    enum
    {
        T_Standard = 0,
        T_Skin     = 1,
        T_Decal    = 2,
        T_Sorted   = 3,
        T_Null     = 4
    };
    
public:
    int   type;
    int   numFrames;
    int   matFrames;
    int   parent;
    Box   bounds;
    Point center;
    float radius;
    
    std::vector<Point>         verts;
    std::vector<Point2D>       tverts;
    std::vector<Point>         normals;
    std::vector<unsigned char> enormals;
    
    std::vector<DTSPrimitive>   primitives;
    std::vector<unsigned short> indices;
    std::vector<unsigned short> mindices;
    
    int vertsPerFrame;
    int flags;

    // Skin data
    std::vector<int>          vindex;
    std::vector<int>          vbone;
    std::vector<float>        vweight;
    std::vector<int>          nodeIndex;
    std::vector<Matrix<4,4> > nodeTransform;

    // Decal data
    std::vector<DTSCluster> clusters;
    std::vector<int>        startCluster;
    std::vector<int>        firstVerts;
    std::vector<int>        numVerts;
    std::vector<int>        firstTVerts;
};

class DTSSequence
{
public:
    std::string name;
    int   nameIndex;
    int   flags;
    int   numKeyFrames;
    float duration;
    int   priority;
    int   firstGroundFrame;
    int   numGroundFrames;
    int   baseRotation;
    int   baseTranslation;
    int   baseScale;
    int   baseObjectState;
    int   baseDecalState;
    int   firstTrigger;
    int   numTriggers;
    float toolBegin;

    struct matters_array {
        std::vector<bool> rotation;
        std::vector<bool> translation;
        std::vector<bool> scale;
        std::vector<bool> decal;
        std::vector<bool> ifl;
        std::vector<bool> vis;
        std::vector<bool> frame;
        std::vector<bool> matframe;
    } matters;
};

class DTSMaterial
{
public:
    std::string name;
    int         flags;
    int         reflectance;
    int         bump;
    int         detail;
    int         detailScale;
    int         reflection;
};

class DTSResolver
{
public:
    std::vector<std::string> paths;
    
public:
    void addPathContaining(const std::string&);
    
    std::string resolve(const std::string&) const;
};

class DTSShape : public DTSBase
{
public:
    int numNodes;
    int numObjects;
    int numDecals;
    int numSubshapes;
    int numIFLmaterials;
    int numNodeRotations;
    int numNodeTranslations;
    int numNodeScalesUniform;
    int numNodeScalesAligned;
    int numNodeScalesArbitrary;
    int numGroundFrames;
    int numObjectStates;
    int numDecalStates;
    int numTriggers;
    int numDetailLevels;
    int numMeshes;
    int numSkins;
    int numNames;
    
    float smallestSize;
    int   smallestDetailLevel;
    
    float radius;
    float tubeRadius;
    Point center;
    Box   bounds;
    
    std::vector<DTSNode>        nodes;
    std::vector<DTSObject>      objects;
    std::vector<DTSDecal>       decals;
    std::vector<DTSIFLMaterial> IFLmaterials;
    std::vector<DTSSubshape>    subshapes;

    std::vector<Quaternion>   nodeDefRotations;
    std::vector<Point>        nodeDefTranslations;
    std::vector<Quaternion>   nodeRotations;
    std::vector<Point>        nodeTranslations;
    std::vector<float>        nodeScalesUniform;
    std::vector<Point>        nodeScalesAligned;
    std::vector<Point>        nodeScalesArbitrary;
    std::vector<Quaternion>   nodeScaleRotsArbitrary;
    std::vector<Quaternion>   groundRotations;
    std::vector<Point>        groundTranslations;
    
    std::vector<DTSObjectState> objectStates;
    std::vector<DTSDecalState>  decalStates;
    std::vector<DTSDetailLevel> detailLevels;
    std::vector<DTSTrigger>     triggers;
    std::vector<DTSMesh>        meshes;
    std::vector<DTSSequence>    sequences;
    std::vector<std::string>    names;
    std::vector<DTSMaterial>    materials;
    
public:
    DTSShape();

    void loadShapeFile(FILE*);
    void loadSequenceFile(FILE*, const DTSShape* baseShape);
    void loadSequences(FILE*, bool dsq);
    
    std::string nodeNameAtIndex  (int) const;
    std::string objectNameAtIndex(int) const;
    std::string decalNameAtIndex (int) const;
    
    int findNode(const char* nodeName) const;

    bool nodeIsLinkedToObject(int node) const;
};

#endif
