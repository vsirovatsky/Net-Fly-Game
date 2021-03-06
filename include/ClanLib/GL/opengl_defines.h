/*
**  ClanLib SDK
**  Copyright (c) 1997-2010 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
**    Mark Page
*/

/// \addtogroup clanGL_Display clanGL Display
/// \{

#pragma once
#include "api_gl.h"

#include "../Core/IOData/datatypes.h"

#ifndef CL_DISPLAYDEFINES_DEFINES
#define CL_DISPLAYDEFINES_DEFINES

#include <cstddef>

#ifndef __APPLE__
// Win32 and linux
typedef unsigned int CLenum;
typedef unsigned char CLboolean;
typedef unsigned int CLbitfield;
typedef signed char CLbyte;
typedef short CLshort;
typedef int CLint;
typedef int CLsizei;
typedef unsigned char CLubyte;
typedef unsigned short CLushort;
typedef unsigned int CLuint;
typedef cl_int64 CLint64;
typedef cl_uint64 CLuint64;
typedef float CLfloat;
typedef float CLclampf;
typedef double CLdouble;
typedef double CLclampd;
typedef void CLvoid;
typedef char CLchar;
typedef ptrdiff_t CLintptr;
typedef ptrdiff_t CLsizeiptr;
typedef struct __CLsync *CLsync;
#else
typedef struct __CLsync *CLsync;
typedef unsigned long CLenum;
typedef unsigned char CLboolean;
typedef unsigned long CLbitfield;
typedef signed char CLbyte;
typedef short CLshort;
typedef long CLint;
typedef long CLsizei;
typedef unsigned char CLubyte;
typedef unsigned short CLushort;
typedef unsigned long CLuint;
typedef float CLfloat;
typedef float CLclampf;
typedef double CLdouble;
typedef double CLclampd;
typedef void CLvoid;
typedef char CLchar;
typedef ptrdiff_t CLintptr;
typedef ptrdiff_t CLsizeiptr;
#endif

/// \brief Display Defines
///
/// \xmlonly !group=GL/Display! !header=gl.h! \endxmlonly
enum CL_DisplayDefines
{
	// AttribMask
	CL_DEPTH_BUFFER_BIT	= 0x00000100,
	CL_STENCIL_BUFFER_BIT	= 0x00000400,
	CL_COLOR_BUFFER_BIT	= 0x00004000,

	// Boolean
	CL_FALSE	= 0,
	CL_TRUE	= 1,

	// BeginMode
	CL_POINTS	= 0x0000,
	CL_LINES	= 0x0001,
	CL_LINE_LOOP	= 0x0002,
	CL_LINE_STRIP	= 0x0003,
	CL_TRIANGLES	= 0x0004,
	CL_TRIANGLE_STRIP	= 0x0005,
	CL_TRIANGLE_FAN	= 0x0006,

	// AlphaFunction
	CL_NEVER	= 0x0200,
	CL_LESS	= 0x0201,
	CL_EQUAL	= 0x0202,
	CL_LEQUAL	= 0x0203,
	CL_GREATER	= 0x0204,
	CL_NOTEQUAL	= 0x0205,
	CL_GEQUAL	= 0x0206,
	CL_ALWAYS	= 0x0207,

	// BlendingFactorDest
	CL_ZERO	= 0,
	CL_ONE	= 1,
	CL_SRC_COLOR	= 0x0300,
	CL_ONE_MINUS_SRC_COLOR	= 0x0301,
	CL_SRC_ALPHA	= 0x0302,
	CL_ONE_MINUS_SRC_ALPHA	= 0x0303,
	CL_DST_ALPHA	= 0x0304,
	CL_ONE_MINUS_DST_ALPHA	= 0x0305,

	// BlendingFactorSrc
	CL_DST_COLOR	= 0x0306,
	CL_ONE_MINUS_DST_COLOR	= 0x0307,
	CL_SRC_ALPHA_SATURATE	= 0x0308,

	// DrawBufferMode
	CL_NONE	= 0,
	CL_FRONT_LEFT	= 0x0400,
	CL_FRONT_RIGHT	= 0x0401,
	CL_BACK_LEFT	= 0x0402,
	CL_BACK_RIGHT	= 0x0403,
	CL_FRONT	= 0x0404,
	CL_BACK	= 0x0405,
	CL_LEFT	= 0x0406,
	CL_RIGHT	= 0x0407,
	CL_FRONT_AND_BACK	= 0x0408,

	// ErrorCode
	CL_NO_ERROR	= 0,
	CL_INVALID_ENUM	= 0x0500,
	CL_INVALID_VALUE	= 0x0501,
	CL_INVALID_OPERATION	= 0x0502,
	CL_OUT_OF_MEMORY	= 0x0505,

	// FrontFaceDirection
	CL_CW	= 0x0900,
	CL_CCW	= 0x0901,

	// GetPName
	CL_POINT_SIZE	= 0x0B11,
	CL_POINT_SIZE_RANGE	= 0x0B12,
	CL_POINT_SIZE_GRANULARITY	= 0x0B13,
	CL_LINE_SMOOTH	= 0x0B20,
	CL_LINE_WIDTH	= 0x0B21,
	CL_LINE_WIDTH_RANGE	= 0x0B22,
	CL_LINE_WIDTH_GRANULARITY	= 0x0B23,
	CL_POLYGON_SMOOTH	= 0x0B41,
	CL_CULL_FACE	= 0x0B44,
	CL_CULL_FACE_MODE	= 0x0B45,
	CL_FRONT_FACE	= 0x0B46,
	CL_DEPTH_RANGE	= 0x0B70,
	CL_DEPTH_TEST	= 0x0B71,
	CL_DEPTH_WRITEMASK	= 0x0B72,
	CL_DEPTH_CLEAR_VALUE	= 0x0B73,
	CL_DEPTH_FUNC	= 0x0B74,
	CL_STENCIL_TEST	= 0x0B90,
	CL_STENCIL_CLEAR_VALUE	= 0x0B91,
	CL_STENCIL_FUNC	= 0x0B92,
	CL_STENCIL_VALUE_MASK	= 0x0B93,
	CL_STENCIL_FAIL	= 0x0B94,
	CL_STENCIL_PASS_DEPTH_FAIL	= 0x0B95,
	CL_STENCIL_PASS_DEPTH_PASS	= 0x0B96,
	CL_STENCIL_REF	= 0x0B97,
	CL_STENCIL_WRITEMASK	= 0x0B98,
	CL_VIEWPORT	= 0x0BA2,
	CL_DITHER	= 0x0BD0,
	CL_BLEND_DST	= 0x0BE0,
	CL_BLEND_SRC	= 0x0BE1,
	CL_BLEND	= 0x0BE2,
	CL_LOGIC_OP_MODE	= 0x0BF0,
	CL_COLOR_LOGIC_OP	= 0x0BF2,
	CL_DRAW_BUFFER	= 0x0C01,
	CL_READ_BUFFER	= 0x0C02,
	CL_SCISSOR_BOX	= 0x0C10,
	CL_SCISSOR_TEST	= 0x0C11,
	CL_COLOR_CLEAR_VALUE	= 0x0C22,
	CL_COLOR_WRITEMASK	= 0x0C23,
	CL_DOUBLEBUFFER	= 0x0C32,
	CL_STEREO	= 0x0C33,
	CL_LINE_SMOOTH_HINT	= 0x0C52,
	CL_POLYGON_SMOOTH_HINT	= 0x0C53,
	CL_UNPACK_SWAP_BYTES	= 0x0CF0,
	CL_UNPACK_LSB_FIRST	= 0x0CF1,
	CL_UNPACK_ROW_LENGTH	= 0x0CF2,
	CL_UNPACK_SKIP_ROWS	= 0x0CF3,
	CL_UNPACK_SKIP_PIXELS	= 0x0CF4,
	CL_UNPACK_ALIGNMENT	= 0x0CF5,
	CL_PACK_SWAP_BYTES	= 0x0D00,
	CL_PACK_LSB_FIRST	= 0x0D01,
	CL_PACK_ROW_LENGTH	= 0x0D02,
	CL_PACK_SKIP_ROWS	= 0x0D03,
	CL_PACK_SKIP_PIXELS	= 0x0D04,
	CL_PACK_ALIGNMENT	= 0x0D05,
	CL_MAX_TEXTURE_SIZE	= 0x0D33,
	CL_MAX_VIEWPORT_DIMS	= 0x0D3A,
	CL_SUBPIXEL_BITS	= 0x0D50,
	CL_TEXTURE_1D	= 0x0DE0,
	CL_TEXTURE_2D	= 0x0DE1,
	CL_POLYGON_OFFSET_UNITS	= 0x2A00,
	CL_POLYGON_OFFSET_POINT	= 0x2A01,
	CL_POLYGON_OFFSET_LINE	= 0x2A02,
	CL_POLYGON_OFFSET_FILL	= 0x8037,
	CL_POLYGON_OFFSET_FACTOR	= 0x8038,
	CL_TEXTURE_BINDING_1D	= 0x8068,
	CL_TEXTURE_BINDING_2D	= 0x8069,

