#include  "life.h"

void fill_it(char *line, int width)
{
    for(int i = 0; i < width; i++)
        line[i] = ' ';
    line[width] = '\0';
}

void draw_board(_life *game)
{
    int i = 0;
    int hold_x = 0;
    int hold_y = 0;
    while(game->buffer[i])
    {
        hold_x = game->col;
        hold_y = game->raw;
        switch(game->buffer[i])
        {
            case 'w': game->raw--; break;
            case 's': game->raw++; break;
            case 'd': game->col++; break;
            case 'a': game->col--; break;
            case 'x': game->count_x++; break;
        }
        if(game->raw < 0 || game->raw >= game->height || game->col < 0 || game->col >= game->width)
        {
            game->col = hold_x;
            game->raw = hold_y;
        }
        if((game->count_x % 2) == 1 )
            game->drawing[game->raw][game->col] = 'O';
        i++;
    }
}

int init_game(_life *game, char **av)
{
    ssize_t n_bytes = read(0, game->buffer, sizeof(game->buffer));
    if(n_bytes == -1)
        return -1;
    game->buffer[n_bytes] = '\0';
    game->alive = 'O';
    game->dead = ' ';
    game->col = 0;
    game->raw = 0;
    game->life = atoi(av[3]);
    game->height = atoi(av[2]);
    game->width = atoi(av[1]);
    game->count_x = 0;
    game->drawing = malloc(sizeof(char *) * (game->height + 1));
    if(!game->drawing)
        return -1;
    for(int i = 0; i < game->height; i++)
    {
        game->drawing[i] = malloc(game->width + 1);
        if(!game->drawing[i])
            return -1;
        fill_it(game->drawing[i], game->width);
    }
    game->drawing[game->height] = NULL;
    return 0;
}

void print_board(char **drawing)
{
    while(*drawing)
    {
        printf("%s\n", *drawing);
        drawing++;
    }
}

int get_n(_life *game, int y, int x)
{
    int count_n = 0;
    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            int ni = i + y;
            int nj = j + x;
            if(i == 0 && j == 0)
                continue;
            if(ni >= 0 && nj >= 0 && ni < game->height && nj < game->width && game->drawing[ni][nj] == game->alive)
                count_n++;
        }
    }
    return count_n;
}

void simulation(_life *game)
{
    int x = 0;
    int y = 0;
    char **dr = malloc(sizeof(char *) * (game->height + 1));
    if(!dr)
        return;
    for(int i = 0; i < game->height; i++)
    {
        dr[i] = malloc(game->width + 1);
        if(!dr[i])
            return;
        fill_it(dr[i], game->width);
    }
    dr[game->height] = NULL; 
    while(game->drawing[y])
    {
        x = 0;
        while(game->drawing[y][x])
        {
            int neib = get_n(game, y, x);
            if(game->drawing[y][x] == 'O')
            {
                if(neib == 2 || neib == 3)
                    dr[y][x] = game->alive;
                else
                    dr[y][x] = game->dead;
            }
            else
            {
                if(neib == 3)
                    dr[y][x] = game->alive;
                else
                    dr[y][x] = game->dead;
            }
            x++;
        }
        y++;
    }
    for(int i = 0; i < game->height; i++)
        free(game->drawing[i]);
    free(game->drawing);
    game->drawing = dr;
}

int main(int ac, char **av)
{
    _life *game = malloc(sizeof(_life));
    if(ac != 4 || !game)
        return 1;
    memset(game, 0, sizeof(_life));
    if(init_game(game, av) == -1)
        return 1;
    draw_board(game);
    while(game->life > 0)
    {
        simulation(game);
        game->life--;
    }
    print_board(game->drawing);
    return 0;
}