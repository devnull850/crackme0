#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	FILE *fd;
	char *buf, *blob;
	long bytes, size, addr;

	if ((fd = fopen("blob", "rb")) == NULL) {
		exit(EXIT_FAILURE);
	}

	fseek(fd, 0, SEEK_END);
	size = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	if ((blob = malloc(size)) == NULL) {
		exit(EXIT_FAILURE);
	}

	fread(blob, 1, size, fd);

	if (fclose(fd) == EOF) {
		exit(EXIT_FAILURE);
	}

	if ((fd = fopen("test", "rb")) == NULL) {
		exit(EXIT_FAILURE);
	}

	fseek(fd, 0, SEEK_END);
	bytes = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	if ((buf = malloc(bytes)) == NULL) {
		exit(EXIT_FAILURE);
	}

	fread(buf, 1, bytes, fd);

	if (fclose(fd) == EOF) {
		exit(EXIT_FAILURE);
	}

	for (size_t i = 0x15a8; i < size+0x15a8; ++i) {
		buf[i] = blob[i-0x15a8];
	}

	free(blob);

	memcpy(&addr, buf+0x28, 8);
	memset(buf+0x28, 0, 8);
	memset(buf+0x3c, 0, 2);

	if ((fd = fopen("test", "wb")) == NULL) {
		exit(EXIT_FAILURE);
	}

	fwrite(buf, 1, addr, fd);

	if (fclose(fd) == EOF) {
		exit(EXIT_FAILURE);
	}

	free(buf);
	
	return EXIT_SUCCESS;
}
