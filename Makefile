CC = "C:/Program Files/LLVM/bin/clang.exe"

SRCS = src/Trj.c src/RegeditFunctions/RegFunctions.c src/utils/utils.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Isrc -Isrc/RegeditFunctions

trj.exe: $(OBJS)
	$(CC) $(OBJS) -o trj.exe

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@