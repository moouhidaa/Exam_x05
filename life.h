#ifndef LIFE
#define LIFE
#include    <stdio.h>
#include    <stdlib.h>
#include    <unistd.h>
#include   <stdbool.h>
#include  <string.h>

typedef  struct  life
{
    int  height;
    int  width;
    char  dead;
    char  alive;
    char  buffer[1024];
    int   raw;
    int   col;
    char  **drawing;
    int   life;
    bool  draw;
    int  count_x
}_life;

#endif