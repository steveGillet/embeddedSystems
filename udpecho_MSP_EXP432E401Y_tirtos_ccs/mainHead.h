/*
 * mainHead.h
 *
 *  Created on: Sep 18, 2022
 *      Author: root
 */

#ifndef MAINHEAD_H_
#define MAINHEAD_H_

#define TICKERNUM   16
#define REGISTERNUM 32
#define SCRIPTNUM 32
#define QUELEN 16

#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <ti/drivers/UART.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Board.h>
#include <ti/drivers/Timer.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Semaphore.h>

#include "ti_drivers_config.h"

typedef struct variables{
    char *aboutOutput;
    int messageIndex;
    char *newLine;
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
    const char *helpRegOutput;
    const char *helpScriptOutput;
    const char *helpIfOutput;

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
    char payload[128];
    int callbackCount;
    int period;
} Callback;

typedef struct _tickers{
    char payload[128];
    int tickerCount;
    int delay;
    int period;
} Ticker;

typedef struct _message{
    char message[128]; //allocate memory
} Message;

typedef struct _messageQueue{
    Message messages[QUELEN];
    int readIndex;
    int writeIndex;
} MessageQueue;

typedef struct _script{
    char payload[128];
} Script;

typedef struct _globals {
    Timer_Handle timer0;
    Timer_Handle timer1;
    UART_Handle uart;
    Variables var;
    MessageQueue msgQue;
    Callback callback[3];
    Ticker ticker[TICKERNUM];
    Semaphore_Handle msgQueSem;
    int32_t reg[REGISTERNUM];
    Script script[SCRIPTNUM];
} Globals;

#ifndef MAIN
extern
#endif
Globals Glo;

void timerCallback(Timer_Handle myHandle, int_fast16_t status);
void tickerCallback(Timer_Handle myHandle, int_fast16_t status);

void addMessage(const char *inMessage);
void commandEntry(char *command);
int commandTest(const char *command, const char *compareString);
int indexOf(const char *string, const char character);
void infra(void);
void initializeDrivers(void);
void leftButtonCallback(void);
void rightButtonCallback(void);
char *secondString(char *fullString);
void stringCopy(char *outString, const char *copiedString);
void taskCommandServicer(void);

#endif /* MAINHEAD_H_ */
