#include <stdio.h>

struct Body{
    char name[50];
    double mass;
    double x,y; // position from the sun (i am visualising sun as the center of the mass of sun, which is a point)
    double vx,vy; // velocity according to the axes
};

int main(){
    struct Body earth = {"Earth", 5.972e24, 0, 1.496e11, 29780, 0};
    printf("%s\nMass: %.3e\nPosition: (%.3e,%.3e)\n", earth.name, earth.mass, earth.x, earth.y);
    // %.3e used to print floating point number in scientific notation.
    return 0;
}