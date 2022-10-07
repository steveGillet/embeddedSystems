/*
 * infrastructure.c
 *
 *  Created on: Sep 26, 2022
 *      Author: root
 */

#include <mainHead.h>

char aboutOutput[128] = "";
int timerCallbackCount = 0;
int leftButtonCallbackCount = 0;
int rightButtonCallbackCount = 0;
int messageIndex = 0;
char newLine[2] = "\r\n";
int queLen = 8;
extern Semaphore_Handle semaphore0;

char        input;
const char echoPrompt[] = "\r\nWelcome to MSP432:\r\n";

const char helpHelpOutput[] = "\r\n-help prints a complete list of supported commands\r\n";
const char helpAboutOutput[] = "\r\n-about prints the name, assignment number, version and date/time of compile\r\n";
const char helpPrintOutput[] = "\r\n-print prints any text following the command\r\n";
const char helpMemrOutput[] = "\r\n-memr shows what is in the memory space specified after the command\r\n\tFlash: 0x00000000 to 0x000FFFFF\r\n\tSRAM: 0x20000000 to 0x2003FFFF\r\n\tPeripherals: 0x40000000 to 0x44055000\r\n";
const char helpGPIOOutput[] = "\r\n-gpio allows to you read (-r), toggle (-t), and write (-w) to the GPIO pins.\r\n\tThe first argument is the pin number, second argument is the command type (-t, -w, -r),\r\n\tand the third is 1 or 0 if you are writing high or low\r\n\t0-3 are LEDs 1-4, 4 and 5 are the left and right buttons, 6 is PK5 and 7 is PD4(*RX)\r\n";
const char helpErrorOutput[] = "\r\n-error shows the current count of errors.\r\n";
const char helpTimerOutput[] = "\r\n-timer gets and sets the current timer period. With no argument it gets. \r\n\tWith a number above 100 following the command the timer is set to that number in microseconds.\r\n";
const char helpCallbackOutput[] = "\r\n-callback gets and sets callback commands for a timer and the two side buttons.\r\n\tThe first argument is which callback (0 = timer, 1 = left button, 2 = right button).\r\n\tThe second argument is the number of callbacks (-1 is infinite).\r\n\tThe third argument is the command that you want to be called (Ex. -gpio 0 -t).\r\n";
const char helpTickerOutput[] = "\r\n-ticker gets and sets callback commands for 16 tickers that call every 10 ms."
                                "\r\n\tThe first argument is which of the 16 tickers to use."
                                "\r\n\tThe second argument is the delay before the ticker callback starts in multiples of 10 ms."
                                "\r\n\tThe third argument is the period between ticker calls."
                                "\r\n\tThe fourth argument is the number of callbacks called in total (-1 = infinite)."
                                "\r\n\tThe fifth argument is the command that you would like to be called.\r\n";

const char help[] = "-help";
const char about[] = "-about";
char command[128] = "";
char previousCommand[128] = "";
char callbackCommand[128] = "";
int i = 0;
char arrowInput[2] = "";
// overflow, incorrect command, invalid mem address
int errorCount[] = {0, 0, 0};
int overflowFlag = 0;
char timerCallbackPayload[128] = "";
char leftButtonCallbackPayload[128] = "";
char rightButtonCallbackPayload[128] = "";
int callbackPeriod = 1000000;

char tickerPayload0[128] = "";
char tickerPayload1[128] = "";
char tickerPayload2[128] = "";
char tickerPayload3[128] = "";
char tickerPayload4[128] = "";
char tickerPayload5[128] = "";
char tickerPayload6[128] = "";
char tickerPayload7[128] = "";
char tickerPayload8[128] = "";
char tickerPayload9[128] = "";
char tickerPayload10[128] = "";
char tickerPayload11[128] = "";
char tickerPayload12[128] = "";
char tickerPayload13[128] = "";
char tickerPayload14[128] = "";
char tickerPayload15[128] = "";

