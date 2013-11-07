//Copyright Adrian McMenamin <acm538@york.ac.uk>, 2013

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include <iostream>
#include "lackeymlfile.hpp"

using namespace std;
using namespace xercesc;

class ThreadCountHandler: public DefaultHandler
{
	private:
	int count;
	int switches;
	int current;

	public:
	ThreadCountHandler(){count = 0; switches = 0; current = 0;}
	void startElement(const XMLCh* const uri, const XMLCh* const localname,
		const XMLCh* const qname, const Attributes attrs) {
		char* temp = XMLString::transcode(localname);
		if (strcmp(temp, "thread") == 0) {
			char* threadID = XMLString::transcode(attrs.getvalue("tid"));
			long int tid = strtol(threadID, &threadID, 16); //hex
			if (tid != current) {
				current = tid;
				cout << "Now made " << ++switches << "thread switches and in thread ";
				cout << current;
				if (tid > count)
					count++;
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

	return 0;
}
