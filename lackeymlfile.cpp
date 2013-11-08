//Copyright Adrian McMenamin <acm538@york.ac.uk>, 2013

#include <iostream>
#include <string>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace std;
using namespace xercesc;

#include "lackeymlfile.hpp"

class ThreadCountHandler: public DefaultHandler
{
	int count;
	int switches;
	int current;
	long int threadbitmap;

public:
	ThreadCountHandler(){
		count = 0;
		switches = 0;
		current = 0;
		threadbitmap = 0;
	}

	void startElement(const XMLCh* const uri, const XMLCh* const localname,
		const XMLCh* const qname, const Attributes& attrs) {
		char* temp = XMLString::transcode(localname);
		if (strcmp(temp, "thread") == 0) {
			char* threadID = XMLString::transcode(attrs.getValue("tid"));
			long int tid = strtol(threadID, &threadID, 16); //hex
			if (tid != current) {
				current = tid;
				cout << "Now made " << ++switches << "thread switches and in thread ";
				cout << current;
				if (threadbitmap & (1 << (tid - 1))) {
					count++;
					threadbitmap = threadbitmap | (1 << (tid - 1));
				}
				cout << " of " << count << " threads." << endl;
			}
			XMLString::release(&threadID);
		}
		XMLString::release(&temp);
	} 

	void fatalError(const SAXParseException& exception)
	{
		char* message = XMLString::transcode(exception.getMessage());
		cout << "Fatal Error: " << message
			 << " at line: " << exception.getLineNumber()
			 << endl;
		XMLString::release(&message);
	}
};



int LackeymlFile::countThreads() const
{
	//initialise SAX2 parser
        SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
	parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
	//parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional

	ThreadCountHandler* countHandler = new ThreadCountHandler();
	parser->setContentHandler(countHandler);
	parser->setErrorHandler(countHandler);

        try {
            parser->parse(xmlFile);
        }
        catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cout << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return -1;
        }
        catch (const SAXParseException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cout << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return -1;
        }
        catch (...) {
            cout << "Unexpected Exception \n" ;
            return -1;
        }

        delete parser;
        delete countHandler;
        return 0;
	return 0;
}
