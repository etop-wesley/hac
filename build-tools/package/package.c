/*****************************************************************************
 * package.c
 *
 *  package tool source
 *
 * 2010/06/27 wesley.xie
 *
 *****************************************************************************/
#define PACKAGE_USE_STDINT
#include "package.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <getopt.h>
#include <time.h>
#include <libconfig.h>

/* Enable/Disable to turn on/off debug */
#define DEBUG

#ifdef	DEBUG
	#define debug(fmt, args...)	do { printf(fmt, ##args); } while(0)
#else
	#define debug(fmt, args...)
#endif	/* DEBUG */

/* Version Converter, used for this program only */
#define VERSION_CODE(a, b, c) (((a) << 16) + ((b) << 8) + (c))

/* Program Name and Version Definition */
#define PROGRAM_NAME "package"
#define PROGRAM_VERSION VERSION_CODE(0, 0, 1) // 0.0.1
#define PROGRAM_VERSION_STRING "0.0.1"

/*
 * global variables
 */
static int quiet = 0;
static const char *config_path = NULL;
static const char *output_path = NULL;

extern unsigned long crc32 (unsigned long, const unsigned char *, unsigned int);


/*
 * display usage help and then exit
 */
static void display_help(void)
{
	printf("\nUsage: package [options] input output\n"
		   "upgrade image package tool\n"
		   "\n"
		   "options:\n"
		   "  -q, --quiet    	 don't display progress messages\n"
		   "\n"
		   "input:\n"
		   "  -c, --config        specify a config file\n"
		   "\n"
		   "output:\n"
		   "  -o file, --output=file   specify output file\n"
		   "\n"
		   "       --help          display this help and exit\n"
		   "       --version      output version information and exit\n");
	exit(0);
}

/*
 * display version and then exit
 */
static void display_version(void)
{
	printf("%s $Revision: %s $\n", PROGRAM_NAME, PROGRAM_VERSION_STRING);
	exit(0);
}

/*
 * process program command line options
 */
static void process_options (int argc, char *argv[])
{
	int error = 0;
	int option_index = 0;
	int c = 0;

	static const char *short_options = "o:c:q";
	static const struct option long_options[] = {
		{"help", no_argument, NULL, 0},
		{"version", no_argument, NULL, 0},
		{"output", required_argument, NULL, 'o'},
		{"config", required_argument, NULL, 'c'},
		{"quiet", no_argument, NULL, 'q'},
		{0, 0, 0, 0}
	};

	for (;;) {
		c = getopt_long(argc, argv, short_options, long_options, &option_index);
		if (c == EOF)
			break;

		switch (c) {
		case 0:
			switch (option_index) {
			case 0:
				display_help();
				break;
			case 1:
				display_version();
				break;
			}
			break;
		case 'o':
			output_path = optarg;
			break;
		case 'c':
			config_path = optarg;
			break;
		case 'q':
			quiet = 1;
			break;
		case '?':
			error = 1;
			break;
		}
	}

	if (error)
		display_help();
}



#define VERSION_NUM(a, b, c, d) (((a) << 24) + ((b) << 16) + ((c) << 8) + (d))

static uint32_t _string_to_class(const char *str)
{
	uint32_t image_class = IMAGE_TYPE_INVALID;
	if (strncasecmp(str, "loader", strlen("loader")) == 0)
		image_class = IMAGE_CLASS_LOADER;
	else if (strncasecmp(str, "param", strlen("param")) == 0)
		image_class = IMAGE_CLASS_PARAM;
	else if (strncasecmp(str, "splash", strlen("splash")) == 0)
		image_class = IMAGE_CLASS_SPLASH;
	else if (strncasecmp(str, "kernel", strlen("kernel")) == 0)
		image_class = IMAGE_CLASS_KERNEL;
	else if (strncasecmp(str, "root", strlen("root")) == 0)
		image_class = IMAGE_CLASS_ROOT;
	else if (strncasecmp(str, "data", strlen("data")) == 0)
		image_class = IMAGE_CLASS_DATA;
	return image_class;
}

