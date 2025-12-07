CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
INCLUDES := -I.

SRCS := main.cpp utilitaires.cpp utilitaire_generation.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := tp4_exec

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
