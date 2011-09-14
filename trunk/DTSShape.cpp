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

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <vector>
#include <sys/stat.h>

#include "DTSTypes.h"
#include "DTSBase.h"
#include "DTSShape.h"

DTSShape::DTSShape() :
    numNodes              (0),
    numObjects            (0),
    numDecals             (0),
    numSubshapes          (0),
    numIFLmaterials       (0),
    numNodeRotations      (0),
    numNodeTranslations   (0),
    numNodeScalesUniform  (0),
    numNodeScalesAligned  (0),
    numNodeScalesArbitrary(0),
    numGroundFrames       (0),
    numObjectStates       (0),
    numDecalStates        (0),
    numTriggers           (0),
    numDetailLevels       (0),
    numMeshes             (0),
    numSkins              (0),
    numNames              (0),

    smallestSize       (0),
    smallestDetailLevel(0),

    radius    (0),
    tubeRadius(0)
{
}

void DTSShape::loadShapeFile(FILE* file)
{
    DTSBase::load(file);
    Read(numNodes);
    Read(numObjects);
    Read(numDecals);
    Read(numSubshapes);
    Read(numIFLmaterials);
    
    if (dtsVersion < 22)
    {
        Read(numNodeRotations);
        numNodeRotations      -= numNodes;
        numNodeTranslations    = numNodeRotations;
        numNodeScalesUniform   = 0;
        numNodeScalesAligned   = 0;
        numNodeScalesArbitrary = 0;
        numGroundFrames        = 0;
    }
    else
    {
        Read(numNodeRotations) ;
        Read(numNodeTranslations);
        Read(numNodeScalesUniform);
        Read(numNodeScalesAligned);
        Read(numNodeScalesArbitrary);
        
        if (dtsVersion > 23)
        {
            Read(numGroundFrames);
        }
    }

    Read(numObjectStates);
    Read(numDecalStates);
    Read(numTriggers);
    Read(numDetailLevels);
    Read(numMeshes);
    
    if (dtsVersion < 23)
        Read(numSkins);
    else
        numSkins = 0;
    
    Read(numNames);
    
    int smallestSizeInt;
    Read(smallestSizeInt);
    Read(smallestDetailLevel);
    smallestSize = (float)smallestSizeInt ;
    
    ReadCheck(0);
    
    // Bounds
    Read(radius);
    Read(tubeRadius);
    Read(center);
    Read(bounds);
    
    ReadCheck(1);
    
    // Nodes
    
    nodes.resize(numNodes);
    Read(nodes);
    ReadCheck(2);
    
    // Objects 
    
    objects.resize(numObjects);
    Read(objects);
    ReadCheck(3);
    
    // Decals
    
    decals.resize(numDecals);
    Read(decals);
    ReadCheck(4);
    
    // IFL Materials
    
    IFLmaterials.resize(numIFLmaterials);
    Read(IFLmaterials);
    ReadCheck(5);
    
    // Subshapes
    
    subshapes.resize(numSubshapes) ;
    std::vector<DTSSubshape>::iterator shape ;
    for (shape = subshapes.begin() ; shape != subshapes.end() ; shape++)
        Read(shape->firstNode);
    for (shape = subshapes.begin() ; shape != subshapes.end() ; shape++)
        Read(shape->firstObject);
    for (shape = subshapes.begin() ; shape != subshapes.end() ; shape++)
        Read(shape->firstDecal);
    ReadCheck(6) ;
    for (shape = subshapes.begin() ; shape != subshapes.end() ; shape++)
        Read(shape->numNodes);
    for (shape = subshapes.begin() ; shape != subshapes.end() ; shape++)
        Read(shape->numObjects);
    for (shape = subshapes.begin() ; shape != subshapes.end() ; shape++)
        Read(shape->numDecals);
    ReadCheck(7) ;
    
    // MeshIndexList (obsolete data)
    
    if (dtsVersion < 16)
    {
        int size, temp ;
        Read(size);
        while (size--) Read(temp);
    }
    
    // Default translations and rotations
    
    nodeDefRotations   .resize(numNodes) ;
    nodeDefTranslations.resize(numNodes) ;
    
    for (size_t n = 0 ; n < nodes.size() ; n++)
    {
        Read(nodeDefRotations[n]);
        Read(nodeDefTranslations[n]);
    }
    
    // Animation translations and rotations
    
    nodeTranslations.resize(numNodeTranslations);
    nodeRotations   .resize(numNodeRotations);
    Read(nodeTranslations);
    Read(nodeRotations);
    ReadCheck(8);
    
    // Default scales
    
    nodeScalesUniform  .resize(numNodeScalesUniform);
    nodeScalesAligned  .resize(numNodeScalesAligned);
    nodeScalesArbitrary.resize(numNodeScalesArbitrary);
    
    if (dtsVersion > 21)
    {
        Read(nodeScalesUniform);
        Read(nodeScalesAligned);
        Read(nodeScalesArbitrary);
        Read(nodeScaleRotsArbitrary);
        ReadCheck(9) ;
    }
    
    // Ground transformations
   
    groundTranslations.resize(numGroundFrames);
    groundRotations   .resize(numGroundFrames);
    
    if (dtsVersion > 23)
    {
        Read(groundTranslations);
        Read(groundRotations);
        ReadCheck(10);
    }
    
    // Object states
    
    objectStates.resize(numObjectStates) ;
    Read(objectStates);
    ReadCheck(11);
    
    // Decal states
    
    decalStates.resize(numDecalStates);
    Read(decalStates);
    ReadCheck(12);
    
    // Triggers
    
    triggers.resize(numTriggers);
    Read(triggers);
    ReadCheck(13);
    
    // Detail Levels
    
    detailLevels.resize(numDetailLevels);
    Read(detailLevels);
    ReadCheck(14);
    
    // Meshes
    
    meshes.resize(numMeshes);
    Read(meshes);
    ReadCheck();

    // Names
    
    names.resize(numNames);
    Read(names);
    ReadCheck();
    
    // Sequences
    loadSequences(file, false);

	// Materials

	/*char materialListVersion =*/ ReadRawTyped<char>(file);
	int  materialCount       = ReadRawTyped<int> (file);

	materials.resize(materialCount);

	std::vector<DTSMaterial>::iterator mat;
	for (mat = materials.begin(); mat != materials.end() ; mat++)
	{
		DTSMaterial&  material = *mat;
		unsigned char length   = ReadRawTyped<unsigned char>(file);

		material.name.resize(length);
		fread((char*)material.name.data(), length, 1, file);
	}

	for (mat = materials.begin() ; mat != materials.end() ; mat++)
		(*mat).flags = ReadRawTyped<int>(file);
	for (mat = materials.begin() ; mat != materials.end() ; mat++)
		(*mat).reflectance = ReadRawTyped<int>(file);
	for (mat = materials.begin() ; mat != materials.end() ; mat++)
		(*mat).bump = ReadRawTyped<int>(file);
	for (mat = materials.begin() ; mat != materials.end() ; mat++)
		(*mat).detail = ReadRawTyped<int>(file);
	for (mat = materials.begin() ; mat != materials.end() ; mat++)
		(*mat).detailScale = ReadRawTyped<int>(file);
	for (mat = materials.begin() ; mat != materials.end() ; mat++)
		(*mat).reflection = ReadRawTyped<int>(file);
}