static char * _class_to_string(uint32_t clas)
{
	if (clas == IMAGE_CLASS_NONE)	return "invalid";
	else if (clas == IMAGE_CLASS_LOADER) return "loader";
	else if (clas == IMAGE_CLASS_PARAM)	return "param";
	else if (clas == IMAGE_CLASS_SPLASH)	return "splash";
	else if (clas == IMAGE_CLASS_KERNEL)	return "kernel";
	else if (clas == IMAGE_CLASS_ROOT)	return "root";
	else if (clas == IMAGE_CLASS_DATA)	return "data";
	else return "invalid";
}

static uint32_t _string_to_version(const char *str)
{
	uint32_t version = 0;
	int a;
	char *delim="."; /* version string delimit */
	char *s = (char *)str, *p;
	int i;

	for (i = 3; i >= 0; i--) {
		p = strtok(s, delim);
		/*
			On the first call to strtok() the string to be parsed should be specified in str. 
			In each subsequent call that should parse the same string, str should be NULL.
		*/
		s = NULL;
		if (p == NULL)
			break;

		a = atoi(p);
		if (a < 0 || a > 0xFF) {
			fprintf(stderr, "string2version error: %s(%d) is out of range\n", p, a);
			version = 0;
			break;
		}

		version += a << i*8;
	}

	return version;
}

static char * _version_to_string(uint32_t version)
{
	static char version_str[16]; // 255.255.255.255
	snprintf(version_str, sizeof(version_str),
			 "%d.%d.%d.%d",
			 ((version >> 24) & 0xFF),
			 ((version >> 16) & 0xFF),
			 ((version >> 8) & 0xFF),
			 ((version >> 0) & 0xFF));
	return version_str;
}

static uint32_t _string_to_time(const char *str)
{
	/*
	* FIXME: This isn't a best way to go, but it's simply and powful. we may rewrite it later!
	 * use "date" util to parse time string, data +%s -d "2010-07-12 17:33:29" to printf seconds since 1970-01-01 00:00:00 UTC
	 * time format: "2010-07-12 17:33:29"(date +%F" "%T), or the format supported by "date"
	 */
	uint32_t time = 0;
	char buf[128];
	char tmpfilename[] = ".image_time.tmp.XXXXXX";
	int tmpfd = mkstemp(tmpfilename);
	if (tmpfd == -1) {
		fprintf(stderr, "%s\n", strerror(errno));
		goto bail;
	}

	close(tmpfd);

	snprintf(buf, sizeof(buf), "date +%%s -d \"%s\" > %s", str, tmpfilename);
	if (system(buf) == -1)
		goto bail;

	FILE *f = fopen(tmpfilename, "r");
	if (f == NULL)
		goto bail;

	fread(buf, sizeof(buf), 1, f);
	time = atoi(buf);
	fclose(f);

	bail:
	remove(tmpfilename);
	return time;
}

static char * _time_to_string(uint32_t time)
{
	char * tm = ctime(&time);
	tm[strlen(tm) - 1] = '\0';
	return tm;
}

static uint32_t _string_to_image_type(const char *str)
{
	uint32_t image_type = IMAGE_TYPE_INVALID;
	if (strncasecmp(str, "bin", strlen("bin")) == 0)
		image_type = IMAGE_TYPE_BIN;
	else if (strncasecmp(str, "yaffs2", strlen("yaffs2")) == 0)
		image_type = IMAGE_TYPE_YAFFS2;

	return image_type;
}

static char * _image_type_to_string(uint32_t type)
{
	if (type == IMAGE_TYPE_INVALID)	return "invalid";
	else if (type == IMAGE_TYPE_BIN) return "bin";
	else if (type == IMAGE_TYPE_YAFFS2)	return "yaffs2";
	else return "invalid";
}

static uint32_t _string_to_image_compress(const char *str)
{
	uint32_t image_comp = IMAGE_COMP_NONE;
	if (strncasecmp(str, "gzip", strlen("gzip")) == 0)
		image_comp = IMAGE_COMP_GZIP;
	else if (strncasecmp(str, "bzip2", strlen("bzip2")) == 0)
		image_comp = IMAGE_COMP_BZIP2;
	else if (strncasecmp(str, "lzma", strlen("lzma")) == 0)
		image_comp = IMAGE_COMP_LZMA;
	else if (strncasecmp(str, "lzo", strlen("lzo")) == 0)
		image_comp = IMAGE_COMP_LZO;

	return image_comp;
}

