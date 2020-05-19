
/* The program uses structures to make points on the plane and 
   calculate a distanse between them. */

#include <stdio.h>
#include <math.h>   /* compile with -lm */

/* this structure represents a point on the plane - x and y */
struct point {
    int x;
    int y;
};

double get_distanse(struct point);
struct point make_point(int, int);
struct point make_vector(struct point, struct point);

int main(void) {
    struct point pt1, pt2, vector;
    
    pt1 = make_point(2, 8);                 /* pt1 == (2, 8) */
    pt2 = make_point(6, 9);                 /* pt2 == (6, 9) */
    vector = make_vector(pt1, pt2);         /* must be (4, 1) */
    printf("%.2f\n", get_distanse(vector)); /* must be 4.12 */
    return 0;
}

/* get_distanse: get a point and return a length of vector */
double get_distanse(struct point pt) {
    return sqrt((double) pt.x * pt.x + (double) pt.y * pt.y);
}

/* make_point: get x and y; return a point on the plane */
struct point make_point(int x, int y) {
    struct point pt;
    
    pt.x = x;
    pt.y = y; 
    return pt;
}

/* make_vector: get points on the plane and return a vector */
struct point make_vector(struct point pt1, struct point pt2) {
    pt1.x = pt2.x - pt1.x;
    pt1.y = pt2.y - pt1.y;
    return pt1;
}
