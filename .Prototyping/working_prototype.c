#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846

// TODO: #1 Function that accepts two points A(x1, y1) and B(x2, y2)
// TODO: #2 Find all the intermediate points required for drawing line AB

// Input  : A(0,0), B(4,4)
// Output : (0,0), (1,1), (2,2), (3,3), (4,4)

// Input  : A(0,0), B(4,2)
// Output : (0,0), (1,0), (2,1), (3,1), (4,2)

#define ROWS 20
#define COLS 20

char arr[ROWS][COLS];

void initialize_array();
void print_array();
void change_coordinate();
void plotPixel(int x1, int y1, int x2, int y2, int dx, int dy, int decide);

int main() {
    initialize_array();

    int x1 = 2;
    int y1 = 2;
    int x2 = 18;
    int y2 = 18;

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


    print_array();
    return 0;
}

// * From point A(x1, y1) to point B(x2, y2) *
int bresenhams_algorithm(int x1, int x2, int y1, int y2) {

}

void initialize_array() {
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1) {
                arr[i][j] = '+'; // ! Border could be implemented here
            } else {
                arr[i][j] = '+';
            }
        }
    }
}

void print_array() {
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }
}

void change_coordinate(int x1, int y1) {
    arr[x1][y1] = '#';
}

void plotPixel(int x1, int y1, int x2, int y2, int dx, int dy, int decide){
    // pk is initial decision making parameter
    // Note:x1&y1,x2&y2, dx&dy values are interchanged
    // and passed in plotPixel function so
    // it can handle both cases when m>1 & m<1
    int pk = 2 * dy - dx;

    for (int i = 0; i <= dx; i++) {
        printf("%d,%d\n", x1, y1);
        change_coordinate(x1,y1);


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
