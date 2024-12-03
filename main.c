#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define FILE_MAX 1024
#define INPUT_MAX 1024
#define CHANGE_LOG "change_log.txt"

// line operations
int append_line()
{
    bool complete = false;
    char filename[FILE_MAX];
    char input[INPUT_MAX];
    FILE *file;
    while (!complete)
    {
        printf("Enter the file name(without .txt, type exit to leave): ");
        scanf("%s", filename);
        getchar();
        if (strcmp(filename, "exit") == 0)
        {
            return 0;
        }
        strcat(filename, ".txt");
        file = fopen(filename, "a");
        if (file == NULL)
        {
            printf("The file does not exist\n");
            return -1;
        }
        printf("Enter the new line of content: ");
        fgets(input, INPUT_MAX, stdin);
        input[strlen(input) - 1] = '\0';
        fprintf(file, "%s\n", input);
        fclose(file);
        file = fopen(CHANGE_LOG, "a");
        fprintf(file, "A line has been appended in %s. Number of lines = (number)\n", filename);
        fclose(file);
        printf("Line appended successfully\n");
        complete = true;
    }
    return 0;
}

int delete_line()
{
    bool complete = false;
    char filename[FILE_MAX];
    char filetemp[FILE_MAX];
    char buffer[BUFFER_SIZE];
    int linedel;
    int line = 1;
    FILE *file;
    FILE *temp;
    while (!complete)
    {
        printf("Enter the file name(without .txt, type exit to leave): ");
        scanf("%s", filename);
        if (strcmp(filename, "exit") == 0)
        {
            return 0;
        }
        strcpy(filetemp, filename);
        strcat(filename, ".txt");
        strcat(filetemp, "_temp.txt");
        file = fopen(filename, "r");
        temp = fopen(filetemp, "w");
        if (file == NULL || temp == NULL)
        {
            printf("The file does not exist\n");
            fclose(file);
            fclose(temp);
            return -1;
        }
        printf("Enter the line number to delete: ");
        scanf("%d", &linedel);
        while (fgets(buffer, BUFFER_SIZE, file) != NULL)
        {
            if (line != linedel)
            {
                fputs(buffer, temp);
            }
            line++;
        }
        fclose(file);
        fclose(temp);
        remove(filename);
        rename(filetemp, filename);
        file = fopen(CHANGE_LOG, "a");
        fprintf(file, "Line %d of %s has been deleted. Number of lines = (number)\n", linedel, filename);
        fclose(file);
        printf("Line deleted successfully\n");
        complete = true;
    }
    return 0;
}

int insert_line()
{
    bool complete = false;
    char filename[FILE_MAX];
    char filetemp[FILE_MAX];
    char input[INPUT_MAX];
    char buffer[BUFFER_SIZE];
    int lineins;
    FILE *file;
    FILE *temp;
    int line = 1;
    while (!complete)
    {
        printf("Enter the file name(without .txt, type exit to leave): ");
        scanf("%s", filename);
        if (strcmp(filename, "exit") == 0)
        {
            return 0;
        }
        strcpy(filetemp, filename);
        strcat(filename, ".txt");
        strcat(filetemp, "_temp.txt");
        file = fopen(filename, "r");
        temp = fopen(filetemp, "w");
        if (file == NULL || temp == NULL)
        {
            printf("The file does not exist\n");
            fclose(file);
            fclose(temp);
            return -1;
        }
        printf("Enter the line number to insert at: ");
        scanf("%d", &lineins);
        getchar();
        printf("Enter the new line of content: ");
        fgets(input, INPUT_MAX, stdin);
        input[strlen(input) - 1] = '\0';
        while (fgets(buffer, BUFFER_SIZE, file) != NULL)
        {
            if (line == lineins)
            {
                fprintf(temp, "%s\n", input);
            }
            fputs(buffer, temp);
            line++;
        }
        if (line <= lineins)
        {
            fprintf(temp, "%s\n", input);
        }
        fclose(file);
        fclose(temp);
        remove(filename);
        rename(filetemp, filename);
        file = fopen(CHANGE_LOG, "a");
        fprintf(file, "A line has been inserted at %d in %s. Number of lines = (number)\n", lineins, filename);
        fclose(file);
        printf("Line inserted successfully\n");
        complete = true;
    }
    return 0;
}

