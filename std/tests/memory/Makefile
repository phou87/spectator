CC=g++
CFLAGS=-std=gnu++11 -I ../../pre/ -I ../../include/memory/ -I ../../include/
LDFLAGS=
SOURCES=allocator_traits_st.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=allocator_traits_st

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -c

clean:
	rm -rf *.o $(EXECUTABLE)


