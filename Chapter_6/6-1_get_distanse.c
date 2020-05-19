
/* The program uses structures to calculate a distanse from (0, 0)
   to (x, y). */

#include <stdio.h>
#include <math.h>   /* compile with -lm */

/* this structure represents a point on the plane - x and y */
struct point {
    int x;
    int y;
};

double get_distanse(struct point);

int main(void) {
    struct point pt = {3, 4};
    printf("%.2f\n", get_distanse(pt));
    return 0;
}

/* get_distanse: get point and return distanse from (0, 0) to
   (pt.x, pt.y) */
double get_distanse(struct point pt) {
    return sqrt((double) pt.x * pt.x + (double) pt.y * pt.y);
}
