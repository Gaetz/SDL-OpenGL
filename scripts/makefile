SRC_DIR := ..\src
OBJ_DIR := ..\build\obj
EXT_DIR := ..\external
BUILD_DIR := ..\build

RELEASE_DIR := ..\release
RELEASE_OBJ_DIR := ..\release\obj

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
RELEASE_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(RELEASE_OBJ_DIR)/%.o,$(SRC_FILES))

INCLUDE :=-I$(EXT_DIR)\SDL2-2.0.7\include \
	-I$(EXT_DIR)\SDL2-2.0.7\include \
	-I$(EXT_DIR)\SDL2_image-2.0.2\include \
	-I$(EXT_DIR)\SDL2_mixer-2.0.2\include \
	-I$(EXT_DIR)\SDL2_ttf-2.0.14\include \
	-I$(EXT_DIR)\glew-2.1.0\include \
	-I$(EXT_DIR)\glm-0.9.5

LIB :=-L$(EXT_DIR)\SDL2-2.0.7\lib\x64 \
	-L$(EXT_DIR)\SDL2_image-2.0.2\lib\x64 \
	-L$(EXT_DIR)\SDL2_mixer-2.0.2\lib\x64 \
	-L$(EXT_DIR)\SDL2_ttf-2.0.14\lib\x64 \
	-L$(EXT_DIR)\glew-2.1.0\lib\Release\x64

LIBRAIRIES := -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llibpng16-16 -lglew32 -lzlib1 -lopengl32

# Target, with all .o prerequisites
Tetris.exe: $(OBJ_FILES)
	g++ -g -o $(BUILD_DIR)\$@ $^ $(LIB) $(LIBRAIRIES)

# Each .o file finds his .cpp counterpart
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -std=c++17 -g -Wall -Wextra -c -o $@ $< $(INCLUDE) 

# Release target
release: $(RELEASE_OBJ_FILES)
	g++ -O3 -mwindows -o $(RELEASE_DIR)\Tetris.exe $^ $(LIB) $(LIBRAIRIES)

# Each .o file finds his .cpp counterpart, with optimisations
$(RELEASE_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -std=c++17 -O3 -Wall -Wextra -c -o $@ $< $(INCLUDE) 