	// GetTextureParameter
	CL_TEXTURE_WIDTH	= 0x1000,
	CL_TEXTURE_HEIGHT	= 0x1001,
	CL_TEXTURE_INTERNAL_FORMAT	= 0x1003,
	CL_TEXTURE_BORDER_COLOR	= 0x1004,
	CL_TEXTURE_RED_SIZE	= 0x805C,
	CL_TEXTURE_GREEN_SIZE	= 0x805D,
	CL_TEXTURE_BLUE_SIZE	= 0x805E,
	CL_TEXTURE_ALPHA_SIZE	= 0x805F,

	// HintMode
	CL_DONT_CARE	= 0x1100,
	CL_FASTEST	= 0x1101,
	CL_NICEST	= 0x1102,

	// DataType
	CL_BYTE	= 0x1400,
	CL_UNSIGNED_BYTE	= 0x1401,
	CL_SHORT	= 0x1402,
	CL_UNSIGNED_SHORT	= 0x1403,
	CL_INT	= 0x1404,
	CL_UNSIGNED_INT	= 0x1405,
	CL_FLOAT	= 0x1406,
	CL_DOUBLE	= 0x140A,

	// LogicOp
	CL_CLEAR	= 0x1500,
	CL_AND	= 0x1501,
	CL_AND_REVERSE	= 0x1502,
	CL_COPY	= 0x1503,
	CL_AND_INVERTED	= 0x1504,
	CL_NOOP	= 0x1505,
	CL_XOR	= 0x1506,
	CL_OR	= 0x1507,
	CL_NOR	= 0x1508,
	CL_EQUIV	= 0x1509,
	CL_INVERT	= 0x150A,
	CL_OR_REVERSE	= 0x150B,
	CL_COPY_INVERTED	= 0x150C,
	CL_OR_INVERTED	= 0x150D,
	CL_NAND	= 0x150E,
	CL_SET	= 0x150F,

	// MatrixMode (for gl3.h, FBO attachment type)
	CL_TEXTURE	= 0x1702,

	// PixelCopyType
	CL_COLOR	= 0x1800,
	CL_DEPTH	= 0x1801,
	CL_STENCIL	= 0x1802,

	// PixelFormat
	CL_STENCIL_INDEX	= 0x1901,
	CL_DEPTH_COMPONENT	= 0x1902,
	CL_RED	= 0x1903,
	CL_GREEN	= 0x1904,
	CL_BLUE	= 0x1905,
	CL_ALPHA	= 0x1906,
	CL_RGB	= 0x1907,
	CL_RGBA	= 0x1908,

	// PolygonMode
	CL_POINT	= 0x1B00,
	CL_LINE	= 0x1B01,
	CL_FILL	= 0x1B02,

	// StencilOp
	CL_KEEP	= 0x1E00,
	CL_REPLACE	= 0x1E01,
	CL_INCR	= 0x1E02,
	CL_DECR	= 0x1E03,

	// StringName
	CL_VENDOR	= 0x1F00,
	CL_RENDERER	= 0x1F01,
	CL_VERSION	= 0x1F02,
	CL_EXTENSIONS	= 0x1F03,

	// TextureMagFilter
	CL_NEAREST	= 0x2600,
	CL_LINEAR	= 0x2601,

	// TextureMinFilter
	CL_NEAREST_MIPMAP_NEAREST	= 0x2700,
	CL_LINEAR_MIPMAP_NEAREST	= 0x2701,
	CL_NEAREST_MIPMAP_LINEAR	= 0x2702,
	CL_LINEAR_MIPMAP_LINEAR	= 0x2703,

	// TextureParameterName
	CL_TEXTURE_MAG_FILTER	= 0x2800,
	CL_TEXTURE_MIN_FILTER	= 0x2801,
	CL_TEXTURE_WRAP_S	= 0x2802,
	CL_TEXTURE_WRAP_T	= 0x2803,

	// TextureTarget
	CL_PROXY_TEXTURE_1D	= 0x8063,
	CL_PROXY_TEXTURE_2D	= 0x8064,

	// TextureWrapMode
	CL_REPEAT	= 0x2901,

	// PixelInternalFormat
	CL_R3_G3_B2	= 0x2A10,
	CL_RGB4	= 0x804F,
	CL_RGB5	= 0x8050,
	CL_RGB8	= 0x8051,
	CL_RGB10	= 0x8052,
	CL_RGB12	= 0x8053,
	CL_RGB16	= 0x8054,
	CL_RGBA2	= 0x8055,
	CL_RGBA4	= 0x8056,
	CL_RGB5_A1	= 0x8057,
	CL_RGBA8	= 0x8058,
	CL_RGB10_A2	= 0x8059,
	CL_RGBA12	= 0x805A,
	CL_RGBA16	= 0x805B,

	CL_UNSIGNED_BYTE_3_3_2	= 0x8032,
	CL_UNSIGNED_SHORT_4_4_4_4	= 0x8033,
	CL_UNSIGNED_SHORT_5_5_5_1	= 0x8034,
	CL_UNSIGNED_INT_8_8_8_8	= 0x8035,
	CL_UNSIGNED_INT_10_10_10_2	= 0x8036,
	CL_TEXTURE_BINDING_3D	= 0x806A,
	CL_PACK_SKIP_IMAGES	= 0x806B,
	CL_PACK_IMAGE_HEIGHT	= 0x806C,
	CL_UNPACK_SKIP_IMAGES	= 0x806D,
	CL_UNPACK_IMAGE_HEIGHT	= 0x806E,
	CL_TEXTURE_3D	= 0x806F,
	CL_PROXY_TEXTURE_3D	= 0x8070,
	CL_TEXTURE_DEPTH	= 0x8071,
	CL_TEXTURE_WRAP_R	= 0x8072,
	CL_MAX_3D_TEXTURE_SIZE	= 0x8073,
	CL_UNSIGNED_BYTE_2_3_3_REV	= 0x8362,
	CL_UNSIGNED_SHORT_5_6_5	= 0x8363,
	CL_UNSIGNED_SHORT_5_6_5_REV	= 0x8364,
	CL_UNSIGNED_SHORT_4_4_4_4_REV	= 0x8365,
	CL_UNSIGNED_SHORT_1_5_5_5_REV	= 0x8366,
	CL_UNSIGNED_INT_8_8_8_8_REV	= 0x8367,
	CL_UNSIGNED_INT_2_10_10_10_REV	= 0x8368,
	CL_BGR	= 0x80E0,
	CL_BGRA	= 0x80E1,
	CL_MAX_ELEMENTS_VERTICES	= 0x80E8,
	CL_MAX_ELEMENTS_INDICES	= 0x80E9,
	CL_CLAMP_TO_EDGE	= 0x812F,
	CL_TEXTURE_MIN_LOD	= 0x813A,
	CL_TEXTURE_MAX_LOD	= 0x813B,
	CL_TEXTURE_BASE_LEVEL	= 0x813C,
	CL_TEXTURE_MAX_LEVEL	= 0x813D,
	CL_SMOOTH_POINT_SIZE_RANGE	= 0x0B12,
	CL_SMOOTH_POINT_SIZE_GRANULARITY	= 0x0B13,
	CL_SMOOTH_LINE_WIDTH_RANGE	= 0x0B22,
	CL_SMOOTH_LINE_WIDTH_GRANULARITY	= 0x0B23,
	CL_ALIASED_LINE_WIDTH_RANGE	= 0x846E,

