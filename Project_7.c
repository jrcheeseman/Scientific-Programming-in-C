// Project 7 - Jake Cheeseman - 3/30/15

// Instructions: "Write a program that performs a two-way within-subjects Analysis of Variance (ANOVA)."

// DECLARES HEADER FILES AND EXTERNAL VARIABLES

#include <stdio.h>

#define max_s 1000
#define max_k 100

int main()
{
    
// DECLARES INTERNAL VARIABLES    
    
    FILE *og_file;
    
    char og_name[25], id[25], c;
    
    int x, y, z, i; /* loop counters */
    int a, b, n, s, n_s; /* levels factor a & b, number cases, subjects per condition, number conditions */
    int df_a, df_b, df_s, df_ab, df_as, df_bs, df_abs, df_total;
    
    double data1[max_s][max_k],data2[max_s][max_k],data3[max_s][max_k];
    double row_sums[max_s];
    double column_sums1[max_k],column_sums2[max_k],column_sums3[max_k];
    double grand_sum, grand_quotient;
    double squared_values [max_s];
    double sums_array[max_k][max_k];
    double ss_total, ss_b, ss_a, ss_s, ss_ab, ss_as, ss_bs, ss_abs;
    double ms_a, ms_b, ms_ab, ms_as, ms_bs, ms_abs;
    double f_a, f_b, f_ab;
    
// WELCOMES USER AND OPENS DATA FILE FROM TERMINAL
    
    printf("\nBefore we begin, please check that your datafile is structured properly... \n\n");
    
    printf("Example: If Factor A has 4 levels and Factor B has 3 levels, \n");
    printf("the row data for each subject should be structured like this: \n");
    
    printf("\nS1 A1B1 A1B2 A1B3 A2B1 A2B2 A2B3 A3B1 A3B2 A3B3 A4B1 A4B2 A4B3 \n");
    
    printf("\nGood to go? [y/n] \n");
    scanf("%1s",&c);
    
    if(c=='n')
    {
        printf("\nOk, come back when you're ready... \n"); return(1);
    }
    else
    {
        printf("\nHooray!\n");
    }
    
    printf("\nPlease input the data filename: \n");
    scanf("%s",og_name);
    og_file=fopen(og_name,"r");
    
    if(og_file==NULL)
    {
        printf("Error opening file! \n");
        return(1);
    }
    
// DEFINES PARAMETERS AND SCANS DATA TO ARRAY
    
    printf("\nHow many subjects per condition? \n");
    scanf("%d",&s);
    
    printf("\nHow many levels of Factor A? \n");
    scanf("%d",&a);
    
    printf("\nHow many levels of Factor B? \n");
    scanf("%d",&b);
    
    n_s = a*b; n = n_s*s; 
    
    for(y=0;y<s;y++)
    {
        fscanf(og_file,"%s",id);
        for(x=0;x<n_s;x++)
        {
            fscanf(og_file,"%lf",&data1[y][x]);
        }
    }
    
    fclose(og_file);
 
// CALCULATES ROW & COLUMN SUMS
    
    z=0;
    for(y=0;y<s;y++)
    {
        for(x=0;x<n_s;x++)
        {
            row_sums[z] += data1[y][x];
        }
        z++;
    }
    
    z=0;
    for(x=0;x<n_s;x++)
    {
        for(y=0;y<s;y++)
        {
            column_sums1[z] += data1[y][x];
        }
        z++;
    }
    
    for(z=0;z<n_s;z++)
    {
        grand_sum += column_sums1[z];
    }
    
    grand_quotient = (grand_sum*grand_sum)/n;
    
// CALCULATES SS_TOTAL
    
    z=0;
    for(x=0;x<n_s;x++)
    {
        for(y=0;y<s;y++)
        {
            squared_values[z] += (data1[y][x]*data1[y][x]);
        }
        z++;
    }
    
    for(z=0;z<n_s;z++)
    {
        ss_total += squared_values[z];
    }
    
    ss_total = ss_total - grand_quotient;
    
// CALCULATES SS_A
    
    z=0;
    for(x=0;x<a;x++)
    {
        for(y=0;y<b;y++)
        {
            sums_array[y][x] = column_sums1[z]; z++;
        }
    }
    
    z=0;
    for(x=0;x<a;x++)
    {
        for(y=0;y<b;y++)
        {
            column_sums2[z] += sums_array[y][x];
        }
        z++;
    }
    
    for(z=0;z<a;z++)
    {
        ss_a += (column_sums2[z]*column_sums2[z]);
    }
    
    ss_a = ss_a/(n/a);
    ss_a = ss_a - grand_quotient;
    
// CALCULATES SS_B

    z=0;
    for(y=0;y<b;y++)
    {
        for(x=0;x<a;x++)
        {
            column_sums3[z] += sums_array[y][x];
        }
        z++;
    }
    
    for(z=0;z<b;z++)
    {
        ss_b += (column_sums3[z]*column_sums3[z]);
    }
    
    ss_b = ss_b/(n/b);
    ss_b = ss_b - grand_quotient;
    
// CALCULATES SS_S
    
    for(z=0;z<s;z++)
    {
        ss_s += (row_sums[z]*row_sums[z]);
    }
    
    ss_s = ss_s/n_s;
    ss_s = ss_s - grand_quotient;

// CALCULATES SS_AB
    
    for(z=0;z<n_s;z++)
    {
        ss_ab += (column_sums1[z]*column_sums1[z]);
    }
    
    ss_ab = ss_ab/s;
    ss_ab = ss_ab - grand_quotient - ss_a - ss_b;
    
// CALCULATES SS_AS
    
    i=0;
    for(z=0;z<a;z++)
    {
        for(x=0;x<b;x++)
        {
            for(y=0;y<s;y++)
            {
                data2[y][z] +=data1[y][x+i];
            }
        }
        i+=b;
    }
    
    for(x=0;x<a;x++)
    {
        for(y=0;y<s;y++)
        {
            data2[y][x] = data2[y][x]*data2[y][x];
            ss_as += data2[y][x];
        }
    }

    ss_as = ss_as/b;
    ss_as = ss_as - grand_quotient - ss_a - ss_s;
    
// CALCULATES SS_BS AND SS_ABS
    
    i=0;
    for(z=0;z<b;z++)
    {
        for(x=0;x<a;x++)
        {
            for(y=0;y<s;y++)
            {
                data3[y][z] += data1[y][x+i];
            }
            i+=(b-1);
        }
        if(b==2)
        {
            i-=a-1;
        }
        else
        {
            i-=a+(b-1);
        }
    }
    
    for(x=0;x<b;x++)
    {
        for(y=0;y<s;y++)
        {
            data3[y][x] = data3[y][x]*data3[y][x];
            ss_bs += data3[y][x];
        }
    }
    
    ss_bs = ss_bs/a;
    ss_bs = ss_bs - grand_quotient - ss_b - ss_s;
    ss_abs = (ss_total - ss_a - ss_b - ss_s - ss_ab - ss_as - ss_bs);
    
// CALCULATES DEGREES OF FREEDOM, MEAN SQUARES, AND F VALUES
    
    df_a = (a-1); 
    df_b = (b-1);
    df_s = (s-1);
    df_ab = ((a-1)*(b-1)); 
    df_as = ((a-1)*(s-1)); 
    df_bs = ((b-1)*(s-1)); 
    df_abs = ((a-1)*(b-1)*(s-1)); 
    df_total = (n-1); 
    
    ms_a = ss_a/df_a; 
    ms_b = ss_b/df_b; 
    ms_ab = ss_ab/df_ab; 
    ms_as = ss_as/df_as; 
    ms_bs = ss_bs/df_bs; 
    ms_abs = ss_abs/df_abs; 
    
    f_a = ms_a/ms_as; 
    f_b = ms_b/ms_bs; 
    f_ab = ms_ab/ms_abs;

// PRINTS OUTPUT AND ENDS PROGRAM
    
    printf("\nbeep boop beep boop beep boop beep boop beep boop beep... DONE!\n");
    
    printf("\n---------- Summary Table: Two-Way Within-Subjects ANOVA ----------\n");
    printf("------------------------------------------------------------------\n");
    printf("      Source          df          SS          MS          F       \n");
    printf("------------------------------------------------------------------\n");
    printf("   Subjects           %d         %6.3f                            \n\n",df_s,ss_s);
    printf("   Factor A           %d         %6.3f     %6.3f      %6.3f       \n",df_a,ss_a,ms_a,f_a);
    printf("   Factor A x S       %d         %6.3f     %6.3f                  \n\n",df_as,ss_as,ms_as);
    printf("   Factor B           %d         %6.3f     %6.3f      %6.3f       \n",df_b,ss_b,ms_b,f_b);
    printf("   Factor B x S       %d         %6.3f     %6.3f                  \n\n",df_bs,ss_bs,ms_bs);
    printf("   Factor A x B       %d         %6.3f     %6.3f      %6.3f       \n",df_ab,ss_ab,ms_ab,f_ab);
    printf("   Factor A x B x S   %d         %6.3f     %6.3f                  \n",df_abs,ss_abs,ms_abs);
    printf("------------------------------------------------------------------\n");
    printf("    Total             %d       %6.3f                              \n",df_total,ss_total);
    printf("------------------------------------------------------------------\n\n");
    
    return(0);
}