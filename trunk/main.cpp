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
#include <errno.h>

#ifndef WIN32
#include <glob.h>
#endif

#include "DTSTypes.h"
#include "DTSBase.h"
#include "DTSShape.h"

int info(FILE* fileOut, DTSShape& shape)
{
    fprintf(fileOut, "Statistics:\n");
    fprintf(fileOut, "  nodes:             %i\n", shape.numNodes);
    fprintf(fileOut, "  objects:           %i\n", shape.numObjects);
    fprintf(fileOut, "  decals:            %i\n", shape.numDecals);
    fprintf(fileOut, "  subshapes:         %i\n", shape.numSubshapes);
    fprintf(fileOut, "  ifl materials:     %i\n", shape.numIFLmaterials);
    fprintf(fileOut, "  node rotations:    %i\n", shape.numNodeRotations);
    fprintf(fileOut, "  node translations: %i\n", shape.numNodeTranslations);
    fprintf(fileOut, "  scales uniform:    %i\n", shape.numNodeScalesUniform);
    fprintf(fileOut, "  scales aligned:    %i\n", shape.numNodeScalesAligned);
    fprintf(fileOut, "  scales arbitrary:  %i\n", shape.numNodeScalesArbitrary);
    fprintf(fileOut, "  ground frames:     %i\n", shape.numGroundFrames);
    fprintf(fileOut, "  object states:     %i\n", shape.numObjectStates);
    fprintf(fileOut, "  decal states:      %i\n", shape.numDecalStates);
    fprintf(fileOut, "  triggers:          %i\n", shape.numTriggers);
    fprintf(fileOut, "  detail levels:     %i\n", shape.numDetailLevels);
    fprintf(fileOut, "  meshes:            %i\n", shape.numMeshes);
    fprintf(fileOut, "  skins:             %i\n", shape.numSkins);
    fprintf(fileOut, "  names:             %i\n", shape.numNames);
    
    fprintf(fileOut, "\nInformations:\n");
    fprintf(fileOut, "  smallest size:         %f\n", shape.smallestSize);
    fprintf(fileOut, "  smallest detail level: %i\n", shape.smallestDetailLevel);
    fprintf(fileOut, "  radius:                %f\n", shape.radius);
    fprintf(fileOut, "  tube radius:           %f\n", shape.tubeRadius);
    fprintf(fileOut, "  center:                %f %f %f\n", shape.center.x, shape.center.y, shape.center.z);
    fprintf(fileOut, "  bounds:                %f %f %f - %f %f %f\n", shape.bounds.min.x, shape.bounds.min.y, shape.bounds.min.z, shape.bounds.max.x, shape.bounds.max.y, shape.bounds.max.z);
    
    int index;
    int sindex;
    
    if (shape.nodes.size() > 0)
    {
        fprintf(fileOut, "\nNodes:\n=======\n");
        
        std::vector<DTSNode>::const_iterator it, end(shape.nodes.end());
        
        for (it = shape.nodes.begin(), index = 0; it != end; ++it, ++index)
        {
            const DTSNode& node(*it);
            
            fprintf(fileOut, "  Node #%i\n", index);
            fprintf(fileOut, "    name:        %s\n", shape.names[node.name].c_str());
            fprintf(fileOut, "    parent:      %s\n", shape.nodeNameAtIndex(node.parent).c_str());
            fprintf(fileOut, "    firstObject: %s\n", shape.nodeNameAtIndex(node.firstObject).c_str());
            fprintf(fileOut, "    child:       %s\n", shape.nodeNameAtIndex(node.child).c_str());
            fprintf(fileOut, "    sibling:     %s\n", shape.nodeNameAtIndex(node.sibling).c_str());
        }
    }

    if (shape.objects.size() > 0)
    {
        fprintf(fileOut, "\nObjects:\n========\n");
        
        std::vector<DTSObject>::const_iterator it, end(shape.objects.end());
        
        for (it = shape.objects.begin(), index = 0; it != end; ++it, ++index)
        {
            const DTSObject& object(*it);
            
            fprintf(fileOut, "  Object #%i\n", index);
            fprintf(fileOut, "    name:        %s\n", shape.names[object.name].c_str());
            fprintf(fileOut, "    mesh count:  %i\n", object.numMeshes);
            fprintf(fileOut, "    firstMesh:   %i\n", object.firstMesh);
            fprintf(fileOut, "    node:        %s\n", shape.nodeNameAtIndex(object.node).c_str());
            fprintf(fileOut, "    sibling:     %i\n", object.sibling);
            fprintf(fileOut, "    firstDecal:  %i\n", object.firstDecal);
        }
    }
    
    if (shape.decals.size() > 0)
    {
        fprintf(fileOut, "\nDecals:\n=======\n");
        
        std::vector<DTSDecal>::const_iterator it, end(shape.decals.end());
        
        for (it = shape.decals.begin(), index = 0; it != end; ++it, ++index)
        {
            const DTSDecal& decal(*it);
            
            fprintf(fileOut, "  Decal #%i\n", index);
            fprintf(fileOut, "    name:        %s\n", shape.names[decal.name].c_str());
            fprintf(fileOut, "    mesh count:  %i\n", decal.numMeshes);
            fprintf(fileOut, "    firstMesh:   %i\n", decal.firstMesh);
            fprintf(fileOut, "    object:      %s\n", shape.objectNameAtIndex(decal.object).c_str());
            fprintf(fileOut, "    sibling:     %i\n", decal.sibling);
        }
    }

    if (shape.IFLmaterials.size() > 0)
    {
        fprintf(fileOut, "\nIFL Materials:\n=======\n");
        std::vector<DTSIFLMaterial>::const_iterator it, end(shape.IFLmaterials.end());
        
        for (it = shape.IFLmaterials.begin(), index = 0; it != end; ++it, ++index)
        {
            const DTSIFLMaterial& iflmaterial(*it);
            
            fprintf(fileOut, "  Decal #%i\n", index);
            fprintf(fileOut, "    name:        %s\n", shape.names[iflmaterial.name].c_str());
        }
    }

    if (shape.subshapes.size() > 0)
    {
        fprintf(fileOut, "\nSubshapes:\n==========\n");
        std::vector<DTSSubshape>::const_iterator it, end(shape.subshapes.end());
        
        for (it = shape.subshapes.begin(), index = 0; it != end; ++it, ++index)
        {
            const DTSSubshape& subshape(*it);
            
            fprintf(fileOut, "  Subshape #%i\n", index);
            fprintf(fileOut, "    first node:        %s\n", shape.nodeNameAtIndex  (subshape.firstNode).c_str());
            fprintf(fileOut, "    first object:      %s\n", shape.objectNameAtIndex(subshape.firstObject).c_str());
            fprintf(fileOut, "    first decal:       %s\n", shape.decalNameAtIndex (subshape.firstDecal).c_str());
            fprintf(fileOut, "    num nodes:         %i\n", subshape.numNodes);
            fprintf(fileOut, "    num objects:       %i\n", subshape.numObjects);
            fprintf(fileOut, "    num decals:        %i\n", subshape.numDecals);
            fprintf(fileOut, "    first translucent: %i\n", subshape.firstTranslucent);
        }
    }
    
    if (shape.nodeDefRotations.size() > 0)
    {
        fprintf(fileOut, "\nNode default rotations:\n========================\n");
        std::vector<Quaternion>::const_iterator it, end(shape.nodeDefRotations.end());
        
        for (it = shape.nodeDefRotations.begin(), index = 0; it != end; ++it, ++index)
        {
            const Quaternion& q(*it);
            
            fprintf(fileOut, "  #%i: %f %f %f %f\n", index, q.x, q.y, q.z, q.w);
        }
    }

    if (shape.nodeDefTranslations.size() > 0)
    {
        fprintf(fileOut, "\nNode default translations:\n========================\n");
        std::vector<Point>::const_iterator it, end(shape.nodeDefTranslations.end());
        
        for (it = shape.nodeDefTranslations.begin(), index = 0; it != end; ++it, ++index)
        {
            const Point& q(*it);
            
            fprintf(fileOut, "  #%i: %f %f %f\n", index, q.x, q.y, q.z);
        }
    }

    if (shape.nodeRotations.size() > 0)
    {
        fprintf(fileOut, "\nNode rotations:\n========================\n");
        std::vector<Quaternion>::const_iterator it, end(shape.nodeRotations.end());
        
        for (it = shape.nodeRotations.begin(), index = 0; it != end; ++it, ++index)
        {
            const Quaternion& q(*it);
            
            fprintf(fileOut, "  #%i: %f %f %f %f\n", index, q.x, q.y, q.z, q.w);
        }
    }

    if (shape.nodeTranslations.size() > 0)
    {
        fprintf(fileOut, "\nNode translations:\n========================\n");
        std::vector<Point>::const_iterator it, end(shape.nodeTranslations.end());
        
        for (it = shape.nodeTranslations.begin(), index = 0; it != end; ++it, ++index)
        {
            const Point& q(*it);
            
            fprintf(fileOut, "  #%i: %f %f %f\n", index, q.x, q.y, q.z);
        }
    }

    if (shape.groundRotations.size() > 0)
    {
        fprintf(fileOut, "\nGround rotations:\n========================\n");
        std::vector<Quaternion>::const_iterator it, end(shape.groundRotations.end());
        
        for (it = shape.groundRotations.begin(), index = 0; it != end; ++it, ++index)
        {
            const Quaternion& q(*it);
            
            fprintf(fileOut, "  #%i: %f %f %f %f\n", index, q.x, q.y, q.z, q.w);
        }
    }
    
    if (shape.groundTranslations.size() > 0)
    {
        fprintf(fileOut, "\nGround translations:\n========================\n");
        std::vector<Point>::const_iterator it, end(shape.groundTranslations.end());
        
        for (it = shape.groundTranslations.begin(), index = 0; it != end; ++it, ++index)
        {
            const Point& q(*it);
            
            fprintf(fileOut, "  #%i: %f %f %f\n", index, q.x, q.y, q.z);
        }
    }

    if (shape.meshes.size() > 0)
    {
        fprintf(fileOut, "\nMaterials:\n========================\n");
        std::vector<DTSMaterial>::const_iterator it, end(shape.materials.end());
        
        for (it = shape.materials.begin(), index = 0; it != end; ++it, ++index)
        {
            const DTSMaterial& material(*it);

            fprintf(fileOut, "  Material #%i\n", index);
            
            fprintf(fileOut, "    name:          %s\n", material.name.c_str());
            fprintf(fileOut, "    flags:         %i\n", material.flags);
            fprintf(fileOut, "    reflectance:   %i\n", material.reflectance);
            fprintf(fileOut, "    bump:          %i\n", material.bump);
            fprintf(fileOut, "    detail:        %i\n", material.detail);
            fprintf(fileOut, "    detailScale:   %i\n", material.detailScale);
            fprintf(fileOut, "    reflection:    %i\n", material.reflection);
        }
    }

    if (shape.meshes.size() > 0)
    {
        fprintf(fileOut, "\nMeshes:\n========================\n");
        std::vector<DTSMesh>::const_iterator it, end(shape.meshes.end());
        
        for (it = shape.meshes.begin(), index = 0; it != end; ++it, ++index)
        {
            const DTSMesh& mesh(*it);
            
            fprintf(fileOut, "  Mesh #%i\n", index);

            const char* typeString = "(unknown)";

            switch (mesh.type)
            {
            case DTSMesh::T_Standard: typeString = "standard"; break;
            case DTSMesh::T_Skin:     typeString = "skin"; break;
            case DTSMesh::T_Decal:    typeString = "decal"; break;
            case DTSMesh::T_Sorted:   typeString = "sorted"; break;
            case DTSMesh::T_Null:     typeString = "null (collision)"; break;
            }

            fprintf(fileOut, "    type:                 %s (%i)\n", typeString, mesh.type);

            if (mesh.type == DTSMesh::T_Null)
            {
                continue;
            }

            fprintf(fileOut, "    frame count:          %i\n", mesh.numFrames);
            fprintf(fileOut, "    material frame count: %i\n", mesh.matFrames);
            fprintf(fileOut, "    parent:               %i\n", mesh.parent);
            fprintf(fileOut, "    bounds:               %f %f %f, %f %f %f\n", mesh.bounds.min.x, mesh.bounds.min.y, mesh.bounds.min.z, mesh.bounds.max.x, mesh.bounds.max.y, mesh.bounds.max.z);
            fprintf(fileOut, "    center:               %f %f %f\n", mesh.center.x, mesh.center.y, mesh.center.z);
            fprintf(fileOut, "    radius:               %f\n", mesh.radius);
            fprintf(fileOut, "    flags:                0x%08x\n", mesh.flags);
            fprintf(fileOut, "    vertex per frame:     %i\n", mesh.vertsPerFrame);
            fprintf(fileOut, "    vertex count:         %i\n", (int)mesh.verts.size());
            fprintf(fileOut, "    tvertex count:        %i\n", (int)mesh.tverts.size());
            fprintf(fileOut, "    normal count:         %i\n", (int)mesh.normals.size());
            
            {
                std::vector<Point>::const_iterator sit, send(mesh.verts.end());
            
                for (sit = mesh.verts.begin(), sindex = 0; sit != send; ++sit, ++sindex)
                {
                    fprintf(fileOut, "    vertex #%i:  %f %f %f\n", sindex, (*sit).x, (*sit).y, (*sit).z);
                }
            }

            {
                std::vector<Point2D>::const_iterator sit, send(mesh.tverts.end());
                
                for (sit = mesh.tverts.begin(), sindex = 0; sit != send; ++sit, ++sindex)
                {
                    fprintf(fileOut, "    tvertex #%i: %f %f\n", sindex, (*sit).x, (*sit).y);
                }
            }

            {
                std::vector<Point>::const_iterator sit, send(mesh.normals.end());
                
                for (sit = mesh.normals.begin(), sindex = 0; sit != send; ++sit, ++sindex)
                {
                    fprintf(fileOut, "    normal #%i:  %f %f %f\n", sindex, (*sit).x, (*sit).y, (*sit).z);
                }
            }

            if (mesh.type == DTSMesh::T_Skin)
            {
                {
                    std::vector<int>::const_iterator sit, send(mesh.vindex.end());
                
                    for (sit = mesh.vindex.begin(), sindex = 0; sit != send; ++sit, ++sindex)
                    {
                        fprintf(fileOut, "    vindex #%i:  %i\n", sindex, (*sit));
                    }

                    send = mesh.vbone.end();
                
                    for (sit = mesh.vbone.begin(), sindex = 0; sit != send; ++sit, ++sindex)
                    {
                        fprintf(fileOut, "    vbone #%i:  %i\n", sindex, (*sit));
                    }
                }

                {
                    std::vector<float>::const_iterator sit, send(mesh.vweight.end());

                    for (sit = mesh.vweight.begin(), sindex = 0; sit != send; ++sit, ++sindex)
                    {
                        fprintf(fileOut, "    vweight #%i:  %f\n", sindex, (*sit));
                    }
                }

                {
                    std::vector<int>::const_iterator sit, send(mesh.nodeIndex.end());
                
                    for (sit = mesh.nodeIndex.begin(), sindex = 0; sit != send; ++sit, ++sindex)
                    {
                        fprintf(fileOut, "    node index #%i:  %i\n", sindex, (*sit));
                    }
                }
            }
        }
    }

    return 0;
}

