CC=g++
CFLAGS=-std=gnu++11 -I ../../util/ -I ../../include/memory/ -I ../../include/type_traits
LDFLAGS=
SOURCES=type_traits_st.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=type_traits_st

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	rm -rf *.o $(EXECUTABLE)


