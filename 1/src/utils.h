#ifndef _UTILS_H_
#define _UTILS_H_

#define MAX(a,b)             \
__extension__                \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

double count_divided_sum_t (int *arr, int arr_length, int processors);
int find_longest_t (int *arr, int arr_length);
double pick_c_max (int *arr, int arr_length, int proc_num);
void prepare_matrix (double ***matrix, int rows, int columns);
void zero_matrix (double **matrix, int rows, int columns);
void print_matrix (double **matrix, int rows, int columns);
void free_matrix (double ***matrix, int rows);
void optimization (double **matrix, double c_max, int *arr, int task_num, int proc_num);
void create_script (double **matrix, char *filename, int rows, int columns);
void run_script (char *filename);


#endif