	CL_CONSTANT_COLOR	= 0x8001,
	CL_ONE_MINUS_CONSTANT_COLOR	= 0x8002,
	CL_CONSTANT_ALPHA	= 0x8003,
	CL_ONE_MINUS_CONSTANT_ALPHA	= 0x8004,
	CL_BLEND_COLOR	= 0x8005,
	CL_FUNC_ADD	= 0x8006,
	CL_MIN	= 0x8007,
	CL_MAX	= 0x8008,
	CL_BLEND_EQUATION	= 0x8009,
	CL_FUNC_SUBTRACT	= 0x800A,
	CL_FUNC_REVERSE_SUBTRACT	= 0x800B,

	CL_TEXTURE0	= 0x84C0,
	CL_TEXTURE1	= 0x84C1,
	CL_TEXTURE2	= 0x84C2,
	CL_TEXTURE3	= 0x84C3,
	CL_TEXTURE4	= 0x84C4,
	CL_TEXTURE5	= 0x84C5,
	CL_TEXTURE6	= 0x84C6,
	CL_TEXTURE7	= 0x84C7,
	CL_TEXTURE8	= 0x84C8,
	CL_TEXTURE9	= 0x84C9,
	CL_TEXTURE10	= 0x84CA,
	CL_TEXTURE11	= 0x84CB,
	CL_TEXTURE12	= 0x84CC,
	CL_TEXTURE13	= 0x84CD,
	CL_TEXTURE14	= 0x84CE,
	CL_TEXTURE15	= 0x84CF,
	CL_TEXTURE16	= 0x84D0,
	CL_TEXTURE17	= 0x84D1,
	CL_TEXTURE18	= 0x84D2,
	CL_TEXTURE19	= 0x84D3,
	CL_TEXTURE20	= 0x84D4,
	CL_TEXTURE21	= 0x84D5,
	CL_TEXTURE22	= 0x84D6,
	CL_TEXTURE23	= 0x84D7,
	CL_TEXTURE24	= 0x84D8,
	CL_TEXTURE25	= 0x84D9,
	CL_TEXTURE26	= 0x84DA,
	CL_TEXTURE27	= 0x84DB,
	CL_TEXTURE28	= 0x84DC,
	CL_TEXTURE29	= 0x84DD,
	CL_TEXTURE30	= 0x84DE,
	CL_TEXTURE31	= 0x84DF,
	CL_ACTIVE_TEXTURE	= 0x84E0,
	CL_MULTISAMPLE	= 0x809D,
	CL_SAMPLE_ALPHA_TO_COVERAGE	= 0x809E,
	CL_SAMPLE_ALPHA_TO_ONE	= 0x809F,
	CL_SAMPLE_COVERAGE	= 0x80A0,
	CL_SAMPLE_BUFFERS	= 0x80A8,
	CL_SAMPLES	= 0x80A9,
	CL_SAMPLE_COVERAGE_VALUE	= 0x80AA,
	CL_SAMPLE_COVERAGE_INVERT	= 0x80AB,
	CL_TEXTURE_CUBE_MAP	= 0x8513,
	CL_TEXTURE_BINDING_CUBE_MAP	= 0x8514,
	CL_TEXTURE_CUBE_MAP_POSITIVE_X	= 0x8515,
	CL_TEXTURE_CUBE_MAP_NEGATIVE_X	= 0x8516,
	CL_TEXTURE_CUBE_MAP_POSITIVE_Y	= 0x8517,
	CL_TEXTURE_CUBE_MAP_NEGATIVE_Y	= 0x8518,
	CL_TEXTURE_CUBE_MAP_POSITIVE_Z	= 0x8519,
	CL_TEXTURE_CUBE_MAP_NEGATIVE_Z	= 0x851A,
	CL_PROXY_TEXTURE_CUBE_MAP	= 0x851B,
	CL_MAX_CUBE_MAP_TEXTURE_SIZE	= 0x851C,
	CL_COMPRESSED_RGB	= 0x84ED,
	CL_COMPRESSED_RGBA	= 0x84EE,
	CL_TEXTURE_COMPRESSION_HINT	= 0x84EF,
	CL_TEXTURE_COMPRESSED_IMAGE_SIZE	= 0x86A0,
	CL_TEXTURE_COMPRESSED	= 0x86A1,
	CL_NUM_COMPRESSED_TEXTURE_FORMATS	= 0x86A2,
	CL_COMPRESSED_TEXTURE_FORMATS	= 0x86A3,
	CL_CLAMP_TO_BORDER	= 0x812D,

	CL_BLEND_DST_RGB	= 0x80C8,
	CL_BLEND_SRC_RGB	= 0x80C9,
	CL_BLEND_DST_ALPHA	= 0x80CA,
	CL_BLEND_SRC_ALPHA	= 0x80CB,
	CL_POINT_FADE_THRESHOLD_SIZE	= 0x8128,
	CL_DEPTH_COMPONENT16	= 0x81A5,
	CL_DEPTH_COMPONENT24	= 0x81A6,
	CL_DEPTH_COMPONENT32	= 0x81A7,
	CL_MIRRORED_REPEAT	= 0x8370,
	CL_MAX_TEXTURE_LOD_BIAS	= 0x84FD,
	CL_TEXTURE_LOD_BIAS	= 0x8501,
	CL_INCR_WRAP	= 0x8507,
	CL_DECR_WRAP	= 0x8508,
	CL_TEXTURE_DEPTH_SIZE	= 0x884A,
	CL_TEXTURE_COMPARE_MODE	= 0x884C,
	CL_TEXTURE_COMPARE_FUNC	= 0x884D,

	CL_BUFFER_SIZE	= 0x8764,
	CL_BUFFER_USAGE	= 0x8765,
	CL_QUERY_COUNTER_BITS	= 0x8864,
	CL_CURRENT_QUERY	= 0x8865,
	CL_QUERY_RESULT	= 0x8866,
	CL_QUERY_RESULT_AVAILABLE	= 0x8867,
	CL_ARRAY_BUFFER	= 0x8892,
	CL_ELEMENT_ARRAY_BUFFER	= 0x8893,
	CL_ARRAY_BUFFER_BINDING	= 0x8894,
	CL_ELEMENT_ARRAY_BUFFER_BINDING	= 0x8895,
	CL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING	= 0x889F,
	CL_READ_ONLY	= 0x88B8,
	CL_WRITE_ONLY	= 0x88B9,
	CL_READ_WRITE	= 0x88BA,
	CL_BUFFER_ACCESS	= 0x88BB,
	CL_BUFFER_MAPPED	= 0x88BC,
	CL_BUFFER_MAP_POINTER	= 0x88BD,
	CL_STREAM_DRAW	= 0x88E0,
	CL_STREAM_READ	= 0x88E1,
	CL_STREAM_COPY	= 0x88E2,
	CL_STATIC_DRAW	= 0x88E4,
	CL_STATIC_READ	= 0x88E5,
	CL_STATIC_COPY	= 0x88E6,
	CL_DYNAMIC_DRAW	= 0x88E8,
	CL_DYNAMIC_READ	= 0x88E9,
	CL_DYNAMIC_COPY	= 0x88EA,
	CL_SAMPLES_PASSED	= 0x8914,

