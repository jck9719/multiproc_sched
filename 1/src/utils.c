#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

double count_divided_sum_t (int *arr, int arr_length, int proc_num)
{
    int sum = 0;
    for (int i = 0; i < arr_length; ++i)
    {
        sum += arr[i];
    }

    fprintf (stdout, "Sum  divided= %d\n", sum/proc_num);

    return (double) sum/proc_num; 
}

int find_longest_t (int *arr, int arr_length)
{
     int max = arr[0];

    for (int i = 1; i < arr_length; ++i)
    {
        if (max < arr[i]) 
        {
            max = arr[i];
        }
    }

    return max;
}

double pick_c_max (int *arr, int arr_length, int proc_num)
{
    return MAX(count_divided_sum_t (arr, arr_length, proc_num), (double) (find_longest_t (arr, arr_length)));
}

void prepare_matrix (double ***matrix, int rows, int columns)
{
    *matrix = malloc (rows * sizeof (double *));

    for (int i = 0; i < rows; ++i)
    {
        (*matrix)[i] = malloc (columns * sizeof (double));
    }
}

void zero_matrix (double **matrix, int rows, int columns)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            matrix[i][j] = 0.0;
        }
    }
}

void print_matrix (double **matrix, int rows, int columns)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            fprintf (stdout, "[%d][%d] = %.1lf\n", i, j, matrix[i][j]);
        }
    }
}

void free_matrix (double ***matrix, int rows)
{
    for (int i = 0; i < rows; ++i)
    {
            free ((*matrix)[i]);
    }

    free (*matrix);
    *matrix = NULL;
}

void optimization (double **matrix, double c_max, int *arr, int task_num, int proc_num)
{
    
    int j = 0;
    double sum;
    double temp, temp2 = 0;


     for (int i = 0; i < proc_num; ++i)
    {
        sum = 0;
        fprintf (stdout, "\nM%d:\t", i + 1);

        while (sum < c_max)
        {
            if (temp2 != 0)
            {
                sum = temp2;
                fprintf (stdout, "Z%d:%.1lf\t\t", j + 1, sum);
                matrix[i][j] = sum;
                temp2 = 0;
                ++j;
                continue;
            }
            if (sum == 0 && sum + ((double)arr[j]) == c_max && temp2 == 0)
            {
                fprintf (stdout, "Z%d:%d", j + 1, arr[j]);
                matrix[i][j] = arr[j];
                ++j;
                break;
            }

            if (sum + ((double)arr[j]) > c_max)
            {
                temp = (double) arr[j];
                while (sum + temp > c_max)
                {
                    temp -= 0.001;
                    temp2 += 0.001;
                }

                fprintf (stdout, "Z%d:%.1lf\t\t", j + 1, temp);
                matrix[i][j] = temp;
                break;
            }

            sum += ((double) arr[j]);
            fprintf (stdout, "Z%d:%d\t\t", j + 1, arr[j]);
            matrix[i][j] = arr[j];
            ++j;

            if(j >= task_num)
            {
                fprintf (stdout, "\n");
                break;
            }

        }
    }
    fprintf (stdout, "\n\n");
}

void create_script (double **matrix, char *filename, int rows, int columns)
{
    
    FILE *handler;
    //int temp = 0;
    
    handler = fopen (filename, "w");

    fprintf (handler, "graphics_toolkit (\"gnuplot\");\nformat long;\noutput_precision = 1;\n\nd = [");
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            if (j == columns - 1 && i == rows - 1)
            {
                fprintf (handler, "%.1lf];\n", matrix[i][j]);
                break;
            }
            else if (j == columns - 1)
            {
                fprintf (handler, "%.1lf;", matrix[i][j]);
                break;
            }
            else
            {
                fprintf (handler, "%.1lf,", matrix[i][j]);
            }
        }
    }

    fprintf (handler, "barh (d, \"stacked\");\nset (gca (), \"ydir\", \"reverse\");\nxlabel (\"Time\");\nylabel (\"Machines\");\ntitle (\"Diagram\");\n");

    fprintf (handler, "legend ({");
    for (int i = 0; i < columns; ++i)
    {
        if (i == columns - 1)
        {
            fprintf (handler, "\"Z%d\"},", i + 1);
            break;
        }
        fprintf (handler, "\"Z%d\",", i + 1);
    }
    fprintf (handler, " \"location\", \"eastoutside\");\n");
    fprintf (handler, "print -dpng output/optimize_diagram.png;\n");
    fclose (handler);
}

void run_script (char *filename)
{
    char *cmd = (char *) malloc (128 * sizeof (char));
    char *feh = (char *) malloc (128 * sizeof (char));

    sprintf(cmd, "octave %s", filename);
    sprintf(feh, "feh output/optimize_diagram.png");

    system (cmd);
    system (feh);
    
    free (feh);
    free (cmd);
}