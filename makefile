CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
SRC_DIR  = src
BIN_DIR  = bin

SFML_CFLAGS = $(shell pkg-config --cflags sfml-graphics 2>/dev/null)
SFML_LIBS   = $(shell pkg-config --libs sfml-graphics sfml-window sfml-system 2>/dev/null)
HAS_SFML    = $(if $(strip $(SFML_LIBS)),1,0)

SRCS = $(SRC_DIR)/main.cpp     \
       $(SRC_DIR)/geometry.cpp \
       $(SRC_DIR)/parser.cpp   \
       $(SRC_DIR)/octree.cpp

VIEWER_SRCS = $(SRC_DIR)/viewer.cpp   \
              $(SRC_DIR)/geometry.cpp \
              $(SRC_DIR)/parser.cpp

TARGET        = $(BIN_DIR)/voxelizer.exe
VIEWER_TARGET = $(BIN_DIR)/viewer.exe

.PHONY: all clean viewer

all: $(TARGET) viewer

$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS)
	@echo "Build selesai: $@"

$(VIEWER_TARGET): $(VIEWER_SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SFML_CFLAGS) -o $@ $(VIEWER_SRCS) $(SFML_LIBS)
	@echo "Build selesai: $@"

ifeq ($(HAS_SFML),1)
viewer: $(VIEWER_TARGET)
else
viewer:
	@echo "Lewati build viewer: SFML tidak terdeteksi."
	@echo "Install SFML di sistem Anda untuk membangun viewer."
endif

clean:
	rm -f $(TARGET) $(VIEWER_TARGET)