static char * _image_compress_to_string(uint32_t type)
{
	if (type == IMAGE_COMP_NONE)	return "none";
	else if (type == IMAGE_COMP_GZIP) return "gzip";
	else if (type == IMAGE_COMP_BZIP2)	return "bzip2";
	else if (type == IMAGE_COMP_LZMA)	return "lzma";
	else if (type == IMAGE_COMP_LZO)	return "lzo";
	else return "none";
}

static uint32_t _string_to_load_type(const char *str)
{
	uint32_t load_type = LOAD_TYPE_INVALID;
	if (strncasecmp(str, "nor", strlen("nor")) == 0)
		load_type = LOAD_TYPE_NOR;
	else if (strncasecmp(str, "nand",  strlen("nand")) == 0)
		load_type = LOAD_TYPE_NAND;

	return load_type;
}

static char * _load_type_to_string(uint32_t type)
{
	if (type == LOAD_TYPE_INVALID) return "invalid";
	else if (type == LOAD_TYPE_NOR)	return "nor";
	else if (type == LOAD_TYPE_NAND) return "nand";
	else return "invalid";
}


static void print_package_header(const package_header_t *package_header)
{
	printf ("package_header->package_id = 0x%08X\n", package_header->package_id);
	printf ("package_header->header_len = 0x%08X(%d)\n", package_header->header_len, package_header->header_len);
	printf ("package_header->total_len = 0x%08X(%d)\n", package_header->total_len, package_header->total_len);
	printf ("package_header->this_version = 0x%08X\n", package_header->this_version);
	printf ("package_header->package_name = %s\n", package_header->package_name);
	printf ("package_header->package_sign = %s\n", package_header->package_sign);
	printf ("package_header->package_desc = %s\n", package_header->package_desc);
	printf ("package_header->package_version = 0x%08X(%s)\n", package_header->package_version, _version_to_string(package_header->package_version));
	printf ("package_header->package_time = 0x%08X(%s)\n", package_header->package_time, _time_to_string(package_header->package_time));
	printf ("package_header->image_num = 0x%08X(%d)\n", package_header->image_num, package_header->image_num);
	printf ("package_header->data_crc = 0x%08X\n", package_header->data_crc);
	printf ("package_header->header_crc = 0x%08X\n", package_header->header_crc);
}

static void print_image_header(const image_header_t *image_header)
{
	printf ("image_header->image_id = 0x%08X\n", image_header->image_id);
	printf ("image_header->header_len = 0x%08X(%d)\n", image_header->header_len, image_header->header_len);
	printf ("image_header->total_len = 0x%08X(%d)\n", image_header->total_len, image_header->total_len);
	printf ("image_header->image_name = %s\n", image_header->image_name);
	printf ("image_header->image_class = 0x%08X(%s)\n", image_header->image_class, _class_to_string(image_header->image_class));
	printf ("image_header->image_version = 0x%08X(%s)\n", image_header->image_version, _version_to_string(image_header->image_version));
	printf ("image_header->image_time = 0x%08X(%s)\n", image_header->image_time, _time_to_string(image_header->image_time));
	printf ("image_header->image_type = 0x%08X(%s)\n", image_header->image_type, _image_type_to_string(image_header->image_type));
	printf ("image_header->image_comp = 0x%08X(%s)\n", image_header->image_comp, _image_compress_to_string(image_header->image_comp));
	printf ("image_header->image_start = 0x%08X(%d)\n", image_header->image_start, image_header->image_start);
	printf ("image_header->image_len = 0x%08X(%d)\n", image_header->image_len, image_header->image_len);
	printf ("image_header->image_flags = 0x%08X\n", image_header->image_flags);
	printf ("image_header->load_type = 0x%08X(%s)\n", image_header->load_type, _load_type_to_string(image_header->load_type));
	printf ("image_header->load_start = 0x%08X(%d)\n", image_header->load_start, image_header->load_start);
	printf ("image_header->load_len = 0x%08X(%d)\n", image_header->load_len, image_header->load_len);
	printf ("image_header->data_crc = 0x%08X\n", image_header->data_crc);
	printf ("image_header->header_crc = 0x%08X\n", image_header->header_crc);
}

/*
 * main entry
 * @param argc: argument count
 * @param argv: argument array
 * @return: 0 for successful, otherwise failed
 */
