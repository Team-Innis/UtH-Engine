#pragma once
#ifndef ENUMS_H_UTH
#define ENUMS_H_UTH

namespace uth
{
    enum ShaderType
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER,

        SHADERTYPE_LAST
    };

    enum DataType
    {
        BYTE_TYPE,
        UNSIGNED_BYTE_TYPE,
        SHORT_TYPE,
        UNSIGNED_SHORT_TYPE,
        INT_TYPE,
        UNSIGNED_INT_TYPE,
        FLOAT_TYPE,

        DATATYPE_LAST
    };

    enum BufferType
    {
        ARRAY_BUFFER,
        ELEMENT_ARRAY_BUFFER,

        BUFFERTYPE_LAST
    };

    enum UsageType
    {
        STREAM_DRAW,
        STATIC_DRAW,
        DYNAMIC_DRAW,

        USAGETYPE_LAST
    };

    enum PixelStoreParam
    {
        PACK_ALIGNMENT,
		UNPACK_ALIGNMENT,

        PIXELSTOREPARAM_LAST
    };

    enum TexUnit
    {
        TEXTURE_0,
        TEXTURE_1,
        TEXTURE_2,
        TEXTURE_3,
        TEXTURE_4,
        TEXTURE_5,
        TEXTURE_6,
        TEXTURE_7,

        TEXUNIT_LAST
    };

    enum TextureType
    {
          
        TEXTURE_2D,
        TEXTURE_CUBE_MAP,

        TEXTURETYPE_LAST
    };

    enum TextureFilter
    {
        NEAREST,
        LINEAR,
        REPEAT,
        CLAMP_TO_EDGE,

        TEXTUREFILTER_LAST
    };

    enum ImageFormat
    {
        RGB_FORMAT,
        RGBA_FORMAT,
        RGBA8_FORMAT,

        IMAGEFORMAT_LAST
    };

    enum TextureParam
    {
        TEXTURE_MIN_FILTER, 
        TEXTURE_MAG_FILTER,
        TEXTURE_WRAP_S, 
        TEXTURE_WRAP_T,
    
        TEXTUREPARAM_LAST
    };

    enum PrimitiveType
    {
        POINTS, 
        LINE_STRIP, 
        LINE_LOOP, 
        LINES,
        TRIANGLE_STRIP, 
        TRIANGLE_FAN, 
        TRIANGLES, 

        PRIMITIVETYPE_LAST
    };

    enum DepthFunction
    {
        NEVER, 
        LESS, 
        EQUAL, 
        LEQUAL, 
        GREATER, 
        NOTEQUAL, 
        GEQUAL, 
        ALWAYS,

        DEPTHFUNCTION_LAST
    };

    enum BlendFunction
    {
        ZERO, 
        ONE, 
        SRC_COLOR, 
        ONE_MINUS_SRC_COLOR, 
        DST_COLOR, 
        ONE_MINUS_DST_COLOR, 
        SRC_ALPHA, 
        ONE_MINUS_SRC_ALPHA, 
        DST_ALPHA, 
        ONE_MINUS_DST_ALPHA, 
        CONSTANT_COLOR, 
        ONE_MINUS_CONSTANT_COLOR, 
        CONSTANT_ALPHA, 
        ONE_MINUS_CONSTANT_ALPHA,

        BLENDFUNCTION_LAST
    };

    enum FaceCulling
    {
         FRONT, 
         BACK, 
         FRONT_AND_BACK,

         FACECULLING_LAST
    };
}

#endif
