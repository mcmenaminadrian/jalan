//Code to manipulate the raw lackeyml file

class LackeymlFile
{
	string xmlFile;
	
	public:
	LackeymlFile(const string& fileName) {xmlFile = fileName;}
	int countThreads() const;
};
