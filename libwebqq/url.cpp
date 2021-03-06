/**
 * @file   test.c
 * @author mathslinux <riegamaths@gmail.com>
 * @date   Thu May 24 22:56:52 2012
 * 
 * @brief  The Encode and Decode helper is based on
 * code where i download from http://www.geekhideout.com/urlcode.shtml
 * 
 * 
 */
#include <string>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "url.hpp"

/* Converts a hex character to its integer value */
static char from_hex(char ch)
{
  return isdigit(ch) ? ch - '0' : tolower(ch) - 'A' + 10;
}

/* Converts an integer value to its hex character*/
static char to_hex(char code)
{
  static char hex[] = "0123456789ABCDEF";
  return hex[code & 15];
}

/** 
 * NB: be sure to free() the returned string after use
 * 
 * @param str 
 * 
 * @return A url-encoded version of str
 */
std::string url_encode(const char *str)
{
    if (!str)
        return "";
	
	char buf[strlen(str) * 3 + 1];
    char *pstr = (char*) str, *pbuf = buf;
    
    while (*pstr) {
        if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~' ) 
            *pbuf++ = *pstr;
        else 
            *pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);
        pstr++;
    }
    *pbuf = '\0';
    return buf;
}

std::string url_encode(const std::string str)
{
	return url_encode(str.c_str());
}

std::string url_whole_encode(const char *str)
{
    if (!str)
        return NULL;

    char *pstr = (char*)str;
	char *pbuf = new char[strlen(str) * 3 + 1];
    while (*pstr) {
        if (isalnum(*pstr) || *pstr == '-' || *pstr == '_' || *pstr == '.' || *pstr == '~' ||*pstr == ':' ||*pstr == '/'
                || *pstr == '&'|| *pstr == '=' || *pstr == '?') 
            *pbuf++ = *pstr;
        else 
            *pbuf++ = '%', *pbuf++ = to_hex(*pstr >> 4), *pbuf++ = to_hex(*pstr & 15);
        pstr++;
    }
    *pbuf = '\0';
	std::string ret = pbuf;
	delete[] pbuf;
	return ret;
}

/** 
 * NB: be sure to free() the returned string after use
 * 
 * @param str 
 * 
 * @return A url-decoded version of str
 */
std::string url_decode(const char *str)
{
    if (!str) {
        return NULL;
    }

    char *pstr = (char*)str;
	char *pbuf = new char[strlen(str) * 3 + 1];
    while (*pstr) {
        if (*pstr == '%') {
            if (pstr[1] && pstr[2]) {
                *pbuf++ = from_hex(pstr[1]) << 4 | from_hex(pstr[2]);
                pstr += 2;
            }
        } else if (*pstr == '+') { 
            *pbuf++ = ' ';
        } else {
            *pbuf++ = *pstr;
        }
        pstr++;
    }
    *pbuf = '\0';
	std::string ret = pbuf;
	delete[] pbuf;
	return ret;
}

/*
char* to_gbk(char* utf8)
{
    char buf[512];
    iconv_t cd = iconv_open("gbk","utf-8");

    char* inbuf = utf8;
    size_t inlen = strlen(utf8);
    char* outbuf = buf;
    size_t outlen = sizeof(buf);
    iconv(cd,&inbuf,&inlen,&outbuf,&outlen);
    iconv_close(cd);
    if(inlen!=0) return NULL;
    *outbuf = '\0';
    return s_strdup(buf);
}

*/
