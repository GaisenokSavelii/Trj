CC = "C:/Program Files/LLVM/bin/clang.exe"
# or CC = clang, if you have compilator on system PATH var or use Linux

SRCS = src/Trj.c src/RegeditFunctions/RegFunctions.c src/utils/utils.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Isrc -Isrc/RegeditFunctions -Isrc/utils 

trj.exe: $(OBJS)
	$(CC) $(OBJS) -o trj.exe

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@