int show_line()
{
    bool complete = false;
    char filename[FILE_MAX];
    char buffer[BUFFER_SIZE];
    int linedis;
    int line = 1;
    FILE *file;
    while (!complete)
    {
        printf("Enter the file name(without .txt, type exit to leave): ");
        scanf("%s", filename);
        if (strcmp(filename, "exit") == 0)
        {
            return 0;
        }
        strcat(filename, ".txt");
        file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("The file does not exist\n");
            return -1;
        }
        printf("Enter the line number to display: ");
        scanf("%d", &linedis);
        while (fgets(buffer, BUFFER_SIZE, file) != NULL)
        {
            if (line == linedis)
            {
                printf("%s", buffer);
                fclose(file);
                file = fopen(CHANGE_LOG, "a");
                fprintf(file, "Line %d of %s has been displayed. Number of lines = (number)\n", linedis, filename);
                fclose(file);
                printf("Line displayed successfully\n");
                complete = true;
            }
            line++;
        }
        fclose(file);
        if (line < linedis)
        {
            printf("Line does not exist in file\n");
            return -1;
        }
    }
    return 0;
}

// general operations
int line_count()
{
    char filename[FILE_MAX];
    int line_count = 0;
    char letter;
    FILE *file;
    printf("Enter the file name(without .txt, type exit to leave): ");
    scanf("%s", filename);
    if (strcmp(filename, "exit") == 0)
    {
        return 0;
    }
    file = fopen(strcat(filename, ".txt"), "r");
    if (file == NULL)
    {
        printf("The file does not exist\n");
        return -1;
    }
    while (true)
    {
        letter = fgetc(file);
        if (letter == EOF)
        {
            break;
        }
        if (letter == '\n')
        {
            line_count++;
        }
    }
    printf("%s has %d lines\n", filename, line_count);
    return 1;
}

int show_change_log()
{
    bool complete = false;
    FILE *file;
    char *data;
    char letter;
    int i = 0;
    while (!complete)
    {
        file = fopen(CHANGE_LOG, "r");
        if (file == NULL)
        {
            printf("The change log is empty\n");
            return -1;
        }
        fseek(file, 0, SEEK_END);
        data = (char *)malloc(ftell(file) + 1);
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
            data[i++] = letter;
        }
        data[i] = '\0';
        fclose(file);
    }
    printf("%s\n", data);
    return 1;
}

int total_lines(char *filename)
{
    int linecount = 0;
    char letter;
    FILE *file;
    file = fopen(filename, "r");
    while (true)
    {
        letter = fgetc(file);
        if (letter == EOF)
        {
            break;
        }
        if (letter == '\n')
        {
            linecount++;
        }
    }
    fclose(file);
    return linecount;
}

// file operations
int create_file()
{
    bool complete = false;
    char filename[FILE_MAX];
    FILE *file;
    while (!complete)
    {
        printf("Enter the new file name(without .txt, type exit to leave): ");
        scanf("%s", filename);
        if (strcmp(filename, "exit") == 0)
        {
            return 0;
        }
        strcat(filename, ".txt");
        if (file = fopen(filename, "r"))
        {
            fclose(file);
            printf("File already exists.\n");
        }
        file = fopen(filename, "w");
        fclose(file);
        file = fopen(CHANGE_LOG, "a");
        fprintf(file, "%s has been created. Number of lines = 0\n", filename);
        fclose(file);
        printf("File created successfully\n");
        complete = true;
    }
    return 0;
}

