CC = "C:/Program Files/LLVM/bin/clang.exe"

SRCS = src/Trj.c src/RegeditFunctions/RegFunctions.c src/utils/utils.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Isrc -Isrc/RegeditFunctions

trj_app.exe: $(OBJS)
	$(CC) $(OBJS) -o trj_app.exe

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@