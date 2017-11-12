// Project 2 - Jake Cheeseman - 2/3/15

// Instructions: "Write a program that when given a data file will transform the data (by calculating the logarithm of the data; the program should be able to do this for arbitrary log bases, such as log base 3, log base 8, log base 10, ect.) and output new files that are the transformed versions of the old file. The program should read in the desired log base using scanf() from the standard C console."

// 1. DECLARES HEADER FILES & EXTERNAL VARIABLES

#include <stdio.h>
#include <math.h>

int n = 100;

int main()
{
    
// 2. DECLARES INTERNAL VARIABLES
    
    FILE *og_file, *new_file;
    
    char og_name[25], new_name[25];
    
    int x;
    
    double f[n], b;
    
// 3. OPENS FILE FROM TERMINAL
    
    printf("Enter original data filename: \n");
    scanf("%s",og_name);
    og_file=fopen(og_name,"r");
    
    if(og_file==NULL)
    {
        printf("Error opening file! \n");
        return(1);
    }
    
// 4. SCANS DATA FROM FILE
    
    for(x=0;x<n;x++)
    {
        fscanf(og_file,"%lf",&f[x]);
    }
    fclose(og_file);
    
// 5. TRANSFORMS DATA
    
    printf("Enter desired log base: \n");
    scanf("%lf",&b);
    
    for(x=0;x<n;x++)
    {
        f[x]=log10(f[x])/log10(b);
    }
    
// 6. CREATES NEW FILE WITH TRANSFORMED DATA 
    
    printf("Enter new data filename: \n");
    scanf("%s",new_name);
    new_file=fopen(new_name,"w");
    
    if(new_file==NULL)
    {
        printf("Error creating file! \n");
        return(1);
    }
    
    for(x=0;x<n;x++)
    {
        fprintf(new_file,"%f\n",f[x]);
    }
    
    fclose(new_file);
    printf("New file created! \n");
     
// 7. ENDS PROGRAM
    
    return(0);
}