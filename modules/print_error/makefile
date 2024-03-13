# Defines
COMPILER := x86_64-w64-mingw32-gcc
INCLUDES := ./src/print_error.c

# Compile, test and clean
all: program test

# Compile `test.c`
program:
	$(COMPILER) -masm=intel -c $(INCLUDES) -o print_error.o
	$(COMPILER) -masm=intel print_error.o ./test.c -o test.exe

# Test `test.exe`
test:
	WINEDEBUG="fixme-all" wine ./test.exe

# Clean all build files
clean:
	rm -f *.exe *.a *.o *.obj *.lib *.dll *.pdb
