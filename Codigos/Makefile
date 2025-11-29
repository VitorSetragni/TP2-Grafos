###############################################
#   Makefile automático para projetos C++     #
#   Compila todos os .cpp em qualquer pasta   #
###############################################

# Compilador
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

# Nome do executável
TARGET = bin/programa

# Diretório onde os .o serão armazenados
OBJDIR = build/obj

# Lista automática de todos os .cpp no projeto
SRCS := $(shell find . -name "*.cpp")

# Converte cada .cpp para um .o dentro de obj/
OBJS := $(SRCS:%=$(OBJDIR)/%.o)

# Regra default
all: $(TARGET)

###############################################
# Como gerar o executável
###############################################
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)
	@echo -e "\n===== ✔ Build finalizado ✔ =====\nArquivo executável -> $(TARGET)\nPara usar basta executar o comando ./$(TARGET)"

###############################################
# Como gerar objetos .o espelhando subpastas
###############################################
$(OBJDIR)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

###############################################
# Limpeza
###############################################
clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "✔ Limpeza concluída."

###############################################
# Rebuild total
###############################################
re: clean all
