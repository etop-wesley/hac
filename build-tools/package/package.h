/****************************************************************************
 *
 * package tool header
 *
 * package structure define
 *
 * Initial creation -------------------- wesley.xie
 *
 *****************************************************************************/

#ifndef _PACKAGE_H_
#define _PACKAGE_H_

#if defined(PACKAGE_USE_STDINT)
#include <stdint.h>
#elif defined(PACKAGE_USE_TYPES)
#include <linux/types.h>
#endif

/* for data alignment, the size must be n * 4 */
#define NAME_LEN   32
#define VER_LEN    32
#define SIGNATURE_LEN 64
#define DESC_LEN   128

/* Configure Key Definitions */
#define PACKAGE_PATH_KEY "path" 
#define PACKAGE_NAME_KEY "name" 
#define PACKAGE_SIGN_KEY "signature" 
#define PACKAGE_DESC_KEY "description" 
#define PACKAGE_VER_KEY "version" 
#define PACKAGE_TIME_KEY "time" 
#define PACKAGE_IMAGES_KEY "images"

#define IMAGE_PATH_KEY "path"
#define IMAGE_NAME_KEY "name"
#define IMAGE_CLASS_KEY "class"
#define IMAGE_VER_KEY "version"
#define IMAGE_TYPE_KEY "type"
#define IMAGE_COMP_KEY "compress"
#define IMAGE_TARGET_KEY "target"
#define IMAGE_OFFSET_KEY "offset"
#define IMAGE_SIZE_KEY "size"
#define IMAGE_TIME_KEY "time"
#define IMAGE_FLAGS_KEY "flags"

/*
 * package structure
 *
 * package header
 * image header 1
 * image data 1
 * image header 2
 * image data 2
 * image header 3
 * image data 3
 * image header ...
 * image data ...
 */

#define PACKAGE_ID 0x706B6768 /* pkgh */

typedef struct package_header {
	uint32_t package_id;	/* package identifier, can use to detect the data endlian */
	uint32_t header_len;	/* package header size */
	uint32_t total_len;			/* size of the header and all images, this will always be the size of the entire file */
	uint32_t this_version;	/* tool version number */
	uint8_t package_name[NAME_LEN];		/* package name */
	uint8_t package_sign[SIGNATURE_LEN];
	uint8_t package_desc[DESC_LEN];
	uint32_t package_version;	/* package version number */
	uint32_t package_time;		/* package Creation Timestamp	*/
	uint32_t image_num;		/* number of the images in package*/
	uint32_t data_crc;		/* package data crc checksum */
	uint32_t header_crc;	/* package header crc checksum */
} package_header_t;

#define IMAGE_ID 0x696D6768 /* imgh */

/* Image Type */
#define IMAGE_TYPE_INVALID		0	/* Invalid Image */
#define IMAGE_TYPE_BIN		1	/* Binary Image	*/
#define IMAGE_TYPE_YAFFS2	2	/* yaffs2 Image	*/

#define LOAD_TYPE_INVALID 0	/* Invalid Load Target */
#define LOAD_TYPE_NOR 1 /* Load to Nor Flash */
#define LOAD_TYPE_NAND 2 /* Load to Nand Flash */

#define IMAGE_COMP_NONE		0	/*  No	 Compression Used	*/
#define IMAGE_COMP_GZIP		1	/* gzip	 Compression Used	*/
#define IMAGE_COMP_BZIP2		2	/* bzip2 Compression Used	*/
#define IMAGE_COMP_LZMA		3	/* lzma  Compression Used	*/
#define IMAGE_COMP_LZO		4	/* lzo   Compression Used	*/

#define IMAGE_CLASS_NONE     0x00	/* No Image Class  */
#define IMAGE_CLASS_LOADER 0x01	/* "loader" */
#define IMAGE_CLASS_PARAM 0x02	/* "param" */
#define IMAGE_CLASS_SPLASH 0x03	/* "splash" */
#define IMAGE_CLASS_KERNEL 0x04	/* "kernel" */
#define IMAGE_CLASS_ROOT 0x05	/* "root" */
#define IMAGE_CLASS_DATA 0x06	/* "data" */

typedef struct image_header {
	uint32_t image_id;		/* image identifier */
	uint32_t header_len;	/* image header size */
	uint32_t total_len;		/* image size, include its image data */
	uint8_t image_name[NAME_LEN];	/* Image Name */
	uint32_t image_class;	/* Image Class */
	uint32_t image_version;	/* Image version number */
	uint32_t image_time;		/* Image Creation Timestamp	*/
	uint32_t image_type;		/* Image Type */
	uint32_t image_comp;		/* Compression Type */
	uint32_t image_start;		/* Image Data  Start Address */
	uint32_t image_len;		/* Image Data Length */
    uint32_t image_flags;   /* Image Flags */
	uint32_t load_type;		/* Load To Type */
	uint32_t load_start;		/* Image Data Load Area Start Address */
	uint32_t load_len;		/* Image Data Load Area Length */
	uint32_t data_crc;		/* Image Data CRC Checksum */
	uint32_t header_crc;	/* Image Header CRC Checksum */
} image_header_t;

#endif

