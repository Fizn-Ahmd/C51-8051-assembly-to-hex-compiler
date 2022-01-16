**Procedure to build:**

1. make -f Makefile.mk all

It will generate the asmtohex.out for linux and asmtohex.exe for windows.

To clean the build

1. make -f Makefile clean

**Using the generated binaries:**

1. Run ./asmtohex < c51 asm file >

2. It will generate the a.hex

3. Load the a.hex into 8051 board.

