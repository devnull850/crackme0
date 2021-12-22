#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH_LEN 0x50
#define LINE_LEN 0x100
#define NAME_LEN 0x14

int main(void) {
	FILE *fd;
	pid_t pid;
	char path[PATH_LEN+1];
	char line[LINE_LEN+1];
	char name[NAME_LEN+1];
	char ch, *s;
	int i, serial;
	long addr;
	int (*func)(char *);

	pid = getpid();

	snprintf(path, PATH_LEN, "/proc/%d/maps", pid);

	if ((fd = fopen(path, "rb")) == NULL) {
		exit(EXIT_FAILURE);
	}

	i = 0;

	while ((ch = fgetc(fd)) != EOF) {
		if (ch == 0x0a) {
			line[i] = 0;

			if (strstr(line, "/test")) {
				break;
			}

			i = 0;
		}
		else {
			line[i] = ch;
			++i;
		}
	}

	if (fclose(fd) == EOF) {
		exit(EXIT_FAILURE);
	}

	line[0xc] = 0;
	addr = strtol(line, NULL, 0x10);
	addr += 0x15a8;
	func = (int (*)(char *)) addr;

	printf("Enter your name: ");
	fgets(name, NAME_LEN, stdin);
	s = strchr(name, 0x0a);
	*s = 0;

	printf("Enter your serial: ");
	scanf("%d", &serial);

	puts(func(name) == serial ? "Correct" : "Incorrect");

	return EXIT_SUCCESS;
}
