CXXFLAGS =	-O0 -g -Wall
OBJS =		AOC2017.o
TARGET =	AOC2017

$(OBJS):	include/*.hpp

$(TARGET):	$(OBJS) Makefile
	$(CXX) -o $(TARGET) $(OBJS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
