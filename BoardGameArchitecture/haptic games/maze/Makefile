# project layout
TOP_DIR = ../../../chai3d-3.2.0/modules/BULLET
include $(TOP_DIR)/Makefile.common

# GLFW dependency
CXXFLAGS += -I$(GLFW_DIR)/include
LDFLAGS  += -L$(GLFW_DIR)/lib/$(CFG)/$(OS)-$(ARCH)-$(COMPILER)
LDLIBS   += $(LDLIBS_GLFW)

# local configuration
SRC_DIR   = .
HDR_DIR   = ../../src
OBJ_DIR   = ../../bin/obj
SOURCES   = $(wildcard $(SRC_DIR)/*.cpp)
INCLUDES  = $(wildcard $(HDR_DIR)/*.h)
OBJECTS   = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SOURCES)))
OBJECTS  += ../../bin/lib/libarchitecture.a
OUTPUT    = $(TOP_DIR)/../../../BoardGameArchitecture/bin/mazeGame
TEST_SOURCES = $(wildcard ../Tests/*.cpp)
TEST_OUTPUT = ../Tests/bin/testexample

.PHONY: all clean output tests

all: output

output: $(OUTPUT) #build main example

$(OBJECTS): $(INCLUDES)

$(OUTPUT): $(OBJ_DIR) $(LIB_TARGET) $(OBJECTS)
	make output -C ../../src
	$(CXX) $(CXXFLAGS) -I$(HDR_DIR) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $(OUTPUT)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(HDR_DIR) -c -o $@ $<

clean:
	make clean -C ../../src
	rm -f $(OUTPUT) $(OBJECTS) *~ 
	-rm -rf $(OBJ_DIR)
	-rm -f $(TEST_OUTPUT)
