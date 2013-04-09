#include <fstream>
#include <string>

using namespace std;

class LOGGER
{
	fstream f;
public:
	LOGGER(std::string file)
	{
		f.open(file,ios::out);
	}
	void out(std::string s)
	{
		f<<s;
	}
	void out (int i)
	{
		f<<i;
	}
	void out (char c)
	{
		f<<c;
	}
	void out (double b)
	{
		f<<b;
	}
	void end()
	{
		f<<endl;
	}
	~LOGGER()
	{
		f.close();
	}
};

