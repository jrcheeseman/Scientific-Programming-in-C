// Project 10 - Jake Cheeseman - 5/2/15

// Instructions: "Write a graphics OpenGL program that depicts a 3-D object using the kinetic depth effect."

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

// ran2 random number generator; from Press et al. (1992), Numerical Recipies in C, p. 282
float ran2(long *idum)
{
//  Long period (> 2 x 10^18) random number generator of L'Ecuyer with Bays-Durham shuffle and added safeguards. Returns a uniform random deviate between 0.0 and 1.0 (exclusive of the endpoint values). Call with idum a negative integer to initialize; thereafter, do not alter idum between successive deviates in a sequence. RNMX should approximate the largest floating value that is less than 1.
    
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
    
    float seedling;
    float u, v;
    float x[5000], y[5000], z[5000];
    float f1, f2, f3;
    
    GLFWwindow *window;
    
    time_t ct;
    struct tm *q;
    extern struct tm *localtime();
    
    // ran2 seed
    ct = time(NULL);
    q = localtime(&ct);
    
    seed = (q->tm_sec)*(q->tm_min)*(q->tm_hour);
    seed = seed * (-1);
    seedling = ran2(&seed);
    
    // Generates random x y z coordinates within a sphere
    for(i=0;i<5000;i++)
    {
        u = (ran2(&seed)*2.0*M_PI);
        v = (ran2(&seed)*2.0*M_PI);
        
        x[i] = (7.35*(cos(u)*sin(v)));
        y[i] = (7.35*(sin(u)*sin(v)));
        z[i] = (7.35*(cos(v)));
        
        //x[i] = (15*(cos(u)*sin(v)));
        //y[i] = (15*(sin(u)*sin(v)));
        //z[i] = (15*(cos(v)));
    }
    
    glfwSetErrorCallback(error_callback);
    
    // Initializes the library
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }
    
    // Creates a window and its OpenGL context
    window = glfwCreateWindow(1136, 682, "Random Dot Stereogram", NULL, NULL);
    //window = glfwCreateWindow(2655, 1501, "Random Dot Stereogram", NULL, NULL);
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
    
    glPointSize(1.7);
    //glPointSize(2);
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-12.5, 12.5, -7.5, 7.5, -12.5, 12.5);
    //glOrtho(-28, 30, -15.25, 17.75, -15.25, 17.75);
    glMatrixMode(GL_MODELVIEW);
    //glColor3f(1.0, 1.0, 1.0); 
    
    // Loops until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        //f1 = cos((float) glfwGetTime()) * ran2(&seed);
        //f2 = sqrt((float) glfwGetTime()) * ran2(&seed);
        //f3 = sqrt((float) glfwGetTime()) * ran2(&seed);
        
        //f1 = ((float) glfwGetTime()) * ran2(&seed);
        //f2 = ((float) glfwGetTime()) * ran2(&seed);
        //f3 = ((float) glfwGetTime()) * ran2(&seed);
        
        // Renders object
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(f1, f2, f3);
        glColor3f(1.0, 1.0, 1.0);
        //glRotatef((float) glfwGetTime() * 1.0, cos(M_PI), sin(M_PI), M_PI); /* infinity */
        glRotatef((float) glfwGetTime() * 1.0, 0.0, 0.0, 1.0); /* pin wheel spiral */
        //glRotatef((float) glfwGetTime() * 1.0, 0.0, 1.0, 0.0); /* horizontal spin */
        glBegin(GL_POINTS);
        {
            for(i=0;i<5000;i++)
            {
                glVertex3f(x[i], y[i], z[i]);
            }
        }
        glEnd();
        
        // Swaps front and back buffers
        glfwSwapBuffers(window);
        
        // Puts call thread to sleep until event occurs
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    
    glfwTerminate();
    
    exit(EXIT_SUCCESS);
    
}
