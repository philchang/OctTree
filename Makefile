TARGET = main
OBJECTS = main.o TreeNode.o dVector.o

CXX = g++ -ftree-vectorize -O3

all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)

# Make's built-in database doesn't provide pattern rules for out-of-source
# builds, so we provide them here.
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean: 
	rm -f $(TARGET) $(OBJECTS)
