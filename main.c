#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

char *directory;

struct file_change
{
    char operation;
    int line_changed;
    int number_of_lines;
};

struct file
{
    char *file_name;
    char *file_directory;
    char *data;
    struct file_change change_log[];
};

struct file current_file;

int open_file()
{
    bool complete = false;
    FILE *fp;
    char input[20];
    char letter;
    char *data;

    while (!complete)
    {
        printf("Enter the file name(without .txt): ");
        scanf("%s", input);
        fp = fopen(strcat(strcat(directory, input), ".txt"), "r");
        fseek(fp, 0, SEEK_END);
        data = (char *)malloc(ftell(fp) * sizeof(char));
        fseek(fp, 0, SEEK_SET);
        while (true)
        {
            letter = fgetc(fp);
            if (letter == EOF)
            {
                complete = true;
                break;
            }
            else
            {
                printf("%s", data);
                data[ftell(fp)] = letter;
            }
        }
        fclose(fp);
    }

    printf("%s", data);
    current_file.file_name = input;
    current_file.file_directory = directory;
    current_file.data = data;
    return 0;
}

int copy()
{
    return 0;
}

int create()
{
    return 0;
}

int delete()
{
    return 0;
}

int show()
{
    printf("%s", current_file.data);
    return 0;
}

int save_file()
{
    return 0;
}

int delete_file()
{
    return 0;
}

int lineOp()
{
    printf("lop\n");
    return 0;
}

int my_exit()
{
    return -1;
}

int menu(char *options[4], int (*functions[])(), int size)
{
    int choice;

    for (int count = 0; count < size; count++)
    {
        printf("%d.%s\n", count, options[count]);
    }

    scanf("%d", &choice);

    if (choice <= size && choice >= 0)
    {
        int result = functions[choice]();
        if (result == -1)
        {
            return -1;
        }
    }
    else
    {
        printf("Invalid Input.\n");
    }
}

int fileOp()
{
    bool run = true;
    char *options[5] = {"copy", "create", "delete", "show", "exit"};
    int (*functions[5])() = {&copy, &create, &delete, &show, &my_exit};
    int result;

    while (run)
    {
        result = menu(options, functions, 5);
        if (result == -1)
        {
            run = false;
        }
    }

    return 0;
}

int generalOp()
{
    bool run = true;
    char *options[4] = {"open", "save", "delete", "exit"};
    int (*functions[4])() = {&open_file, &save_file, &delete_file, &my_exit};
    int result;

    while (run)
    {
        result = menu(options, functions, 4);
        if (result == -1)
        {
            run = false;
        }
    }

    return 0;
}

int main()
{
    int max_directory = 100;
    directory = (char *)malloc(max_directory * sizeof(char));
    getcwd(directory, max_directory);
    bool run = true;
    char *options[4] = {"File Operation", "Line Operation", "General Operation", "Exit"};
    int (*functions[4])() = {&fileOp, &lineOp, &generalOp, &my_exit};
    int result;

    while (run)
    {
        result = menu(options, functions, 4);
        if (result == -1)
        {
            run = false;
        }
    }

    return 0;
}