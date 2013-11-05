// JALAN - Just Another Lackey ANalyser
// Copyright Adrian McMenamin <acm538@york.ac.uk>, 2013
// Licensed under GNU GPL version 3
//
// Processes XMLised output from Valgrind's Lackey tool
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include "lackeymlfile.hpp"


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
	cout << "-f [name]	Specify input XML file name" << endl;
	cout << "-d [name]	Load existing data file" << endl;
	cout << "-t 		Map thread use" << endl;	
	cout << "-?		Print this usage message" << endl;
}

int main(int argc, char* argv[])
{

	string xmlFile;
	string dataFile;
	bool readXMLFile = false;
	bool readDataFile = false;
	bool mapThreads = false;
	LackeymlFile *rawFile = NULL;
	ProcessedFile *cookedFile = NULL;
	SAX2XMLReader* saxParser = NULL;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-f") == 0)
		{
			if (argc >= i + 1) {
				xmlFile = argv[i + 1];
				i++;
				readXMLFile = true;
				continue;
			} else {
				usage();
				return 1;
			}
		}

		if (strcmp(argv[i], "-d") == 0)
		{
			if (argc >= i + 1) {
				dataFile = argv[i + 1];
				i++;
				readDataFile = true;
				continue;
			} else {
				usage();
				return 1;
			}
		}

		if (strcmp(argv[i], "-t") == 0) 
			mapThreads = true;

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

	// Got this far - so we have we been tasked with something?
	if (readXMLFile)
		rawFile = new LackeymlFile(xmlFile);
	if (readDataFile)
		cookedFile = new ProcessedFile(dataFile);
		

	XMLPlatformUtils::Terminate();
	return 0;
}		