void infra(void){
    Glo.var.helpAboutOutput = helpAboutOutput;
    Glo.var.input = input;
    Glo.var.echoPrompt = echoPrompt;
    Glo.var.helpHelpOutput = helpHelpOutput;
    Glo.var.helpPrintOutput = helpPrintOutput;
    Glo.var.helpMemrOutput = helpMemrOutput;
    Glo.var.helpGPIOOutput = helpGPIOOutput;
    Glo.var.helpErrorOutput = helpErrorOutput;
    Glo.var.helpTimerOutput = helpTimerOutput;
    Glo.var.helpCallbackOutput = helpCallbackOutput;
    Glo.var.helpTickerOutput = helpTickerOutput;
    Glo.var.help = help;
    Glo.var.about = about;
    Glo.var.command = command;
    Glo.var.previousCommand = previousCommand;
    Glo.var.callbackCommand = callbackCommand;

    Glo.var.i = i;
    Glo.var.arrowInput = arrowInput;
    Glo.var.errorCount[0] = errorCount[0];
    Glo.var.errorCount[1] = errorCount[1];
    Glo.var.errorCount[2] = errorCount[2];
    Glo.var.overflowFlag = overflowFlag;

    sprintf(aboutOutput, "\r\nSteve Gillet, Assignment 3, v1.431234, %s, %s\r\n", __TIME__, __DATE__); //put outside subroutine
    Glo.var.aboutOutput = aboutOutput;
    Glo.callback.callbackNumber[0] = timerCallbackCount;
    Glo.callback.callbackNumber[1] = leftButtonCallbackCount;
    Glo.callback.callbackNumber[2] = rightButtonCallbackCount;
    Glo.var.messageIndex = messageIndex;
    Glo.var.newLine = newLine;
    Glo.msgQue.readIndex = 0;
    Glo.msgQue.writeIndex = 0;
    Glo.var.queLen = queLen;
    Glo.msgQueSem = semaphore0;
    Glo.callback.payload[0] = timerCallbackPayload;
    Glo.callback.payload[1] = leftButtonCallbackPayload;
    Glo.callback.payload[2] = rightButtonCallbackPayload;
    Glo.callback.period = callbackPeriod;

    Glo.ticker.payload[0] = tickerPayload0;
    Glo.ticker.payload[1] = tickerPayload1;
    Glo.ticker.payload[2] = tickerPayload2;
    Glo.ticker.payload[3] = tickerPayload3;
    Glo.ticker.payload[4] = tickerPayload4;
    Glo.ticker.payload[5] = tickerPayload5;
    Glo.ticker.payload[6] = tickerPayload6;
    Glo.ticker.payload[7] = tickerPayload7;
    Glo.ticker.payload[8] = tickerPayload8;
    Glo.ticker.payload[9] = tickerPayload9;
    Glo.ticker.payload[10] = tickerPayload10;
    Glo.ticker.payload[11] = tickerPayload11;
    Glo.ticker.payload[12] = tickerPayload12;
    Glo.ticker.payload[13] = tickerPayload13;
    Glo.ticker.payload[14] = tickerPayload14;
    Glo.ticker.payload[15] = tickerPayload15;

    for(i = 0; i < TICKERNUM; i++){
        Glo.ticker.period[i] = 0;
        Glo.ticker.delay[i] = 0;
        Glo.ticker.tickerCount[i] = 0;
    }

    for(i = 0; i < REGISTERNUM; i++){
        Glo.reg[i] = i * 10;
    }
}

void addMessage(const char *inMessage){
    strcpy(Glo.msgQue.messages[Glo.msgQue.writeIndex].message, inMessage);
    Glo.msgQue.messages[Glo.msgQue.writeIndex].queIndex = Glo.msgQue.writeIndex;
    Glo.msgQue.messages[Glo.msgQue.writeIndex].msgIndex = strlen(inMessage) - 1;
    Glo.msgQue.writeIndex++;
    if(Glo.msgQue.writeIndex == Glo.var.queLen) Glo.msgQue.writeIndex = 0;
}

