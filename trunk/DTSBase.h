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

#ifndef DTSConverter_DTSBase_h
#define DTSConverter_DTSBase_h

#include "DTSTypes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

class DTSNode;
class DTSObject;
class DTSDecal;
class DTSIFLMaterial;
class DTSSubshape;
class DTSObjectState;
class DTSDecalState;
class DTSTrigger;
class DTSDetailLevel;
class DTSMesh;
class DTSPrimitive;
class DTSCluster;

class DTSBase
{
protected:
    int dtsVersion;
    int totalSize;
    int offset16;
    int offset8;
    
    std::vector<int>   buffer32;
    std::vector<short> buffer16;
    std::vector<char>  buffer8;
    
    int allocated32;
    int allocated16;
    int allocated8;
    
    int checkCount;
    int used32;
    int used16;
    int used8;
    
public:
    template <typename DataType>
    DataType ReadRawTyped(FILE* file);

    void ReadRawTyped(FILE* file, std::vector<bool>& booleanVector);
    void ReadRawTyped(FILE* file, std::string& string);

    void Read(int&);
    void Read(unsigned int&);
    void Read(int*, int count);
    
    void Read(short&);
    void Read(unsigned short&);
    void Read(short*, int count);
    
    void Read(char&);
    void Read(unsigned char&);
    void Read(char*, int count);
    
    void Read(float&);

    void Read(std::string&);

    void Read(Point&);
    void Read(Point2D&);
    void Read(Box&);
    void Read(Quaternion&);
    void Read(Matrix<4,4>&);
    
    void Read(DTSNode&);
    void Read(DTSObject&);
    void Read(DTSDecal&);
    void Read(DTSIFLMaterial&);
    void Read(DTSObjectState&);
    void Read(DTSDecalState&);
    void Read(DTSTrigger&);
    void Read(DTSDetailLevel&);
    void Read(DTSMesh&);
    void Read(DTSPrimitive&);
    void Read(DTSCluster&);
    
    void ReadCheck(int checkPoint = -1);
    
    template <typename DataType> void Read(std::vector<DataType>& vectorType)
    {
        size_t index, count = vectorType.size();
        
        for (index = 0; index < count; index++)
        {
            Read(vectorType[index]);
        }
    }
    
public:
    DTSBase();
    
protected:
    void load(FILE* file);
};

template <typename DataType> DataType DTSBase::ReadRawTyped(FILE* file)
{
    DataType scalar;
    
    fread(&scalar, sizeof(scalar), 1, file);
    return scalar;
}

#endif
