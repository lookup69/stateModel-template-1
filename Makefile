TARGET   = ut
SOURCES  = main.cpp thread.cpp machine.cpp  
OBJECTS  = $(addsuffix .o, $(basename $(SOURCES)))
DEPS     = $(addsuffix .d, $(basename $(SOURCES)))
LDFLAGS  = -pthread 
CPPFLAGS = -std=c++11 -g -Wall -fpermissive
CFLAGS   = -g -Wall


all: $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LDFLAGS)

#include dependency
-include $(DEPS)

%.o : %.cpp
	g++ $(CPPFLAGS) -c $< -o $@

%.o : %.c
	gcc $(CFLAGS) -c $< -o $@

# create dependency file (.d)
%.d: %.c
	gcc $(CFLAGS) -MM $< | sed 's/$*.o/& $@/g' > $@

# create dependency file (.d)
%.d: %.cpp
	g++ $(CPPFLAGS) -MM $< | sed 's/$*.o/& $@/g' > $@ 

clean:
	rm -f *.d
	rm -f *.o
	rm -f $(TARGET)