void DTSShape::loadSequences(FILE* file, bool dsq)
{
	int numSequences = ReadRawTyped<int>(file);
    
	sequences.resize(numSequences);
    
	for (size_t seq = 0 ; seq < sequences.size() ; seq++)
	{
		DTSSequence& p = sequences[seq];
        
        if (dsq)
        {
            std::string name;
            
            ReadRawTyped(file, name);
        }
        else
        {
            p.nameIndex = ReadRawTyped<int>(file);
		}
        
        p.flags            = ReadRawTyped<int>(file);
		p.numKeyFrames     = ReadRawTyped<int>(file);
		p.duration         = ReadRawTyped<float>(file);
		p.priority         = ReadRawTyped<int>(file);
		p.firstGroundFrame = ReadRawTyped<int>(file);
		p.numGroundFrames  = ReadRawTyped<int>(file);
		p.baseRotation     = ReadRawTyped<int>(file);
		p.baseTranslation  = ReadRawTyped<int>(file);
		p.baseScale        = ReadRawTyped<int>(file);
		p.baseObjectState  = ReadRawTyped<int>(file);
		p.baseDecalState   = ReadRawTyped<int>(file);
		p.firstTrigger     = ReadRawTyped<int>(file);
		p.numTriggers      = ReadRawTyped<int>(file);
		p.toolBegin        = ReadRawTyped<float>(file);
        
		ReadRawTyped(file, p.matters.rotation);
		ReadRawTyped(file, p.matters.translation);
		ReadRawTyped(file, p.matters.scale);
		ReadRawTyped(file, p.matters.decal);
		ReadRawTyped(file, p.matters.ifl);
		ReadRawTyped(file, p.matters.vis);
		ReadRawTyped(file, p.matters.frame);
		ReadRawTyped(file, p.matters.matframe);
	}
}

