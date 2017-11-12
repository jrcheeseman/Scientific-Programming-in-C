// Project 6 - Jake Cheeseman - 3/20/15

// Instructions: "Write a program that performs a Kruskal-Wallis one-way Analysis of Variance of Ranks (ANOVA of Ranks)."

// DECLARES HEADER FILES & EXTERNAL VARIABLES

#include <stdio.h>

#define max_s 1000
#define max_k 10

int main()
{
    
// DECLARES INTERNAL VARIABLES    
    
    FILE *og_file;
    
    char og_name[25];
    
    int i, x, y, z; /* loop counters */
    int k; /* conditions */
    int eof; /* end of file */
    int sk[max_s]; /* subjects per condition */
    
    float og_column1[max_s][max_k], og_column2[max_s][max_k], og_list[max_s];
    float sorted_list1[max_s], sorted_list2[max_s], sorted_list3[max_s];
    float ranked_list1[max_s], ranked_list2[max_s];
    float sum[max_k], square[max_k], mean[max_k], sum_mean, rank_sum;
    float ties[max_s], t, sum_t; 
    float a, b, c, n, h; /* formula terms */
    float r, p;
    
// OPENS DATA FILE FROM TERMINAL AND SCANS DATA TO ARRAYS
    
    printf(" -- Welcome to the Kruskal-Wallis ANOVA Experience! -- \n\n");
    
    printf("Input data filename: \n"); scanf("%s",og_name); 
    
    og_file=fopen(og_name,"r");
    
    if(og_file==NULL)
    {
        printf("Error opening file! \n"); return(1);
    }
    
    printf("How many conditions? \n"); scanf("%d",&k);
    
    i=1,x=0,y=0;
    for(i=1;i<(k+1);i++)
    {
        printf("How many subjects for condition %d? \n",i); scanf("%d",&sk[x]);
        for(y=0;y<sk[x];y++)
        {
            fscanf(og_file,"%f",&og_column1[y][x]);
        }
        //n+=sk[x]; 
        x++;
    }
    
    fclose(og_file); 
    
    og_file=fopen(og_name,"r");
    
    eof=0,i=0,n=0;
    do
    {   
        eof = fscanf(og_file,"%f",&og_list[i]); i++; n=(i-1);
    }
    while(eof!=EOF); fclose(og_file);
    
    i=0;
    for(i=0;i<n;i++)
    {
        sorted_list1[i]=og_list[i];
        ranked_list1[i]=(i+1);
        ranked_list2[i]=(i+1);
    }
    
// SORTS SECOND LIST ARRAY INTO ASCENDING ORDER
    
    i=0,x=0,y=0,p=0;
    for(i=0;i<n;i++)
    {
        for(x=0;x<n-1;x++)
        {
            if(sorted_list1[x+1]!=0 && sorted_list1[x]>sorted_list1[x+1])
            {
                p=sorted_list1[x]; sorted_list1[x]=sorted_list1[x+1]; sorted_list1[x+1]=p;
            }
        }
    }
    
    for(i=0;i<n;i++)
    {
        sorted_list2[i]=sorted_list1[i];
    }
    
// CONVERTS FIRST LIST ARRAY TO RANK VALUES
    
    /* strange bug at the end of data6_ex2 */
    
    x=0,y=0,p=0;
    for(x=0;x<n;x++)
    {
        for(y=0;y<n;y++)
        {
            if(og_list[x]==sorted_list1[y] && sorted_list1[y]!=0)
            {
                //printf("og_list[x] = %6.3f sorted_list1[y] = %6.3f \n",og_list[x],sorted_list1[y]);
                og_list[x]=y+1;
                sorted_list1[y]=0;   
            }
        }
    }
/*    
    for(x=0;x<n;x++)
    {
        printf("og_list[x] = %6.3f \n",og_list[x]);
    }
*/    
// CONVERTS SECOND COLUMNATED ARRAY TO RANKS
    
    x=0,y=0,z=0;
    for(x=0;x<k;x++)
    {
        for(y=0;y<sk[x];y++)
        {
            og_column1[y][x] = og_list[y+z]; 
        }
        z+=sk[x];
    } 
/*    
    printf("-- original ranks -- \n\n");
    
    for(x=0;x<k;x++)
    {
        for(y=0;y<sk[x];y++)
        {
            printf("og_column1[y][x] = %6.3f \n",og_column1[y][x]);
        }
    }
*/    
// COUNTS TIES IN SECOND LIST ARRAY AND CALCULATES T VALUES
/*    
    i=0,x=0;y=1;z=0;t=1;
    for(i=0;i<n;i++)
    {
        for(x=0;x<n;x++)
        {
            if(sorted_list1[i]==sorted_list1[x] && sorted_list1[i]!=sorted_list1[i+1] && i!=x)
            {
                t++;
            }
        }
        if(t>1)
        {
            ties[z] = (t*t*t)-t; z++; t=1;
        }
        
    }   
    
    for(x=0;x<k;x++)
    {
        for(y=0;y<sk[x];y++)
        {
            printf("og_column12[y][x] = %6.3f \n",og_column12[y][x]);
        }
    }
*/    
    
// ADJUSTS RANK VALUES FOR TIES
/*    
    if(ties[0]>0)
    {
        i=0,x=0;y=1;rank_sum=0;
        for(i=0;i<n;i++)
        {
            for(x=0;x<n;x++)
            {
                if(sorted_list2[i]==sorted_list2[x] && i!=x) 
                {
                    y++;
                    if(sorted_list2[i]!=sorted_list2[i+1])
                    {                    
                        rank_sum = (ranked_list2[i]+=ranked_list2[x]);
                        ranked_list2[i] = (rank_sum/y);
                        ranked_list2[x] = (rank_sum/y);
                    }
                }
                rank_sum=0;
                y=1;
            }
        }
        
        i=0,x=0,y=0;
        for(i=0;i<n;i++)
        {
            for(x=0;x<k;x++)
            {
                for(y=0;y<sk[x];y++)
                {
                    if(ranked_list1[i]!=ranked_list2[i] && ranked_list1[i]==og_column12[y][x])
                    {
                        og_column12[y][x] = ranked_list2[i];
                    }
                }
            }
        }
    }
    
    
    printf("-- adjusted ranks -- \n\n");
    
    for(x=0;x<k;x++)
    {
        for(y=0;y<sk[x];y++)
        {
            printf("og_column12[y][x] = %6.3f \n",og_column12[y][x]);
        }
    }    
*/    
    
// DOES THE MATH
    
    x=0,y=0;
    for(x=0;x<k;x++)
    {
        for(y=0;y<sk[x];y++)
        {
            sum[x] += og_column1[y][x];
        }
        printf("Condition %d sum of ranks = %6.3f \n",x+1,sum[x]);
        square[x] = (sum[x]*sum[x]); mean[x] = (square[x]/sk[x]); sum_mean += mean[x];
    }
    
    a = n*(n+1); a = 12/a; b = 3*(n+1); h = (a*sum_mean)-b; 
    
    if(ties[0]>0)
    {
        for(i=0;i<z;i++)
        {
            sum_t += ties[i];
        }
        n = (n*n)-n; c = sum_t/n; c = 1-c; h = h/c;
    }
    
// PRINTS OUTPUT AND ENDS PROGRAM
    
    printf("h = %6.3f \n",h);
    
    return(0);
}