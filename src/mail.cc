


//#include <libxml/xmlmemory.h>
//#include <libxml/parser.h>
//#include <libxml/xmlreader.h>

#include <iostream>


#include <octetos/core/Error.hh>
#include "mail.hh"


 
/*
 * This is a simple example show how to send an email using libcurl's SMTP
 * capabilities.
 *
 * Note that this example requires libcurl 7.66.0 or above.
 */ 
 
/* The libcurl options want plain addresses, the viewable headers in the mail
 * can very well get a full name as well.
 */ 
#define FROM_ADDR    "<azael.devel@gmail.com>"
#define SENDER_ADDR  "<azael.devel@gmail.com>"
#define TO_ADDR      "<azael.rmartz@gmail.com>"
 
#define FROM_MAIL    "Azael " FROM_ADDR
#define SENDER_MAIL  "Azael " SENDER_ADDR
#define TO_MAIL      "A Receiver " TO_ADDR
 

 

 



namespace oct::mail
{

	struct upload_status 
	{
  		int lines_read;
	};








	


	const char * SMTP::payload_text[] = 
	{
	  "To: " TO_MAIL "\r\n",
	  "From: " FROM_MAIL "\r\n",
	  "Sender: " SENDER_MAIL "\r\n",
	  "Message-ID: <arm2>\r\n",
	  "Subject: SMTP example message\r\n",
	  "\r\n", /* empty line to divide headers from body, see RFC5322 */ 
	  "The body of the message starts here.\r\n",
	  "\r\n",
	  "It could be a lot of lines, could be MIME encoded, whatever.\r\n",
	  "Check RFC5322.\r\n",
	  NULL
	};

	
	size_t SMTP::payload_source(char *ptr, size_t size, size_t nmemb, void *userp)
	{
	  	struct upload_status *upload_ctx = (struct upload_status *)userp;
	  	const char *data;
	 
	  	if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
			return 0;
	  	}
	 
	  	data = payload_text[upload_ctx->lines_read];
	 
	  	if(data) 
		{
			size_t len = strlen(data);
			memcpy(ptr, data, len);
			upload_ctx->lines_read++;
	 
			return len;
	  	}
	 
	  	return 0;
	}

	SMTP::SMTP()
	{
		curl = curl_easy_init();
		
	}
	SMTP::~SMTP()
	{
		curl_easy_cleanup(curl);
	}
	void SMTP::send()
	{
  		CURLcode res = CURLE_OK;
	  	struct curl_slist *recipients = NULL;
	  	struct upload_status upload_ctx;
		
	  	upload_ctx.lines_read = 0;
		
	  	if(curl) 
		{
			curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:465");
			curl_easy_setopt(curl, CURLOPT_USERNAME, "azael.devel@gmail.com");
			curl_easy_setopt(curl, CURLOPT_PASSWORD, "---"); 

			curl_easy_setopt(curl, CURLOPT_SASL_AUTHZID, "ursel");
			curl_easy_setopt(curl, CURLOPT_LOGIN_OPTIONS, "AUTH=*");
			curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM_ADDR);
			recipients = curl_slist_append(recipients, TO_ADDR);
			curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
			curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
			curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
			curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
		 	
			res = curl_easy_perform(curl);

			if(res != CURLE_OK) 
			{
				fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));
			}
			curl_slist_free_all(recipients);

	  	}		
	}
}
