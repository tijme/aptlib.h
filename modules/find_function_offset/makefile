# Defines
COMPILER := x86_64-w64-mingw32-gcc
INCLUDES := ./src/find_function_offset.c

# Compile, test and clean
all: objects program test

# Compile object
objects:
	$(COMPILER) -masm=intel -c $(INCLUDES) -o find_function_offset.o

# Compile `test.c`
program:
	$(COMPILER) -masm=intel find_function_offset.o ./test.c -o test.exe

# Test `test.exe`
test:
	WINEDEBUG="fixme-all" wine ./test.exe

# Clean all build files
clean:
	rm -f *.exe *.a *.o *.obj *.lib *.dll *.pdb
