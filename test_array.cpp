#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ptr(double *array)
{
    double *array_t = (double *)malloc(32);
    array_t[0] = 1;
    array_t[1] = 1;
    memcpy(array, array_t, 32);
}

void transpose1(double *array, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = i; j < col; j++)
        {
            double tmp = array[i * row + j];
            array[i * row + j] = array[j * row + i];
            array[j * row + i] = tmp;
        }
    }
}

//打印矩阵
void print_array(double *a, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%g\t", a[i * row + j]);
        }
        printf("\n");
    }
}

//生成P和P的逆
void generate(double *result_P, double *result_P_inverse, double *a, int *pai, int *pai_inverse, int row)
{
    for (int i = 0; i < row; i++)
    {
        int mk_pai = 1, mk_pai_in = 1;
        for (int j = 0; mk_pai || mk_pai_in; j++)
        {
            if (pai[i] == (j + 1))
            {
                result_P[i * row + j] = a[i];
                mk_pai = 0;
            }
            if (pai_inverse[i] == (j + 1))
            {
                result_P_inverse[i * row + j] = (double)1 / a[j];
                mk_pai_in = 0;
            }
        }
    }
}

//求pai的逆
void inverse_pai(int *pai, int size_pai, int *result_pai)
{
    int *pai_inverse = (int *)malloc(size_pai * sizeof(int));
    for (int i = 0; i < size_pai; i++)
    {
        pai_inverse[pai[i] - 1] = (i + 1);
    }
    memcpy(result_pai, pai_inverse, size_pai * sizeof(int));
    free(pai_inverse);
}

//矩阵相乘
void mult_array(double *x, double *y, double *r, int x_r, int x_c, int y_c)
{
    // print_array(x, x_r, x_c);
    // print_array(y, x_c, y_c);
    for (int i = 0; i < x_r; i++)
    {
        for (int y_j = 0; y_j < y_c; y_j++)
        {
            double res = 0;
            for (int j = 0; j < x_c; j++)
                res = x[i * x_c + j] * y[j * y_c + y_j] + res;
            r[i * y_c + y_j] = res;
        }
    }
    // print_array(r, x_r, y_c);
    // printf("\n\n");
}

void Random_Permutation(int size, int *array)
{
    for (int i = 0; i < size; i++)
        array[i] = i + 1;
    for (int i = size; i >= 2; i--)
    {
        int j = rand() % i;
        int temp = array[i - 1];
        array[i - 1] = array[j];
        array[j] = temp;
    }
}
int main()
{
    double X[2][3] = {{1, 1, 1}, {1, 1, 1}};
    double Y[3][4] = {{2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}};
    double a[2] = {2, 3};
    double b[3] = {4, 5, 6};
    double c[4] = {7, 8, 9, 10};
    int pai1[2] = {2, 1};
    int pai2[3] = {2, 1, 3};
    int pai3[4] = {1, 3, 4, 2};
    int pai1_in[2];
    int pai2_in[3];
    int pai3_in[4];
    double P1[2][2] = {0};
    double P2[3][3] = {0};
    double P3[4][4] = {0};
    double P1_in[2][2] = {0};
    double P2_in[3][3] = {0};
    double P3_in[4][4] = {0};
    inverse_pai(&pai1[0], 2, &pai1_in[0]);
    inverse_pai(&pai2[0], 3, &pai2_in[0]);
    inverse_pai(&pai3[0], 4, &pai3_in[0]);
    /*
    for(int i=0;i<4;i++)
    {
        printf("%d\t",pai3_in[i]);
    }
    */

    generate(&P1[0][0], &P1_in[0][0], &a[0], &pai1[0], &pai1_in[0], 2);
    generate(&P2[0][0], &P2_in[0][0], &b[0], &pai2[0], &pai2_in[0], 3);
    generate(&P3[0][0], &P3_in[0][0], &c[0], &pai3[0], &pai3_in[0], 4);
    /*
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%lf\t%lf\t", P3[i][j], P3_in[i][j]);
        }
        printf("\n");
    }
    */
    double X_new[2][3];
    double X_apo[2][3];
    mult_array(&P1[0][0], &X[0][0], &X_new[0][0], 2, 2, 3);
    mult_array(&X_new[0][0], &P2_in[0][0], &X_apo[0][0], 2, 3, 3);

    double Y_new[3][4];
    double Y_apo[3][4];
    mult_array(&P2[0][0], &Y[0][0], &Y_new[0][0], 3, 3, 4);
    mult_array(&Y_new[0][0], &P3_in[0][0], &Y_apo[0][0], 3, 4, 4);

    double Z_apo[2][4];
    mult_array(&X_apo[0][0], &Y_apo[0][0], &Z_apo[0][0], 2, 3, 4);

    double Z_new[2][4];
    double Z[2][4];
    mult_array(&P1_in[0][0], &Z_apo[0][0], &Z_new[0][0], 2, 2, 4);
    mult_array(&Z_new[0][0], &P3[0][0], &Z[0][0], 2, 4, 4);
    
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%lf\t", Z[i][j]);
        }
        printf("\n");
    }

    return 0;
}