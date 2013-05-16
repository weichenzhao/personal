OBJS = add/add_int.o add/add_float.o sub/sub_int.o sub/sub_float.o main.o
CC = gcc
CFLAGS = -Isub -Iadd -O2
TARGET = cacu
RM = rm -f

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

$(OBJS):%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(TARGET) $(OBJS)

hello:
	@echo "this is a test for 'make hello'"
	@echo "and 'make' usually execute the first target"
