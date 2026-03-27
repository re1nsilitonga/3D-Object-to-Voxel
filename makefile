CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
SRC_DIR  = src
BIN_DIR  = bin

SRCS = $(SRC_DIR)/main.cpp     \
       $(SRC_DIR)/geometry.cpp \
       $(SRC_DIR)/parser.cpp   \
       $(SRC_DIR)/octree.cpp

TARGET = $(BIN_DIR)/voxelizer.exe

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)
	@echo "Build selesai: $@"

clean:
	rm -f $(TARGET)