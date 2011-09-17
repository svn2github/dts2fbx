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

#include "DTSBase.h"
#include "DTSShape.h"
#include <assert.h>
#include <string.h>

void DTSBase::Read(float& value)
{
    Read((int*)&value, 1);
}

void DTSBase::Read(int& value)
{
    Read(&value, 1);
}

void DTSBase::Read(unsigned int& value)
{
    Read((int*)&value, 1);
}

void DTSBase::Read(short& value)
{
    Read(&value, 1);
}

void DTSBase::Read(unsigned short& value)
{
    Read((short*)&value, 1);
}

void DTSBase::Read(char& value)
{
    Read(&value, 1);
}

void DTSBase::Read(unsigned char& value)
{
    Read((char*)&value, 1);
}

void DTSBase::Read(int* data, int count)
{
    assert(count > 0);
    assert((used32 + count) <= allocated32);
    
    if (data)
        memcpy(data, &(buffer32[used32]), sizeof(int) * count);
    
    used32 += count;
}

void DTSBase::Read(short* data, int count)
{
    assert(count > 0);
    assert((used16 + count) <= allocated16);
    
    if (data)
        memcpy(data, &(buffer16[used16]), sizeof(short) * count);
    
    used16 += count;
}

void DTSBase::Read(char* data, int count)
{
    assert(count > 0);
    assert((used8 + count) <= allocated8);
    
    if (data)
        memcpy(data, &(buffer8[used8]), sizeof(char) * count);
    
    used8 += count;
}

void DTSBase::ReadCheck(int checkPoint)
{
    if (checkPoint >= 0)
        assert(checkPoint == checkCount) ;
    
    int   checkCount_int ;
    short checkCount_short ;
    char  checkCount_char  ;
    
    Read(checkCount_int);
    Read(checkCount_short);
    Read(checkCount_char);
    
    assert(checkCount_char  == (char) checkCount) ;
    assert(checkCount_short == (short)checkCount) ;
    assert(checkCount_int   == (int)  checkCount) ;
    
    checkCount++;
}

void DTSBase::Read(Point& value)
{
    Read(value.x);
    Read(value.y);
    Read(value.z);
}

void DTSBase::Read(Point2D& value)
{
    Read(value.x);
    Read(value.y);
}

void DTSBase::Read(Box& value)
{
    Read(value.min);
    Read(value.max);
}

void DTSBase::Read(Quaternion& value)
{
    short x, y, z, w;
    
    Read(x); Read(y); Read(z); Read(w);
    
    value.x = (x / 32767.0f);
    value.y = (y / 32767.0f);
    value.z = (z / 32767.0f);
    value.w = (w / 32767.0f);
}

void DTSBase::Read(Matrix<4,4>& matrix)
{
	float* m = matrix.data;

	Read((int*)m, 16);
}

void DTSBase::Read(std::string& value)
{
	char c;

	value.clear();

	while (true)
	{
		Read(c);

		if (c == 0)
		{
			break;
		}

		value += c;
	}
}

void DTSBase::Read(DTSNode& value)
{
    Read(value.name);
    Read(value.parent);
    Read(value.firstObject);
    Read(value.child);
    Read(value.sibling);
}

void DTSBase::Read(DTSObject& value)
{
    Read(value.name);
    Read(value.numMeshes);
    Read(value.firstMesh);
    Read(value.node);
    Read(value.sibling);
    Read(value.firstDecal);
}

void DTSBase::Read(DTSDecal& value)
{
    Read(value.name);
    Read(value.numMeshes);
    Read(value.firstMesh);
    Read(value.object);
    Read(value.sibling);
}

void DTSBase::Read(DTSIFLMaterial& value)
{
    Read(value.name);
    Read(value.slot);
    Read(value.firstFrame);
    Read(value.time);
    Read(value.numFrames);
}

void DTSBase::Read(DTSObjectState& value)
{
    Read(value.vis);
    Read(value.frame);
    Read(value.matFrame);
}

void DTSBase::Read(DTSDetailLevel& value)
{
    Read(value.name);
    Read(value.subshape);
    Read(value.objectDetail);
    Read(value.size);
    Read(value.avgError);
    Read(value.maxError);
    Read(value.polyCount);
}

void DTSBase::Read(DTSTrigger& value)
{
    Read(value.state);
    Read(value.pos);
}

void DTSBase::Read(DTSDecalState& value)
{
    Read(value.frame);
}

void DTSBase::Read(DTSPrimitive& value)
{
    Read(value.firstElement);
    Read(value.numElements);
    Read(value.type);
}

void DTSBase::Read(DTSCluster& value)
{
    Read(value.startPrimitive);
    Read(value.endPrimitive);
    Read(value.normal);
    Read(value.k);
    Read(value.frontCluster);
    Read(value.backCluster);
}

