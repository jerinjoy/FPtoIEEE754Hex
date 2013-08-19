# Makefile for the FPToHex
CLANG = /usr/bin/clang

TOOLNAME = FP_to_IEEE754_Hex
OPTIMIZATIONS = -O3

all: $(TOOLNAME)

$(TOOLNAME): $(TOOLNAME).c
	$(CLANG) $(OPTIMIZATIONS) $(TOOLNAME).c -o $(TOOLNAME)

clean:
	rm $(TOOLNAME)