	CL_BLEND_EQUATION_RGB	= 0x8009,
	CL_VERTEX_ATTRIB_ARRAY_ENABLED	= 0x8622,
	CL_VERTEX_ATTRIB_ARRAY_SIZE	= 0x8623,
	CL_VERTEX_ATTRIB_ARRAY_STRIDE	= 0x8624,
	CL_VERTEX_ATTRIB_ARRAY_TYPE	= 0x8625,
	CL_CURRENT_VERTEX_ATTRIB	= 0x8626,
	CL_VERTEX_PROGRAM_POINT_SIZE	= 0x8642,
	CL_VERTEX_ATTRIB_ARRAY_POINTER	= 0x8645,
	CL_STENCIL_BACK_FUNC	= 0x8800,
	CL_STENCIL_BACK_FAIL	= 0x8801,
	CL_STENCIL_BACK_PASS_DEPTH_FAIL	= 0x8802,
	CL_STENCIL_BACK_PASS_DEPTH_PASS	= 0x8803,
	CL_MAX_DRAW_BUFFERS	= 0x8824,
	CL_DRAW_BUFFER0	= 0x8825,
	CL_DRAW_BUFFER1	= 0x8826,
	CL_DRAW_BUFFER2	= 0x8827,
	CL_DRAW_BUFFER3	= 0x8828,
	CL_DRAW_BUFFER4	= 0x8829,
	CL_DRAW_BUFFER5	= 0x882A,
	CL_DRAW_BUFFER6	= 0x882B,
	CL_DRAW_BUFFER7	= 0x882C,
	CL_DRAW_BUFFER8	= 0x882D,
	CL_DRAW_BUFFER9	= 0x882E,
	CL_DRAW_BUFFER10	= 0x882F,
	CL_DRAW_BUFFER11	= 0x8830,
	CL_DRAW_BUFFER12	= 0x8831,
	CL_DRAW_BUFFER13	= 0x8832,
	CL_DRAW_BUFFER14	= 0x8833,
	CL_DRAW_BUFFER15	= 0x8834,
	CL_BLEND_EQUATION_ALPHA	= 0x883D,
	CL_MAX_VERTEX_ATTRIBS	= 0x8869,
	CL_VERTEX_ATTRIB_ARRAY_NORMALIZED	= 0x886A,
	CL_MAX_TEXTURE_IMAGE_UNITS	= 0x8872,
	CL_FRAGMENT_SHADER	= 0x8B30,
	CL_VERTEX_SHADER	= 0x8B31,
	CL_MAX_FRAGMENT_UNIFORM_COMPONENTS	= 0x8B49,
	CL_MAX_VERTEX_UNIFORM_COMPONENTS	= 0x8B4A,
	CL_MAX_VARYING_FLOATS	= 0x8B4B,
	CL_MAX_VERTEX_TEXTURE_IMAGE_UNITS	= 0x8B4C,
	CL_MAX_COMBINED_TEXTURE_IMAGE_UNITS	= 0x8B4D,
	CL_SHADER_TYPE	= 0x8B4F,
	CL_FLOAT_VEC2	= 0x8B50,
	CL_FLOAT_VEC3	= 0x8B51,
	CL_FLOAT_VEC4	= 0x8B52,
	CL_INT_VEC2	= 0x8B53,
	CL_INT_VEC3	= 0x8B54,
	CL_INT_VEC4	= 0x8B55,
	CL_BOOL	= 0x8B56,
	CL_BOOL_VEC2	= 0x8B57,
	CL_BOOL_VEC3	= 0x8B58,
	CL_BOOL_VEC4	= 0x8B59,
	CL_FLOAT_MAT2	= 0x8B5A,
	CL_FLOAT_MAT3	= 0x8B5B,
	CL_FLOAT_MAT4	= 0x8B5C,
	CL_SAMPLER_1D	= 0x8B5D,
	CL_SAMPLER_2D	= 0x8B5E,
	CL_SAMPLER_3D	= 0x8B5F,
	CL_SAMPLER_CUBE	= 0x8B60,
	CL_SAMPLER_1D_SHADOW	= 0x8B61,
	CL_SAMPLER_2D_SHADOW	= 0x8B62,
	CL_DELETE_STATUS	= 0x8B80,
	CL_COMPILE_STATUS	= 0x8B81,
	CL_LINK_STATUS	= 0x8B82,
	CL_VALIDATE_STATUS	= 0x8B83,
	CL_INFO_LOG_LENGTH	= 0x8B84,
	CL_ATTACHED_SHADERS	= 0x8B85,
	CL_ACTIVE_UNIFORMS	= 0x8B86,
	CL_ACTIVE_UNIFORM_MAX_LENGTH	= 0x8B87,
	CL_SHADER_SOURCE_LENGTH	= 0x8B88,
	CL_ACTIVE_ATTRIBUTES	= 0x8B89,
	CL_ACTIVE_ATTRIBUTE_MAX_LENGTH	= 0x8B8A,
	CL_FRAGMENT_SHADER_DERIVATIVE_HINT	= 0x8B8B,
	CL_SHADING_LANGUAGE_VERSION	= 0x8B8C,
	CL_CURRENT_PROGRAM	= 0x8B8D,
	CL_POINT_SPRITE_COORD_ORIGIN	= 0x8CA0,
	CL_LOWER_LEFT	= 0x8CA1,
	CL_UPPER_LEFT	= 0x8CA2,
	CL_STENCIL_BACK_REF	= 0x8CA3,
	CL_STENCIL_BACK_VALUE_MASK	= 0x8CA4,
	CL_STENCIL_BACK_WRITEMASK	= 0x8CA5,

	CL_PIXEL_PACK_BUFFER	= 0x88EB,
	CL_PIXEL_UNPACK_BUFFER	= 0x88EC,
	CL_PIXEL_PACK_BUFFER_BINDING	= 0x88ED,
	CL_PIXEL_UNPACK_BUFFER_BINDING	= 0x88EF,
	CL_FLOAT_MAT2x3	= 0x8B65,
	CL_FLOAT_MAT2x4	= 0x8B66,
	CL_FLOAT_MAT3x2	= 0x8B67,
	CL_FLOAT_MAT3x4	= 0x8B68,
	CL_FLOAT_MAT4x2	= 0x8B69,
	CL_FLOAT_MAT4x3	= 0x8B6A,
	CL_SRGB	= 0x8C40,
	CL_SRGB8	= 0x8C41,
	CL_SRGB_ALPHA	= 0x8C42,
	CL_SRGB8_ALPHA8	= 0x8C43,
	CL_COMPRESSED_SRGB	= 0x8C48,
	CL_COMPRESSED_SRGB_ALPHA	= 0x8C49,

