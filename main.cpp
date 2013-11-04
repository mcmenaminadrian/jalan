// JALAN - Just Another Lackey ANalyser
// Copyright Adrian McMenamin <acm538@york.ac.uk>, 2013
// Licensed under GNU GPL version 3
//
// Processes XMLised output from Valgrind's Lackey tool
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <xercesc/util/PlatformUtils.hpp>


using namespace std;
using namespace xercesc;


void usage()
{
	cout << "JALAN - Just Another Lackey ANalyser" << endl;
	cout << "Copyright Adrian McMenamin, acm538@york.ac.uk, 2013" << endl;
	cout << "Licensed under GNU GPL version 3." << endl;
	cout << "Usage..." << endl;
	cout << "jalan [options] inputfile" << endl;
	cout << "Options..." << endl;
	cout << "-f	Specify input file name" << endl;
	cout << "-?	Print this usage message" << endl;
}

int main(int argc, char* argv[])
{

	string xmlFile;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-f") == 0)
		{
			if (argc >= i + 1) {
				xmlFile = argv[i + 1];
				i++;
				continue;
			} else {
				usage();
				return 1;
			}
		}

		if (strcmp(argv[i], "-?") == 0) {
			usage();
			return 0;
		}
	}
	try {
		XMPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		cout << "Failed to initialise Xerces XML engine." << endl;
		char *message = XMLString::transcode(toCatch.getMessage());
		cout << message << endl;
		XMString::release(&message);
		return 1;
	}

	XMLPlatformUtils::Terminate();
	return 0;
}		
