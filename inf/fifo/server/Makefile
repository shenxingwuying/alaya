CC=g++
AR=ar

LIBS= -lpthread

TARGET=main
SOURCES=$(wildcard *.cc)
OBJS=$(patsubst %.cc, %.o, $(SOURCES))

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIBPATHS) $(LIBS)
%.o:%.cc
	$(CC) -c -g $< -o $@ $(INCLUDE)
.PHONY:clean
clean:
	rm -rf *.o
	rm -rf $(TARGET)