void commandEntry(char *command) {
    if(commandTest(help, command)){
        char *helpCommand;
        helpCommand = secondString(command);

        if(strstr(helpCommand, "help")) UART_write(Glo.uart, Glo.var.helpHelpOutput, strlen(Glo.var.helpHelpOutput));
        else if(strstr(helpCommand, "about")) UART_write(Glo.uart, Glo.var.helpAboutOutput, strlen(Glo.var.helpAboutOutput));
        else if(strstr(helpCommand, "print")) UART_write(Glo.uart, Glo.var.helpPrintOutput, strlen(Glo.var.helpPrintOutput));
        else if(strstr(helpCommand, "memr")) UART_write(Glo.uart, Glo.var.helpMemrOutput, strlen(Glo.var.helpMemrOutput));
        else if(strstr(helpCommand, "gpio")) UART_write(Glo.uart, Glo.var.helpGPIOOutput, strlen(Glo.var.helpGPIOOutput));
        else if(strstr(helpCommand, "error")) UART_write(Glo.uart, Glo.var.helpErrorOutput, strlen(Glo.var.helpErrorOutput));
        else if(strstr(helpCommand, "timer")) UART_write(Glo.uart, Glo.var.helpTimerOutput, strlen(Glo.var.helpTimerOutput));
        else if(strstr(helpCommand, "callback")) UART_write(Glo.uart, Glo.var.helpCallbackOutput, strlen(Glo.var.helpCallbackOutput));
        else if(strstr(helpCommand, "ticker")) UART_write(Glo.uart, Glo.var.helpTickerOutput, strlen(Glo.var.helpTickerOutput));
        else{
            UART_write(Glo.uart, Glo.var.helpHelpOutput, strlen(Glo.var.helpHelpOutput));
            UART_write(Glo.uart, Glo.var.helpAboutOutput, strlen(Glo.var.helpAboutOutput));
            UART_write(Glo.uart, Glo.var.helpPrintOutput, strlen(Glo.var.helpPrintOutput));
            UART_write(Glo.uart, Glo.var.helpMemrOutput, strlen(Glo.var.helpMemrOutput));
            UART_write(Glo.uart, Glo.var.helpGPIOOutput, strlen(Glo.var.helpGPIOOutput));
            UART_write(Glo.uart, Glo.var.helpErrorOutput, strlen(Glo.var.helpErrorOutput));
            UART_write(Glo.uart, Glo.var.helpTimerOutput, strlen(Glo.var.helpTimerOutput));
            UART_write(Glo.uart, Glo.var.helpCallbackOutput, strlen(Glo.var.helpCallbackOutput));
            UART_write(Glo.uart, Glo.var.helpTickerOutput, strlen(Glo.var.helpTickerOutput));
       }
    }
    else if(commandTest(about, command)) UART_write(Glo.uart, Glo.var.aboutOutput, strlen(Glo.var.aboutOutput));
    else if(commandTest("-print", command)) {
        char *print;
        print = secondString(command);
        UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
        UART_write(Glo.uart, print, strlen(print));
        UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
    }
    else if(commandTest("-memr", command)) {
        char *memoryBuffer;
        long memoryAddress = 0;
        long memoryContents = 0;
        char memoryString[128] = "";
        char memoryAddressString[128] = "";
        char *ptr;

        memoryBuffer = secondString(command);
        memoryAddress = strtol(memoryBuffer, &ptr, 16);
        if(memoryAddress < 0x00000000 || (memoryAddress > 0x000FFFFF && memoryAddress < 0x20000000) || (memoryAddress > 0x2003FFFF && memoryAddress < 0x40000000) || memoryAddress > 0x44055000){
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
            UART_write(Glo.uart, "Error: Invalid Address", strlen("Error: Invalid Address"));
            errorCount[2]++;
        }

        else{
            memoryAddress = memoryAddress & 0xFFFFFFF0;
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
            for(i = 0xC; i >= 0; i -= 0x4){
                sprintf(memoryAddressString, "0x%08lx\t\t", memoryAddress + i);
                UART_write(Glo.uart, &memoryAddressString, strlen(memoryAddressString));
            }
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
            for(i = 0xC; i >= 0; i -= 0x4){
                memoryContents = *(int32_t *) (memoryAddress + i);
                sprintf(memoryString, "0x%08lx\t\t", memoryContents);
                UART_write(Glo.uart, memoryString, strlen(memoryString));
            }
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
        }
    }
    else if(commandTest("-gpio", command)) {
        char *gpioBuffer;
        char *writeBuffer;
        char *pinBuffer;
        int pinNumber = 0;
        pinBuffer = secondString(command);
        pinNumber = atoi(pinBuffer);
        gpioBuffer = secondString(pinBuffer);
        if(commandTest("-w", gpioBuffer)){
            writeBuffer = secondString(gpioBuffer);
            if(commandTest("0", writeBuffer)) GPIO_write(pinNumber, 0);
            else if(commandTest("1", writeBuffer)) GPIO_write(pinNumber, 1);
            else GPIO_write(0, 1);
        }
        else if(commandTest("-r", gpioBuffer)){
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
            if(GPIO_read(pinNumber)) UART_write(Glo.uart, "1", 1);
            else UART_write(Glo.uart, "0", 1);
        }
        else if(commandTest("-t", gpioBuffer)){
            GPIO_toggle(pinNumber);

        }
        else{
            for (i = 0; i < 8; i++){
                UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
                if(GPIO_read(i)) UART_write(Glo.uart, "1", 1);
                else UART_write(Glo.uart, "0", 1);
            }
        }
    }
    else if(commandTest("-error", command)) {
        char errorBufferOverflow[128] = "";
        sprintf(errorBufferOverflow,         "Overflow:          %2d", errorCount[0]);
        char errorBufferIncorrectCommand[128] = "";
        sprintf(errorBufferIncorrectCommand, "Incorrect Command: %2d", errorCount[1]);
        char errorBufferInvalidMemory[128] = "";
        sprintf(errorBufferInvalidMemory,    "Invalid Memory:    %2d", errorCount[2]);
        UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
        UART_write(Glo.uart, errorBufferOverflow, strlen(errorBufferOverflow));
        UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
        UART_write(Glo.uart, errorBufferIncorrectCommand, strlen(errorBufferIncorrectCommand));
        UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
        UART_write(Glo.uart, errorBufferInvalidMemory, strlen(errorBufferInvalidMemory));
        UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
    }
    else if(commandTest("-timer", command)) {
        char *periodBuffer;
        int period;
        periodBuffer = secondString(command);
        period = atoi(periodBuffer);
        if(period > 100) {
            Glo.callback.period = period;
            Timer_setPeriod(Glo.timer0, Timer_PERIOD_US, Glo.callback.period);
        }
        else if(!period){
            char currPerBuff[50];
            sprintf(currPerBuff, "Period is %d", Glo.callback.period);
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
            UART_write(Glo.uart, currPerBuff, strlen(currPerBuff));
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
        }
        else{
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
            UART_write(Glo.uart, "Invalid Period. Period must be > 100", strlen("Invalid Period. Period must be > 100"));
        }
    }
    else if(commandTest("-callback", command)) {
        char *callbackBuffer;
        callbackBuffer = secondString(command);
        char *numberBuffer;
        numberBuffer = secondString(callbackBuffer);
        char *payloadBuffer;
        payloadBuffer = secondString(numberBuffer);

        if(!callbackBuffer){
            UART_write(Glo.uart, "\r\nCallback 0 (Timer)       :\t", strlen("\r\nCallback 0 (Timer)       :\t"));
            UART_write(Glo.uart, Glo.callback.payload[0], strlen(Glo.callback.payload[0]));
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
            UART_write(Glo.uart, "\r\nCallback 1 (Left Button) :\t", strlen("\r\nCallback 1 (Left Button) :\t"));
            UART_write(Glo.uart, Glo.callback.payload[1], strlen(Glo.callback.payload[1]));
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
            UART_write(Glo.uart, "\r\nCallback 2 (Right Button):\t", strlen("\r\nCallback 2 (Right Button):\t"));
            UART_write(Glo.uart, Glo.callback.payload[2], strlen(Glo.callback.payload[2]));
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
        }
        else if(!numberBuffer){
            if(atoi(callbackBuffer) == 0) UART_write(Glo.uart, "\r\nCallback 0 (Timer)       :\t", strlen("\r\nCallback 0 (Timer)       :\t"));
            else if(atoi(callbackBuffer) == 1) UART_write(Glo.uart, "\r\nCallback 1 (Left Button)       :\t", strlen("\r\nCallback 1 (Left Button)       :\t"));
            else UART_write(Glo.uart, "\r\nCallback 2 (Right Button)       :\t", strlen("\r\nCallback 2 (Right Button)       :\t"));
            UART_write(Glo.uart, Glo.callback.payload[atoi(callbackBuffer)], strlen(Glo.callback.payload[atoi(callbackBuffer)]));
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
        }
        else{
            Glo.callback.callbackNumber[atoi(callbackBuffer)] = atoi(numberBuffer);
            strcpy(Glo.callback.payload[atoi(callbackBuffer)], payloadBuffer);
        }
    }
    else if(commandTest("-ticker", command)) {
        char *tickerIndexBuffer;
        tickerIndexBuffer = secondString(command);
        char *tickerDelayBuffer;
        tickerDelayBuffer = secondString(tickerIndexBuffer);
        char *tickerPeriodBuffer;
        tickerPeriodBuffer = secondString(tickerDelayBuffer);
        char *tickerCountBuffer;
        tickerCountBuffer = secondString(tickerPeriodBuffer);
        char *payloadBuffer;
        payloadBuffer = secondString(tickerCountBuffer);

        if(!tickerIndexBuffer){
            int i = 0;
            for(i = 0; i < TICKERNUM; i++){
                char tickerOutputBuffer[48];
                sprintf(tickerOutputBuffer, "\r\nTicker %2d :\t", i);
                UART_write(Glo.uart, tickerOutputBuffer, strlen(tickerOutputBuffer));
                UART_write(Glo.uart, Glo.ticker.payload[i], strlen(Glo.ticker.payload[i]));
            }
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
        }
        else if(!tickerDelayBuffer){
            char tickerOutputBuffer[48];
            sprintf(tickerOutputBuffer, "\r\nTicker %2d :\t", atoi(tickerIndexBuffer));
            UART_write(Glo.uart, tickerOutputBuffer, strlen(tickerOutputBuffer));
            UART_write(Glo.uart, Glo.ticker.payload[atoi(tickerIndexBuffer)], strlen(Glo.ticker.payload[atoi(tickerIndexBuffer)]));
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
        }
        else{
            Glo.ticker.delay[atoi(tickerIndexBuffer)] = atoi(tickerDelayBuffer);

            Glo.ticker.period[atoi(tickerIndexBuffer)] = atoi(tickerPeriodBuffer);

            Glo.ticker.tickerCount[atoi(tickerIndexBuffer)] = atoi(tickerCountBuffer);

            strcpy(Glo.ticker.payload[atoi(tickerIndexBuffer)], payloadBuffer);
        }
    }
    else if(commandTest("-reg", command)) {
        char *regInBuffer;
        regInBuffer = secondString(command);
        char *regOperatorBuffer;
        regOperatorBuffer = secondString(regInBuffer);
        char *regOperandBuffer1;
        regOperandBuffer1 = secondString(regOperatorBuffer);
        char *regOperandBuffer2;
        regOperandBuffer2 = secondString(regOperandBuffer1);
        int i;

        if(!regInBuffer){
            for(i = 0; i < REGISTERNUM; i++){
                char regOutputBuffer[48];
                sprintf(regOutputBuffer, "\r\nRegister %2d :\t%4d", i, Glo.reg[i]);
                UART_write(Glo.uart, regOutputBuffer, strlen(regOutputBuffer));
            }
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
        }
        else if(!regOperatorBuffer){
            char regOutputBuffer[48];
            sprintf(regOutputBuffer, "\r\nRegister %2d :\t%4d", atoi(regInBuffer), Glo.reg[atoi(regInBuffer)]);
            UART_write(Glo.uart, regOutputBuffer, strlen(regOutputBuffer));
            UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));
        }
        else if(commandTest("=", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)]  = atoi(regOperandBuffer1);
        else if(commandTest("++", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)] = Glo.reg[atoi(regOperandBuffer1)] + 1;
        else if(commandTest("--", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)] = Glo.reg[atoi(regOperandBuffer1)] - 1;
        else if(commandTest("+", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)]  = Glo.reg[atoi(regOperandBuffer1)] + Glo.reg[atoi(regOperandBuffer2)];
        else if(commandTest("-", regOperatorBuffer)){
            if(!regOperandBuffer2) Glo.reg[atoi(regInBuffer)] = -Glo.reg[atoi(regOperandBuffer1)];
            else Glo.reg[atoi(regInBuffer)] = Glo.reg[atoi(regOperandBuffer1)] - Glo.reg[atoi(regOperandBuffer2)];
        }
        else if(commandTest("~", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)]  = ~Glo.reg[atoi(regOperandBuffer1)];
        else if(commandTest("&", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)]  = Glo.reg[atoi(regOperandBuffer1)] & Glo.reg[atoi(regOperandBuffer2)];
        else if(commandTest("|", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)]  = Glo.reg[atoi(regOperandBuffer1)] | Glo.reg[atoi(regOperandBuffer2)];
        else if(commandTest("^", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)]  = Glo.reg[atoi(regOperandBuffer1)] ^ Glo.reg[atoi(regOperandBuffer2)];
        else if(commandTest("*", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)]  = Glo.reg[atoi(regOperandBuffer1)] * Glo.reg[atoi(regOperandBuffer2)];
        else if(commandTest("/", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)]  = Glo.reg[atoi(regOperandBuffer1)] / Glo.reg[atoi(regOperandBuffer2)];
        else if(commandTest("%", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)]  = Glo.reg[atoi(regOperandBuffer1)] % Glo.reg[atoi(regOperandBuffer2)];
        else if(commandTest(">", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)]  = (Glo.reg[atoi(regOperandBuffer1)] > Glo.reg[atoi(regOperandBuffer2)]) ? Glo.reg[atoi(regOperandBuffer1)] : Glo.reg[atoi(regOperandBuffer2)];
        else if(commandTest("<", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)]  = (Glo.reg[atoi(regOperandBuffer1)] < Glo.reg[atoi(regOperandBuffer2)]) ? Glo.reg[atoi(regOperandBuffer1)] : Glo.reg[atoi(regOperandBuffer2)];
        else if(commandTest("c", regOperatorBuffer)) Glo.reg[atoi(regInBuffer)]  = Glo.reg[atoi(regOperandBuffer1)];
        else if(commandTest("x", regOperatorBuffer)){
            int32_t tempReg;
            tempReg = Glo.reg[atoi(regInBuffer)];
            Glo.reg[atoi(regInBuffer)]  = Glo.reg[atoi(regOperandBuffer1)];
            Glo.reg[atoi(regOperandBuffer1)] = tempReg;
        }
    }
    else errorCount[1]++;
}

