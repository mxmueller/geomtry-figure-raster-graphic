#include <stdio.h>
#include <math.h>

// TODO: make filename a global scope, but with timestamp or sth each time

int ini_ppm();
void set_pixel(int x, int y);

int main(void) {
    ini_ppm();

    int x1 = 100;
    int y1 = 100;
    int x2 = 700;
    int y2 = 700;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    // If slope is less than one
    if (dx > dy){
        // passing argument as 0 to plot(x,y)
        plotPixel(x1, y1, x2, y2, dx, dy, 0);
    }
        // if slope is greater than or equal to 1
    else {
        // passing argument as 1 to plot (y,x)
        plotPixel(y1, x1, y2, x2, dy, dx, 1);
    }

    return 0;
}

int ini_ppm() {
    const int dimx = 800, dimy = 800;
    int i, j;
    FILE *fp = fopen("../first.ppm", "wb"); /* b - binary mode */
    (void) fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
    (void) fclose(fp);
    return 0;
}

void set_pixel(int x, int y) {
    const int dimx = 800;
    FILE *fp = fopen("../first.ppm", "r+b"); /* r+b - read and write in binary mode */
    fseek(fp, (long)(y*dimx + x)*3, SEEK_SET); // Move file pointer to position of pixel (x, y)
    fputc(255, fp);
    fputc(0, fp);
    fputc(0, fp);
    fclose(fp);
}

void plotPixel(int x1, int y1, int x2, int y2, int dx, int dy, int decide){
    // pk is initial decision making parameter
    // Note:x1&y1,x2&y2, dx&dy values are interchanged
    // and passed in plotPixel function so
    // it can handle both cases when m>1 & m<1
    int pk = 2 * dy - dx;

    for (int i = 0; i <= dx; i++) {
        printf("%d,%d\n", x1, y1);

        set_pixel(x1, y1);

        // checking either to decrement or increment the
        // value if we have to plot from (0,100) to (100,0)
        if(x1<x2){
            x1 = x1 + 1;
        } else {
            x1 = x1 - 1;
        }

        if (pk < 0){
            // decision value will decide to plot
            // either  x1 or y1 in x's position
            if (decide == 0){
                // putpixel(x1, y1, RED);
                pk = pk + 2 * dy;
            } else {
                //(y1,x1) is passed in xt
                // putpixel(y1, x1, YELLOW);
                pk = pk + 2 * dy;
            }
        } else {
            if(y1<y2){
                y1 = y1 + 1;
            } else {
                y1 = y1 - 1;
            }

            if (decide == 0){
                // putpixel(x1, y1, RED)
            } else {
                //  putpixel(y1, x1, YELLOW);
            }
            pk = pk + 2 * dy - 2 * dx;
        }
    }
}



