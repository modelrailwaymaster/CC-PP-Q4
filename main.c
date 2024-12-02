#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

// structures for the file and changes made
struct file_change
{
    char operation;
    int line_changed;
    int number_of_lines;
};

struct file
{
    char *file_name;
    char *data;
    struct file_change change_log[];
};

struct file current_file;

// open file and store in above var
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
        fp = fopen(strcat(input, ".txt"), "r");
        fseek(fp, 0, SEEK_END);
        data = (char *)malloc(ftell(fp) + 1 * sizeof(char));
        data[ftell(fp) + 1] = '\0';
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
                data[ftell(fp)] = letter;
            }
        }
        fclose(fp);
    }

    current_file.file_name = input;
    current_file.data = data;
    printf("\n\n\ntest: %s\n %s\n %s\n\n\n", current_file.file_name, current_file.data);
    return 0;
}

// line operations
int append()
{
    return 0;
}

int delete()
{
    return 0;
}

int insert()
{
    return 0;
}

int show()
{
    return 0;
}

// general operations

int show_line_count()
{
    int line_count = 0;
    char letter;
    FILE *fp;
    fp = fopen(strcat(current_file.file_name, ".txt"), "r");
    while (true)
    {
        letter = fgetc(fp);
        if (letter == EOF)
        {
            break;
        }
        else
        {
            if (letter == '\n')
            {
                line_count++;
            }
        }
    }
    printf("Line number for %s is %d\n", current_file.file_name, line_count);
    return 1;
}

int show_change_log()
{
    bool complete = false;
    char filelogname[23];
    FILE *file;
    char *data;
    char letter;
    while (!complete)
    {
        printf("Enter the file name(without .txt, type exit to leave): ");
        scanf("%s", filelogname);
        strcat(filelogname, "log.txt");
        file = fopen(filelogname, "r");
        fseek(file, 0, SEEK_END);
        data = (char *)malloc(ftell(file) + 1 * sizeof(char));
        data[ftell(file) + 1] = '\0';
        fseek(file, 0, SEEK_SET);
        while (true)
        {
            letter = fgetc(file);
            if (letter == EOF)
            {
                complete = true;
                break;
            }
            else
            {
                data[ftell(file)] = letter;
            }
        }
    }
    printf("%s\n", data);
    return 1;
}

// file operations
int create_file()
{
    bool complete = false;
    char filename[20];
    char filelogname[23];
    FILE *file;
    while (!complete)
    {
        printf("Enter the file name(without .txt, type exit to leave): ");
        scanf("%s", filename);
        strcpy(filelogname, filename);
        strcat(filelogname, "log.txt");
        if (strcmp(filename, "exit") == 0)
        {
            return 1;
        }
        strcat(filename, ".txt");
        if (file = fopen(filename, "r"))
        {
            fclose(file);
            printf("File already exists.\n");
        }
        else
        {
            file = fopen(filename, "w");
            fclose(file);
            file = fopen(filelogname, "w");
            fprintf(file, "created,0,0\n");
            fclose(file);
            complete = true;
        }
    }
    return 1;
}

int copy_file()
{
    bool complete = false;
    char source[20];
    char new[20];
    char newlogname[23];
    FILE *file;
    while (!complete)
    {
        printf("Enter the source file name(without .txt, type exit to leave): ");
        scanf("%s", source);
        if (strcmp(source, "exit") == 0)
        {
            return 0;
        }
        else
        {
            strcat(source, ".txt");
            FILE *srcfp = fopen(source, "r");
            if (srcfp == NULL)
            {
                printf("The file does not exist\n");
            }
            else
            {
                printf("Enter the new file name(without .txt): ");
                scanf("%s", new);
                strcpy(newlogname, new);
                strcat(newlogname, "log.txt");
                strcat(new, ".txt");
                FILE *fp = fopen(new, "w");
                if (fp == NULL)
                {
                    printf("Unable to create the file\n");
                    fclose(srcfp);
                }
                else
                {
                    file = fopen(newlogname, "w");
                    fprintf(file, "copied,0,0\n");
                    fclose(file);
                    int ch;
                    while ((ch = fgetc(srcfp)) != EOF)
                    {
                        fputc(ch, fp);
                    }
                    fclose(srcfp);
                    fclose(fp);
                    complete = true;
                }
            }
        }
    }
    return 0;
}

int delete_file()
{
    bool complete = false;
    char input[20];
    char inputlog[20];
    while (!complete)
    {
        printf("Enter the file name(without .txt, type exit to leave): ");
        scanf("%s", input);
        strcpy(inputlog, input);
        strcat(inputlog, "log.txt");
        if (strcmp(input, "exit") == 0)
        {
            return 0;
        }
        else
        {
            if (remove(strcat(input, ".txt")) == 0)
            {
                remove(inputlog);
                printf("Deleted successfully\n");
                complete = true;
            }
            else
            {
                printf("Unable to delete the file\n");
            }
        }
    }
    return 0;
}

int show_file()
{
    printf("%s\n", current_file.data);
    return 0;
}

// exit function
int my_exit()
{
    return -1;
}

// menu template
int menu(char *options[4], int (*functions[])(), int size)
{
    int choice;

    printf("\n");

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

// file and general operation menu
int fileOp()
{
    bool run = true;
    char *options[5] = {"copy", "create", "delete", "show", "exit"};
    int (*functions[5])() = {&copy_file, &create_file, &delete_file, &show_file, &my_exit};
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
    char *options[4] = {"open", "show change log", "show line count", "exit"};
    int (*functions[4])() = {&open_file, &show_change_log, &show_line_count, &my_exit};
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

int lineOp()
{
    bool run = true;
    char *options[5] = {"append", "delete", "insert", "show", "exit"};
    int (*functions[5])() = {&append, &delete, &insert, &show, &my_exit};
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

// main loop
int main()
{
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