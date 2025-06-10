# Compiler and Flags
CC = clang
CFLAGS = -g -Wall -std=c99 -O1 -fsanitize=address -c
LDFLAGS = -g -Wall -O1 -fsanitize=address

# Try to auto-detect platform for leak detection
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    DETECT_LEAKS =
else
    DETECT_LEAKS = ASAN_OPTIONS=detect_leaks=1
endif

all: PartA PartB

PartA: imageloader.o imageloadertester.o steganography.o
	$(CC) $(LDFLAGS) -o imageloadertester imageloader.o imageloadertester.o
	$(CC) $(LDFLAGS) -o steganography steganography.o imageloader.o

PartB: imageloader.o gameoflife.o
	$(CC) $(LDFLAGS) -o gameOfLife gameoflife.o imageloader.o

imageloader: imageloader.o imageloadertester.o
	$(CC) $(LDFLAGS) -o imageloadertester imageloader.o imageloadertester.o
	echo "Running imageloadertest"
	./imageloadertester testInputs/JohnConway.ppm > studentOutputs/JohnConway.ppm
	diff testInputs/JohnConway.ppm studentOutputs/JohnConway.ppm
	echo "Diff check: The above lines were different than expected. If no lines show up, then this passed"

imagememcheck: imageloader
	echo "Running AddressSanitizer on imageloadertest"
	$(DETECT_LEAKS) ./imageloadertester testInputs/JohnConway.ppm > studentOutputs/JohnConway.ppm

steganography: imageloader.o steganography.o
	$(CC) $(LDFLAGS) -o steganography steganography.o imageloader.o
	echo "Running steganography"
	./steganography testInputs/JohnConway.ppm > studentOutputs/secretMessage.ppm

steganographymemcheck: steganography
	$(DETECT_LEAKS) ./steganography testInputs/JohnConway.ppm > studentOutputs/secretMessage.ppm

gameoflife: imageloader.o gameoflife.o
	$(CC) $(LDFLAGS) -o gameOfLife gameoflife.o imageloader.o
	echo "Successfully compiled"
	echo "Run ./frames.csh for various tests"

gameoflifememcheck: gameoflife
	$(DETECT_LEAKS) ./gameOfLife testInputs/JohnConway.ppm 0x1808 > studentOutputs/temp.ppm

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o
	rm -f gameOfLife
	rm -f steganography
	rm -f imageloadertester
	rm -f studentOutputs/*.ppm
