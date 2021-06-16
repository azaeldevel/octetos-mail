
#ifndef OCTETOS_CORE_MAIL_HH
#define OCTETOS_CORE_MAIL_HH

#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>


namespace oct::mail
{

class SMTP
{
private:
	CURL *curl;
	std::string server;
	int port;
	std::string username;
	std::string password;
	static const char *payload_text[];
	void readConfig(const std::string& filename)const;
public:
	//
	SMTP();
	~SMTP();
	void send();
	static size_t payload_source(char *ptr, size_t size, size_t nmemb, void *userp);
};


} 

#endif