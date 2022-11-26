/*
 * uart7echo.c
 *
 *  Created on: Oct 26, 2022
 *      Author: root
 */

#include "mainHead.h"

void taskUart7Read()
{
    int len;
    char uart7Buffer[MESSAGELEN];
    char uart7IncBuff[MESSAGELEN];
    while(1){
        uart7Buffer[MESSAGELEN - 1] = 0;
        len = UART_read(Glo.uart7, uart7Buffer, sizeof(uart7Buffer));
        uart7Buffer[len - 1] = 0;

        sprintf(uart7IncBuff, "UART7: %s", uart7Buffer);
        UART_write(Glo.uart, uart7IncBuff, strlen(uart7IncBuff));
        UART_write(Glo.uart, Glo.var.newLine, strlen(Glo.var.newLine));

        addMessage(uart7Buffer);
        Semaphore_post(Glo.msgQueSem);
    }
}

