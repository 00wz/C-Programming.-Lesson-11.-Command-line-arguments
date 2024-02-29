#include <stdio.h>
#include <stdlib.h>
#include "temp_functions.h"
#define BUFFER 1000
#define MONTHS_COUNT 12
#define N 6

typedef struct MonthlyStatistics
{
    int max;
    double sum;
    int min;
    __uint64_t row_count;
} Month_t;

static char* months_names[MONTHS_COUNT] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December" };

static Month_t* months = NULL;

static short month_input_index = -1;

static void UpdateMonth(int index, int temp)
{
    index--;
    if(temp < months[index].min)
    {
        months[index].min = temp;
    }

    if(temp > months[index].max)
    {
        months[index].max = temp;
    }

    months[index].sum += temp;
    months[index].row_count++;
}

static void print_month_statistic(int index)
{
    Month_t month = months[index];
    double average = month.sum / month.row_count;
    printf("%s: Max(%d) Min(%d) Average(%lf)\n",
    months_names[index], month.max, month.min, average);
}

static void print_year_statistic()
{
    double sum = 0;
    int max = -__INT_MAX__;
    int min = __INT_MAX__;

    for (size_t i = 0; i < MONTHS_COUNT; i++)
    {
        Month_t month = months[i];
        double month_average = month.sum / month.row_count;
        sum += month_average;

        if(month.max > max)
        {
            max = month.max;
        }
        if(month.min < min)
        {
            min = month.min;
        }
    }
    double average = sum / MONTHS_COUNT;

    printf("====================\n");
    printf("Year: Max(%d) Min(%d) Average(%lf)\n", max, min, average);
    printf("====================\n");
}

static void init_months()
{
    if(months == NULL)
    {
        months = malloc(sizeof(Month_t)*MONTHS_COUNT);
    }

    for (size_t i = 0; i < MONTHS_COUNT; i++)
    {
        months[i].max = -__INT_MAX__;
        months[i].min = __INT_MAX__;
        months[i].row_count = 0;
        months[i].sum = 0.;
    }
    
}

void help()
{
    FILE *open;
    char name[] = "help.txt";
    open = fopen(name, "r");
    char str[BUFFER];
    fscanf(open, "%[^EOF]", str);
    fclose(open);
    printf("%s\n", str);
}

void input_file(char* name)
{
    FILE *open;
    open = fopen(name, "r");
    if(open == NULL)
    {
        printf("file \"%s\" not found\n", name);
        exit(0);
    }
    
    init_months();

    int Y, M, D, H, Min, T;

    int r;
    int row = 0;

    while((r = fscanf(open, "%d;%d;%d;%d;%d;%d",
    &Y, &M, &D, &H, &Min, &T)) > 0)
    {
        if(r<N)
        {
            char s[30];
            r = fscanf(open, "%[^\n]", s);
            printf("ERROR line %d: %s\n", row, s);
        }
        else
        {
            if(M >= 1 && M <= MONTHS_COUNT)
            {
                UpdateMonth(M, T);
            }
            else
            printf("month in %d\n", row);
        }
        row++;
    }

    fclose(open);
}

void set_month(char* num)
{
    short index = atoi(num);
    if(index >= 1 && index <= MONTHS_COUNT)
    {
        month_input_index = index - 1;
    }
    else
    {
        printf("incorrect month index: %d\n", index);
        exit(0);
    }
}

void print_statistic()
{
    if(months == NULL)
    {
        printf("empty input\n");
        exit(0);
    }

    if(month_input_index == -1)
    {
        for (size_t i = 0; i < MONTHS_COUNT; i++)
        {
            print_month_statistic(i);
        }
        print_year_statistic();
    }
    else
    {
        print_month_statistic(month_input_index);
    }
}