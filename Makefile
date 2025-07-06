# Kompilator
CXX = g++
CXXFLAGS = -Wall -Wextra -Iinclude

# Katalogi
SRC_DIR = src
OBJ_DIR = build
INCLUDE_DIR = include

# Nazwa biblioteki
LIB_NAME = imageTools.a

# Pliki źródłowe i obiektowe
LIB_SRC = $(SRC_DIR)/imageTools.cpp
LIB_OBJ = $(OBJ_DIR)/imageTools.o

MAIN_SRC = main.cpp
MAIN_OBJ = $(OBJ_DIR)/main.o

# Nazwa pliku wykonywalnego
BIN = main

# Domyślny cel
all: $(LIB_NAME) $(BIN)

# Budowanie biblioteki statycznej
$(LIB_NAME): $(LIB_OBJ)
	ar rcs $@ $^

# Budowanie programu głównego
$(BIN): $(MAIN_OBJ) $(LIB_NAME)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Kompilacja plików źródłowych biblioteki
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Kompilacja main.cpp
$(OBJ_DIR)/main.o: main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Uruchamianie
run: all
	./$(BIN)

# Sprzątanie
clean:
	rm -rf $(OBJ_DIR) $(BIN) $(LIB_NAME)

.PHONY: all clean
