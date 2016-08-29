#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char* argv[]) {
	if(argc <= 1) {
		printf("That's not how this works, maaaan.\n");
		return -1;
	}
	int max = open("/sys/class/backlight/intel_backlight/max_brightness", O_RDONLY);
	int bright = open("/sys/class/backlight/intel_backlight/brightness", O_RDWR);
	if((max < 0) || (bright < 0)) {
		printf("Could not open files! Why dis? Try sudo !!\n");
		return -1;
	}
	void *readBuffer = malloc(128);
	read(max, readBuffer, 127);
	int getMax = atoi(readBuffer);
	memset(readBuffer, 0, 127);
	read(bright, readBuffer, 127);
	int getCurrent = atoi(readBuffer);
	int toAdd = atoi(argv[1]);
	int toWrite = getCurrent + toAdd;
	if(toWrite > getMax) {
		toWrite = getMax;
	}
	else if(toWrite < 0) {
		toWrite = 0;
	}
	memset(readBuffer, 0, 127);
	sprintf(readBuffer, "%i", toWrite);
	write(bright, readBuffer, sizeof(readBuffer));
	printf("Max: %i\nTo Add: %i\n", getMax, toAdd);
	free(readBuffer);
	close(max);
	close(bright);
	return 0;
}