int copy_file()
{
    bool complete = false;
    char source[FILE_MAX];
    char new[FILE_MAX];
    FILE *file;
    while (!complete)
    {
        printf("Enter the source file name(without .txt, type exit to leave): ");
        scanf("%s", source);
        if (strcmp(source, "exit") == 0)
        {
            return 0;
        }
        strcat(source, ".txt");
        FILE *srcfp = fopen(source, "r");
        if (srcfp == NULL)
        {
            printf("The file does not exist\n");
            return -1;
        }
        printf("Enter the new file name(without .txt): ");
        scanf("%s", new);
        strcat(new, ".txt");
        FILE *fp = fopen(new, "w");
        if (fp == NULL)
        {
            printf("Unable to create the file\n");
            fclose(srcfp);
            return -1;
        }
        file = fopen(CHANGE_LOG, "a");
        fprintf(file, "%s has been copied to %s. Number of lines = (number)\n", source, new);
        fclose(file);
        int ch;
        while ((ch = fgetc(srcfp)) != EOF)
        {
            fputc(ch, fp);
        }
        fclose(srcfp);
        fclose(fp);
        printf("File copied successfully\n");
        complete = true;
    }
    return 0;
}

int delete_file()
{
    bool complete = false;
    char filename[FILE_MAX];
    FILE *file;
    while (!complete)
    {
        printf("Enter the file name(without .txt, type exit to leave): ");
        scanf("%s", filename);
        if (strcmp(filename, "exit") == 0)
        {
            return 0;
        }
        if (remove(strcat(filename, ".txt")) == 0)
        {
            file = fopen(CHANGE_LOG, "a");
            fprintf(file, "%s has been deleted. Number of lines = 0\n", filename);
            fclose(file);
            printf("Deleted successfully\n");
            complete = true;
        }
        else
        {
            printf("Unable to delete the file\n");
        }
    }
    return 0;
}

int show_file()
{
    bool complete = false;
    char filename[FILE_MAX];
    char buffer[BUFFER_SIZE];
    FILE *file;
    while (!complete)
    {
        printf("Enter the file name(without .txt, type exit to leave): ");
        scanf("%s", filename);
        if (strcmp(filename, "exit") == 0)
        {
            return 0;
        }
        strcat(filename, ".txt");
        file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("The file does not exist\n");
            return -1;
        }
        while (fgets(buffer, BUFFER_SIZE, file) != NULL)
        {
            printf("%s", buffer);
        }
        fclose(file);
        file = fopen(CHANGE_LOG, "a");
        fprintf(file, "%s has been displayed. Number of lines = (number)\n", filename);
        fclose(file);
        printf("File contents displayed successfully\n");
        complete = true;
    }
    return 0;
}

int rename_file()
{
    bool complete = false;
    char source[FILE_MAX];
    char new[FILE_MAX];
    FILE *file;
    FILE *srcfile;
    while (!complete)
    {
        printf("Enter the file name (without .txt, type exit to leave): ");
        scanf("%s", source);
        if (strcmp(source, "exit") == 0)
        {
            return 0;
        }
        strcat(source, ".txt");
        srcfile = fopen(source, "r");
        if (srcfile == NULL)
        {
            printf("The file does not exist\n");
            return -1;
        }
        printf("Enter the new name(without .txt): ");
        scanf("%s", new);
        strcat(new, ".txt");
        file = fopen(new, "w");
        if (file == NULL)
        {
            printf("Unable to create the file\n");
            fclose(srcfile);
            return -1;
        }
        int ch;
        while ((ch = fgetc(srcfile)) != EOF)
        {
            fputc(ch, file);
        }
        fclose(srcfile);
        fclose(file);
        if (remove(source) == 0)
        {
            int lines = total_lines(new);
            file = fopen(CHANGE_LOG, "a");
            fprintf(file, "%s has been renamed to %s. Number of lines = %d\n", source, new, lines);
            fclose(file);
            printf("File renamed successfully\n");
            complete = true;
        }
        else
        {
            printf("Unable to delete the file\n");
            return -1;
        }
    }
    return 1;
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
    char *options[6] = {"copy", "create", "delete", "show", "rename", "exit"};
    int (*functions[6])() = {&copy_file, &create_file, &delete_file, &show_file, &rename_file, &my_exit};
    int result;

    while (run)
    {
        result = menu(options, functions, 6);
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
    char *options[3] = {"show change log", "show line count", "exit"};
    int (*functions[3])() = {&show_change_log, &line_count, &my_exit};
    int result;

    while (run)
    {
        result = menu(options, functions, 3);
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
    int (*functions[5])() = {&append_line, &delete_line, &insert_line, &show_line, &my_exit};
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