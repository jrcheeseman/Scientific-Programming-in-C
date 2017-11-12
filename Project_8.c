// Project 8 - Jake Cheeseman - 4/11/15

// Instructions: "Write a graphics program using OpenGL that draws selected portions of the Mandelbrot set (a "fractal") into a graphics window. Alternatively you can choose to draw Julia sets if you prefer."

#include <glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Prints description in case a gflw function fails */
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

/* Allows window to be closed by pressing escape */
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

/* Allows region to be selected with cursor position */
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    glfwGetCursorPos(window, &xpos, &ypos);
}

/* Allows left-click to trigger region selection */
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        
    }
}

int main()
{
    //double xpos, ypos;
    double red=0.0, green=0.0, blue=0.0;
    double a_corner, b_corner, side, gap=side/1000;
    double a, b, x, y, z;
    int n, j, k, f1, f2, f3;
    
    float ratio;
    int width, height;
    //int state;
    
    printf("\nInput a value between -2.0 and 0.5: \n");
    scanf("%lf",&a_corner); a = a_corner;
    
    printf("\nInput a value between -1.25 and 1.25: \n");
    scanf("%lf",&b_corner); b = b_corner;
    
    printf("\nInput a positive value less than or equal to 2.5 \n");
    scanf("%lf",&side); gap=side/1000;
    
    GLFWwindow* window;
    
    GLFWcursor* cursor;
    
    glfwSetErrorCallback(error_callback);
    
    /* Initializes the library */
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }
    
    /* Creates a window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Mandelzoom", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    /* Makes the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    /* Initializes callback to receive keyboard input */
    glfwSetKeyCallback(window, key_callback);
    
    /* Creates a cursor */
    cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
    if (!cursor)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    /* Initializes callbacks to receive mouse cursor input */
    glfwSetCursor(window, cursor);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    
    /* Loops until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Need to get cursor position, convert to ortho scale, replace corner values... 
        state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if (state == GLFW_PRESS)
        {
            glfwGetCursorPos(window, &xpos, &ypos);
            a_corner=xpos/gap; b_corner=ypos/gap;
        }*/
        
        /* Checks for input */
        a=a_corner; b=b_corner; gap=side/1000;
        
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        
        /* Renders object */
        glClearColor(0.0, 1.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(a_corner, a_corner+side, b_corner, b_corner+side, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        
        glPointSize(1);
        glBegin(GL_POINTS);
        {
            for(j=0;j<1000;j++)
            {
                a = a+gap;
                b = b_corner;
                
                for(k=0;k<1000;k++)
                {
                    b = b+gap;
                    x = 0;
                    y = 0;
                    n = 0;
                    
                    while(n<1000 && ((x*x)+(y*y))<10000)
                    {
                        z = ((x*x)-(y*y))+a;
                        y = (2*(x*y))+b;
                        x = z;
                        n = n+1;
                    }
                    
                    if(n<=1000) 
                    {
                        
                        /* Assigns rgb values to non mandelbrot set */
                        f1=n; f2=f1+f1; f3=f1+f2;
                        
                        red=f1*0.001;
                        if(f1<100)
                            red=f1*0.01;
                        if(f1<10)
                            red=f1*0.1;
                        
                        if(f2>1000)
                            green=f2*0.0001;
                        if(f2<1000)
                            green=f2*0.001;
                        if(f2<100)
                            green=f2*0.01;
                        if(f2<10)
                            green=f2*0.1;
                        
                        if(f3>1000)
                            blue=f3*0.0001;
                        if(f3<1000)
                            blue=f3*0.001;
                        if(f3<100)
                            blue=f3*0.01;
                        if(f3<10)
                            blue=f3*0.1;
                        
                        if (n >= 1000) /* Mandelbrot set = black */
                        {
                            red = 0;
                            green = 0;
                            blue = 0;
                        }
                        
                        glColor3d(red, green, blue);
                        glVertex2d(a, b);
                    }
                }
            }
        }
        glEnd();
        
        /* Swaps front and back buffers */
        glfwSwapInterval(1);
        glfwSwapBuffers(window);
        
        /* Puts call thread to sleep until event occurs */
        glfwWaitEvents();
        
    }
    
    glfwDestroyWindow(window);
    
    glfwTerminate();
    
    exit(EXIT_SUCCESS);
    
}