int main(int argc, char *argv[])
{
	package_header_t package_header;
	FILE *package_file;

	config_t cfg;
	config_setting_t *setting;
	const char *str;
	int val;
	int i;
	int ret = 0;

	process_options(argc, argv);

	if (!quiet)	printf("====================%s====================\n", PROGRAM_NAME);

	/* init package header */
	memset(&package_header, 0, sizeof(package_header));
	package_header.package_id = PACKAGE_ID;
	package_header.header_len = sizeof(package_header_t);
	package_header.total_len = package_header.header_len;
	package_header.this_version = PROGRAM_VERSION;

	if (!quiet)	printf("parse config ... %s\n", config_path);

	config_init(&cfg);

	/* Read the file. If there is an error, report it and exit. */
	if (!config_read_file(&cfg, config_path)) {
		fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
		ret = EXIT_FAILURE;
		goto bail;
	}

	/* parse package output path */
	if (output_path == NULL) {
		if (!quiet)
			printf("you don't specify a output file in command line, try to find from configure file\n");
		if (config_lookup_string(&cfg, PACKAGE_PATH_KEY, &str))
			output_path = str;
	}

	if (output_path == NULL) {
		fprintf(stderr, "No output file specified\n");
		ret = EXIT_FAILURE;
		goto bail;
	}

	if (!quiet)	printf("output file is %s\n", output_path);

	package_file = fopen(output_path, "wb");
	if (package_file == NULL) {
		fprintf(stderr, "unable to open package file : %s\n", output_path);
		ret = EXIT_FAILURE;
		goto bail;
	}

	/*
	 * we will write the package header at the end of this program
	 * just seek the package header now
	 */
	if (fseek(package_file, sizeof(package_header_t), SEEK_SET) != 0) {
		fprintf(stderr, "unable to seek package file : %s\n", output_path);
		ret = EXIT_FAILURE;
		goto bail;
	}

	/* parse package header */
	if (!quiet)	printf("parse package header...\n");
	if (config_lookup_string(&cfg, PACKAGE_NAME_KEY, &str))
		snprintf((char *)package_header.package_name, sizeof(package_header.package_name), "%s", str);

	if (config_lookup_string(&cfg, PACKAGE_SIGN_KEY, &str))
		snprintf((char *)package_header.package_sign, sizeof(package_header.package_sign), "%s", str);

	if (config_lookup_string(&cfg, PACKAGE_DESC_KEY, &str))
		snprintf((char *)package_header.package_desc, sizeof(package_header.package_desc), "%s", str);

	if (config_lookup_string(&cfg, PACKAGE_VER_KEY, &str))
		package_header.package_version = _string_to_version(str);

	/* parse image header */
	setting = config_lookup(&cfg, PACKAGE_IMAGES_KEY);
	if (setting == NULL) {
		fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
		ret = EXIT_FAILURE;
		goto bail;
	}

	image_header_t image_header;
	config_setting_t *image_setting;
	char *image_path;
	FILE *image_file;
	char image_buf[1024];

	int image_num = config_setting_length(setting);

	/*
	 * write the image header at the end of the following loop
	 * just seek all the image headers for now
	 */
	if (fseek(package_file, sizeof(image_header_t) * image_num, SEEK_CUR) != 0) {
		fprintf(stderr, "unable to seek package file : %s\n", output_path);
		ret = EXIT_FAILURE;
		goto bail;
	}

	for (i = 0; i < image_num; i++) {
		if (!quiet)	printf("\nparse image header %d ...\n", i);
		/* init image header */
		memset(&image_header, 0, sizeof(image_header_t));
		image_header.image_id = IMAGE_ID;
		image_header.header_len = sizeof(image_header_t);
		image_header.total_len = image_header.header_len;

		image_setting = config_setting_get_elem(setting, i);
		if (config_setting_lookup_string(image_setting, IMAGE_PATH_KEY, &str))
			image_path = str;
		if (config_setting_lookup_string(image_setting, IMAGE_NAME_KEY, &str))
			snprintf((char *)image_header.image_name, sizeof(image_header.image_name), "%s", str);
		if (config_setting_lookup_string(image_setting, IMAGE_CLASS_KEY, &str))
			image_header.image_class = _string_to_class(str);
		if (config_setting_lookup_string(image_setting, IMAGE_VER_KEY, &str))
			image_header.image_version = _string_to_version(str);
		if (config_setting_lookup_string(image_setting, IMAGE_TYPE_KEY, &str))
			image_header.image_type = _string_to_image_type(str);
		if (config_setting_lookup_string(image_setting, IMAGE_COMP_KEY, &str))
			image_header.image_comp = _string_to_image_compress(str);
		if (config_setting_lookup_string(image_setting, IMAGE_TARGET_KEY, &str))
			image_header.load_type = _string_to_load_type(str);
		if (config_setting_lookup_int(image_setting, IMAGE_OFFSET_KEY, &val))
			image_header.load_start = val;
		if (config_setting_lookup_int(image_setting, IMAGE_SIZE_KEY, &val))
			image_header.load_len = val;
		if (config_setting_lookup_string(image_setting, IMAGE_TIME_KEY, &str))
			image_header.image_time = _string_to_time(str);
		if (config_setting_lookup_int(image_setting, IMAGE_FLAGS_KEY, &val))
			image_header.image_flags = val;

		/* create package */
		image_file = fopen(image_path, "rb");
		if (image_file == NULL) {
			fprintf(stderr, "unable to open image file : %s\n", image_path);
			ret = EXIT_FAILURE;
			goto bail;
		}

		while (!feof(image_file)) {
			int actual_len = fread(image_buf, 1, sizeof(image_buf), image_file);

			if (actual_len < sizeof(image_buf) && ferror(image_file) != 0)
				break;

			if (fwrite(image_buf, actual_len, 1 , package_file) != 1 || ferror(package_file) != 0)
				break;

			image_header.image_len += actual_len;
			image_header.data_crc = crc32(image_header.data_crc, image_buf, actual_len);
		}

		if (ferror(image_file) != 0
			|| ferror(package_file) != 0
			|| image_header.image_len > image_header.load_len) {
			if (ferror(image_file) != 0)
				fprintf(stderr, "read image data error: %s\n", image_path);
			else if (ferror(package_file) != 0)
				fprintf(stderr, "write package data error: %s\n", output_path);
			else if (image_header.image_len > image_header.load_len)
				fprintf(stderr, "image length is larger than load length : %s\n", image_path);

			fclose(image_file);
			image_file = NULL;
			ret = EXIT_FAILURE;
			goto bail;
		}

		/* update image header */
		image_header.image_start = ftell(package_file) - image_header.image_len;
		image_header.total_len += image_header.image_len;
		image_header.header_crc = crc32(image_header.header_crc, &image_header, sizeof(image_header));

		/* wirte image header */
		fseek(package_file, 0 + sizeof(package_header_t) + sizeof(image_header_t) * i, SEEK_SET);
		if (fwrite(&image_header, sizeof(image_header_t), 1, package_file) != 1) {
			fprintf(stderr, "write image header error: %s\n", output_path);
			ret = EXIT_FAILURE;
			goto bail;
		}
		/* seek back, "image_header.image_start + image_header.image_len" is the end of package file stream */
		fseek(package_file, image_header.image_start + image_header.image_len, SEEK_SET);

		/* update package header */
		package_header.data_crc = crc32(package_header.data_crc, &image_header.data_crc, sizeof(image_header.data_crc));
		package_header.total_len += image_header.total_len;
		package_header.image_num ++;

		fclose(image_file);
		image_file = NULL;
		if (!quiet) {
			printf("\nimage path %d : %s\n", i, image_path);
			printf("\nimage header %d:\n", i);
		}

		if (!quiet)	print_image_header(&image_header);
	}

	/* complete package header */
	package_header.package_time = time((time_t*)NULL);
	package_header.header_crc = crc32(package_header.header_crc, &package_header, sizeof(package_header));

	/* wirte package header */
	fseek(package_file, 0, SEEK_SET);
	if (fwrite(&package_header, sizeof(package_header_t), 1, package_file) != 1) {
		fprintf(stderr, "write package header error: %s\n", output_path);
		ret = EXIT_FAILURE;
		goto bail;
	}

	ret = EXIT_SUCCESS;
	if (!quiet) {
		printf("\npackage:\n");
		print_package_header(&package_header);
	}

bail:
	if (package_file != NULL) {
		fclose(package_file);
		package_file = NULL;
	}
	config_destroy(&cfg);
	if (!quiet)	printf("===============================================\n", PROGRAM_NAME);
	return ret;
}


