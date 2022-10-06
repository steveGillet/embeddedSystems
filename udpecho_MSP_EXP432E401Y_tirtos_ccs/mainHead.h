/*
 * mainHead.h
 *
 *  Created on: Sep 18, 2022
 *      Author: root
 */

#ifndef MAINHEAD_H_
#define MAINHEAD_H_

#define TICKERNUM 16

#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//#include <pthread.h>
/* BSD support */
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>

#include <ti/net/slnetutils.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Board.h>
#include <ti/drivers/Timer.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>

#define UDPPACKETSIZE 1472
#define MAXPORTLEN    6

extern void fdOpenSession();
extern void fdCloseSession();
extern void *TaskSelf();

#include "ti_drivers_config.h"

typedef struct variables{
    char *aboutOutput;
    int messageIndex;
    char *newLine;
    int queLen;
    char        input;
    const char *echoPrompt;

    const char *helpHelpOutput;
    const char *helpAboutOutput;
    const char *helpPrintOutput;
    const char *helpMemrOutput;
    const char *helpGPIOOutput;
    const char *helpErrorOutput;
    const char *helpTimerOutput;
    const char *helpCallbackOutput;
    const char *helpTickerOutput;

    const char *help;
    const char *about;
    char *command;
    char *previousCommand;
    char *callbackCommand;
    int i;
    char *arrowInput;
    // overflow, incorrect command, invalid mem address
    int errorCount[3];
    int overflowFlag;
} Variables;

typedef struct _callbacks{
    char *payload[3];
    int callbackNumber[3];
    int period;
} Callback;

typedef struct _tickers{
    char *payload[TICKERNUM];
    int tickerCount[TICKERNUM];
    int delay[TICKERNUM];
    int period[TICKERNUM];
} Ticker;

typedef struct _message{
    char message[128]; //allocate memory
    int queIndex;
    int msgIndex;
} Message;

typedef struct _messageQueue{
    Message messages[8];
    int readIndex;
    int writeIndex;
} MessageQueue;

typedef struct _globals {
    Timer_Handle timer0;
    Timer_Handle timer1;
    UART_Handle uart;
    Variables var;
    MessageQueue msgQue;
    Callback callback;
    Ticker ticker;
    Semaphore_Handle msgQueSem;
} Globals;

#ifndef MAIN
extern
#endif
Globals Glo;

void timerCallback(Timer_Handle myHandle, int_fast16_t status);
void tickerCallback(Timer_Handle myHandle, int_fast16_t status);

void commandEntry(char *command);
void initializeDrivers(void);
void stringCopy(char *outString, const char *copiedString);
char *secondString(char *fullString);
int commandTest(const char *command, const char *compareString);
void addMessage(const char *inMessage);
void commandServicer(void);
void infra(void);
void leftButtonCallback(void);
void rightButtonCallback(void);

#endif /* MAINHEAD_H_ */