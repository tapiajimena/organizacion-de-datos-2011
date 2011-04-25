# Extensión de los archivos a compilar (c para C, cpp o cc o cxx para C++).
extension = cpp

CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =	Tree.o BPlusTree.o Node.o InternalNode.o LeafNode.o NodeFactory.o ../Common/Record.o  ../Common/FileManager.o

LIBS =		

TARGET =	Tree

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
