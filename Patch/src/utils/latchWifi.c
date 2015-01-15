/*
* Latch Wi-Fi plugin.
* Copyright (C) 2015 Tavella Ezequiel (@EzequielTBH)
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "latch.h"

//Write the option choiced for error condition: 0 NO allow connection , 1 YES allow connection.
#define OPTION_ERROR 1

//IMPORTANT!!!
//Write the Application ID, Secret and the configuration file path here.
#define APP_ID " "
#define SECRET " "
#define FILE_CONFIG "/etc/latchWifi.conf"

char accountId[65];

int initLW(){

	FILE * file;
	file = fopen(FILE_CONFIG,"rt");
	if(!file)
		return 0;

	if( fscanf(file,"%64s",accountId) == EOF)
		return 0;

	init(APP_ID,SECRET);
	fclose(file);
	return 1;
}

int statusLW(){
	
	char * buffer;
	int response = OPTION_ERROR;

	buffer = status(accountId);
	if(buffer == NULL || strcmp(buffer,"") == 0){
		
        free(buffer);
		return OPTION_ERROR;	
	}

	if (strstr(buffer, "\"status\":\"off\"") != NULL)
		response = 0;
	else if (strstr(buffer, "\"status\":\"on\"") != NULL)
		response = 1;
	
	free(buffer);
	return response;	
}

int pairLW(char * code){

	FILE * file;
	char * buffer = NULL;
      
	buffer = pair(code);
    printf("Account Id:%.64s",buffer+22);
	if( strstr(buffer,"{\"data\":{\"accountId\":") != NULL ){

		file = fopen(FILE_CONFIG,"wt");
		if(!file)
			return -1;
		fprintf(file, "%.64s\n", buffer+22);
		fclose(file);
		free(buffer);
		return 1;
	}
	free(buffer);
	return 0;
}

int unpairLW(){

	FILE * file;
	char * buffer;
    	char command[50];
    
	buffer = unpair(accountId);
	if( strstr(buffer,"{}") != NULL ){

	    strcat(command,"rm ");
	    strcat(command, FILE_CONFIG);
		system(command);
		free(buffer);
		return 1;
	}
	free(buffer);
	return 0;
}

