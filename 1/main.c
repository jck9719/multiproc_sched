#include <stdio.h>
#include <stdlib.h>


#define MAX(a,b) ((a) > (b) ? a : b)


// sum/machines
double sum_t_values (int *arr, int arr_length, int machines)
{
    int sum = 0;
    for (int i = 0; i < arr_length; ++i)
    {
        sum += arr[i];
    }

    //fprintf (stdout, "Sum = %d\n", sum);

    return (double) sum/machines; 
}

int find_max_t_value (int *arr, int arr_length)
{
    int max = arr[0];

    for (int i = 1; i < arr_length; ++i)
    {
        if (max < arr[i]) 
        {
            max = arr[i];
        }
    }

    //fprintf (stdout, "Max = %d\n", max);

    return max;
}

double pick_max (double sum_t_values, int max_t_value)
{
    return (double) MAX (sum_t_values, max_t_value);
}



int main ()
{
    int proc_num;
    int task_num;
    double sum_t;
    int f_max_t;
    double max_c;

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

    sum_t = sum_t_values (arr, task_num, proc_num);
    fprintf (stdout, "Sum/proc = %.1lf\n", sum_t);
    
    f_max_t = find_max_t_value (arr, task_num);
    fprintf (stdout, "Max = %d\n", f_max_t);

    max_c = pick_max (sum_t, (double) f_max_t);

    fprintf (stdout, "C = %.1lf\n", max_c);

    double sum;
    int j = 0;
    double temp;
    double temp2 = 0;

    for (int i = 0; i < proc_num; ++i)
    {
        sum = 0;
        fprintf (stdout, "\nM%d:\t", i + 1);

        while (sum < max_c)
        {
            if (temp2 != 0)
            {
                sum = temp2;
                fprintf (stdout, "Z%d:%.1lf\t\t", j + 1, sum);
                temp2 = 0;
                ++j;
                continue;
            }
            if (sum == 0 && sum + ((double)arr[j]) == max_c && temp2 == 0)
            {
                fprintf (stdout, "Z%d:%d", j + 1, arr[j]);
                ++j;
                break;
            }

            if (sum + ((double)arr[j]) > max_c)
            {
                temp = (double) arr[j];
                while (sum + temp > max_c)
                {
                    temp -= 0.5;
                    temp2 += 0.5;
                }
                // temp = (sum + ((double) arr[j]) - max_c);
                // temp2 = ((double) arr[j]) - temp;
                fprintf (stdout, "Z%d:%.1lf\t\t", j + 1, temp);
                break;
            }

            sum += ((double) arr[j]);
            fprintf (stdout, "Z%d:%d\t\t", j + 1, arr[j]);
            ++j;

            if(j >= task_num)
            {
                fprintf (stdout, "\n");
                exit (0);
            }

        }
    }

    fprintf (stdout, "\n");


    // for (int i = 0; i < task_num; ++i)
    // {
    //     fprintf (stdout, "%d\n", arr[i]);
    // }



    return 0;




}