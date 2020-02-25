#include <stdio.h>
#include <stdlib.h>

int sum_max (int *arr, int arr_length)
{
    int sum = 0;
    for (int i = 0; i < arr_length; ++i)
    {
        sum += arr[i];
    }

    fprintf (stdout, "Sum = %d\n", sum);

    return sum;
}

int find_max (int *arr, int arr_length)
{
    int max = arr[0];

    for (int i = 1; i < arr_length; ++i)
    {
        if (max < arr[i]) 
        {
            max = arr[i];
        }
    }

    fprintf (stdout, "Max = %d\n", max);

    return max;
}



int main ()
{
    int proc_num;
    int task_num;
    int sum;
    int max;
    fprintf (stdout, "Insert number of processors:\n");
    fscanf (stdin, "%d", &proc_num);
    fprintf (stdout, "Insert number of task:\n ");
    fscanf (stdin, "%d", &task_num);

    int arr[task_num];

    fprintf (stdout, "Insert time values:\n");
    for (int i = 0; i < task_num; ++i)
    {
        fscanf (stdin, "%d", &arr[i]);
    }

    sum = sum_max (arr, task_num);
    fprintf (stdout, "Sum again = %d\n", sum);
    
    max = find_max (arr, task_num);
    fprintf (stdout, "Max again = %d\n", max);


    // for (int i = 0; i < task_num; ++i)
    // {
    //     fprintf (stdout, "%d\n", arr[i]);
    // }



    return 0;




}