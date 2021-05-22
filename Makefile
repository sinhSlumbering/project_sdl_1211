#objects
OBJS = src/main.cpp src/utils.cpp
#compiler
CC = g++
#flags
FLAGS = -w
#linkers
LINKERS = -lSDL2 -lSDL2_image
all : $(OBJS)
	$(CC) $(OBJS) $(FLAGS) $(LINKERS) && ./a.out