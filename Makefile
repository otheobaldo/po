# all e clean não são arquivos
.PHONY: all clean

# Definir variáveis

# Compilador 
CXX := g++

# Diretório dos arquivos .cpp, .o e teste
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Executável
EXE := teste

# Lista todos os arquivos .cpp
SRC := $(wildcard $(SRC_DIR)/*.cpp)

# Transformar todos os arquivos .cpp em .o
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Flags do preprocessador
CXXFLAGS := -Iinclude -MMD -MP 
# Flags
CFLAGS   := -Wall          
# Flags de linkedição
LDFLAGS  := -Llib             
# Bibliotecas
LDLIBS   := -lSDL2     

all: $(EXE)

# Cria o executável
$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# Cria os objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Cria as pastas /bin e /obj
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Remove as pastas /bin e /obj
clean:
	@$(RM) -rv  $(BIN_DIR) $(OBJ_DIR)

# Executa o teste
run :
	@$(MAKE) && ./$(EXE)