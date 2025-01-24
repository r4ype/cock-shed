CXX = g++
CXXFLAGS = -std=c++11 -Iinclude $(shell pkg-config --cflags sdl2 SDL2_image)
LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_image)

SRC = main.cpp components/button.cpp
OBJ = $(addprefix build/,$(notdir $(SRC:.cpp=.o)))
TARGET = cockshed

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

build/%.o: components/%.cpp include/button.hpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/main.o: main.cpp include/button.hpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@
