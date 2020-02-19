include /usr/local/include/cantera/Cantera.mak

CC=gcc
CXX=g++
RM=rm -f
CXXFLAGS=-pthread -O3 -Wno-inline -g -std=c++0x
CPPFLAGS=$(CANTERA_INCLUDES)
LDFLAGS=
LDLIBS=$(CANTERA_LIBS)

SRCS=NASA_coeffs.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: NASA_coeffs

clean:
	$(RM) $(OBJS) NASA_coeffs

dist-clean: clean
	$(RM) *~ 
