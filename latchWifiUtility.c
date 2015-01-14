/*
* Utility for install/uninstall latch Wi-Fi Plugin.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "latchWifi.h"
#include "latch.h"

//Write the Application ID and Secret here.
#define APP_ID "UYjWUpLdqF6JvmjPFgLX"
#define SECRET "zizv8LL8sUs9YGnpLVsUuymXDhDnNdBPBbA3i4nU"

void usage(){

    printf("Latch Wifi Plugin installer/uninstaller\n");
    printf("2015, Tavella Ezequiel @EzequielTBH\n");
    printf("Usage: latchWifiUtility [Options]\n");
    printf("Options:\n");
    printf("\t-i [Pair Code]\t Pair with Latch\n");
    printf("\t-u \t\t Unpair with Latch\n");
    printf("\t-s \t\t Query status Latch\n");
    printf("Note: This program need read/write privileges in latchWifi.conf file!!!\n");
}

int main(int argc, char *argv[]){

    printf("Important: This program need read/write privileges in latchWifi.conf file!!!\n");
    if(strcmp(argv[1],"-i") == 0){

        init(APP_ID,SECRET); 
        if ( pairLW(argv[2]) != 1){

            printf("\nBad pair with Latch ... Try again..\n");
            exit(-1);
        }
        printf("\nAll OK!!\n");
        return 0;
    }

    else if (strcmp(argv[1],"-u") == 0){

        initLW();
        if ( unpairLW() != 1){

               printf("\nBad unpair with Latch ... Try again..\n");
               exit(-1);
        }
        printf("\nAll OK!!\n");
        return 0;
    }
    else if(strcmp(argv[1],"-s") == 0 ){

        initLW();
        if(statusLW() == 1)
            printf("\n Latch NO Activated... Free Login\n");
        else
            printf("\n Latch Activated... Login Blocked\n");
        return 0;    
    }
    usage();
    return 0;
}
