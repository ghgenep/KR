
/* The program uses structures to make points on the plane and 
   restangles(screen); say, whether a point is on screen. */

#include <stdio.h>
#include <math.h>   /* compile with -lm */

/* this structure represents a point on the plane - x and y */
struct point {
    int x;
    int y;
};

/* this structure represents a rectangle - two points */
struct rect {
    struct point pt1;
    struct point pt2;
};

struct point make_point(int, int);
struct rect make_screen(struct point pt1, struct point pt2);
int pt_in_rect(struct rect r, struct point pt);
struct rect canon_rect(struct rect r);

int main(void) {
    struct point pt1, pt2, pt3;
    struct rect screen;
    
    pt1 = make_point(8, 8);                 /* pt1 == (8, 8) */
    pt2 = make_point(1, 1);                 /* pt2 == (1, 1) */
    screen = canon_rect(make_screen(pt1, pt2));
    
    pt3 = make_point(3, 3);
    if (pt_in_rect(screen, pt3))
        printf("(%d, %d) is in screen\n", pt3.x, pt3.y);
    
    pt3 = make_point(8, 8);
    if (pt_in_rect(screen, pt3))
        ;   /* don't do */
    else
        printf("(%d, %d) isn't in screen\n", pt3.x, pt3.y);
    
    return 0;
}

/* make_point: get x and y; return a point on the plane */
struct point make_point(int x, int y) {
    struct point pt;
    
    pt.x = x;
    pt.y = y; 
    return pt;
}

/* make_screen: get two points and return rectangle(screen) */
struct rect make_screen(struct point pt1, struct point pt2) {
    struct rect screen;
    
    screen.pt1 = pt1;
    screen.pt2 = pt2;
    return screen;
}

/* pt_in_rect: return 0, if a point pt is out of rectangle */
int pt_in_rect(struct rect r, struct point pt) {
    return (pt.x >= r.pt1.x && pt.x < r.pt2.x &&
            pt.y >= r.pt1.y && pt.y < r.pt2.y);
}

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

/* canon_rect: return a rectangle with points in canonical form */
struct rect canon_rect(struct rect r) {
    struct rect temp;
    
    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);
    return temp;
}
