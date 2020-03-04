#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


/* TODO
    better implementation of run_script () function,
    should not waiting for closing feh
*/

int main ()
{
    int proc_num;
    int task_num;
    int *arr;
    double c_max;
    double **matrix = NULL;
    char *filepath = "src/script/plot_with_octave_script.m";

    fprintf (stdout, "Insert number of processors: ");
    fscanf (stdin, "%d", &proc_num);
    fprintf (stdout, "Insert number of tasks: ");
    fscanf (stdin, "%d", &task_num);
    
    arr = (int *) malloc (sizeof(int) * task_num);

    fprintf (stdout, "Insert time values:\n");
    for (int i = 0; i < task_num; ++i)
    {
        fscanf (stdin, "%d", arr + i);
    }

    c_max = pick_c_max (arr, task_num, proc_num);
    fprintf (stdout, "%.1lf\n", c_max);
    
    prepare_matrix (&matrix, proc_num, task_num);
    zero_matrix (matrix, proc_num, task_num);
    //print_matrix (matrix, proc_num, task_num);
    
    optimization (matrix, c_max, arr, task_num, proc_num);
    print_matrix (matrix, proc_num, task_num);

    create_script (matrix, filepath, proc_num, task_num);
    //print_matrix (matrix, proc_num, task_num);
    run_script (filepath);

    free_matrix (&matrix, proc_num);
    free (arr);
    return 0;

}