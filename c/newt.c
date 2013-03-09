//newt.c

#include <stdio.h>
#include <stdlib.h> 
#include <complex.h>
#include <float.h>
#include <math.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/ioctl.h> 

#include "expression.h" 
#include "expression_parse.tab.h" 

expression_list *expressions; 
extern int yyparse(); 
extern FILE *yyin; 
//complex f(complex z); 

void drawFractal(char *filename , expression_t * expr) ; 

const int WIDTH = 10000, HEIGHT = 10000; // actual image size in pixels 

// we have to map WIDTH and HEIGHT to a nomralized domain 
const double SCALED_X_MAX = 1.0;
const double SCALED_X_MIN = -1.0;
const double SCALED_Y_MAX = 1.0;
const double SCALED_Y_MIN = -1.0;
double SCALED_WIDTH; 
double SCALED_HEIGHT; 

const int MAX_ITERATIONS = 200;
const double EPSILON = 1e-3; // max error

struct winsize winsize;
static void loadBar( int x , int n , int r, int w ) ; 

int main(int argc, char **argv) { 
    SCALED_WIDTH = SCALED_X_MAX - SCALED_X_MIN ;
    SCALED_HEIGHT = SCALED_Y_MAX - SCALED_Y_MIN ; 

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &winsize);

    yyin = fopen("functions.txt", "r" ) ; 
    expressions = new_expression_list(); 
    yyparse(); 
    expression_t *expression =  expression_list_pop(expressions);

    int filenum= 0 ; 
    while( expression  != NULL ) { 
        char *template = strdup("XXXXXX") ; 
        template = mktemp(template); 
        char *filename; 
        asprintf(&filename,"img/fractal-%s.ppm", template) ; 
        puts(filename) ; 
        puts("" );
        drawFractal(filename, expression) ;
        free((void*) filename) ;
        free_expression(expression); 

        expression = expression_list_pop(expressions) ; 
    }
    free_expression_list(expressions ) ;
    exit(0); 

}

void drawFractal(char *filename, expression_t *expr) { 
    FILE *image = fopen(filename, "w") ; 
    fprintf(image, "P3\n"); // color pixmap, ASCII
    fprintf(image, "%d %d\n" , WIDTH , HEIGHT ) ; 
    fprintf(image, "%d\n", 255) ; // 255 = max value for color
    fprintf(image, "#") ; 
    print_expression(expr,image) ; 
    fprintf(image, "\n" ) ; 
    // end PPM file header // 

    for ( int y = 0 ; y < HEIGHT ; ++y) { // for every row of pixels 
        double zy = y * (SCALED_HEIGHT)/(HEIGHT-1) + SCALED_Y_MIN; //scaled point at this y value 
        loadBar(y,WIDTH,100,winsize.ws_col ) ; 
        for ( int x = 0 ; x < WIDTH ; ++x ) {  // for every pixel in that row
            double zx = x * (SCALED_WIDTH)/(WIDTH-1) + SCALED_X_MIN; //scaled point at this x value 
            complex z = zx + zy*I; 
            int iteration = 0;
            while(iteration < MAX_ITERATIONS ) { 
                //numerical derivative of f'(z) 
                complex h=sqrt(DBL_EPSILON) + sqrt(DBL_EPSILON)*I; // base h on our floating point percison 
                complex volatile zph = z + h; // volatile to prevent an optimizing complier from removing the following calculations at complile time 
                complex dz = zph - z; 
                complex slope = (eval_expression(expr,zph) - eval_expression(expr,z))/dz; // f'(z) 

                complex z0 = z - eval_expression(expr,z)/slope     ;       // newton iteration 
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
} 

// x / n iters complete, r resolution, w width
static inline void loadBar(int x, int n, int r, int width)
{
     //based on : http://www.rosshemsley.co.uk/2011/02/creating-a-progress-bar-in-c-or-any-other-console-app/
     
    int w = (int)(0.9*width ); 
    //Only update r times.
    if ( x % (n/r) != 0 ) return;

    // Calculuate the ratio of complete-to-incomplete.
    float ratio = x/(float)n;
    int   c     = ratio * w;

    // Show the percentage complete.
    fprintf(stderr, "%3d%% [", (int)(ratio*100) );

    // Show the load bar.
    for (int x=0; x<c; x++)
    fprintf(stderr, "=");

    for (int x=c; x<w; x++)
    fprintf(stderr, " ");

    // ANSI Control codes to go back to the
    // previous line and clear it.
    //fprintf(stderr,"]\n\033[F\033[J");
    fprintf(stderr,"]\n\033[F");
    //fprintf(stderr,"]\r"); 
  //  fflush(stderr) ; 
}