	CL_COMPARE_REF_TO_TEXTURE	= 0x884E,
	CL_CLIP_DISTANCE0	= 0x3000,
	CL_CLIP_DISTANCE1	= 0x3001,
	CL_CLIP_DISTANCE2	= 0x3002,
	CL_CLIP_DISTANCE3	= 0x3003,
	CL_CLIP_DISTANCE4	= 0x3004,
	CL_CLIP_DISTANCE5	= 0x3005,
	CL_CLIP_DISTANCE6	= 0x3006,
	CL_CLIP_DISTANCE7	= 0x3007,
	CL_MAX_CLIP_DISTANCES	= 0x0D32,
	CL_MAJOR_VERSION	= 0x821B,
	CL_MINOR_VERSION	= 0x821C,
	CL_NUM_EXTENSIONS	= 0x821D,
	CL_CONTEXT_FLAGS	= 0x821E,
	CL_DEPTH_BUFFER	= 0x8223,
	CL_STENCIL_BUFFER	= 0x8224,
	CL_COMPRESSED_RED	= 0x8225,
	CL_COMPRESSED_RG	= 0x8226,
	CL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT	= 0x0001,
	CL_RGBA32F	= 0x8814,
	CL_RGB32F	= 0x8815,
	CL_RGBA16F	= 0x881A,
	CL_RGB16F	= 0x881B,
	CL_VERTEX_ATTRIB_ARRAY_INTEGER	= 0x88FD,
	CL_MAX_ARRAY_TEXTURE_LAYERS	= 0x88FF,
	CL_MIN_PROGRAM_TEXEL_OFFSET	= 0x8904,
	CL_MAX_PROGRAM_TEXEL_OFFSET	= 0x8905,
	CL_CLAMP_READ_COLOR	= 0x891C,
	CL_FIXED_ONLY	= 0x891D,
	CL_MAX_VARYING_COMPONENTS	= 0x8B4B,
	CL_TEXTURE_1D_ARRAY	= 0x8C18,
	CL_PROXY_TEXTURE_1D_ARRAY	= 0x8C19,
	CL_TEXTURE_2D_ARRAY	= 0x8C1A,
	CL_PROXY_TEXTURE_2D_ARRAY	= 0x8C1B,
	CL_TEXTURE_BINDING_1D_ARRAY	= 0x8C1C,
	CL_TEXTURE_BINDING_2D_ARRAY	= 0x8C1D,
	CL_R11F_G11F_B10F	= 0x8C3A,
	CL_UNSIGNED_INT_10F_11F_11F_REV	= 0x8C3B,
	CL_RGB9_E5	= 0x8C3D,
	CL_UNSIGNED_INT_5_9_9_9_REV	= 0x8C3E,
	CL_TEXTURE_SHARED_SIZE	= 0x8C3F,
	CL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH	= 0x8C76,
	CL_TRANSFORM_FEEDBACK_BUFFER_MODE	= 0x8C7F,
	CL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS	= 0x8C80,
	CL_TRANSFORM_FEEDBACK_VARYINGS	= 0x8C83,
	CL_TRANSFORM_FEEDBACK_BUFFER_START	= 0x8C84,
	CL_TRANSFORM_FEEDBACK_BUFFER_SIZE	= 0x8C85,
	CL_PRIMITIVES_GENERATED	= 0x8C87,
	CL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN	= 0x8C88,
	CL_RASTERIZER_DISCARD	= 0x8C89,
	CL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS	= 0x8C8A,
	CL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS	= 0x8C8B,
	CL_INTERLEAVED_ATTRIBS	= 0x8C8C,
	CL_SEPARATE_ATTRIBS	= 0x8C8D,
	CL_TRANSFORM_FEEDBACK_BUFFER	= 0x8C8E,
	CL_TRANSFORM_FEEDBACK_BUFFER_BINDING	= 0x8C8F,
	CL_RGBA32UI	= 0x8D70,
	CL_RGB32UI	= 0x8D71,
	CL_RGBA16UI	= 0x8D76,
	CL_RGB16UI	= 0x8D77,
	CL_RGBA8UI	= 0x8D7C,
	CL_RGB8UI	= 0x8D7D,
	CL_RGBA32I	= 0x8D82,
	CL_RGB32I	= 0x8D83,
	CL_RGBA16I	= 0x8D88,
	CL_RGB16I	= 0x8D89,
	CL_RGBA8I	= 0x8D8E,
	CL_RGB8I	= 0x8D8F,
	CL_RED_INTEGER	= 0x8D94,
	CL_GREEN_INTEGER	= 0x8D95,
	CL_BLUE_INTEGER	= 0x8D96,
	CL_RGB_INTEGER	= 0x8D98,
	CL_RGBA_INTEGER	= 0x8D99,
	CL_BGR_INTEGER	= 0x8D9A,
	CL_BGRA_INTEGER	= 0x8D9B,
	CL_SAMPLER_1D_ARRAY	= 0x8DC0,
	CL_SAMPLER_2D_ARRAY	= 0x8DC1,
	CL_SAMPLER_1D_ARRAY_SHADOW	= 0x8DC3,
	CL_SAMPLER_2D_ARRAY_SHADOW	= 0x8DC4,
	CL_SAMPLER_CUBE_SHADOW	= 0x8DC5,
	CL_UNSIGNED_INT_VEC2	= 0x8DC6,
	CL_UNSIGNED_INT_VEC3	= 0x8DC7,
	CL_UNSIGNED_INT_VEC4	= 0x8DC8,
	CL_INT_SAMPLER_1D	= 0x8DC9,
	CL_INT_SAMPLER_2D	= 0x8DCA,
	CL_INT_SAMPLER_3D	= 0x8DCB,
	CL_INT_SAMPLER_CUBE	= 0x8DCC,
	CL_INT_SAMPLER_1D_ARRAY	= 0x8DCE,
	CL_INT_SAMPLER_2D_ARRAY	= 0x8DCF,
	CL_UNSIGNED_INT_SAMPLER_1D	= 0x8DD1,
	CL_UNSIGNED_INT_SAMPLER_2D	= 0x8DD2,
	CL_UNSIGNED_INT_SAMPLER_3D	= 0x8DD3,
	CL_UNSIGNED_INT_SAMPLER_CUBE	= 0x8DD4,
	CL_UNSIGNED_INT_SAMPLER_1D_ARRAY	= 0x8DD6,
	CL_UNSIGNED_INT_SAMPLER_2D_ARRAY	= 0x8DD7,
	CL_QUERY_WAIT	= 0x8E13,
	CL_QUERY_NO_WAIT	= 0x8E14,
	CL_QUERY_BY_REGION_WAIT	= 0x8E15,
	CL_QUERY_BY_REGION_NO_WAIT	= 0x8E16,
	CL_BUFFER_ACCESS_FLAGS	= 0x911F,
	CL_BUFFER_MAP_LENGTH	= 0x9120,
	CL_BUFFER_MAP_OFFSET	= 0x9121,

	CL_SAMPLER_2D_RECT	= 0x8B63,
	CL_SAMPLER_2D_RECT_SHADOW	= 0x8B64,
	CL_SAMPLER_BUFFER	= 0x8DC2,
	CL_INT_SAMPLER_2D_RECT	= 0x8DCD,
	CL_INT_SAMPLER_BUFFER	= 0x8DD0,
	CL_UNSIGNED_INT_SAMPLER_2D_RECT	= 0x8DD5,
	CL_UNSIGNED_INT_SAMPLER_BUFFER	= 0x8DD8,
	CL_TEXTURE_BUFFER	= 0x8C2A,
	CL_MAX_TEXTURE_BUFFER_SIZE	= 0x8C2B,
	CL_TEXTURE_BINDING_BUFFER	= 0x8C2C,
	CL_TEXTURE_BUFFER_DATA_STORE_BINDING	= 0x8C2D,
	CL_TEXTURE_BUFFER_FORMAT	= 0x8C2E,
	CL_TEXTURE_RECTANGLE	= 0x84F5,
	CL_TEXTURE_BINDING_RECTANGLE	= 0x84F6,
	CL_PROXY_TEXTURE_RECTANGLE	= 0x84F7,
	CL_MAX_RECTANGLE_TEXTURE_SIZE	= 0x84F8,
	CL_RED_SNORM	= 0x8F90,
	CL_RG_SNORM	= 0x8F91,
	CL_RGB_SNORM	= 0x8F92,
	CL_RGBA_SNORM	= 0x8F93,
	CL_R8_SNORM	= 0x8F94,
	CL_RG8_SNORM	= 0x8F95,
	CL_RGB8_SNORM	= 0x8F96,
	CL_RGBA8_SNORM	= 0x8F97,
	CL_R16_SNORM	= 0x8F98,
	CL_RG16_SNORM	= 0x8F99,
	CL_RGB16_SNORM	= 0x8F9A,
	CL_RGBA16_SNORM	= 0x8F9B,
	CL_SIGNED_NORMALIZED	= 0x8F9C,
	CL_PRIMITIVE_RESTART	= 0x8F9D,
	CL_PRIMITIVE_RESTART_INDEX	= 0x8F9E,

