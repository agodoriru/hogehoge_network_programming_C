OBJS=hoge.o analyzer.o printer.o
SRCS=$(OBJS:%.o=%.c)
CFLAGS=-g -Wall
LDLIBS=
TARGET=hoge
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)
	