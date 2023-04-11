# project layout
TOP_DIR = ../../chai3d-3.2.0/modules/BULLET
include $(TOP_DIR)/Makefile.common

# GLFW dependency
CXXFLAGS += -I$(GLFW_DIR)/include
LDFLAGS  += -L$(GLFW_DIR)/lib/$(CFG)/$(OS)-$(ARCH)-$(COMPILER)
LDLIBS   += $(LDLIBS_GLFW)

# local configuration
SRC_DIR   = .
HDR_DIR   = .
OBJ_DIR   = ../bin/obj
LIB_DIR_A = ../bin/lib #LIB_DIR already exists
SOURCES   = $(shell find $(SRC_DIR) -name '*.cpp')
INCLUDES  = $(shell find $(HDR_DIR) -name '*.h')
OBJECTS   = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SOURCES)))
OUTPUT    = $(TOP_DIR)/../../../BoardGameArchitecture/bin/architecture
TEST_SOURCES = $(wildcard ../Tests/*.cpp)
TEST_OUTPUT = ../Tests/bin/testMap

.PHONY: all clean output tests

output: $(OUTPUT) #Build library libarchitecture
	
$(OBJECTS): $(INCLUDES)

$(OUTPUT): $(OBJ_DIR) $(LIB_DIR_A) $(LIB_TARGET) $(OBJECTS)
	ar rcs ../bin/lib/libarchitecture.a $(OBJECTS)

# catch test framework for AI testing
tests:
	$(CXX) $(CXXFLAGS) ../Tests/TestAI.cpp Map.cpp -I$(HDR_DIR) -o $(TEST_OUTPUT)

$(OBJ_DIR):
	mkdir -p $@

$(LIB_DIR_A):
	mkdir -p $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OUTPUT) $(OBJECTS) *~ 
	-rm -rf $(OBJ_DIR)
	-rm -rf $(LIB_DIR_A)
	-rm -f $(TEST_OUTPUT)
