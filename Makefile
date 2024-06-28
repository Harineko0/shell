CC := gcc
NAME := main.exe
SRCS := src/**.c src/cmd/**.c
OBJS := $(SRCS:.c=.c)
CFLAGS := -W -Wall

main: $(OBJS)

$(OBJS):

.PHONY: clean
clean:
	-rm *.o
	-rm main

.DEFAULT_GOAL=main