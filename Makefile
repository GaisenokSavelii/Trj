CC = clang
# "C:/Program Files/LLVM/bin/clang.exe"
CFLAGS = --target=x86_64-w64-windows-gnu

SRCS = src/Trj.c src/registryFunctions/registryFunctions.c src/utils/utils.c src/core/core.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Isrc -Isrc/registryFunctions -Isrc/utils -Isrc/core 

trj.exe: $(OBJS)
	$(CC) $(OBJS) -o trj.exe

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@