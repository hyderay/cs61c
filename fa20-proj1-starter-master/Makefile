########################################
# Platform-specific compiler / ASan
########################################
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)          # macOS
    CC       := clang
    SANFLAGS := -fsanitize=address -fno-omit-frame-pointer
    RUN_ENV  := env MallocNanoZone=0
else                               # Linux / other
    CC       := gcc
    SANFLAGS :=
    RUN_ENV  :=
endif

########################################
# Common flags
########################################
CFLAGS  := -g -Wall -std=c99 -c $(SANFLAGS)
LDFLAGS := -g -Wall $(SANFLAGS)

########################################
# Phony groups
########################################
.PHONY: all clean \
        imageloader imagememcheck \
        steganography steganographymemcheck \
        gameoflife gameoflifememcheck

all: imageloadertester steganography_bin gameOfLife   # just build

########################################
# Binary-only rules
########################################
imageloadertester: imageloader.o imageloadertester.o
	$(CC) $(LDFLAGS) $^ -o $@

steganography_bin: steganography.o imageloader.o
	$(CC) $(LDFLAGS) $^ -o steganography

gameOfLife: gameoflife.o imageloader.o
	$(CC) $(LDFLAGS) $^ -o $@

########################################
# STEP 1 – functional tests
########################################
imageloader: imageloadertester
	@echo "⇒ imageloadertest (diff)"
	@$(RUN_ENV) ./imageloadertester testInputs/JohnConway.ppm \
	    > studentOutputs/JohnConway.ppm
	@diff -q testInputs/JohnConway.ppm studentOutputs/JohnConway.ppm && \
	   echo "...diff passed." || echo "...diff FAILED."

steganography: steganography_bin
	@echo "⇒ steganography (functional run)"
	@$(RUN_ENV) ./steganography testInputs/JohnConway.ppm \
	    > studentOutputs/secretMessage.ppm
	@echo "...output written to studentOutputs/secretMessage.ppm"

gameoflife: gameOfLife
	@echo "⇒ Game of Life built — run ./frames.csh for visual test"

########################################
# STEP 2 – AddressSanitizer mem-checks
########################################
imagememcheck: imageloadertester
	@echo "⇒ ASan memcheck — imageloadertester"
	@$(RUN_ENV) ./imageloadertester testInputs/JohnConway.ppm >/dev/null

steganographymemcheck: steganography_bin
	@echo "⇒ ASan memcheck — steganography"
	@$(RUN_ENV) ./steganography testInputs/JohnConway.ppm >/dev/null

gameoflifememcheck: gameOfLife
	@echo "⇒ ASan memcheck — Game of Life"
	@$(RUN_ENV) ./gameOfLife testInputs/JohnConway.ppm 0x1808 >/dev/null

########################################
# Pattern rule for objects
########################################
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

########################################
# Cleanup
########################################
clean:
	rm -f *.o imageloadertester steganography gameOfLife \
	       studentOutputs/*.ppm
