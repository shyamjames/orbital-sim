#include <stdio.h>
#include <math.h>

struct Body{
    char name[50];
    double mass;
    double x,y; // position from the sun (i am visualising sun as the center of the mass of sun, which is a point)
    double vx,vy; // velocity according to the axes
};

double gravitational_force(struct Body a, struct Body b){
    double G = 6.674e-11;
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double distance = sqrt(dx*dx + dy*dy);
    return G * (a.mass * b.mass)/(distance*distance);
}

int main(){
    struct Body sun = {"Sun",1.989e30,0,0,0,0};
    struct Body earth = {"Earth", 5.972e24, 0, 1.496e11, 29780, 0};
    printf("%s\nMass: %.3e\nPosition: (%.3e,%.3e)\n", earth.name, earth.mass, earth.x, earth.y);
    // %.3e used to print floating point number in scientific notation.
    double force = gravitational_force(earth,sun);
    printf("Gravitational Force: %.3e N\n",force);
    return 0;
}