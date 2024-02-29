#include <stdio.h>
#include <unistd.h>
#include "temp_functions.h"

int main(int argc, char *argv[])
{
    if(argc <= 1)
    {
        help();
        return 0;
    }

    int res = 0;
    while((res = getopt(argc, argv, "hf:m:")) != -1)
    {
        switch(res)
        {
            case 'h':
                help();
                break;
            case 'f':
                input_file(optarg);
                break;
            case 'm':
                set_month(optarg);
                break;
        }
    }

    print_statistic();
}