void DTSShape::loadSequenceFile(FILE* file)
{
    size_t index;
    
    dtsVersion = ReadRawTyped<int>(file);
    
    names.resize(numNames = ReadRawTyped<int>(file));
    for (index = 0; index < names.size(); index++)
    {
        ReadRawTyped(file, names[index]);
    }
    
    // Objects Export ?
    ReadRawTyped<int>(file);
    
    numObjects = ReadRawTyped<int>(file);
    
    nodeRotations.resize(numNodeRotations = ReadRawTyped<int>(file));
    
    for (index = 0; index < nodeRotations.size(); index++)
    {
        Quaternion q;
        
        q.x = (float)ReadRawTyped<short>(file) / 32767.0f;
        q.y = (float)ReadRawTyped<short>(file) / 32767.0f;
        q.z = (float)ReadRawTyped<short>(file) / 32767.0f;
        q.w = (float)ReadRawTyped<short>(file) / 32767.0f;
        nodeRotations[index] = q;
    }
    
    nodeTranslations.resize(numNodeTranslations = ReadRawTyped<int>(file));
    
    for (index = 0; index < nodeTranslations.size(); index++)
    {
        Point p;
        
        p.x = ReadRawTyped<float>(file);
        p.y = ReadRawTyped<float>(file);
        p.z = ReadRawTyped<float>(file);
        nodeTranslations[index] = p;
    }
    
    nodeScalesUniform.resize(numNodeScalesUniform = ReadRawTyped<int>(file));
    
    for (index = 0; index < nodeScalesUniform.size(); index++)
    {
        nodeScalesUniform.push_back(ReadRawTyped<float>(file));
    }
    
    nodeScalesAligned.resize(numNodeScalesAligned = ReadRawTyped<int>(file));
    
    for (index = 0; index < nodeScalesAligned.size(); index++)
    {
        Point p;
        
        p.x = ReadRawTyped<float>(file);
        p.y = ReadRawTyped<float>(file);
        p.z = ReadRawTyped<float>(file);
        nodeScalesAligned[index] = p;
    }
    
    nodeScaleRotsArbitrary.resize(numNodeScalesArbitrary = ReadRawTyped<int>(file));
    nodeScalesArbitrary   .resize(numNodeScalesArbitrary);
    
    for (index = 0; index < nodeScaleRotsArbitrary.size(); index++)
    {
        Quaternion q;
        
        q.x = (float)ReadRawTyped<short>(file) / 32767.0f;
        q.y = (float)ReadRawTyped<short>(file) / 32767.0f;
        q.z = (float)ReadRawTyped<short>(file) / 32767.0f;
        q.w = (float)ReadRawTyped<short>(file) / 32767.0f;
        nodeScaleRotsArbitrary[index] = q;
    }
    
    for (index = 0; index < nodeScalesArbitrary.size(); index++)
    {
        Point p;
        
        p.x = ReadRawTyped<float>(file);
        p.y = ReadRawTyped<float>(file);
        p.z = ReadRawTyped<float>(file);
        nodeScalesArbitrary[index] = p;
    }
    
    groundTranslations.resize(numGroundFrames = ReadRawTyped<int>(file));
    groundRotations   .resize(numGroundFrames);
    
    for (index = 0; index < groundTranslations.size(); index++)
    {
        Point p;
        
        p.x = ReadRawTyped<float>(file);
        p.y = ReadRawTyped<float>(file);
        p.z = ReadRawTyped<float>(file);
        groundTranslations[index] = p;
    }
    
    for (index = 0; index < groundRotations.size(); index++)
    {
        Quaternion q;
        
        q.x = (float)ReadRawTyped<short>(file) / 32767.0f;
        q.y = (float)ReadRawTyped<short>(file) / 32767.0f;
        q.z = (float)ReadRawTyped<short>(file) / 32767.0f;
        q.w = (float)ReadRawTyped<short>(file) / 32767.0f;
        groundRotations[index] = q;
    }
    
    ReadRawTyped<int>(file);
    
    loadSequences(file, true);
    
    triggers.resize(numTriggers = ReadRawTyped<int>(file));
    
    for (index = 0; index < triggers.size(); index++)
    {
        DTSTrigger& trigger = triggers[index];
        
        trigger.state = ReadRawTyped<int>(file);
        trigger.pos   = ReadRawTyped<float>(file);
    }
}

std::string DTSShape::nodeNameAtIndex(int index) const
{
    if (index < 0)
    {
        return "(null)";
    }
    
    return names[nodes[index].name];
}

std::string DTSShape::objectNameAtIndex(int index) const
{
    if (index < 0)
    {
        return "(null)";
    }
    
    return names[objects[index].name];
}

std::string DTSShape::decalNameAtIndex(int index) const
{
    if (index < 0)
    {
        return "(null)";
    }
    
    if (index >= (int)decals.size())
    {
        return "(invalid)";
    }
    
    return names[decals[index].name];
}

bool DTSShape::nodeIsLinkedToObject(int node) const
{
    std::vector<DTSObject>::const_iterator it, end(objects.end());
    
    for (it = objects.begin(); it != end; ++it)
    {
        if ((*it).node == node)
        {
            return true;
        }
    }
    
    return false;
}

#ifdef WIN32
#define PATHSEP "\\"
#else
#define PATHSEP "/"
#endif

void DTSResolver::addPathContaining(const std::string& n)
{
    size_t lastEntry = n.rfind(PATHSEP);
    
    if (lastEntry == std::string::npos)
    {
        paths.push_back(n);
    }
    else
    {
        paths.push_back(n.substr(0, lastEntry));
    }
}

std::string DTSResolver::resolve(const std::string& n) const
{
    struct stat s;
    
    std::vector<std::string>::const_iterator it, end(paths.end());
    
    for (it = paths.begin(); it != end; ++it)
    {
        std::string e(*it);
        
        e += PATHSEP;
        e += n;
        
        if (stat(e.c_str(), &s) == 0)
        {
            return e;
        }
    }
    
    return n;
}
