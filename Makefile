all: jalan

jalan: main.cpp lackeymlfile.cpp lackeymlfile.hpp
	g++ -O2 -o jalan -I/usr/local/pkg/xerces-c-3.1.1-x86_64-1/include -Wall main.cpp lackeymlfile.cpp -l/usr/local/pkg/xerces-c-3.1.1-x86_64-1/libxerces-c
