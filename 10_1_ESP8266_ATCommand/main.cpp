#include "mbed.h"

RawSerial pc(USBTX, USBRX);    // computer to mbed board
RawSerial esp(D1, D0);         // mbed board to target board

int main()
{
    pc.baud(115200);
    esp.baud(115200);
    wait(0.1);
    pc.printf("\r\n########### ready ###########\r\n");
    esp.printf("AT\r\n"); // pas some information to the board
    char str[50];
    int i = 0;

    while(1) {
        if(pc.readable()) {
            char c = pc.getc();
            // print out whatever type in 
            if(c != '\r' && c != '\n') {
                pc.printf("%c", c);
                str[i++] = c;
            }
            else { 
            // if we press enter, send the thing in buffer to the target board
                pc.printf("(%d)\r\n", c);
                str[i] = 0;
                i = 0;
                esp.printf("%s\r\n", str);
            }
        }
        // print the information from the target board
        while(esp.readable()) {
            char c = esp.getc();
            pc.printf("%c",c);
        }
        wait(.001);
    }
}