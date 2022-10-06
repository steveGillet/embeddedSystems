/*
 * mainHead.h
 *
 *  Created on: Sep 18, 2022
 *      Author: root
 */

#ifndef MAINHEAD_H_
#define MAINHEAD_H_

int commandTest(char command[], char compareString[]){
    int i;
    for (i = 0; i < strlen(command); i++){
        if(compareString[i] != command[i]) return 0;
    }
    return 1;
}

void secondString(char outString[], char fullString[]){
    int i = 0;
    int j;
    for (i = 0; i < strlen(fullString); i++){
        if(fullString[i] == ' ') break;
    }
    i++;
    for (j = 0; j < (strlen(fullString) - i); j++){
        outString[j] = fullString[i];
    }
}


#endif /* MAINHEAD_H_ */
