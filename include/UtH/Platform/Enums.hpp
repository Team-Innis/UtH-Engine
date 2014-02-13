#pragma once

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
        DOUBLE_TYPE,

        DATATYPE_LAST
    };

    enum BufferType
    {
        ARRAY_BUFFER,
        COPY_READ_BUFFER,
        COPY_WRITE_BUFFER,
        ELEMENT_ARRAY_BUFFER,
        PIXEL_PACK_BUFFER,
        PIXEL_UNPACK_BUFFER,
        TEXTURE_BUFFER,
        TRANSFORM_FEEDBACK_BUFFER,
        UNIFORM_BUFFER,

        BUFFERTYPE_LAST
    };

    enum UsageType
    {
        STREAM_DRAW,
        STREAM_READ,
        STREAM_COPY,
        STATIC_DRAW,
        STATIC_READ,
        STATIC_COPY,
        DYNAMIC_DRAW,
        DYNAMIC_READ,
        DYNAMIC_SOPY,

        USAGETYPE_LAST
    };

    enum PixelStoreParam
    {
        PACK_SWAP_BYTES,
        PACK_LSB_FIRST, 
        PACK_ROW_LENGTH, 
        PACK_IMAGE_HEIGHT, 
        PACK_SKIP_PIXELS, 
        PACK_SKIP_ROWS, 
        PACK_SKIP_IMAGES, 
        PACK_ALIGNMENT,
        UNPACK_SWAP_BYTES, 
        UNPACK_LSB_FIRST, 
        UNPACK_ROW_LENGTH, 
        UNPACK_IMAGE_HEIGHT, 
        UNPACK_SKIP_PIXELS, 
        UNPACK_SKIP_ROWS, 
        UNPACK_SKIP_IMAGES, 
        UNPACK_ALIGNMENT,

        PIXELSTOREPARAM_LAST
    };

    enum TexUnit
    {
        TEXTURE_0,

        TEXUNIT_LAST
    };

    enum TextureType
    {
        TEXTURE_1D, 
        TEXTURE_2D, 
        TEXTURE_3D, 
        TEXTURE_1D_ARRAY, 
        TEXTURE_2D_ARRAY, 
        TEXTURE_RECTANGLE, 
        TEXTURE_CUBE_MAP,
        TEXTURE_2D_MULTISAMPLE,
        TEXTURE_2D_MULTISAMPLE_ARRAY,

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

        IMAGEFORMAT_LAST
    };

    enum TextureParam
    {
        TEXTURE_BASE_LEVEL, 
        TEXTURE_COMPARE_FUNC, 
        TEXTURE_COMPARE_MODE, 
        TEXTURE_LOD_BIAS, 
        TEXTURE_MIN_FILTER, 
        TEXTURE_MAG_FILTER, 
        TEXTURE_MIN_LOD, 
        TEXTURE_MAX_LOD, 
        TEXTURE_MAX_LEVEL, 
        TEXTURE_SWIZZLE_R, 
        TEXTURE_SWIZZLE_G, 
        TEXTURE_SWIZZLE_B, 
        TEXTURE_SWIZZLE_A, 
        TEXTURE_WRAP_S, 
        TEXTURE_WRAP_T,
        TEXTURE_WRAP_R,
    
        TEXTUREPARAM_LAST
    };

    enum PrimitiveType
    {
        POINTS, 
        LINE_STRIP, 
        LINE_LOOP, 
        LINES, 
        LINE_STRIP_ADJACENCY, 
        LINES_ADJACENCY, 
        TRIANGLE_STRIP, 
        TRIANGLE_FAN, 
        TRIANGLES, 
        TRIANGLE_STRIP_ADJACENCY,
        TRIANGLES_ADJACENCY,

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