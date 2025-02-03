CXX = g++
CXXFLAGS = -std=c++11 -Iinclude $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf)
LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf)

SRC = main.cpp components/button.cpp components/texture_manager.cpp
OBJ = $(addprefix build/,$(notdir $(SRC:.cpp=.o)))
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

build/%.o: components/%.cpp include/button.hpp include/texture_manager.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/main.o: main.cpp include/button.hpp include/texture_manager.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)
