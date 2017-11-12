// Project 9 - Jake Cheeseman - 5/1/15

// Instructions: "Write a graphics OpenGL program that draws a random-dot stereogram of a curved surface portrayed as an anaglyph (i.e., can be viewed with red/green glasses)."

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <glfw3.h>

// ran2 constants
#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

long seed;

// ran2 code

// Long period (> 2 x 10^18) random number generator of L'Ecuyer with Bays-Durham shuffle and added
// safeguards. Returns a uniform random deviate between 0.0 and 1.0 (exclusive of the endpoint values). 
// Call with idum a negative integer to initialize; thereafter, do not alter idum between successive deviates 
// in a sequence. RNMX should approximate the largest floating value that is less than 1. 
float ran2(long *idum)
{
    int j;
    long k;
    static long idum2=123456789;
    static long iy=0;
    static long iv[NTAB];
    float temp;
    
    if (*idum <= 0) {                       // Initialize
        if (-(*idum) < 1) *idum=1;          // Be sure to prevent idum = 0
        else *idum = -(*idum);
        idum2=(*idum);
        for (j=NTAB+7;j>=0;j--) {           // Load the shuffle table (after 8 warm-ups)
            k=(*idum)/IQ1;
            *idum=IA1*(*idum-k*IQ1)-k*IR1;
            if (*idum < 0) *idum += IM1;
            if (j < NTAB) iv[j] = *idum;
        }
        iy=iv[0];
    }
    k=(*idum)/IQ1;                          // Start here when not initializing
    *idum=IA1*(*idum-k*IQ1)-k*IR1;          // Compute idum=(IA1*idum) % IM1 without overflows 
    if (*idum < 0) *idum += IM1;                
    k=idum2/IQ2;
    idum2=IA2*(idum2-k*IQ2)-k*IR2;          // Compute idum2=(IA2*idum) % IM2 likewise.
    if (idum2 < 0) idum2 += IM2;
    j=iy/NDIV;                              // Will be in the range 0..NTAB-1.
    iy=iv[j]-idum2;                         // Idum is shuffled; idum & idum2 combined to generate output
    iv[j] = *idum;
    if (iy < 1) iy += IMM1;
    if ((temp=AM*iy) > RNMX) return RNMX;   // Because users don't expect endpoint values
    else return temp;
}

// Prints description in case a gflw function fails
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

// Allows window to be closed by pressing escape
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main()
{
    // variables
    int i;
    
    float s;
    float left_x[5000], right_x[5000], binoc_y[5000];
    //float disparities[5000], total, mean;
    float frequency=1.5, amplitude=0.15;
    
    time_t ct;
    struct tm *q;
    extern struct tm *localtime();
    
    GLFWwindow *window;
    
    // ran2 seed
    ct = time(NULL);
    q = localtime(&ct);
    
    seed = (q->tm_sec)*(q->tm_min)*(q->tm_hour);
    seed = seed * (-1);
    s = ran2(&seed);
    
    // Randomly generate x and y coordinates for left eye
    for(i=0;i<5000;i++)
    {
        left_x[i] = 25*ran2(&seed);
    }
    for(i=0;i<5000;i++)
    {
        binoc_y[i] = 15*ran2(&seed);
    }
    for(i=0;i<5000;i++)
    {
        right_x[i] = left_x[i]+(sin(frequency*binoc_y[i])*amplitude);
    }
    /*
    for(i=0;i<5000;i++)
    {
        disparities[i] = right_x[i] - left_x[i];
        total += disparities[i];
    }
    
    mean = (total / 5000); 
    
    printf("frequency = %6.3f\n",frequency);
    printf("amplitude = %6.3f\n",amplitude);
    printf("disparity = %6.3f\n",mean);
    */    
    glfwSetErrorCallback(error_callback);
    
    // Initializes the library
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }
    
    // Creates a window and its OpenGL context
    window = glfwCreateWindow(1136, 682, "Random Dot Stereogram", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // Makes the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    // Initializes callback to receive keyboard input
    glfwSetKeyCallback(window, key_callback);
    
    // Loops until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        
        // Renders object
        glDrawBuffer(GL_FRONT_AND_BACK);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 25, 0, 15, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        
        //glPointSize(100.0);
        glPointSize(2.0);
        glBegin(GL_POINTS);
        {
            
            for(i=0;i<5000;i++)
            {
                glColor3f(1.0, 0.0, 0.0); // red
                glVertex2f(left_x[i], binoc_y[i]); 
            }
            
            //glColor3f(1.0, 0.0, 0.0); // red
            //glVertex2f(12.0, 7.5);
        
        }
        glEnd();
        
        glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
        
        //glPointSize(100.0);
        glPointSize(2.0);
        glBegin(GL_POINTS);
        {
            
            for(i=0;i<5000;i++)
            {
                glColor3f(0.0, 1.0, 0.0); // green
                glVertex2f(right_x[i], binoc_y[i]);
            }
            
            //glColor3f(0.0, 1.0, 0.0); // green
            //glVertex2f(13.0, 7.5);
            
        }
        glEnd();
        
        // Swaps front and back buffers
        glfwSwapInterval(1);
        glfwSwapBuffers(window);
        
        // Puts call thread to sleep until event occurs
        glfwWaitEvents();
        
    }
    
    glfwDestroyWindow(window);
    
    glfwTerminate();
    
    exit(EXIT_SUCCESS);
     
    //return(0);
}