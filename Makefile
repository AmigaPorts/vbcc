# Native Unix Makefile

# may be used when cross-compiling binaries for multiple hosts
HOSTID =

# used to compile vbcc, vc, ucpp, etc. for the selected host
CC = gcc -std=c9x -D_POSIX_C_SOURCE=200809L -g -Wno-format-security #-fsanitize=address #-DHAVE_ECPP -DHAVE_MISRA
LDFLAGS = -lm

# used to compile dtgen and osekrm natively
NCC = $(CC)
NLDFLAGS = $(LDFLAGS)

# emulator, may be used to run dtgen when cross-compiling for a different host
EMUL =

# OS-specific commands
RM = rm -f
MD = mkdir
MV = mv

include make.rules
