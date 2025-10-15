# --- Compiler settings ---
CXX      := g++
CXXFLAGS := -std=c++14 -Wall -g

# --- Files ---
SRCS     := Monsters.cpp tree.cpp main.cpp
OBJS     := $(SRCS:.cpp=.o)
HEADERS  := Monsters.h tree.h
TARGET   := monstertale

# --- Default target ---
.PHONY: all
all: $(TARGET)

# --- Link ---
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# --- Compile ---
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Clean up ---
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
