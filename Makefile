all: jalan

jalan: main.cpp lackeymlfile.cpp lackeymlfile.hpp
	g++ -O2 jalan -Wall main.cpp lackeymlfile.cpp -lxerces-c