int commandTest(const char *command, const char *compareString){
    int i;
    for (i = 0; i < strlen(command); i++){
        if(compareString[i] != command[i]) return 0;
    }
    return 1;
}

void initializeDrivers(void){
    Timer_Handle timer0, timer1;
    Timer_Params params;
    UART_Handle uart;
    UART_Params uartParams;

    /* Call driver init functions */
    Board_init();
    Timer_init();
    UART_init();
    GPIO_init();
    GPIO_enableInt(4);
    GPIO_enableInt(5);


    Timer_Params_init(&params);
    params.period = Glo.callback.period;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback;

    timer0 = Timer_open(CONFIG_TIMER_0, &params);

    if (timer0 == NULL) {
        /* Failed to initialized timer */
        while (1) {}
    }
    /* Call driver init functions */
    if (Timer_start(timer0) == Timer_STATUS_ERROR) {
        /* Failed to start timer */
        while (1) {}
    }

    Timer_Params_init(&params);
    params.period = 10000;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = tickerCallback;

    timer1 = Timer_open(CONFIG_TIMER_1, &params);

    if (timer1 == NULL) {
        /* Failed to initialized timer */
        while (1) {}
    }
    /* Call driver init functions */
    if (Timer_start(timer1) == Timer_STATUS_ERROR) {
        /* Failed to start timer */
        while (1) {}
    }

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.baudRate = 115200;

    uart = UART_open(CONFIG_UART_0, &uartParams);

    if (uart == NULL) {
        /* UART_open() failed */
        while (1);
    }
    Glo.timer0 = timer0;
    Glo.timer1 = timer1;
    Glo.uart = uart;
}

