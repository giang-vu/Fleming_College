/*
The processor frequency is 10MHz, so each tick will consume: 4/10MHz = 0.4us
In order to generate the lowest frequency of a square wave, I have to obtain the highest time period of that wave.
Because the time period is equal to double delay time, I will use the Timer0 to generate delay time as much as possible.
Timer0 can be used as 16-bit timer, so the maximum number of ticks will be: 216 - 1 = 65,535 ticks = 0xFFFF ticks
I use the largest prescaler (1:256), so the actual ticks will be: 65,535 x 256 = 16,776,960 ticks
The possible highest delay time will be: 16,776,960 x 0.4us = 6,710,784us ~ 6.71s
The lowest frequency generated will be: 1/(6.71 x 2) ~ 0.75Hz
*/
