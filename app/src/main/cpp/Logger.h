#pragma once
#include <fstream>
#include <string>

using namespace std;

enum{
    LEVEL_DEBUG=0,
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR
};

class Logger
{
public:
    void log(int msgLevel,const char *info);
    static Logger* getInstance();

private:
    Logger(void);
    ~Logger(void);
    Logger(const Logger &obj);
    Logger& operator=(const Logger& obj);

    ofstream *outFileStream;
    int level;
    string path;
    void getNowString(const char *format,char *output,int size);
    void openLogFile();
    void closeLogFile();
    void init();
    void getLogFileName(char *fileName);

    static Logger* instance;
    class Garbo
    {
    public:
	    ~Garbo()
	    {
		    if(NULL!=Logger::instance)
		    {
			    delete Logger::instance;
			    Logger::instance=NULL;
		    }
	    }
    };
    static Garbo garbo;
};

void log_debug(const char *format,...);
void log_info(const char *format,...);
void log_warning(const char *format,...);
void log_error(const char *format,...);
