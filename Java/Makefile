# Nome do diretório onde os arquivos .class serão armazenados
OUTDIR = out

# Arquivos-fonte Java
SOURCES = $(wildcard *.java)

# Arquivos compilados (.class) correspondentes
CLASSES = $(patsubst %.java, $(OUTDIR)/%.class, $(SOURCES))

# Comando do compilador
JAVAC = javac

# Diretório de saída para os arquivos compilados
OUT_OPTION = -d $(OUTDIR)

# Outras opções do compilador
FLAGS = -Xlint -g

# Regra principal para compilar todos os arquivos
all: $(CLASSES)

# Compilação de cada arquivo-fonte .java em .class
$(OUTDIR)/%.class: %.java
	@mkdir -p $(OUTDIR)
	$(JAVAC) $(OUT_OPTION) $(FLAGS) $(CLASSPATH) $<

# Limpeza dos arquivos gerados
clean:
	rm -rf $(OUTDIR)
