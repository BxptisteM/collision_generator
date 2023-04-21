/*
** EPITECH STUDENT
** @BxptisteM | colls_generator.c
** File description:
** Program to generate the collision of a map. You just have to convert you map in PPm format and then use this program to generate the map with the collisions.
** Wall = '#' & Space = ' '
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_errors(int ac, char **av)
{
    char *extension = NULL;

    if (ac != 4) {
        printf("Invalid Arguments.\n\nDo: ./colls_maker [file] [size_y] [size_x] > file.txt\n\n");
        printf("Example: ./colls_maker map.ppm 10 10 > file.txt\n\n");
        printf("Be sure to remove the first 4 lines of the PPM file.\n\n");
        printf("GitHub: BxptisteM\n");
        return (84);
    }
    for (size_t i = 0; i < strlen(av[2]); i++) {
        if (!isdigit(av[2][i])) {
            printf("The second argument must be a positive integer.\n");
            return (84);
        }
    }
    for (size_t i = 0; i < strlen(av[3]); i++) {
        if (!isdigit(av[3][i])) {
            printf("The third argument must be a positive integer.\n");
            return (84);
        }
    }
    extension = strrchr(av[1], '.');
    if (extension == NULL || strcmp(extension, ".ppm") != 0) {
        printf("The first argument must be a PPM image.\n");
        return (84);
    }
    return (0);
}


char **read_file(FILE *file)
{
    int row_count = 0;
    int col_count = 0;
    char **pixels = NULL;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file)) {
        if (buffer[0] != '\n') {
            if (col_count == 0) {
                pixels = realloc(pixels, sizeof(char *) * (row_count + 1));
                if (pixels == NULL)
                    return (NULL);
                pixels[row_count] = malloc(sizeof(char) * 10);
                if (pixels[row_count] == NULL)
                    return (NULL);
                pixels[row_count][0] = '\0';
            }
            char *newline_ptr = strchr(buffer, '\n');
            if (newline_ptr != NULL) {
                *newline_ptr = '\0';
            }
            if (col_count < 2) {
                strcat(pixels[row_count], buffer);
                strcat(pixels[row_count], " ");
                col_count++;
            } else {
                strcat(pixels[row_count], buffer);
                row_count++;
                col_count = 0;
            }
        }
    }
    return pixels;
}

int main(int ac, char **av)
{
    int j = 0;
    char **pixels = NULL;
    char **map = NULL;

    if(check_errors(ac, av) == 84)
        return (84);
    FILE *file = fopen(av[1], "r");
    pixels = read_file(file);
    map = malloc(sizeof(char *) * (atoi(av[2]) + 1));
    if (map == NULL)
        return (84);
    for (int y = 0; y != atoi(av[2]); y++) {
        map[y] = malloc(sizeof(char) * (atoi(av[3]) + 1));
        if (map[y] == NULL)
            return (84);
        for (int x = 0; x != atoi(av[3]); x++) {
            if (strcmp(pixels[j], "0 0 0") == 0) {
                map[y][x] = '#';
            } else {
                map[y][x] = ' ';
            }
            j++;
        }
        map[y][(atoi(av[3]) + 1)] = '\0';
    }
    map[(atoi(av[2]) + 1)] = NULL;
    for (int i = 0; i != atoi(av[2]); i++)
        printf("%s\n", map[i]);
    fclose(file);
    return (0);
}