void leftButtonCallback(void){
    if(Glo.callback.callbackNumber[1] != 0){
        addMessage(Glo.callback.payload[1]);
        Semaphore_post(Glo.msgQueSem);
        if(Glo.callback.callbackNumber[1]>0){
            Glo.callback.callbackNumber[1]--;
        }
    }
}

void rightButtonCallback(void){
    if(Glo.callback.callbackNumber[2] != 0){
        addMessage(Glo.callback.payload[2]);
        Semaphore_post(Glo.msgQueSem);
        if(Glo.callback.callbackNumber[2]>0){
            Glo.callback.callbackNumber[2]--;
        }
    }
}

char *secondString(char *fullString){
    char *outString = NULL;
    int i = 0;
    for (i = 0; i < strlen(fullString); i++){
        if(fullString[i] == ' '){
            outString = &fullString[i + 1];
            return outString;
        }
    }
    return outString;
}

void stringCopy(char *outString, const char *copiedString){
    for(i = 0; i < 128; i++) if(copiedString[i] == 0) break;
    int j = 0;
    for(j = 0; j < i+1; j++){
        outString[j] = copiedString[j];
    }
    outString[j+1] = 0;
}

void taskCommandServicer(void){
    while(1){
        Semaphore_pend(Glo.msgQueSem, BIOS_WAIT_FOREVER);

        commandEntry(Glo.msgQue.messages[Glo.msgQue.readIndex].message);
        Glo.msgQue.readIndex++;
        if(Glo.msgQue.readIndex == Glo.var.queLen) Glo.msgQue.readIndex = 0;
    }
}

void tickerCallback(Timer_Handle myHandle, int_fast16_t status)
{
    for(i = 0; i < TICKERNUM; i++){
        if(Glo.ticker.tickerCount[i] != 0 && Glo.ticker.delay[i] == 0){
            addMessage(Glo.ticker.payload[i]);
            Semaphore_post(Glo.msgQueSem);
            if(Glo.ticker.tickerCount[i]>0){
                Glo.ticker.tickerCount[i]--;
            }
            Glo.ticker.delay[i] = Glo.ticker.period[i];
        }
        else if(Glo.ticker.delay[i] != 0){
            Glo.ticker.delay[i]--;
        }
    }
}

void timerCallback(Timer_Handle myHandle, int_fast16_t status)
{
    if(Glo.callback.callbackNumber[0] != 0){
        addMessage(Glo.callback.payload[0]);
        Semaphore_post(Glo.msgQueSem);
        if(Glo.callback.callbackNumber[0]>0){
            Glo.callback.callbackNumber[0]--;
        }
    }
}