int convert(const DTSResolver&, const DTSShape& shape, const std::vector<DTSShape>& files, const char* fbxFile, bool addAnim);

int main (int argc, const char * argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Syntax:\n");
        fprintf(stderr, "  %s info    file.dts\n", argv[0]);
        fprintf(stderr, "  %s convert file.fbx file.dts [file.dsq ...]\n", argv[0]);
        fprintf(stderr, "  %s addanim file.fbx file.dts [file.dsq ...]\n", argv[0]);
        return -1;
    }
    
    FILE*    f = NULL;   
    DTSShape shape;

    if (strcmp(argv[1], "info") == 0)
    {
        f = fopen(argv[2], "rb");
        
        if (f == NULL)
        {
            fprintf(stderr, "Failed to open %s: %s\n", argv[2], strerror(errno));
            return -1;
        }

        if (strcmp(argv[2] + strlen(argv[2]) - 4, ".dsq") == 0)
        {
            shape.loadSequenceFile(f, NULL);
        }
        else
        {
            shape.loadShapeFile(f);
        }
        
        fclose(f);
        
        return info(stdout, shape);
    }

    /********************
     * Read Main Shape  *
     ********************/
    
    f = fopen(argv[3], "rb");
    
    if (f == NULL)
    {
        fprintf(stderr, "Failed to open %s: %s\n", argv[3], strerror(errno));
        return -1;
    }
    
    shape.loadShapeFile(f);
    fclose(f);

    /********************
     * Read Sequences   *
     ********************/
    std::vector<DTSShape> sequenceFiles;
    DTSResolver           resolver;

    resolver.addPathContaining(argv[2]);
    resolver.addPathContaining(argv[3]);

    for (int index = 4; index < argc; index++)
    {
#ifdef WIN32
        f = fopen(argv[index], "rb");
#else
        glob_t g;
        
        glob(argv[index], 0, NULL, &g);
        
        for (int gindex = 0; gindex < g.gl_pathc; gindex++)
        {
            f = fopen(g.gl_pathv[gindex], "rb");
#endif
            
            if (f)
            {
                DTSShape sequence;
                
                sequence.loadSequenceFile(f, &shape);
                fclose(f);
                
                sequenceFiles.push_back(sequence);
            }
            else
            {
                fprintf(stderr, "Error: Can't open %s\n", argv[index]);
            }

#ifndef WIN32
            resolver.addPathContaining(g.gl_pathv[gindex]);
        }
        
        globfree(&g);
#endif
    }

    /**********************
     * Perform Operations *
     **********************/
    if (strcmp(argv[1], "convert") == 0)
    {
        return convert(resolver, shape, sequenceFiles, argv[2], false);
    }
    else if (strcmp(argv[1], "addanim") == 0)
    {
        return convert(resolver, shape, sequenceFiles, argv[2], true);
    }
    else
    {
        fprintf(stderr, "Unknown command %s\n", argv[1]);
        return -1;
    }
}
