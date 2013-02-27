//newt.c

#include <stdio.h>
#include <stdlib.h> 
#include <complex.h>
#include <float.h>
#include <math.h> 

complex f(complex z); 


const int WIDTH = 2048, HEIGHT = 2048; // actual image size in pixels 

// we have to map WIDTH and HEIGHT to a nomralized domain 
const double SCALED_X_MAX = 1.0;
const double SCALED_X_MIN = -1.0;
const double SCALED_Y_MAX = 1.0;
const double SCALED_Y_MIN = -1.0;



const int MAX_ITERATIONS = 200;
const double EPSILON = 1e-3; // max error

int main(int argc, char **argv) { 
    const double SCALED_WIDTH = SCALED_X_MAX - SCALED_X_MIN ;
    const double SCALED_HEIGHT = SCALED_Y_MAX - SCALED_Y_MIN ; 

    FILE * image = fopen("newton.ppm", "w") ; 
    // PPM file header //
    fprintf(image, "P3\n"); // color pixmap, ASCII
    fprintf(image, "%d %d\n" , WIDTH , HEIGHT ) ; 
    fprintf(image, "%d\n", 255) ; // 255 = max value for color
    // end PPM file header // 

    for ( int y = 0 ; y < HEIGHT ; ++y) { // for every row of pixels 
        double zy = y * (SCALED_HEIGHT)/(HEIGHT-1) + SCALED_Y_MIN; //scaled point at this y value 
        for ( int x = 0 ; x < WIDTH ; ++x ) {  // for every pixel in that row
            double zx = x * (SCALED_WIDTH)/(WIDTH-1) + SCALED_X_MIN; //scaled point at this x value 
            complex z = zx + zy*I; 
            int iteration = 0;
            while(iteration < MAX_ITERATIONS ) { 
                //numerical derivative of f'(z) 
                complex h=sqrt(DBL_EPSILON) + sqrt(DBL_EPSILON)*I; // base h on our floating point percison 
                complex volatile zph = z + h; // volatile to prevent an optimizing complier from removing the following calculations at complile time 
                complex dz = zph - z; 
                complex slope = (f(zph) - f(z))/dz; // f'(z) 

                complex z0 = z - f(z)/slope     ;       // newton iteration 
                if ( cabs(z0 - z) < EPSILON){ // when we get close enough break, base the color on the number of iterations it took. 
                    break; 
                }
                z = z0;
                iteration++;
            }
            fprintf(image,"%3d %3d %3d ", iteration % 4 * 64 , 
                                          iteration % 8 * 32 , 
                                          iteration % 16 * 16);
        }
       fprintf(image, "\n") ; 
    }
    fclose(image) ; 

    exit(0); 

}
complex f(complex z ) { 
    return cpow(z,4)-cpow(z,3)-1.0 ;
}
