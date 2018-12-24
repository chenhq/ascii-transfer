CXX ?= g++

# path #
SRC_PATH = .
BUILD_PATH = .
BIN_PATH = .
INSTALL_PATH = /usr/local/bin

# executable #
BIN_NAME = axfer

SOURCES = main.cpp AsciiTransfer.cpp
OBJECTS = $(SOURCES:%.cpp=%.o)
DEPS = $(OBJECTS:.o=.d)
COMPILE_FLAGS = -std=c++11 -Wall -Wextra -g
INCLUDES = -I include/ -I /usr/local/include
LIBS =

.PHONY: all
all: $(BIN_NAME)

.PHONY: install
install: $(BIN_NAME)
	@echo "Installing $(BIN_NAME) to $(INSTALL_PATH)"
	@cp $(BIN_NAME) $(INSTALL_PATH)

.PHONY: clean
clean:
	$(RM) $(BIN_NAME) $(OBJECTS)

# Creation of the executable
$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $@"
	$(CXX) $(OBJECTS) -o $@

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
