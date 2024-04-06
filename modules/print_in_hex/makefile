# Defines
COMPILER := x86_64-w64-mingw32-gcc
INCLUDES := ./src/print_in_hex.c

# Compile, test and clean
all: objects program test

# Compile object
objects:
	@$(COMPILER) -masm=intel -c $(INCLUDES) -o print_in_hex.o

# Compile `test.c`
program:
	@$(COMPILER) -masm=intel print_in_hex.o ./test.c -o test.exe

# Test `test.exe`
test:
	@WINEDEBUG="fixme-all" wine ./test.exe

# Clean all build files
clean:
	rm -f *.exe *.a *.o *.obj *.lib *.dll *.pdb
