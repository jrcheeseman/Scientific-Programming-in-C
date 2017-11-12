// Project 5 - Jake Cheeseman - 2/25/15

// Instructions: "Write a program that performs a one-way within-subjects Analysis of Variance (ANOVA)."

// 1. DECLARES HEADER FILES

#include <stdio.h>

#define max_s 1000 /* max subjects */
#define max_k 10 /* max conditions */

int main()
{

// 2. DECLARES INTERNAL VARIABLES    
    
    FILE *og_file;
    
    char og_name[25], id[25];
    
    int x, y, i; /* loop counters */
    int s, k, n; /* subjects, conditions, cases */
    int df_total, df_between, df_within, df_model, df_error;
    
    double data[max_s][max_k];
    double sum_x[max_s], mean_x[max_s];
    double sum_y[max_k], mean_y[max_k];
    double sum_grand, mean_grand;
    double dev_grand[max_s][max_k];
    double dev_x[max_s][max_k];
    double prod_k[max_k];
    double ss_total, ss_within, ss_between, ss_model, ss_error;
    double ms_model, ms_error, f;
    
// 3. OPENS DATA FILE FROM TERMINAL
    
    printf("Input data filename: \n");
    scanf("%s",og_name);
    og_file=fopen(og_name,"r");
    
    if(og_file==NULL)
    {
        printf("Error opening file! \n");
        return(1);
    }
    
// 4. DEFINES PARAMETERS AND SCANS DATA TO ARRAY
    
    printf("How many subjects? \n");
    scanf("%d",&s);
    
    printf("How many conditions? \n");
    scanf("%d",&k);
    
    n=s*k;
    
    for(y=0;y<s;y++)
    {
        fscanf(og_file,"%s",id);
        for(x=0;x<k;x++)
        {
            fscanf(og_file,"%lf",&data[y][x]);
        }
    }
    
    fclose(og_file);
    
// 5. CALCULATES MEANS
    
    i=0;
    for(y=0;y<s;y++)
    {
        for(x=0;x<k;x++)
        {
            sum_x[i] += data[y][x];
        }
        mean_x[i] = sum_x[i] / k;
        sum_grand += mean_x[i];
        i++;
    }
    mean_grand = sum_grand / s;
    
    i=0;
    for(x=0;x<k;x++)
    {
        for(y=0;y<s;y++)
        {
            sum_y[i] += data[y][x];
        }
        mean_y[i] = sum_y[i] / s;
        i++;
    }
    
// 6. CALCULATES SUM OF SQUARES TOTAL
    
    for(y=0;y<s;y++)
    {
        for(x=0;x<k;x++)
        {
            dev_grand[y][x] = ((data[y][x]-mean_grand)*(data[y][x]-mean_grand));
        }
    }
    
    for(x=0;x<k;x++)
    {
        for(y=0;y<s;y++)
        {
            ss_total += dev_grand[y][x];
        }
    }
    
// 7. CALCULATES SUM OF SQUARES WITHIN & BETWEEN
    
    i=0;
    for(y=0;y<s;y++)
    {
        for(x=0;x<k;x++)
        {
            dev_x[y][x] = ((data[y][x]-mean_x[i])*(data[y][x]-mean_x[i]));
        }
        i++;
    }
    
    for(x=0;x<k;x++)
    {
        for(y=0;y<s;y++)
        {
            ss_within += dev_x[y][x];
        }
    }
    ss_between = ss_total - ss_within;
    
// 8. CALCULATES SUM OF SQUARES MODEL & ERROR

    for(i=0;i<k;i++)
    {
        prod_k[i] = s * ((mean_y[i]-mean_grand)*(mean_y[i]-mean_grand));
        ss_model += prod_k[i];
    }
    ss_error = ss_within - ss_model;

// 9. CALCULATES DEGREES OF FREEDOM
    
    df_total = n-1;
    df_between = s-1;
    df_within = s*(k-1);
    df_model = k-1;
    df_error = df_within - df_model;
    
// 10. CALCULATES MEAN SQUARE MODEL & ERROR, F STAT
    
    ms_model = ss_model / df_model;
    ms_error = ss_error / df_error;
    f = ms_model / ms_error;
    
// 11. PRINTS OUTPUT AND ENDS PROGRAM
    
    printf("F(%d,%d) = %6.3f \n",df_model,df_error,f);
    
    return(0);
}