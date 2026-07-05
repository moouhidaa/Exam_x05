#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <stdbool.h>

static  int  monitor;

void   draw(char  **container,char *buffer,int  *index)
{
    (*index)++;
    int  raw = 0;
    int  col = 0;
    while(buffer[(*index)] || buffer[(*index)] == 'x')
    {
        if(buffer[(*index)] == 's')
        {
            int  check =  raw + 1;
            if(!container[check])
                continue;
            else
            {
                raw += 1;
                container[raw][col] = ' ';
            }
        }
        else if(buffer[(*index)] == 'w')
        {
            int  check =  raw  - 1;
            if(check < 0)
                continue;
            else
            {
                raw -=1;
                container[raw][col] = ' ';
            }
        }
        else if(buffer[(*index)] == 'd')
        {
            int check  =  col + 1;
            if(!container[raw][col])
                continue;
            else
            {
                col+=1;
                container[raw][col] = ' ';
            }
           
        }
        else if(buffer[(*index)] == 'a')
        {
            int  check =  raw -1;
            if(check < 0)
                continue;
            else
            {
                col-= 1;
                container[raw][col] = ' ';
            }
        }
        (*index)++;
    }

}

bool  valid_chars(char  *dir,int  _len)
{
    int  i = 0;
    while(i < _len)
    {
        if(dir[i] != 'a' && dir[i] != 'w' && dir[i] != 'd' && dir[i] != 's' && dir[i] != 'x' )
            return  false;
        i++;
    }
    return true;
}

void print(char  **drawing,int  life,char *buffer)
{
    int  index = 0;
    while(life >= 0)
    {
        while(buffer[index])
        {
            if(buffer[index] == 'x')
                draw(drawing,buffer,&index);
            index++;
        }
        life--;
    }
    while(*drawing)
    {
        printf("%s\n",*drawing);
        drawing++;
    }
}

void  fill_it(char *col,int size)
{
    for(int i = 0;i < size;i++)
        col[i] = '0';
    col[size] = '\0';
}

int  main(int  ac,char  **av)
{
    char **drawing;
    monitor = 0;
    int  life = atoi(av[3]);
    int  col  = atoi(av[1]);
    int  raw  = atoi(av[2]);
    char buffer[1024];

    int  _read =  read(0,buffer,sizeof(buffer));
    buffer[_read] = '\0';
    if(!valid_chars(buffer,_read -1))
        return 1;
    drawing =  malloc(sizeof(char *) * (raw + 1));
    if(!drawing)
        return 1;
    for (int i = 0;i < raw ;i++)
    {
        drawing[i] = malloc(col + 1);
        if(!drawing[i])
            return 1;
        fill_it(drawing[i],col);
    }
    drawing[raw] = NULL;
    print(drawing,life,buffer);
    // free();
    return  0;
}