	CL_CONTEXT_CORE_PROFILE_BIT	= 0x00000001,
	CL_CONTEXT_COMPATIBILITY_PROFILE_BIT	= 0x00000002,
	CL_LINES_ADJACENCY	= 0x000A,
	CL_LINE_STRIP_ADJACENCY	= 0x000B,
	CL_TRIANGLES_ADJACENCY	= 0x000C,
	CL_TRIANGLE_STRIP_ADJACENCY	= 0x000D,
	CL_PROGRAM_POINT_SIZE	= 0x8642,
	CL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS	= 0x8C29,
	CL_FRAMEBUFFER_ATTACHMENT_LAYERED	= 0x8DA7,
	CL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS	= 0x8DA8,
	CL_GEOMETRY_SHADER	= 0x8DD9,
	CL_GEOMETRY_VERTICES_OUT	= 0x8916,
	CL_GEOMETRY_INPUT_TYPE	= 0x8917,
	CL_GEOMETRY_OUTPUT_TYPE	= 0x8918,
	CL_MAX_GEOMETRY_UNIFORM_COMPONENTS	= 0x8DDF,
	CL_MAX_GEOMETRY_OUTPUT_VERTICES	= 0x8DE0,
	CL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS	= 0x8DE1,
	CL_MAX_VERTEX_OUTPUT_COMPONENTS	= 0x9122,
	CL_MAX_GEOMETRY_INPUT_COMPONENTS	= 0x9123,
	CL_MAX_GEOMETRY_OUTPUT_COMPONENTS	= 0x9124,
	CL_MAX_FRAGMENT_INPUT_COMPONENTS	= 0x9125,
	CL_CONTEXT_PROFILE_MASK	= 0x9126,

	CL_DEPTH_COMPONENT32F	= 0x8CAC,
	CL_DEPTH32F_STENCIL8	= 0x8CAD,
	CL_FLOAT_32_UNSIGNED_INT_24_8_REV	= 0x8DAD,

	CL_INVALID_FRAMEBUFFER_OPERATION	= 0x0506,
	CL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING	= 0x8210,
	CL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE	= 0x8211,
	CL_FRAMEBUFFER_ATTACHMENT_RED_SIZE	= 0x8212,
	CL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE	= 0x8213,
	CL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE	= 0x8214,
	CL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE	= 0x8215,
	CL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE	= 0x8216,
	CL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE	= 0x8217,
	CL_FRAMEBUFFER_DEFAULT	= 0x8218,
	CL_FRAMEBUFFER_UNDEFINED	= 0x8219,
	CL_DEPTH_STENCIL_ATTACHMENT	= 0x821A,
	CL_MAX_RENDERBUFFER_SIZE	= 0x84E8,
	CL_DEPTH_STENCIL	= 0x84F9,
	CL_UNSIGNED_INT_24_8	= 0x84FA,
	CL_DEPTH24_STENCIL8	= 0x88F0,
	CL_TEXTURE_STENCIL_SIZE	= 0x88F1,
	CL_TEXTURE_RED_TYPE	= 0x8C10,
	CL_TEXTURE_GREEN_TYPE	= 0x8C11,
	CL_TEXTURE_BLUE_TYPE	= 0x8C12,
	CL_TEXTURE_ALPHA_TYPE	= 0x8C13,
	CL_TEXTURE_DEPTH_TYPE	= 0x8C16,
	CL_UNSIGNED_NORMALIZED	= 0x8C17,
	CL_FRAMEBUFFER_BINDING	= 0x8CA6,
	CL_DRAW_FRAMEBUFFER_BINDING	= CL_FRAMEBUFFER_BINDING,
	CL_RENDERBUFFER_BINDING	= 0x8CA7,
	CL_READ_FRAMEBUFFER	= 0x8CA8,
	CL_DRAW_FRAMEBUFFER	= 0x8CA9,
	CL_READ_FRAMEBUFFER_BINDING	= 0x8CAA,
	CL_RENDERBUFFER_SAMPLES	= 0x8CAB,
	CL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE	= 0x8CD0,
	CL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME	= 0x8CD1,
	CL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL	= 0x8CD2,
	CL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE	= 0x8CD3,
	CL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER	= 0x8CD4,
	CL_FRAMEBUFFER_COMPLETE	= 0x8CD5,
	CL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT	= 0x8CD6,
	CL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT	= 0x8CD7,
	CL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER	= 0x8CDB,
	CL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER	= 0x8CDC,
	CL_FRAMEBUFFER_UNSUPPORTED	= 0x8CDD,
	CL_MAX_COLOR_ATTACHMENTS	= 0x8CDF,
	CL_COLOR_ATTACHMENT0	= 0x8CE0,
	CL_COLOR_ATTACHMENT1	= 0x8CE1,
	CL_COLOR_ATTACHMENT2	= 0x8CE2,
	CL_COLOR_ATTACHMENT3	= 0x8CE3,
	CL_COLOR_ATTACHMENT4	= 0x8CE4,
	CL_COLOR_ATTACHMENT5	= 0x8CE5,
	CL_COLOR_ATTACHMENT6	= 0x8CE6,
	CL_COLOR_ATTACHMENT7	= 0x8CE7,
	CL_COLOR_ATTACHMENT8	= 0x8CE8,
	CL_COLOR_ATTACHMENT9	= 0x8CE9,
	CL_COLOR_ATTACHMENT10	= 0x8CEA,
	CL_COLOR_ATTACHMENT11	= 0x8CEB,
	CL_COLOR_ATTACHMENT12	= 0x8CEC,
	CL_COLOR_ATTACHMENT13	= 0x8CED,
	CL_COLOR_ATTACHMENT14	= 0x8CEE,
	CL_COLOR_ATTACHMENT15	= 0x8CEF,
	CL_DEPTH_ATTACHMENT	= 0x8D00,
	CL_STENCIL_ATTACHMENT	= 0x8D20,
	CL_FRAMEBUFFER	= 0x8D40,
	CL_RENDERBUFFER	= 0x8D41,
	CL_RENDERBUFFER_WIDTH	= 0x8D42,
	CL_RENDERBUFFER_HEIGHT	= 0x8D43,
	CL_RENDERBUFFER_INTERNAL_FORMAT	= 0x8D44,
	CL_STENCIL_INDEX1	= 0x8D46,
	CL_STENCIL_INDEX4	= 0x8D47,
	CL_STENCIL_INDEX8	= 0x8D48,
	CL_STENCIL_INDEX16	= 0x8D49,
	CL_RENDERBUFFER_RED_SIZE	= 0x8D50,
	CL_RENDERBUFFER_GREEN_SIZE	= 0x8D51,
	CL_RENDERBUFFER_BLUE_SIZE	= 0x8D52,
	CL_RENDERBUFFER_ALPHA_SIZE	= 0x8D53,
	CL_RENDERBUFFER_DEPTH_SIZE	= 0x8D54,
	CL_RENDERBUFFER_STENCIL_SIZE	= 0x8D55,
	CL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE	= 0x8D56,
	CL_MAX_SAMPLES	= 0x8D57,

