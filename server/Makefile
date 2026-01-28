# Makefile za C++ HTTP Server

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -g -O0
LDFLAGS = -lm

# Direktorijumi
OUT_DIR = out
OBJ_DIR = $(OUT_DIR)/obj
BIN_DIR = $(OUT_DIR)/bin
DEP_DIR = $(OUT_DIR)/dep

# Izlazni fajl
TARGET = $(BIN_DIR)/web-server

# Automatski pronalaženje svih .cpp fajlova
SOURCES := $(shell find . -maxdepth 1 -name "*.cpp" -type f | sed 's|^\./||') \
           $(shell find utils router controllers models services -name "*.cpp" -type f)

OBJECTS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
DEPS := $(patsubst %.cpp,$(DEP_DIR)/%.d,$(SOURCES))

# Izvršavanje
all: directories $(TARGET)

# Pravljenje direktorijuma
directories:
	@mkdir -p $(OUT_DIR) $(OBJ_DIR) $(BIN_DIR) $(DEP_DIR)
	@mkdir -p $(OBJ_DIR)/utils $(OBJ_DIR)/router $(OBJ_DIR)/controllers $(OBJ_DIR)/models $(OBJ_DIR)/services
	@mkdir -p $(DEP_DIR)/utils $(DEP_DIR)/router $(DEP_DIR)/controllers $(DEP_DIR)/models $(DEP_DIR)/services

# Linkovanje
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@cp level7_export.txt $(BIN_DIR)/level7_export.txt 2>/dev/null || true
	@echo "Build completed: $(TARGET)"

# Kompajliranje sa dependency generiranjem
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(DEP_DIR)/$*.d)
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

# Uključi dependency fajlove ako postoje
-include $(DEPS)

# Pokretanje servera
run: all
	cd $(BIN_DIR) && ./$(notdir $(TARGET))

# Brisanje generisanih fajlova
clean:
	rm -rf $(OUT_DIR)
	@echo "Cleaned build artifacts"

# Rebuild
rebuild: clean all

# Info o fajlovima
info:
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "Target: $(TARGET)"

# Help
help:
	@echo "Available targets:"
	@echo "  make          - Build the project"
	@echo "  make run      - Build and run the server"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make rebuild  - Clean and build"
	@echo "  make info     - Show build information"
	@echo "  make help     - Show this message"

.PHONY: all run clean rebuild info help directories
