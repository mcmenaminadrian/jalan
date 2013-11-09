CXX=g++
XERCESC=/n/staffstore/adrianm/xercesinstall
CFLAGS=-O2 -I$(XERCESC)/include -Wall
RPATH=-rpath $(XERCESC)/lib

LDFLAGS=-Wl,$(RPATH) $(XERCESC)/lib/libxerces-c.so 

all: jalan

jalan: main.cpp lackeymlfile.cpp lackeymlfile.hpp
	$(CXX) $(CFLAGS) $(LDFLAGS) -o jalan main.cpp lackeymlfile.cpp
