// Project 1 - Jake Cheeseman - 1/30/15

// Instructions: "Write a program that reads in a data file (using fopen) and then calculates and prints out the mean, standard deviation, and standard error."

// 1. DECLARES HEADER FILES & EXTERNAL VARIABLES

#include <stdio.h>
#include <math.h>

int n = 100; /* sample size */

int main()
{
    
// 2. DECLARES INTERNAL VARIABLES
    
    FILE *data;
    
    int x;
    
    float f[n];
    float sum;
    float mean;
    float sos;
    float sd;
    float se;
    
// 3. OPENS FILE 
    
    data=fopen("/Users/JakeCheeseman/Documents/Grad School/Courses/PSYS 590 - Programming/Projects/p1/dataP1.dat","r"); /*Better to be able to input file name from terminal...*/
    
    if(data==NULL)
    {
        puts("Error opening file!"); /*Use printf instead...*/
        return(1);
    }
    
// 4. SCANS DATA FROM FILE
    
    for(x=0;x<n;x++)
        fscanf(data,"%f",&f[x]);
    fclose(data);
    
// 5. CALCULATES & PRINTS MEAN 
    
    for(x=0;x<n;x++)
    {
        sum += f[x];
    }
    
    mean = sum/n;
    
    printf(" M = %f\n",mean);
    
// 6. CALCULATES & PRINTS STANDARD DEVIATION
    
    for(x=0;x<n;x++)
        f[x] -= mean;
    
    for(x=0;x<n;x++)
        f[x] = pow(f[x],2);
    
    for(x=0;x<n;x++)
    {
        sos += f[x];
    }
    
    sd = sqrt(sos/(n-1));
    
    printf("SD = %f\n",sd);
    
// 7. CALCULATES & PRINTS STANDARD ERROR
    
    se = sd/sqrt(n);
    
    printf("SE = %f\n",se);
    
// 8. ENDS PROGRAM
    
    return(0);
}