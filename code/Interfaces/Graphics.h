// Copyright © 2008-2009 Intel Corporation
// All Rights Reserved
//
// Permission is granted to use, copy, distribute and prepare derivative works of this
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  THIS SOFTWARE IS PROVIDED "AS IS."
// INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, AND ALL LIABILITY,
// INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES, FOR THE USE OF THIS SOFTWARE,
// INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY RIGHTS, AND INCLUDING THE
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTANTS: IndexDecl
// DESCRIPTION: Format of indices for procedural mesh index buffer.
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace IndexDecl
{
    namespace Type
    {
        static const u32                Index16         = 0x00000000;
        static const u32                Index32         = 0x00000001;
    }

    // <summary>
    //   Calculates the size in byes of an index based on its declaration.
    // </summary>
    // <param name=Type">The index declaration.</param>
    // <returns>The size of an index in bytes.</returns>
    __inline__ u32 CalculateSize( In u32 Type )
    {
        return (Type == Type::Index16) ? sizeof (u16) : sizeof (u32);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTANTS: VertexDecl
// DESCRIPTION: Format of vertices for procedural mesh vertex buffer.
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace VertexDecl
{
    namespace Type
    {
        static const u32                Color           = 0x00000000;
        static const u32                Float1          = 0x00000001;
        static const u32                Float2          = 0x00000002;
        static const u32                Float3          = 0x00000003;
        static const u32                Float4          = 0x00000004;
        static const u32                UByte4          = 0x00000005;
    }

    namespace Usage
    {
        static const u32                Position        = 0x00000000;
        static const u32                Normal          = 0x00000001;
        static const u32                Diffuse         = 0x00000002;
        static const u32                Specular        = 0x00000003;
        static const u32                Tangent         = 0x00000004;
        static const u32                Texture         = 0x00000005;

        // Vertex Bone Assignments - typically UByte4
        static const u32                BlendIndices    = 0x00000006;
        // Vertex Blend Weights - typically a Float4
        static const u32                BlendWeights    = 0x00000007;
    }

    struct Element
    {
        u32                             Type;
        u32                             Usage;
        u32                             UsageIndex;
        u32                             StreamIndex;
    };

    __inline__ u32 FindUsageInStream( In Element* pElements, In u32 cElements, In u32 VertUsage, In u32 UsageIndex=0 )
    {
        u32 Stream = static_cast<u32>(-1);

        u32 usageCount = 0;
        for ( u32 i=0; i < cElements; i++ )
        {
            if ( pElements[ i ].Usage == VertUsage )
            {
                if( UsageIndex == usageCount++ )
                {
                    Stream = pElements[ i ].StreamIndex;
                    break;
                }
            }
        }

        return Stream;
    }

    // <summary>
    //   Calculates the size in bytes of a vertex based on its declaration.
    // </summary>
    // <param name="pElements">The vertex declaration.</param>
    // <param name="cElements">The number of vertex declaration elements.</param>
    // <returns>The size of a vertex in bytes.</returns>
    __inline__ u32 CalculateSize( In Element* pElements, In u32 cElements, u32 StreamIndex=0 )
    {
        u32 Size = 0;

        for ( u32 i=0; i < cElements; i++ )
        {
            if ( pElements[ i ].StreamIndex == StreamIndex )
            {
                switch( pElements[ i ].Type )
                {
                case Type::Color: Size += sizeof (u32); break;
                case Type::Float1: Size += sizeof (f32); break;
                case Type::Float2: Size += sizeof (f32) * 2; break;
                case Type::Float3: Size += sizeof (f32) * 3; break;
                case Type::Float4: Size += sizeof (f32) * 4; break;
                case Type::UByte4: Size += sizeof (unsigned char) * 4; break;
                default: ASSERT( False ); break;
                }
            }
        }

        return Size;
    }

    // <summary>
    //   Calculates the offset of a particular usage within the vertex.
    // </summary>
    // <param name="Usage">The usage to look for.</param>
    // <param name="pElements">The vertex declaration.</param>
    // <param name="cElements">The number of vertex declaration elements.</param>
    // <param name="Type">The returned type of the usage.</param>
    // <returns>The offset of the usage in the vertex in bytes.</returns>
    __inline__ i32 CalculateUsageOffsetInVertex( In Element* pElements, In u32 cElements,
                                                    In u32 Usage, Out u32& Type, 
                                                    In u32 StreamIndex=0, In u32 UsageIndex=0 )
    {
        i32 Offset = 0;

        u32 i;
        u32 usageCount = 0;
        for ( i=0; i < cElements; i++ )
        {
            if ( pElements[ i ].Usage == Usage )
            {
                Type = pElements[ i ].Type;
                if( UsageIndex == usageCount++ )
                    break;
            }

            if ( pElements[ i ].StreamIndex == StreamIndex )
            {
                switch( pElements[ i ].Type )
                {
                case Type::Color: Offset += sizeof (u32); break;
                case Type::Float1: Offset += sizeof (f32); break;
                case Type::Float2: Offset += sizeof (f32) * 2; break;
                case Type::Float3: Offset += sizeof (f32) * 3; break;
                case Type::Float4: Offset += sizeof (f32) * 4; break;
                case Type::UByte4: Offset += sizeof (unsigned char) * 4; break;
                default: ASSERT( False ); break;
                }
            }
        }

        if ( i == cElements )
        {
            Offset = -1;
        }

        return Offset;
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
///   <c>IGraphicsObject</c> is an interface for providing graphics related functionality.  Any
///    objects that modify graphics data are required to implement this class.
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////

class IGraphicsObject
{
public:

    /// <summary>
    ///   Returns the number of submeshes.
    /// </summary>
    /// <returns>The submesh count.</returns>
    virtual u32 GetSubMeshCount( void ) = 0;

    /// <summary>
    ///   Returns the declaration for the index buffer.
    /// </summary>
    /// <returns>The index declaration.</returns>
    virtual u32 GetIndexDeclaration( In  u16 nSubMeshIndex = 0 ) = 0;

    /// <summary>
    ///   Returns the number of vertex declaration elements.
    /// </summary>
    /// <param name="nSubMeshIndex">The index of the SubMesh being referenced (default = 0).</param>
    /// <returns>The vertex declaration element count.</returns>
    virtual u32 GetVertexDeclarationCount( In  u16 nSubMeshIndex = 0 ) = 0;

    /// <summary>
    ///   Returns the declaration for the vertex buffer.
    /// </summary>
    /// <remarks cref="GetVertexDeclarationCount">
    ///   The size of the passed in array must be able to contain the number of elements returned by
    ///    GetVertexDeclarationCount.
    /// </remarks>
    /// <param name="pVertexDecl">The filled in vertex declaration array.</param>
    /// <param name="nSubMeshIndex">The index of the SubMesh being referenced (default = 0).</param>
    virtual void GetVertexDeclaration( Out VertexDecl::Element* pVertexDecl,
                                       In  u16 nSubMeshIndex = 0 ) = 0;

    /// <summary>
    ///   Returns the number of index buffer entries.
    /// </summary>
    /// <param name="nSubMeshIndex">The index of the SubMesh being referenced (default = 0).</param>
    /// <returns>The index count.</returns>
    virtual u32 GetIndexCount( In  u16 nSubMeshIndex = 0 ) = 0;

    /// <summary>
    ///   Returns the number of vertex buffer entries.
    /// </summary>
    /// <param name="nSubMeshIndex">The index of the SubMesh being referenced (default = 0).</param>
    /// <returns>The vertex count.</returns>
    virtual u32 GetVertexCount( In  u16 nSubMeshIndex = 0 ) = 0;

    /// <summary>
    ///   Copies over the index buffer.
    /// </summary>
    /// <param name="pIndices">The returned index list.</param>
    /// <param name="nSubMeshIndex">The index of the SubMesh being referenced (default = 0).</param>
    virtual void GetIndices( Out void* pIndices,
                             In  u16 nSubMeshIndex = 0 ) = 0;

    /// <summary>
    ///   Copies over the vertex buffer.
    /// </summary>
    /// <param name="pVertices">The returned vertex list.</param>
    /// <param name="nSubMeshIndex">The index of the SubMesh whose vertex buffer is referenced (default = 0).</param>
    /// <param name="nStreamIndex">Index of the Vertex Stream to return.</param>
    /// <param name="nVertexDeclCount">Element count in the requested FVF.
    ///                                Value of 0 means all elements in the vertex buffer (default=0)</param>
    /// <param name="pVertexDecl">VertexDecl Format to be used for the returned list of Vertices</param>
    virtual void GetVertices( Out void* pVertices,
                              In  u16 nSubMeshIndex = 0,
                              In  u16 nStreamIndex = 0,
                              In  u32 nVertexDeclCount = 0,
                              In  VertexDecl::Element* pVertexDecl = NULL ) = 0;

    /// <summary>
    ///   Queries a system for the indices of changed vertex streams.
    /// </summary>
    /// <returns>A bitmask with indices of modified vertex streams.</returns>
    virtual u32 GetStreamsChanged( void ) = 0;

    /// <summary>
    ///   Returns the axis-aligned bounding box for the object.
    /// </summary>
    /// <param name="Min">The returned minimum AABB point.</param>
    /// <param name="Max">The returned maximum AABB point.</param>
    virtual void GetAABB( Out Math::Vector3& Min, Out Math::Vector3& Max ) = 0;
};


class IGraphicsParticleObject
{
public:

    struct ParticleGroupData
    {
        f32                 Age;
        bool                visible;
    };

    struct ParticleData
    {
        Math::Vector3       Position;
        Math::Vector3       Velocity;
        f32                 Size;
        f32                 Time;
        f32                 LifeTime;
        f32                 Mass;
        u32                 Color;
    };


public:

	virtual u32 GetParticleGroupCount( void ){return 0;};

	virtual void GetParticleGroup( u32 iParticleGroup, Out ParticleGroupData& ParticleGroup ){};

	virtual u32 GetParticleCount( u32 iParticleGroup ) { return 0;};

	virtual void GetParticles( u32 iParticleGroup, Out ParticleData* pParticles ) {};

	virtual std::string GetParticleGroupTechnique(void) {return "turkey breath";};

	virtual f32 GetParticleSystemAge() {return 0.0f;};

};
