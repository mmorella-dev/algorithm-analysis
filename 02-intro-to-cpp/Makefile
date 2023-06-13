CFLAGS := -Wall -Wextra
CBINARY := ex2
CSOURCE := ex2.c main.c

CXXFLAGS := -Wall -Wextra -std=c++11
CXXBINARY := exercise2
CXXSOURCE := exercise2.cpp

JAVAC := javac
JFLAGS :=
JAVABINARY := Exercise2.class
JAVASOURCE := Exercise2.java

# Default target to build all binaries
all: $(CBINARY) $(CXXBINARY) $(JAVABINARY)

# Rule to build the C binary
$(CBINARY): $(CSOURCE)

# Rule to build the C++ binary
$(CXXBINARY): $(CXXSOURCE)

# Rule to build the Java binary
$(JAVABINARY): $(JAVASOURCE)
	$(JAVAC) $(JFLAGS) $<

# Rule to clean up the build artifacts
clean:
	rm -f $(CBINARY) $(CXXBINARY) $(JAVABINARY) *.class