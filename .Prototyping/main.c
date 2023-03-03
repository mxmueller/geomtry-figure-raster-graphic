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

void bresenham_line(int x0, int y0, int x1, int y1) {
    const int dimx = 800;
    FILE *fp = fopen("../circle_test.ppm", "r+b"); /* r+b - read and write in binary mode */
    int dx = abs(x1 - x0), dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    while (1) {
        fseek(fp, (long)(y0*dimx + x0)*3, SEEK_SET); // Move file pointer to position of pixel (x0, y0)
        fputc(0, fp);
        fputc(0, fp);
        fputc(255, fp);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
    }
    fclose(fp);
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
    const int dimx = 800;
    FILE *fp = fopen("../circle_test.ppm", "r+b"); /* r+b - read and write in binary mode */
    fseek(fp, (long)(y*dimx + x)*3, SEEK_SET); // Move file pointer to position of pixel (x, y)
    fputc(255, fp);
    fputc(0, fp);
    fputc(0, fp);
    fclose(fp);
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

void draw_lines(Point* points, int num_points) {
    for (int i = 0; i < num_points; i++) {
        for (int j = i + 1; j < num_points; j++) {
            bresenham_line(points[i].x, points[i].y, points[j].x, points[j].y);
        }
    }
}

int main(void) {
    int N = 23;
    ini_ppm();
    Point* points = get_points_on_circle(400, 400, 300, N);
    draw_lines(points, N);
    draw_circle(400, 400, 300);
    free(points);
    return 0;
}

