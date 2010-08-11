/* linux dn2 main file. This depends on libusb.
 *
 * License:	GPL
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <usb.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


/* Default Definitions */
#define		OK2440_USB_IDVENDOR	0x5345
#define		OK2440_USB_IDPRODUCT	0x1234
#define		OK2440_USB_INTERFACE	0
#define		OK2440_USB_BULKENDPOINT	0x03

#define		OK2440_USB_DOWNLOADADDRESS	0x30800000

#define		OK2440_USB_TIMEOUT	30000


struct usb_device * find_device(uint16_t vid, uint16_t pid)
{
	struct usb_bus *busses, *bus;

	usb_init();
	usb_find_busses();
	usb_find_devices();

	busses = usb_get_busses();
	for(bus=busses; bus != NULL; bus = bus->next) {
	 	struct usb_device *dev;
		for(dev = bus->devices; dev != NULL; dev = dev->next) {
			if(vid == dev->descriptor.idVendor && pid == dev->descriptor.idProduct) {
				return dev;
			}
		}
	}
	
	return NULL;
}

void usage()
{
	printf("Usage: dnw2 <file name> [<download address(0x30800000)>]\n\n");
	printf("example:\n");
	printf("	dnw2 foo 300800fa\n");
	printf("\n\n");
}

int hexstr_to_int(const char *str)
{
	int len, res, tmp, i;
	char c;

	assert(str != NULL);
	
	len = strlen(str);
	if (len > 2*sizeof(int))
		return 0;

	res = 0;
	for (i = 0; i < len; i++) {
		c = str[i];
		if (c >= '0' && c <= '9')
			tmp = c - '0';
		else if (c >= 'a' && c <= 'f')
			tmp = c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			tmp = c - 'A' + 10;
		else
			res = 0;
	
		tmp <<= ((len-i-1)<<2);
		res |= tmp;
	}
	
	return res;
}

unsigned char* prepare_write_buf(const char *filename, const char *address, unsigned int *len)
{
	unsigned char *write_buf = NULL;
	int i = 0;
	u_int32_t download_addr = OK2440_USB_DOWNLOADADDRESS;
	u_int32_t buf_len = 0;
	u_int16_t checksum = 0;
	struct stat fs;

	// parse downloadress
	if (address != NULL)
		download_addr = hexstr_to_int(address);

	// read data
	int fd = open(filename, O_RDONLY);
	if(-1==fd) {
		perror("open");
		return NULL;
	}
	if(-1==fstat(fd, &fs)) {
		perror("fstat");
		goto error;
	}

	buf_len = fs.st_size + 10; // 4 + 4 + ... + 2 : | download address | download size | ... data ... | checksum | 
	write_buf = (unsigned char*)malloc(buf_len);
	if(NULL == write_buf) {
		perror("malloc");
		goto error;
	}

	if(fs.st_size != read(fd, write_buf+8, fs.st_size)) {
		perror("read");
		goto error;
	}

	checksum = 0;
	for (i = 8; i < buf_len -2; i ++)
		checksum += write_buf[i];
	
	printf("File Name : %s\n", filename);
	printf("File Size : %d bytes\n", fs.st_size);

	// recognizing buffer
	*((u_int32_t*)write_buf) = download_addr; //download address
	*((u_int32_t*)write_buf+1) = buf_len;	//download size;
	*((u_int16_t*)(write_buf + buf_len - 2)) = checksum;

	printf("\n");
	printf("Download Address : %xh\n", download_addr);
	printf("Download Size: %d bytes\n", buf_len);
	printf("Checksum: %xh\n", checksum);
	printf("\n");

	*len = buf_len;
	return write_buf;

error:
	if(fd!=-1) close(fd);
	if(NULL!=write_buf) free(write_buf);
	fs.st_size = 0;
	return NULL;
	
}

int main(int argc, char *argv[])
{
	const char *file = NULL;
	const char *address = NULL;
	if(argc == 2) {
		file = argv[1];
	} else if (argc == 3) {
		file = argv[1];
		address = argv[2];
	} else {
		usage();
		return 1;
	}
				

	struct usb_device *dev = find_device(OK2440_USB_IDVENDOR, OK2440_USB_IDPRODUCT);
	if(!dev) {
		perror("find_device");	
		return 1;
	}
	
	printf("Target usb device found!\n");

	struct usb_dev_handle *hdev = usb_open(dev);
	if(!hdev) {
		perror("usb_open");
		return 1;	
	}
	
	if(0 != usb_claim_interface(hdev, OK2440_USB_INTERFACE)) {
		perror("usb_claim_interface");
		usb_close(hdev);
		hdev = NULL;
	}
	
	unsigned int len = 0;
	unsigned char *write_buf = prepare_write_buf(file, address, &len);
	
	if(NULL == write_buf)
		return 1;

	unsigned int remain = len;
	unsigned int towrite;
	printf("Writing data ...\n");
	
	while(remain) {
		towrite = remain > 512 ? 512 : remain; 
		if(towrite != usb_bulk_write(hdev, OK2440_USB_BULKENDPOINT, write_buf + (len - remain), towrite, OK2440_USB_TIMEOUT)) {
			perror("usb_bulk_write");
			break;
		}

		remain -= towrite;
		printf("\r%d%\t %d bytes     ", (len - remain) * 100 / len, len - remain);
		fflush(stdout);
	}

	if(0 == remain)
		printf("Done!\n");

	return 0;
}
