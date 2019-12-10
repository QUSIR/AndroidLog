#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "Logger.h"

#include "Log.h"

#define LOGNAME_FORMAT "%s/%s.log"
#define DATE_SIZE 10
#define DATE_FORMAT "%Y%m%d"

using namespace std;

#define DEBUGSAVELOG 1

Logger* Logger::instance=NULL;
Logger::Garbo Logger::garbo;

Logger* Logger::getInstance()
{
	if(instance==NULL)
	{
		Logger* inst=instance;
		if(inst==NULL)
		{
			inst=new Logger();
		}
		instance=inst;
	}
	return instance;
}

Logger::Logger(void){
    init();
    openLogFile();
}

Logger::~Logger(void)
{
    closeLogFile();
}

void Logger::init(){
    outFileStream=new ofstream;
    if(outFileStream==NULL){
        printf("new ofstream failed:");
        exit(-1);
    }
    path="/sdcard/SaveLog/";
    level=0;
}

void Logger::openLogFile(){
    char fileName[512];
    memset(fileName,0,512);
    getLogFileName(fileName);
    outFileStream->open(fileName, ios::app);
    if(!outFileStream->is_open()){
	printf("fail to open log file, log file name=%s",fileName);
        exit(-1);
    }
}

void Logger::getLogFileName(char *fileName){
    char date_str[DATE_SIZE];
    getNowString(DATE_FORMAT,date_str,DATE_SIZE);
    sprintf(fileName,LOGNAME_FORMAT,path.c_str(),date_str);
}

void Logger::closeLogFile(){
    if(outFileStream==NULL) return;
    if(outFileStream->is_open()) outFileStream->close();
    delete outFileStream;
    outFileStream=NULL;
}

void Logger::log(int msgLevel, const char *info){
    if(msgLevel<level) return;
    char time_buff[32];
    getNowString("%Y-%m-%d  %H:%M:%S",time_buff,32);
    if((outFileStream!=NULL)&&(outFileStream->is_open())){
        switch(msgLevel){
        case 0:
            *outFileStream<<"Debug\t";
            break;
        case 1:
            *outFileStream<<"Info\t";
            break;
        case 2:
            *outFileStream<<"Warning\t";
            break;
        case 3:
            *outFileStream<<"Error\t";
            break;
        default:
            break;
        }
        *outFileStream<<time_buff<<info<<endl;
    }
}


void Logger::getNowString(const char *format, char *output,int size){
    memset(output,0,size);
    time_t now;
    time(&now);
    strftime(output, size, format, localtime(&now));
}

void log_debug(const char *format...){
    char buff[1024]={'\0'};
    if(DEBUGSAVELOG==1){
        va_list args;
        va_start(args, format);
        vsprintf(buff, format, args);
        va_end(args);
        Logger::getInstance()->log(LEVEL_DEBUG,buff);
        LOGD("%s",buff);
    } else{
        va_list args;
        va_start(args, format);
        vsprintf(buff, format, args);
        va_end(args);
        LOGD("%s",buff);
    }
    //__android_log_print(ANDROID_LOG_DEBUG, "softsim", format...);
}

void log_info(const char *format...){
    char buff[1024];
    memset(buff, 0, 1024);
    va_list args;
    va_start(args, format);
    vsprintf(buff, format, args);
    va_end(args);
    Logger::getInstance()->log(LEVEL_INFO,buff);
}

void log_warning(const char *format...){
    char buff[1024];
    memset(buff, 0, 1024);
    va_list args;
    va_start(args, format);
    vsprintf(buff, format, args);
    va_end(args);
    Logger::getInstance()->log(LEVEL_WARNING,buff);
}

void log_error(const char *format...){
    char buff[1024];
    memset(buff, 0, 1024);
    va_list args;
    va_start(args, format);
    vsprintf(buff, format, args);
    va_end(args);
    Logger::getInstance()->log(LEVEL_ERROR,buff);
}
