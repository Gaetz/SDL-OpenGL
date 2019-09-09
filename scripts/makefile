# -------------
#    Windows
# -------------
ifeq ($(OS),Windows_NT)

SRC_DIR := ..\src
OBJ_DIR := ..\build\obj
EXT_DIR := ..\external
BUILD_DIR := ..\build

RELEASE_DIR := ..\release
RELEASE_OBJ_DIR := ..\release\obj

SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
RELEASE_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(RELEASE_OBJ_DIR)/%.o,$(SRC_FILES))

LIBRAIRIES := -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lglew32 -lzlib1 -lopengl32

INCLUDE :=-I$(EXT_DIR)\SDL2-2.0.10\include \
	-I$(EXT_DIR)\SDL2_mixer-2.0.2\include \
	-I$(EXT_DIR)\SDL2_ttf-2.0.15\include \
	-I$(EXT_DIR)\glew-2.1.0\include \

LIB :=-L$(EXT_DIR)\SDL2-2.0.10\lib\x64 \
	-L$(EXT_DIR)\SDL2_mixer-2.0.2\lib\x64 \
	-L$(EXT_DIR)\SDL2_ttf-2.0.15\lib\x64 \
	-L$(EXT_DIR)\glew-2.1.0\lib\Release\x64

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

# -------------
#     Linux
# -------------
else

SRC_DIR := ../src
OBJ_DIR := ../build/obj
EXT_DIR := ../external
BUILD_DIR := ../build

RELEASE_DIR := ../release
RELEASE_OBJ_DIR := ../release/obj

SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
RELEASE_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(RELEASE_OBJ_DIR)/%.o,$(SRC_FILES))

LIBRAIRIES := -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lGLEW  -lGLU -lGL

# Target, with all .o prerequisites
Tetris: $(OBJ_FILES)
	g++ -g -o $(BUILD_DIR)/$@ $^ $(LIBRAIRIES)

# Each .o file finds his .cpp counterpart
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -std=c++17 -g -Wall -Wextra -c -o $@ $<

# Release target
release: $(RELEASE_OBJ_FILES)
	g++ -O3 -mwindows -o $(RELEASE_DIR)\Tetris $^

# Each .o file finds his .cpp counterpart, with optimisations
$(RELEASE_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -std=c++17 -O3 -Wall -Wextra -c -o $@ $<

endif