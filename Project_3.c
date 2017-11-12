// Project 3 - Jake Cheeseman - 2/10/15

// Instructions: "Write a program that reads in a data file, sorts the numbers into ascending and descending orders, and outputs the sorted numbers into two new files."

// 1. DECLARES HEADER FILES

#include <stdio.h>

int main()
{
    
// 2. DECLARES INTERNAL VARIABLES
    
    FILE *og_file, *new_file1, *new_file2;
    
    char og_name[25], new_name1[25], new_name2[25], c;
    
    int x, y, z;
    
    float f1[10000], f2[10000], p;
    
// 3. OPENS ORIGINAL FILE FROM TERMINAL
    
    printf("Enter original data filename: \n");
    scanf("%s",og_name);
    og_file=fopen(og_name,"r");
    
    if(og_file==NULL)
    {
        printf("Error opening file! \n");
        return(1);
    }
    
// 4. SCANS DATA FROM ORIGINAL FILE TO FIRST ARRAY
    
    x=0,y=0,z=0;
    do
    {   
        y = fscanf(og_file,"%f",&f1[x]);
        x++;
        z=(x-1); /* number data points scanned */
    }
    while(y!=EOF);
    
    fclose(og_file);
    
// 5. SORTS DATA INTO ASCENDING ORDER
    
    /* could have done this with for loops using z... */
    
    x=0,y=0,p=0;
    do
    {
        do
        {
            if(f1[x+1]!=0 && f1[x]>f1[x+1]) /* swap if next not zero and current > next */
            {
                p=f1[x];      
                f1[x]=f1[x+1];    
                f1[x+1]=p;
            }
            if(f1[x]!=0)
            {
                x++; /* inner counter */
            }
            else
            {
                x=0; /* reset inner counter and end looping */
            }
        }
        while(x!=0);
        y++; /* outer counter */
    }
    while(y<z); /* end looping when y = number data points scanned */
    
// 6. CHECKS FOR EXISTING FILE WITH SAME NAME
    
    printf("Enter new ascending data filename: \n");
    scanf("%s",new_name1);
    new_file1=fopen(new_name1,"r");
    
    if(new_file1)
    {
        printf("File already exists! Overwrite it? [y/n] \n");
        scanf("%1s",&c); 
        if(c=='n')
        {
            fclose(new_file1);
            printf("Enter filename other than \"%s\": \n",new_name1);
            scanf("%s",new_name1);
        }
        else
        {
            fclose(new_file1);
        }
    }
    
// 7. CREATES NEW FILE WITH DATA SORTED INTO ASCENDING ORDER
    
    new_file1=fopen(new_name1,"w");
    
    if(new_file1==NULL)
    {
        printf("Error creating file! \n");
        return(1);
    }
    
    x=0;
    do
    {
        fprintf(new_file1,"%f\n",f1[x]);
        x++;
    }
    while(x<z);
    
    fclose(new_file1);
    
// 8. SCANS DATA FROM ORIGINAL FILE TO SECOND ARRAY
    
    og_file=fopen(og_name,"r");
    
    if(og_file==NULL)
    {
        printf("Error opening file! \n");
        return(1);
    }
    
    x=0,y=0,z=0;
    do
    {   
        y = fscanf(og_file,"%f",&f2[x]);
        x++;
        z=(x-1); /* number of data points scanned */
    }
    while(y!=EOF);
    
    fclose(og_file);
    
// 9. SORTS DATA INTO DESCENDING ORDER
    
    /* could have decremented from top... */
    
    x=0,y=0,p=0;
    do
    {
        do
        {
            if(f2[x+1]!=0 && f2[x]<f2[x+1]) /* sign switched in second argument */
            {
                p=f2[x];      
                f2[x]=f2[x+1];    
                f2[x+1]=p; 
            }
            if(f2[x]!=0)
            {
                x++;
            }
            else
            {
                x=0;
            }
        }
        while(x!=0);
        y++;
    }
    while(y<z);
    
// 10. CHECKS FOR EXISTING FILE WITH SAME NAME
    
    printf("Enter new descending data filename: \n");
    scanf("%s",new_name2);
    new_file2=fopen(new_name2,"r");
    
    if(new_file2)
    {
        printf("File already exists! Overwrite it? [y/n] \n");
        scanf("%1s",&c); 
        if(c=='n')
        {
            fclose(new_file2);
            printf("Enter filename other than \"%s\": \n",new_name2);
            scanf("%s",new_name2);
        }
        else
        {
            fclose(new_file2);
        }
    }

// 11. CREATES NEW FILE WITH DATA SORTED INTO DESCENDING ORDER
    
    new_file2=fopen(new_name2,"w");
    
    if(new_file2==NULL)
    {
        printf("Error creating file! \n");
        return(1);
    }
    
    x=0;
    do
    {
        fprintf(new_file2,"%f\n",f2[x]);
        x++;
    }
    while(x<z);
    
    fclose(new_file2);
    
// 12. PRINTS STATUS AND ENDS PROGRAM
    
    printf("New files created! \n");
    
    return(0);
}