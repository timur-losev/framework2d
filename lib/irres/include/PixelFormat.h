#ifndef PixelFormat_h__
#define PixelFormat_h__

#include "irrTypes.h"
#include "SColor.h"

namespace irr { namespace video {

/** A color format specifies how color information is stored. */

struct SPixelFormatDescription
{
    enum E_COMPONENT_INDEX
    {
        RED = 0,
        GREEN = 1,
        BLUE = 2,
        ALPHA = 3
    };

    u32 Flags;
    u32 Masks[4];
    u8 Type;
    u8 ByteCount;
    u8 BitsPerPixel;
    u8 ComponentCount;
    u8 Bits[4];
    u8 Shifts[4];
    u8 Indices[4];
    u8 BlockSize[3];
    u8 MinSize;
};

const SPixelFormatDescription PFDTable[ECF_COUNT] = {
    {
		/* Flags */
		EPFF_LUMINANCE,
		/* Masks */
		{0xFF, 0xFF, 0xFF, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		1,
		/* Bits per Pixel */
		8,
		/* Component Count */
		1,
		/* Bit Counts */
		{8, 8, 8, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{0, 0, 0, u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_L16
	{
		/* Flags */
		EPFF_LUMINANCE,
		/* Masks */
		{0xFFFF, 0xFFFF, 0xFFFF, 0},
		/* Type */
		EPCT_SHORT,
		/* Byte Count */
		2,
		/* Bits per Pixel */
		16,
		/* Component Count */
		1,
		/* Bit Counts */
		{16, 16, 16, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{0, 0, 0, u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_A8
	{
		/* Flags */
		EPFF_ALPHA,
		/* Masks */
		{0, 0, 0, 0xFF},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		1,
		/* Bits per Pixel */
		8,
		/* Component Count */
		1,
		/* Bit Counts */
		{0, 0, 0, 8},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), 0},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_A8L8
	{
		/* Flags */
		EPFF_LUMINANCE | EPFF_ALPHA,
		/* Masks */
		{0xFF00, 0xFF00, 0xFF00, 0x00FF},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		2,
		/* Bits per Pixel */
		16,
		/* Component Count */
		2,
		/* Bit Counts */
		{8, 0, 0, 8},
		/* Shifts */
		{8, 0, 0, 0},
		/* Indices */
		{1, 1, 1, 0},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_L8A8
	{
		/* Flags */
		EPFF_LUMINANCE | EPFF_ALPHA,
		/* Masks */
		{0x00FF, 0x00FF, 0x00FF, 0xFF00},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		2,
		/* Bits per Pixel */
		16,
		/* Component Count */
		2,
		/* Bit Counts */
		{8, 0, 0, 8},
		/* Shifts */
		{0, 0, 0, 8},
		/* Indices */
		{0, 0, 0, 1},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_R5G6B5
	{
		/* Flags */
		EPFF_PACKED,
		/* Masks */
		{0xF800, 0x07E0, 0x001F, 0},
		/* Type */
		EPCT_SHORT,
		/* Byte Count */
		2,
		/* Bits per Pixel */
		16,
		/* Component Count */
		3,
		/* Bit Counts */
		{5, 6, 5, 0},
		/* Shifts */
		{11, 5, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_A4R4G4B4
	{
		/* Flags */
		EPFF_ALPHA | EPFF_PACKED,
		/* Masks */
		{0x0F00, 0x00F0, 0x000F, 0xF000},
		/* Type */
		EPCT_SHORT,
		/* Byte Count */
		2,
		/* Bits per Pixel */
		16,
		/* Component Count */
		4,
		/* Bit Counts */
		{4, 4, 4, 4},
		/* Shifts */
		{8, 4, 0, 12},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_R4G4B4A4
	{
		/* Flags */
		EPFF_ALPHA | EPFF_PACKED,
		/* Masks */
		{0xF000, 0x0F00, 0x00F0, 0x000F},
		/* Type */
		EPCT_SHORT,
		/* Byte Count */
		2,
		/* Bits per Pixel */
		16,
		/* Component Count */
		4,
		/* Bit Counts */
		{4, 4, 4, 4},
		/* Shifts */
		{12, 8, 4, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
 	// EPF_A1R5G5B5
	{
		/* Flags */
		EPFF_ALPHA | EPFF_PACKED,
		/* Masks */
		{0x7C00, 0x03E0, 0x001F, 0x8000},
		/* Type */
		EPCT_SHORT,
		/* Byte Count */
		2,
		/* Bits per Pixel */
		16,
		/* Component Count */
		4,
		/* Bit Counts */
		{5, 5, 5, 1},
		/* Shifts */
		{10, 5, 0, 15},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_R5G5B5A1
	{
		/* Flags */
		EPFF_ALPHA | EPFF_PACKED,
		/* Masks */
		{0xF800, 0x07C0, 0x003E, 0x0001},
		/* Type */
		EPCT_SHORT,
		/* Byte Count */
		2,
		/* Bits per Pixel */
		16,
		/* Component Count */
		4,
		/* Bit Counts */
		{5, 5, 5, 1},
		/* Shifts */
		{11, 6, 1, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_R8G8B8
	{
		/* Flags */
		0,
		/* Masks */
		{0x000000FF, 0x0000FF00, 0x00FF0000, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		3,
		/* Bits per Pixel */
		24,
		/* Component Count */
		3,
		/* Bit Counts */
		{8, 8, 8, 0},
		/* Shifts */
		{0, 8, 16, 0},
		/* Indices */
		{0, 1, 2, u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_B8G8R8
	{
		/* Flags */
		0,
		/* Masks */
		{0x00FF0000, 0x0000FF00, 0x000000FF, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		3,
		/* Bits per Pixel */
		24,
		/* Component Count */
		3,
		/* Bit Counts */
		{8, 8, 8, 0},
		/* Shifts */
		{16, 8, 0, 0},
		/* Indices */
		{2, 1, 0, u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_A8R8G8B8
	{
		/* Flags */
		EPFF_ALPHA,
		/* Masks */
		{0x0000FF00, 0x00FF0000, 0xFF000000, 0x000000FF},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		4,
		/* Bits per Pixel */
		32,
		/* Component Count */
		4,
		/* Bit Counts */
		{8, 8, 8, 8},
		/* Shifts */
		{8, 16, 24, 0},
		/* Indices */
		{1, 2, 3, 0},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
    // EPF_B8G8R8A8
	{
		/* Flags */
		EPFF_ALPHA,
		/* Masks */
		{0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		4,
		/* Bits per Pixel */
		32,
		/* Component Count */
		4,
		/* Bit Counts */
		{8, 8, 8, 8},
		/* Shifts */
		{16, 8, 0, 24},
		/* Indices */
		{2, 1, 0, 3},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
    // EPF_R8G8B8A8
	{
		/* Flags */
		EPFF_ALPHA,
		/* Masks */
		{0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		4,
		/* Bits per Pixel */
		32,
		/* Component Count */
		4,
		/* Bit Counts */
		{8, 8, 8, 8},
		/* Shifts */
		{0, 8, 16, 24},
		/* Indices */
		{0, 1, 2, 3},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
    // EPF_A8B8G8R8
	{
		/* Flags */
		EPFF_ALPHA,
		/* Masks */
		{0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		4,
		/* Bits per Pixel */
		32,
		/* Component Count */
		4,
		/* Bit Counts */
		{8, 8, 8, 8},
		/* Shifts */
		{24, 16, 8, 0},
		/* Indices */
		{3, 2, 1, 0},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_A2B10G10R10
	{
		/* Flags */
		EPFF_ALPHA | EPFF_PACKED,
		/* Masks */
		{0x000003FF, 0x000FFC00, 0x3FF00000, 0xC0000000},
		/* Type */
		EPCT_INT32,
		/* Byte Count */
		4,
		/* Bits per Pixel */
		32,
		/* Component Count */
		4,
		/* Bit Counts */
		{10, 10, 10, 2},
		/* Shifts */
		{0, 10, 20, 30},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_COMPRESSED_RGB_S3TC_DXT1
	{
		/* Flags */
		EPFF_COMPRESSED,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		4,
		/* Component Count */
		3,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1},
		/* MinSize */
		0
	},
	// EPF_COMPRESSED_RGBA_S3TC_DXT1
	{
		/* Flags */
		EPFF_COMPRESSED | EPFF_ALPHA,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		4,
		/* Component Count */
		4,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1},
		/* MinSize */
		0
	},
	// EPF_COMPRESSED_RGBA_S3TC_DXT3
	{
		/* Flags */
		EPFF_COMPRESSED | EPFF_ALPHA,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		16,
		/* Bits per Pixel */
		8,
		/* Component Count */
		4,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1},
		/* MinSize */
		0
	},
	// EPF_COMPRESSED_RGBA_S3TC_DXT5
	{
		/* Flags */
		EPFF_COMPRESSED | EPFF_ALPHA,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		16,
		/* Bits per Pixel */
		8,
		/* Component Count */
		4,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1},
		/* MinSize */
		0
	},

 	// EPF_COMPRESSED_RGB_PVRTC_2BPP
	{
		/* Flags */
		EPFF_COMPRESSED,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		2,
		/* Component Count */
		3,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{8, 4, 1},
		/* MinSize */
		32
	},
 	// EPF_COMPRESSED_RGBA_PVRTC_2BPP
	{
		/* Flags */
		EPFF_COMPRESSED | EPFF_ALPHA,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		2,
		/* Component Count */
		4,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{8, 4, 1},
		/* MinSize */
		32
	},
 	// EPF_COMPRESSED_RGB_PVRTC_4BPP
	{
		/* Flags */
		EPFF_COMPRESSED,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		4,
		/* Component Count */
		3,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1},
		/* MinSize */
		32
	},
 	// EPF_COMPRESSED_RGBA_PVRTC_4BPP
	{
        /* Flags */
		EPFF_COMPRESSED | EPFF_ALPHA,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		4,
		/* Component Count */
		4,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1},
		/* MinSize */
		32
	},
 	// EPF_COMPRESSED_RGB_PVRTCII_2BPP
	{
        /* Flags */
		EPFF_COMPRESSED,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		2,
		/* Component Count */
		3,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{8, 4, 1},
		/* MinSize */
		32
	},
 	// EPF_COMPRESSED_RGBA_PVRTCII_2BPP
	{
        /* Flags */
		EPFF_COMPRESSED | EPFF_ALPHA,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		2,
		/* Component Count */
		4,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{8, 4, 1},
		/* MinSize */
		32
	},
 	// EPF_COMPRESSED_RGB_PVRTCII_4BPP
	{
        /* Flags */
		EPFF_COMPRESSED,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		4,
		/* Component Count */
		3,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1},
		/* MinSize */
		32
	},
 	// EPF_COMPRESSED_RGBA_PVRTCII_4BPP
	{
        /* Flags */
		EPFF_COMPRESSED | EPFF_ALPHA,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		4,
		/* Component Count */
		4,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1},
		/* MinSize */
		32
	},
    // EPF_COMPRESSED_ETC1_RGB8
	{
        /* Flags */
		EPFF_COMPRESSED,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		4,
		/* Component Count */
		3,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1},
		/* MinSize */
		8
	},
    // EPF_COMPRESSED_ETC1_RGB8_NATIVE_DMP
	{
        /* Flags */
		EPFF_COMPRESSED,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		4,
		/* Component Count */
		3,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1},
		/* MinSize */
		8
	},
    // EPF_COMPRESSED_ETC1_ALPHA_RGB8_A4_NATIVE_DMP
	{
        /* Flags */
		EPFF_COMPRESSED | EPFF_ALPHA,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		16,
		/* Bits per Pixel */
		8,
		/* Component Count */
		4,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1},
		/* MinSize */
		16
	},
    // EPF_COMPRESSED_ATC_RGB
	{
        /* Flags */
		EPFF_COMPRESSED,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		4,
		/* Component Count */
		3,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1},
		/* MinSize */
		8
	},
    // EPF_COMPRESSED_ATC_RGBA_EXPLICIT_ALPHA
	{
        /* Flags */
		EPFF_COMPRESSED | EPFF_ALPHA,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		16,
		/* Bits per Pixel */
		8,
		/* Component Count */
		4,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1}, // Note: we assume this, but details are actually not disclosed
		/* MinSize */
		16
	},
    // EPF_COMPRESSED_ATC_RGBA_INTERPOLATED_ALPHA
	{
        /* Flags */
		EPFF_COMPRESSED | EPFF_ALPHA,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		16,
		/* Bits per Pixel */
		8,
		/* Component Count */
		4,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1}, // Note: we assume this, but details are actually not disclosed
		/* MinSize */
		16
	},
    // EPF_COMPRESSED_3DC_X
	{
        /* Flags */
		EPFF_COMPRESSED,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		4,
		/* Component Count */
		1,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1}, // Note: we assume this, but details are actually not disclosed
		/* MinSize */
		8
	},
    // EPF_COMPRESSED_3DC_XY
	{
        /* Flags */
		EPFF_COMPRESSED,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		16,
		/* Bits per Pixel */
		8,
		/* Component Count */
		2,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{4, 4, 1}, // Note: we assume this, but details are actually not disclosed
		/* MinSize */
		16
	},
	// EPF_RGB16F
	{
		/* Flags */
		EPFF_FLOAT,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_FLOAT16,
		/* Byte Count */
		6,
		/* Bits per Pixel */
		48,
		/* Component Count */
		3,
		/* Bit Counts */
		{16, 16, 16, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{0, 1, 2, u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_RGBA16F
	{
		/* Flags */
		EPFF_FLOAT | EPFF_ALPHA,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_FLOAT16,
		/* Byte Count */
		8,
		/* Bits per Pixel */
		64,
		/* Component Count */
		4,
		/* Bit Counts */
		{16, 16, 16, 16},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{0, 1, 2, 3},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_RGB32F
	{
		/* Flags */
		EPFF_FLOAT,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_FLOAT32,
		/* Byte Count */
		12,
		/* Bits per Pixel */
		96,
		/* Component Count */
		3,
		/* Bit Counts */
		{32, 32, 32, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{0, 1, 2, u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_RGBA32F
	{
		/* Flags */
		EPFF_FLOAT,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_FLOAT32,
		/* Byte Count */
		16,
		/* Bits per Pixel */
		128,
		/* Component Count */
		4,
		/* Bit Counts */
		{32, 32, 32, 32},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{0, 1, 2, 3},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_LF
	{
		/* Flags */
		EPFF_LUMINANCE | EPFF_FLOAT,
		/* Masks */
		{0xFFFF, 0xFFFF, 0xFFFF, 0},
		/* Type */
		EPCT_FLOAT32,
		/* Byte Count */
		4,
		/* Bits per Pixel */
		16,
		/* Component Count */
		1,
		/* Bit Counts */
		{32, 32, 32, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{0, 0, 0, u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_DEPTH16
	{
		/* Flags */
		EPFF_DEPTH,
		/* Masks */
		{0xFFFF, 0, 0, 0},
		/* Type */
		EPCT_SHORT,
		/* Byte Count */
		2,
		/* Bits per Pixel */
		16,
		/* Component Count */
		1,
		/* Bit Counts */
		{16, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{0, u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_DEPTH24
	{
		/* Flags */
		EPFF_DEPTH | EPFF_PACKED,
		/* Masks */
		{0xFFFFFF00, 0, 0, 0},
		/* Type */
		EPCT_INT32,
		/* Byte Count */
		4,
		/* Bits per Pixel */
		32,
		/* Component Count */
		1,
		/* Bit Counts */
		{24, 0, 0, 0},
		/* Shifts */
		{8, 0, 0, 0},
		/* Indices */
		{0, u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_DEPTH32
	{
		/* Flags */
		EPFF_DEPTH,
		/* Masks */
		{0xFFFFFFFF, 0, 0, 0},
		/* Type */
		EPCT_INT32,
		/* Byte Count */
		4,
		/* Bits per Pixel */
		32,
		/* Component Count */
		1,
		/* Bit Counts */
		{32, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{0, u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_DEPTH24_STENCIL8
	{
		/* Flags */
		EPFF_DEPTH | EPFF_STENCIL | EPFF_PACKED,
		/* Masks */
		{0xFFFFFF00, 0x000000FF, 0, 0},
		/* Type */
		EPCT_INT32,
		/* Byte Count */
		4,
		/* Bits per Pixel */
		32,
		/* Component Count */
		2,
		/* Bit Counts */
		{24, 8, 0, 0},
		/* Shifts */
		{8, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_STENCIL1,
	{
		/* Flags */
		EPFF_STENCIL | EPFF_PACKED,
		/* Masks */
		{0xFFFFFFFE, 0, 0, 0},
		/* Type */
		EPCT_UNKNOWN,
		/* Byte Count */
		1,
		/* Bits per Pixel */
		1,
		/* Component Count */
		1,
		/* Bit Counts */
		{1, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_STENCIL4,
	{
		/* Flags */
		EPFF_STENCIL | EPFF_PACKED,
		/* Masks */
		{0xFFFFFFF8, 0, 0, 0},
		/* Type */
		EPCT_UNKNOWN,
		/* Byte Count */
		1,
		/* Bits per Pixel */
		4,
		/* Component Count */
		1,
		/* Bit Counts */
		{4, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_STENCIL8,
	{
		/* Flags */
		EPFF_STENCIL,
		/* Masks */
		{0xFFFFFFF0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		1,
		/* Bits per Pixel */
		8,
		/* Component Count */
		1,
		/* Bit Counts */
		{8, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{0, u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{1, 1, 1},
		/* MinSize */
		0
	},
	// EPF_UNKNOWN
	{
		/* Flags */
		0,
		/* Masks */
		{0, 0, 0, 0},
		/* Type */
		EPCT_BYTE,
		/* Byte Count */
		0,
		/* Bits per Pixel */
		0,
		/* Component Count */
		0,
		/* Bit Counts */
		{0, 0, 0, 0},
		/* Shifts */
		{0, 0, 0, 0},
		/* Indices */
		{u8(-1), u8(-1), u8(-1), u8(-1)},
		/* BlockSize */
		{0, 0, 0},
		/* MinSize */
		0
	}
};

}}
#endif // PixelFormat_h__