	CL_FRAMEBUFFER_SRGB	= 0x8DB9,

	CL_HALF_FLOAT	= 0x140B,

	CL_MAP_READ_BIT	= 0x0001,
	CL_MAP_WRITE_BIT	= 0x0002,
	CL_MAP_INVALIDATE_RANGE_BIT	= 0x0004,
	CL_MAP_INVALIDATE_BUFFER_BIT	= 0x0008,
	CL_MAP_FLUSH_EXPLICIT_BIT	= 0x0010,
	CL_MAP_UNSYNCHRONIZED_BIT	= 0x0020,

	CL_COMPRESSED_RED_RGTC1	= 0x8DBB,
	CL_COMPRESSED_SIGNED_RED_RGTC1	= 0x8DBC,
	CL_COMPRESSED_RG_RGTC2	= 0x8DBD,
	CL_COMPRESSED_SIGNED_RG_RGTC2	= 0x8DBE,

	CL_RG	= 0x8227,
	CL_RG_INTEGER	= 0x8228,
	CL_R8	= 0x8229,
	CL_R16	= 0x822A,
	CL_RG8	= 0x822B,
	CL_RG16	= 0x822C,
	CL_R16F	= 0x822D,
	CL_R32F	= 0x822E,
	CL_RG16F	= 0x822F,
	CL_RG32F	= 0x8230,
	CL_R8I	= 0x8231,
	CL_R8UI	= 0x8232,
	CL_R16I	= 0x8233,
	CL_R16UI	= 0x8234,
	CL_R32I	= 0x8235,
	CL_R32UI	= 0x8236,
	CL_RG8I	= 0x8237,
	CL_RG8UI	= 0x8238,
	CL_RG16I	= 0x8239,
	CL_RG16UI	= 0x823A,
	CL_RG32I	= 0x823B,
	CL_RG32UI	= 0x823C,

	CL_VERTEX_ARRAY_BINDING	= 0x85B5,

	CL_UNIFORM_BUFFER	= 0x8A11,
	CL_UNIFORM_BUFFER_BINDING	= 0x8A28,
	CL_UNIFORM_BUFFER_START	= 0x8A29,
	CL_UNIFORM_BUFFER_SIZE	= 0x8A2A,
	CL_MAX_VERTEX_UNIFORM_BLOCKS	= 0x8A2B,
	CL_MAX_GEOMETRY_UNIFORM_BLOCKS	= 0x8A2C,
	CL_MAX_FRAGMENT_UNIFORM_BLOCKS	= 0x8A2D,
	CL_MAX_COMBINED_UNIFORM_BLOCKS	= 0x8A2E,
	CL_MAX_UNIFORM_BUFFER_BINDINGS	= 0x8A2F,
	CL_MAX_UNIFORM_BLOCK_SIZE	= 0x8A30,
	CL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS	= 0x8A31,
	CL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS	= 0x8A32,
	CL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS	= 0x8A33,
	CL_UNIFORM_BUFFER_OFFSET_ALIGNMENT	= 0x8A34,
	CL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH	= 0x8A35,
	CL_ACTIVE_UNIFORM_BLOCKS	= 0x8A36,
	CL_UNIFORM_TYPE	= 0x8A37,
	CL_UNIFORM_SIZE	= 0x8A38,
	CL_UNIFORM_NAME_LENGTH	= 0x8A39,
	CL_UNIFORM_BLOCK_INDEX	= 0x8A3A,
	CL_UNIFORM_OFFSET	= 0x8A3B,
	CL_UNIFORM_ARRAY_STRIDE	= 0x8A3C,
	CL_UNIFORM_MATRIX_STRIDE	= 0x8A3D,
	CL_UNIFORM_IS_ROW_MAJOR	= 0x8A3E,
	CL_UNIFORM_BLOCK_BINDING	= 0x8A3F,
	CL_UNIFORM_BLOCK_DATA_SIZE	= 0x8A40,
	CL_UNIFORM_BLOCK_NAME_LENGTH	= 0x8A41,
	CL_UNIFORM_BLOCK_ACTIVE_UNIFORMS	= 0x8A42,
	CL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES	= 0x8A43,
	CL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER	= 0x8A44,
	CL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER	= 0x8A45,
	CL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER	= 0x8A46,
	CL_INVALID_INDEX	= 0xFFFFFFFFu,

	CL_COPY_READ_BUFFER	= 0x8F36,
	CL_COPY_WRITE_BUFFER	= 0x8F37,

	CL_DEPTH_CLAMP	= 0x864F,

	CL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION	= 0x8E4C,
	CL_FIRST_VERTEX_CONVENTION	= 0x8E4D,
	CL_LAST_VERTEX_CONVENTION	= 0x8E4E,
	CL_PROVOKING_VERTEX	= 0x8E4F,

	CL_TEXTURE_CUBE_MAP_SEAMLESS	= 0x884F,

	CL_MAX_SERVER_WAIT_TIMEOUT	= 0x9111,
	CL_OBJECT_TYPE	= 0x9112,
	CL_SYNC_CONDITION	= 0x9113,
	CL_SYNC_STATUS	= 0x9114,
	CL_SYNC_FLAGS	= 0x9115,
	CL_SYNC_FENCE	= 0x9116,
	CL_SYNC_GPU_COMMANDS_COMPLETE	= 0x9117,
	CL_UNSIGNALED	= 0x9118,
	CL_SIGNALED	= 0x9119,
	CL_ALREADY_SIGNALED	= 0x911A,
	CL_TIMEOUT_EXPIRED	= 0x911B,
	CL_CONDITION_SATISFIED	= 0x911C,
	CL_WAIT_FAILED	= 0x911D,
	CL_SYNC_FLUSH_COMMANDS_BIT	= 0x00000001,
	CL_TIMEOUT_IGNORED	= 0xFFFFFFFFFFFFFFFFull,

	CL_SAMPLE_POSITION	= 0x8E50,
	CL_SAMPLE_MASK	= 0x8E51,
	CL_SAMPLE_MASK_VALUE	= 0x8E52,
	CL_MAX_SAMPLE_MASK_WORDS	= 0x8E59,
	CL_TEXTURE_2D_MULTISAMPLE	= 0x9100,
	CL_PROXY_TEXTURE_2D_MULTISAMPLE	= 0x9101,
	CL_TEXTURE_2D_MULTISAMPLE_ARRAY	= 0x9102,
	CL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY	= 0x9103,
	CL_TEXTURE_BINDING_2D_MULTISAMPLE	= 0x9104,
	CL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY	= 0x9105,
	CL_TEXTURE_SAMPLES	= 0x9106,
	CL_TEXTURE_FIXED_SAMPLE_LOCATIONS	= 0x9107,
	CL_SAMPLER_2D_MULTISAMPLE	= 0x9108,
	CL_INT_SAMPLER_2D_MULTISAMPLE	= 0x9109,
	CL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE	= 0x910A,
	CL_SAMPLER_2D_MULTISAMPLE_ARRAY	= 0x910B,
	CL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY	= 0x910C,
	CL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY	= 0x910D,
	CL_MAX_COLOR_TEXTURE_SAMPLES	= 0x910E,
	CL_MAX_DEPTH_TEXTURE_SAMPLES	= 0x910F,
	CL_MAX_INTEGER_SAMPLES	= 0x9110,



