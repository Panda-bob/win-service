/*parse_ini.h*/
#ifndef PARSE_INI_H
#define PARSE_INI_H

#include <stdio.h>  
#include <string.h>

int GetIniKeyString(char *title,char *key,char *filename,char *buf);

int PutIniKeyString(char *title,char *key,char *val,char *filename);

#endif /*PARSE_INI_H*/
