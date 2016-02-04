CXXFLAGS =	-O0 -g -Wall -fmessage-length=0

OBJS =		1001.o

LIBS =

TARGET =	1001

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