void DTSBase::Read(DTSMesh& value)
{
    Read(value.type);
    
    if (value.type == DTSMesh::T_Null) return ;
    
    ReadCheck() ;
    
    // Header & Bounds
    
    Read(value.numFrames);
    Read(value.matFrames);
    Read(value.parent);
    Read(value.bounds);
    Read(value.center);
    
    int radiusInt ;
    Read(radiusInt);
    value.radius = (float)radiusInt ;
    
    // Vertexes
    
    int numVertexes ;
    Read(numVertexes);
    value.verts.resize (numVertexes) ;
    Read(value.verts);
    
    // Texture coordinates
    
    int numTVerts ;
    Read(numTVerts);
    value.tverts.resize (numTVerts) ;
    Read(value.tverts);
    
    // Normals 
    
    value.normals.resize (numVertexes);
    value.enormals.resize (numVertexes);
    Read(value.normals);
    Read(value.enormals);
    
    // Primitives and other stuff
    
    int numPrimitives ;
    Read(numPrimitives);
    value.primitives.resize(numPrimitives);
    Read(value.primitives);
    
    int numIndices ;
    Read(numIndices);
    value.indices.resize(numIndices);
    Read(value.indices);
    
    int numMIndices ;
    Read(numMIndices);
    value.mindices.resize(numMIndices);
    Read(value.mindices);
    
    Read(value.vertsPerFrame);
    Read(value.flags);
    ReadCheck();

    if (value.type == DTSMesh::T_Skin)
    {
        Read(numVertexes);
        Read(value.verts);
        Read(value.normals);
        Read(value.enormals);

		int numNodeIndex;

		Read(numNodeIndex);
		value.nodeTransform.resize(numNodeIndex);
		Read(value.nodeTransform);

		int numVindex;

		Read(numVindex);
		value.vindex .resize(numVindex);
		value.vbone  .resize(numVindex);
		value.vweight.resize(numVindex);
		Read(value.vindex);
		Read(value.vbone);
		Read(value.vweight);

		Read(numNodeIndex);
		value.nodeIndex.resize(numNodeIndex);
		Read(value.nodeIndex);
		ReadCheck();
    }
    
	if (value.type == DTSMesh::T_Sorted)
    {
		int numCluster;
		int numStartCluster;
		int numFirstVerts;
		int numNumVerts;
		int numFirstTVerts;

		Read(numCluster);
		value.clusters.resize(numCluster);
		Read(value.clusters);

		Read(numStartCluster);
		value.startCluster.resize(numStartCluster);
		Read(value.startCluster);

		Read(numFirstVerts);
		value.firstVerts.resize(numFirstVerts);
		Read(value.firstVerts);

		Read(numNumVerts);
		value.numVerts.resize(numNumVerts);
		Read(value.numVerts);

		Read(numFirstTVerts);
		value.firstTVerts.resize(numFirstTVerts);
		Read(value.firstTVerts);

		int alwaysWriteDepth;

		Read(alwaysWriteDepth);
		ReadCheck();
	}
};

void DTSBase::ReadRawTyped(FILE* file, std::string& string)
{
    int i, l = ReadRawTyped<int>(file);
    
    for (i = 0; i < l; i++)
    {
        string += ReadRawTyped<char>(file);
    }
}

void DTSBase::ReadRawTyped(FILE* file, std::vector<bool>& booleanVector)
{
	int use = ReadRawTyped<int>(file);

	use = ReadRawTyped<int>(file);

	if (use <= 0)
	{
		return;
	}

	std::vector<int> intVector;

	intVector    .resize(use);
	booleanVector.resize(use * 32);

	fread(&intVector[0], use, sizeof(int), file);

	for (int i = 0; i < (use * 32); i++)
	{
		int w = intVector[i >> 5];
		int b = 1 << (i & 31);

		if (w & b)
		{
			booleanVector[i] = true;
		}
		else
		{
			booleanVector[i] = false;
		}
	}
}

DTSBase::DTSBase()
{
}

void DTSBase::load(FILE* file)
{
    dtsVersion = ReadRawTyped<int>(file);
    totalSize  = ReadRawTyped<int>(file);
    offset16   = ReadRawTyped<int>(file);
    offset8    = ReadRawTyped<int>(file);
    
    allocated32 = offset16;
    allocated16 = (offset8   - offset16) * 2;
    allocated8  = (totalSize - offset8)  * 4;
    
    buffer32.resize(allocated32);
    buffer16.resize(allocated16);
    buffer8 .resize(allocated8);
    
    size_t readed;
    
    readed = fread(&buffer32[0], sizeof(int),   allocated32, file);
    assert(readed == allocated32);
    readed = fread(&buffer16[0], sizeof(short), allocated16, file);
    assert(readed == allocated16);
    readed = fread(&buffer8[0],  sizeof(char),  allocated8,  file);
    assert(readed == allocated8);
    
    checkCount = 0;
    used32     = 0;
    used16     = 0;
    used8      = 0;
}
