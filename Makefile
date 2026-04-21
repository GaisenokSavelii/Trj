CC = clang
CFLAGS = --target=x86_64-w64-windows-gnu

SRCS = src/Trj.c src/registry/registry.c src/utils/utils.c src/modules/modules.c src/system/system.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Isrc -Isrc/registry -Isrc/utils -Isrc/modules -Isrc/system.c

trj.exe: $(OBJS)
	$(CC) $(OBJS) -o trj.exe

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@