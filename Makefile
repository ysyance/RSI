PREFIX_XENO :=  
EXECUTABLE := exec
LIBDIR := 
LIBS := antlr4-runtime
INCLUDES := ./src/Antlr4 ./src/TinyXml 
SRCDIR := ./src ./src/TinyXml

CC = gcc
CXX = g++
CFLAGS := -std=c++11 -g

CPPFLAGS += $(CFLAGS) $(addprefix -I,$(INCLUDES))

RM-F := rm -f

SRCS := $(wildcard *.cpp) $(wildcard $(addsuffix /*.cpp, $(SRCDIR)))
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

.PHONY : all clean rebuild

all: $(EXECUTABLE)

clean:
	@$(RM-F) ${OBJS}

rebuild: clean all

$(EXECUTABLE) : $(OBJS)
	$(CXX) -o $(EXECUTABLE) $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))
