CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
SRC_DIR  = src
BIN_DIR  = bin

SRCS = $(SRC_DIR)/main.cpp     \
       $(SRC_DIR)/geometry.cpp \
       $(SRC_DIR)/parser.cpp   \
       $(SRC_DIR)/octree.cpp

VIEWER_SRCS = $(SRC_DIR)/viewer.cpp   \
              $(SRC_DIR)/geometry.cpp \
              $(SRC_DIR)/parser.cpp

TARGET        = $(BIN_DIR)/voxelizer.exe
VIEWER_TARGET = $(BIN_DIR)/viewer.exe

.PHONY: all clean

all: $(TARGET) $(VIEWER_TARGET)

$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)
	@echo "Build selesai: $@"

$(VIEWER_TARGET): $(VIEWER_SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(VIEWER_SRCS) -lsfml-graphics -lsfml-window -lsfml-system
	@echo "Build selesai: $@"

clean:
	rm -f $(TARGET) $(VIEWER_TARGET)