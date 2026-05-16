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

void update(struct Body *b, double fx, double fy, double dt){
    double ax = fx/b->mass; // acceleration = force/mass (f=ma)
    double ay = fy/b->mass; // so calculation acceletation towards both directions
    b->vx += ax*dt; // new velocity = acceleration * time
    b->vy += ay*dt;
    b->x += b->vx*dt; // new position = updated acceleration * time
    b->y += b->vy*dt;
}

int main(){
    struct Body sun = {"Sun",1.989e30,0,0,0,0};
    struct Body earth = {"Earth", 5.972e24, 0, 1.496e11, 29780, 0};
    
    double dt = 3600; // one hour

    for(int i=0;i<24;i++){
        double dx = sun.x - earth.x;
        double dy = sun.y  - earth.y;
        double dist =  sqrt(dx*dx + dy*dy);
        double force = gravitational_force(earth,sun);
        double fx = force*(dx/dist);
        double fy = force*(dy/dist);
        update(&earth,fx,fy,dt);
        printf("Hour %2d: position: (%.3e, %.3e)\n",i+1,earth.x,earth.y);
    }
    return 0;
}