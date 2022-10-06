/*
 * uartEcho.c
 *
 *  Created on: Sep 17, 2022
 *      Author: root
 */

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <mainHead.h>

#include <pthread.h>
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

#define UDPPACKETSIZE 1472
#define MAXPORTLEN    6

extern void fdOpenSession();
extern void fdCloseSession();
extern void *TaskSelf();

#include "ti_drivers_config.h"

void *uartEcho(void *arg0)
{
    char        input;
    const char  echoPrompt[] = "Welcome to MSP432:\r\n";
    UART_Handle uart;
    UART_Params uartParams;

    /* Call driver init functions */
    UART_init();
    GPIO_init();

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

    UART_write(uart, echoPrompt, sizeof(echoPrompt));

    const char helpHelpOutput[] = "\r\n-help prints a complete list of supported commands\r\n";
    const char helpAboutOutput[] = "\r\n-about prints the name, assignment number, version and date/time of compile\r\n";
    const char helpPrintOutput[] = "\r\n-print prints any text following the command\r\n";
    const char helpMemrOutput[] = "\r\n-memr shows what is in the memory space specified after the command\r\n\tFlash: 0x00000000 to 0x000FFFFF\r\n\tSRAM: 0x20000000 to 0x2003FFFF\r\n\tPeripherals: 0x40000000 to 0x44055000\r\n";
    const char helpGPIOOutput[] = "\r\n-gpio allows to you read (-r), toggle (-t), and write (-w) to the GPIO pins.\r\n\tThe first argument is the pin number, second argument is the command type (-t, -w, -r), and the third is 1 or 0 if you are writing high or low\r\n";
    const char helpErrorOutput[] = "\r\n-error shows the current count of errors.\r\n";
    char aboutOutput[80] = "";
    sprintf(aboutOutput, "\r\nSteve Gillet, Assignment 3, v1.431234, %s, %s\r\n", __TIME__, __DATE__);
    const char help[128] = "-help";
    const char about[128] = "-about";
    const char newLine[] = "\r\n";
    char command[128] = "";
    char previousCommand[128] = "";
    int i = 0;
    char arrowInput[2] = "";
    // overflow, incorrect command, invalid mem address
    int errorCount[] = {0, 0, 0};
    int overflowFlag = 0;

    /* Loop forever echoing */
    while (1) {
        arrowInput[0] = 0;
        UART_read(uart, &input, 1);
        if(input == '\33') {
            UART_read(uart, &arrowInput, 2);
            if(commandTest("[A", arrowInput)){
                UART_write(uart, "\r", strlen("\r"));
                UART_write(uart, "                                    ", strlen("                                    "));
                UART_write(uart, "\r", strlen("\r"));
                UART_write(uart, &previousCommand, strlen(previousCommand));
                strcpy(command, previousCommand);
                i = strlen(command);
                continue;
            }
            else{
                UART_write(uart, &input, 1);
                UART_write(uart, &arrowInput, 2);
            }
        }
        if(i < 127){
            UART_write(uart, &input, 1);
        }
        if(input == '\r') {
            if(commandTest(&help, command)){
                char helpCommand[128] = "";
                secondString(helpCommand, command);
                if(strstr(helpCommand, "help")) UART_write(uart, &helpHelpOutput, sizeof(helpHelpOutput));
                else if(strstr(helpCommand, "about")) UART_write(uart, &helpAboutOutput, sizeof(helpAboutOutput));
                else if(strstr(helpCommand, "print")) UART_write(uart, &helpPrintOutput, sizeof(helpPrintOutput));
                else if(strstr(helpCommand, "memr")) UART_write(uart, &helpMemrOutput, sizeof(helpMemrOutput));
                else if(strstr(helpCommand, "gpio")) UART_write(uart, &helpGPIOOutput, sizeof(helpGPIOOutput));
                else if(strstr(helpCommand, "error")) UART_write(uart, &helpErrorOutput, sizeof(helpErrorOutput));
                else{
                    UART_write(uart, &helpHelpOutput, sizeof(helpHelpOutput));
                    UART_write(uart, &helpAboutOutput, sizeof(helpAboutOutput));
                    UART_write(uart, &helpPrintOutput, sizeof(helpPrintOutput));
                    UART_write(uart, &helpMemrOutput, sizeof(helpMemrOutput));
                    UART_write(uart, &helpGPIOOutput, sizeof(helpGPIOOutput));
                    UART_write(uart, &helpErrorOutput, sizeof(helpErrorOutput));
                }
            }
            else if(commandTest(&about, command)) UART_write(uart, &aboutOutput, sizeof(aboutOutput));
            else if(commandTest("-print", command)) {
                char print[128] = "";
                secondString(print, command);
                UART_write(uart, &newLine, sizeof(newLine));
                UART_write(uart, &print, strlen(print));
            }
            else if(commandTest("-memr", command)) {
                char memoryBuffer[128] = "";
                long memoryAddress = 0;
                long memoryContents = 0;
                char memoryString[128] = "";
                char memoryAddressString[128] = "";
                char *ptr;

                secondString(memoryBuffer, command);
                memoryAddress = strtol(memoryBuffer, &ptr, 16);
                if(memoryAddress < 0x00000000 || (memoryAddress > 0x000FFFFF && memoryAddress < 0x20000000) || (memoryAddress > 0x2003FFFF && memoryAddress < 0x40000000) || memoryAddress > 0x44055000){
                    UART_write(uart, &newLine, strlen(newLine));
                    UART_write(uart, "Error: Invalid Address", strlen("Error: Invalid Address"));
                    errorCount[2]++;
                }

                else{
                    memoryAddress = memoryAddress & 0xFFFFFFF0;

                    UART_write(uart, &newLine, sizeof(newLine));
                    for(i = 0xC; i >= 0; i -= 0x4){
                        sprintf(memoryAddressString, "0x%08lx\t\t", memoryAddress + i);
                        UART_write(uart, &memoryAddressString, strlen(memoryAddressString));
                    }
                    UART_write(uart, &newLine, sizeof(newLine));
                    for(i = 0xC; i >= 0; i -= 0x4){
                        memoryContents = *(int32_t *) (memoryAddress + i);
                        sprintf(memoryString, "0x%08lx\t\t", memoryContents);
                        UART_write(uart, &memoryString, strlen(memoryString));
                    }
                }
            }
            else if(commandTest("-gpio", command)) {
                char gpioBuffer[128] = "";
                char writeBuffer[1] = "";
                char pinBuffer[128] = "";
                int pinNumber = 0;
                secondString(pinBuffer, command);
                pinNumber = atoi(pinBuffer);
                secondString(gpioBuffer, pinBuffer);
                if(commandTest("-w", gpioBuffer)){
                    secondString(writeBuffer, gpioBuffer);
                    if(commandTest("0", writeBuffer)) GPIO_write(pinNumber, 0);
                    else if(commandTest("1", writeBuffer)) GPIO_write(pinNumber, 1);
                    else GPIO_write(0, 1);
                }
                else if(commandTest("-r", gpioBuffer)){
                    UART_write(uart, &newLine, strlen(newLine));
                    if(GPIO_read(pinNumber)) UART_write(uart, "1", 1);
                    else UART_write(uart, "0", 1);
                }
                else if(commandTest("-t", gpioBuffer)){
                    GPIO_toggle(pinNumber);

                }
                else{
                    for (i = 0; i < 8; i++){
                        UART_write(uart, &newLine, strlen(newLine));
                        if(GPIO_read(i)) UART_write(uart, "1", 1);
                        else UART_write(uart, "0", 1);
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
                UART_write(uart, &newLine, strlen(newLine));
                UART_write(uart, errorBufferOverflow, strlen(errorBufferOverflow));
                UART_write(uart, &newLine, strlen(newLine));
                UART_write(uart, errorBufferIncorrectCommand, strlen(errorBufferIncorrectCommand));
                UART_write(uart, &newLine, strlen(newLine));
                UART_write(uart, errorBufferInvalidMemory, strlen(errorBufferInvalidMemory));
            }
            else errorCount[1]++;

            strcpy(previousCommand, command);
            memset(command,0,sizeof(command));
            i=0;
            UART_write(uart, &newLine, sizeof(newLine));
            overflowFlag = 0;
        }
        else if (input == '\b' && i > 0){
            i--;
            command[i] = 0;
            UART_write(uart, " \b", strlen(" \b"));
        }
        else if (i < 127) {
            command[i] = input;
            i++;
        }
        if (i == 127 && overflowFlag == 0) {
            overflowFlag = 1;
            errorCount[0]++;
        }
    }
}


