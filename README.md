# This is a simple 8051(C51) assembly compiler.

## Procedure to build:

make -f Makefile.mk all

- This will generate the asmtohex.out for linux and asmtohex.exe for windows

make -f Makefile clean

-  To clean the build

## Direction of Use:

1. Run ./asmtohex <8051 asm file>

2. This will generate the a.hex

3. Load the a.hex into 8051 board