	CL_SAMPLE_SHADING	= 0x8C36,
	CL_MIN_SAMPLE_SHADING_VALUE	= 0x8C37,

	CL_TEXTURE_CUBE_MAP_ARRAY	= 0x9009,
	CL_TEXTURE_BINDING_CUBE_MAP_ARRAY	= 0x900A,
	CL_PROXY_TEXTURE_CUBE_MAP_ARRAY	= 0x900B,
	CL_SAMPLER_CUBE_MAP_ARRAY	= 0x900C,
	CL_SAMPLER_CUBE_MAP_ARRAY_SHADOW	= 0x900D,
	CL_INT_SAMPLER_CUBE_MAP_ARRAY	= 0x900E,
	CL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY	= 0x900F,

	CL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET_ARB	= 0x8E5E,
	CL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET_ARB	= 0x8E5F,

	CL_SRC1_COLOR	= 0x88F9,
	CL_ONE_MINUS_SRC1_COLOR	= 0x88FA,
	CL_ONE_MINUS_SRC1_ALPHA	= 0x88FB,
	CL_MAX_DUAL_SOURCE_DRAW_BUFFERS	= 0x88FC,

	CL_ANY_SAMPLES_PASSED	= 0x8C2F,

	CL_SAMPLER_BINDING	= 0x8919,

	CL_RGB10_A2UI	= 0x906F,

	CL_TEXTURE_SWIZZLE_R	= 0x8E42,
	CL_TEXTURE_SWIZZLE_G	= 0x8E43,
	CL_TEXTURE_SWIZZLE_B	= 0x8E44,
	CL_TEXTURE_SWIZZLE_A	= 0x8E45,
	CL_TEXTURE_SWIZZLE_RGBA	= 0x8E46,

	CL_TIME_ELAPSED	= 0x88BF,
	CL_TIMESTAMP	= 0x8E28,

	CL_INT_2_10_10_10_REV	= 0x8D9F,

	CL_DRAW_INDIRECT_BUFFER	= 0x8F3F,
	CL_DRAW_INDIRECT_BUFFER_BINDING	= 0x8F43,

	CL_GEOMETRY_SHADER_INVOCATIONS	= 0x887F,
	CL_MAX_GEOMETRY_SHADER_INVOCATIONS	= 0x8E5A,
	CL_MIN_FRAGMENT_INTERPOLATION_OFFSET	= 0x8E5B,
	CL_MAX_FRAGMENT_INTERPOLATION_OFFSET	= 0x8E5C,
	CL_FRAGMENT_INTERPOLATION_OFFSET_BITS	= 0x8E5D,
	CL_MAX_VERTEX_STREAMS	= 0x8E71,

	CL_DOUBLE_VEC2	= 0x8FFC,
	CL_DOUBLE_VEC3	= 0x8FFD,
	CL_DOUBLE_VEC4	= 0x8FFE,
	CL_DOUBLE_MAT2	= 0x8F46,
	CL_DOUBLE_MAT3	= 0x8F47,
	CL_DOUBLE_MAT4	= 0x8F48,
	CL_DOUBLE_MAT2x3	= 0x8F49,
	CL_DOUBLE_MAT2x4	= 0x8F4A,
	CL_DOUBLE_MAT3x2	= 0x8F4B,
	CL_DOUBLE_MAT3x4	= 0x8F4C,
	CL_DOUBLE_MAT4x2	= 0x8F4D,
	CL_DOUBLE_MAT4x3	= 0x8F4E,

	CL_ACTIVE_SUBROUTINES	= 0x8DE5,
	CL_ACTIVE_SUBROUTINE_UNIFORMS	= 0x8DE6,
	CL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS	= 0x8E47,
	CL_ACTIVE_SUBROUTINE_MAX_LENGTH	= 0x8E48,
	CL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH	= 0x8E49,
	CL_MAX_SUBROUTINES	= 0x8DE7,
	CL_MAX_SUBROUTINE_UNIFORM_LOCATIONS	= 0x8DE8,
	CL_NUM_COMPATIBLE_SUBROUTINES	= 0x8E4A,
	CL_COMPATIBLE_SUBROUTINES	= 0x8E4B,

	CL_PATCHES	= 0x000E,
	CL_PATCH_VERTICES	= 0x8E72,
	CL_PATCH_DEFAULT_INNER_LEVEL	= 0x8E73,
	CL_PATCH_DEFAULT_OUTER_LEVEL	= 0x8E74,
	CL_TESS_CONTROL_OUTPUT_VERTICES	= 0x8E75,
	CL_TESS_GEN_MODE	= 0x8E76,
	CL_TESS_GEN_SPACING	= 0x8E77,
	CL_TESS_GEN_VERTEX_ORDER	= 0x8E78,
	CL_TESS_GEN_POINT_MODE	= 0x8E79,
	CL_ISOLINES	= 0x8E7A,
	CL_FRACTIONAL_ODD	= 0x8E7B,
	CL_FRACTIONAL_EVEN	= 0x8E7C,
	CL_MAX_PATCH_VERTICES	= 0x8E7D,
	CL_MAX_TESS_GEN_LEVEL	= 0x8E7E,
	CL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS	= 0x8E7F,
	CL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS	= 0x8E80,
	CL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS	= 0x8E81,
	CL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS	= 0x8E82,
	CL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS	= 0x8E83,
	CL_MAX_TESS_PATCH_COMPONENTS	= 0x8E84,
	CL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS	= 0x8E85,
	CL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS	= 0x8E86,
	CL_MAX_TESS_CONTROL_UNIFORM_BLOCKS	= 0x8E89,
	CL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS	= 0x8E8A,
	CL_MAX_TESS_CONTROL_INPUT_COMPONENTS	= 0x886C,
	CL_MAX_TESS_EVALUATION_INPUT_COMPONENTS	= 0x886D,
	CL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS	= 0x8E1E,
	CL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS	= 0x8E1F,
	CL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER	= 0x84F0,
	CL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER	= 0x84F1,
	CL_TESS_EVALUATION_SHADER	= 0x8E87,
	CL_TESS_CONTROL_SHADER	= 0x8E88,

	CL_TRANSFORM_FEEDBACK	= 0x8E22,
	CL_TRANSFORM_FEEDBACK_BUFFER_PAUSED	= 0x8E23,
	CL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE	= 0x8E24,
	CL_TRANSFORM_FEEDBACK_BINDING	= 0x8E25,

	CL_MAX_TRANSFORM_FEEDBACK_BUFFERS	= 0x8E70,

//------------------------------------------------------------------------------
// Legacy defines to be removed when graphics cards drivers support the new defines

	// ARB_geometry_shader4
	CL_GEOMETRY_VERTICES_OUT_ARB = 0x8DDA,
	CL_GEOMETRY_INPUT_TYPE_ARB = 0x8DDB,
	CL_GEOMETRY_OUTPUT_TYPE_ARB = 0x8DDC,
	CL_MAX_GEOMETRY_VARYING_COMPONENTS_ARB = 0x8DDD,
	CL_MAX_VERTEX_VARYING_COMPONENTS_ARB = 0x8DDE,
	CL_MAX_GEOMETRY_UNIFORM_COMPONENTS_ARB = 0x8DDF,
	CL_MAX_GEOMETRY_OUTPUT_VERTICES_ARB = 0x8DE0,
	CL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_ARB = 0x8DE1,

//------------------------------------------------------------------------------
// Extensions not in the specification

	// EXT_texture_filter_anisotropic
	CL_TEXTURE_MAX_ANISOTROPY_EXT	= 0x84FE,
	CL_MAX_TEXTURE_MAX_ANISOTROPY_EXT = 0x84FF
};

#endif

/// \}


