// Project 4 - Jake Cheeseman - 2/19/15

// Instructions: "Write a program that when a given data file containing columns of x and y values, performs linear regression (using least squares minimization), determines the slope and y-intercept of the best-fitting regression line as well as the Pearson r correlation coefficient."

// 1. DECLARES HEADER FILES

#include <stdio.h>
#include <math.h>

int main()
{

// 2. DECLARES INTERNAL VARIABLES
    
    FILE *og_file;
    
    char og_name[25], c;
    
    int x, y, n, eof;
    
    double x_values[10000], y_values[10000]; 
    double sum_x, sum_y;
    double mean_x, mean_y;
    double x_dev[10000], y_dev[10000];
    double x_sqdev[10000], y_sqdev[10000];
    double sos_x, sos_y;
    double sd_x, sd_y;
    double dev_prod[10000], sum_dev_prod;
    double cov_xy, r_xy;
    double b, a;
    double input_x, pred_y;
    
// 3. OPENS DATA FILE FROM TERMINAL
    
    printf("Input data filename: \n");
    scanf("%s",og_name);
    og_file=fopen(og_name,"r");
    
    if(og_file==NULL)
    {
        printf("Error opening file! \n");
        return(1);
    }
    
// 4. SCANS DATA FROM FILE TO SEPARATE ARRAYS
    
    x=0,y=0,n=0;
    do
    {   
        eof = fscanf(og_file,"%lf%lf",&x_values[x],&y_values[y]); 
        x++,y++; /* could have used 'i' instead of two integers */
        n=(x-1); /* n = number of cases */
    }
    while(eof!=EOF);
    
    fclose(og_file);
    
// 5. CALCULATES MEANS FOR X & Y VALUES
    
    for(x=0,y=0;y<n;x++,y++)
    {
        sum_x += x_values[x];
        sum_y += y_values[y];
    }
    
    mean_x = sum_x / n;
    mean_y = sum_y / n;
    
// 6. CALCULATES MEAN DEVIATION VALUES
    
    for(x=0,y=0;y<n;x++,y++)
    {
        x_dev[x] = x_values[x] -= mean_x;
        y_dev[y] = y_values[y] -= mean_y;
    }
    
// 7. CALCULATES SQUARED MEAN DEVIATION VALUES
    
    for(x=0,y=0;y<n;x++,y++)
    {
        x_sqdev[x] = pow(x_values[x],2);
        y_sqdev[y] = pow(y_values[y],2);
    }
    
// 8. CALCULATES SUM OF SQUARED MEAN DEVIATION VALUES
    
    for(x=0,y=0;y<n;x++,y++)
    {
        sos_x += x_sqdev[x];
        sos_y += y_sqdev[y];
    }
    
// 9. CALCULATES STANDARD DEVIATION FOR X & Y VALUES
    
    sd_x = sqrt(sos_x/(n-1));
    sd_y = sqrt(sos_y/(n-1));
    
// 10. CALCULATES COVARIANCE, PEARSON R, REGRESSION EQUATION TERMS
    
    for(x=0,y=0;y<n;x++,y++)
    {
        dev_prod[x] = x_dev[x] *= y_dev[y]; /* products of deviation values */
    }
        
    for(x=0;x<n;x++)
    {
        sum_dev_prod += dev_prod[x]; /* sum of products */
    }
    
    cov_xy = sum_dev_prod / (n-1); /* covariance */
    
    r_xy = cov_xy / (sd_x * sd_y); /* correlation coefficient */
    
    b = r_xy * (sd_y / sd_x); /* slope */
    
    a = mean_y - (b * mean_x); /* y-int */
    
// 11. PRINTS COEFFICIENT AND EQUATION, PROMPTS FOR FUTHER CALCULATION
    
    printf("Here's what you need: \n");
    
    printf("r = %6.3f \n",r_xy); /* "6" = field width, ".3" = decimal precision */
    
    printf("Y' = %6.3f x + %6.3f \n",b,a);
    
    printf("Would you like to calculate the predicted y value for a given x value? [y/n] \n");
    scanf("%1s",&c);
    
// 12. CALCULATES PREDICTED Y UNTIL USER ENDS PROGRAM
    
    if(c=='y')
    {
        do
        {    
            input_x=0,pred_y=0;
            
            printf("Input x value: \n");
            scanf("%lf",&input_x);
            
            pred_y = (b * input_x) + a;
            printf("Predicted y value: %6.3f \n",pred_y);
            
            printf("Would you like to calculate another predicted y value? [y/n] \n");
            scanf("%1s",&c);
        }
        while(c!='n');
    }
    
    return(0);
    
}
