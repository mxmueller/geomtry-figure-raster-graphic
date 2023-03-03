#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

Point* get_points_on_circle(int xc, int yc, int radius, int num_points) {
    Point* points = malloc(num_points * sizeof(Point));
    double angle_increment = 2 * M_PI / num_points;
    for (int i = 0; i < num_points; i++) {
        double angle = i * angle_increment;
        int x = (int)round(xc + radius * cos(angle));
        int y = (int)round(yc + radius * sin(angle));
        points[i].x = x;
        points[i].y = y;
    }
    return points;
}


// TODO: make filename a global scope, but with timestamp or sth each time

int ini_ppm();
void set_pixel(int x, int y);
void plot_line(int x1, int y1, int x2, int y2, int dx, int dy, int decide);
void draw_circle(int cx, int cy, int r);
void connect_points_on_circle(int xc, int yc, int radius, int num_points);

int main(void) {
    ini_ppm();
    draw_circle(400, 400, 200);

    int N = 9;

    //Point* points = get_points_on_circle(400, 400, 200, N);
    int xc = 400;
    int yc = 400;
    int radius = 200;

    connect_points_on_circle(xc, yc, radius, N);
    return 0;
}

int ini_ppm() {
    const int dimx = 800, dimy = 800;
    int i, j;
    FILE *fp = fopen("../circle_test.ppm", "wb"); /* b - binary mode */
    (void) fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
    (void) fclose(fp);
    return 0;
}

void set_pixel(int x, int y) {
    printf("[%d][%d]\n", x, y);
    const int dimx = 800;
    //printf("%d,%d\n", x, y);
    FILE *fp = fopen("../circle_test.ppm", "r+b"); /* r+b - read and write in binary mode */
    fseek(fp, (long)(y*dimx + x)*3, SEEK_SET); // Move file pointer to position of pixel (x, y)
    fputc(255, fp);
    fputc(0, fp);
    fputc(0, fp);
    fclose(fp);
}

void plot_line(int x1, int y1, int x2, int y2, int dx, int dy, int decide){
    // pk is initial decision making parameter
    // Note:x1&y1,x2&y2, dx&dy values are interchanged
    // and passed in plotPixel function so
    // it can handle both cases when m>1 & m<1
    int pk = 2 * dy - dx;

    for (int i = 0; i <= dx; i++) {
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

void draw_circle(int xc, int yc, int radius) {
    int x = 0, y = radius;
    int d = 1 - radius;
    set_pixel(xc + x, yc + y);
    set_pixel(xc - x, yc + y);
    set_pixel(xc + x, yc - y);
    set_pixel(xc - x, yc - y);
    set_pixel(xc + y, yc + x);
    set_pixel(xc - y, yc + x);
    set_pixel(xc + y, yc - x);
    set_pixel(xc - y, yc - x);
    while (x < y) {
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        set_pixel(xc + x, yc + y);
        set_pixel(xc - x, yc + y);
        set_pixel(xc + x, yc - y);
        set_pixel(xc - x, yc - y);
        set_pixel(xc + y, yc + x);
        set_pixel(xc - y, yc + x);
        set_pixel(xc + y, yc - x);
        set_pixel(xc - y, yc - x);
    }
}

void connect_points_on_circle(int xc, int yc, int radius, int num_points) {
    Point* points = get_points_on_circle(xc, yc, radius, num_points);

    for (int i = 0; i < num_points; i++) {
        for (int j = 0; j < num_points; j++) {
            plot_line(
                    points[i].x,
                    points[i].y,
                    points[j].x,
                    points[j].y,
                    abs(points[j].x - points[i].x),
                    abs(points[j].y - points[i].y),
                    points[i].x < points[j].x ? 0 : 1);
        }
        plot_line(points[num_points - 1].x,
                  points[num_points - 1].y,
                  points[0].x,
                  points[0].y,
                  abs(points[0].x - points[num_points - 1].x),
                  abs(points[0].y - points[num_points - 1].y),
                  points[num_points - 1].x < points[0].x ? 0 : 1);
    }
    // connect the last point to the first point to complete the circle
}


