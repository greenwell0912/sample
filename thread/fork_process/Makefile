PROGRAM=main
OBJS=main.o
SRCS=$(OBJS:%.o=%.c)
CFLAGS=-Wall -g
LDFLAGS=
LDLIBS= -lpthread
$(PROGRAM):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)
