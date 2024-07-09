# Defines
COMPILER := x86_64-w64-mingw32-gcc
INCLUDES := ./src/http_request.c

# Compile, test and clean
all: objects program test

# Compile object
objects:
	@$(COMPILER) -masm=intel -c $(INCLUDES) -lwinhttp -o http_request.o

# Compile `test.c`
program:
	@$(COMPILER) -masm=intel http_request.o ./test.c -lwinhttp -o test.exe

# Test `test.exe`
test:
	@WINEDEBUG="fixme-all" wine ./test.exe

# Clean all build files
clean:
	rm -f *.exe *.a *.o *.obj *.lib *.dll *.pdb
