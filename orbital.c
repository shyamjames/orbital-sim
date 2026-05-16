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
    struct Body moon = {"Moon", 7.342e22, earth.x+3.944e8, earth.y, earth.vx, earth.vy+1022};

    double dt = 1800; // time in seconds

    for(int i=0;i<8760;i++){
        //force on earth from sun
        double dx = sun.x - earth.x; 
        double dy = sun.y  - earth.y;
        double dist =  sqrt(dx*dx + dy*dy); // actual distance
        double force = gravitational_force(earth,sun);
        double fx = force*(dx/dist); // force in x dir
        double fy = force*(dy/dist); // force in y dir
        update(&earth,fx,fy,dt);

        //force on moon from sun
        double mdx = sun.x - moon.x;
        double mdy = sun.y - moon.y;
        double mdist_s = sqrt(mdx*mdx + mdy*mdy);
        double mforce_s = gravitational_force(moon,sun);
        double mfx_s = force*(mdx/mdist_s);
        double mfy_s = force*(mdy/mdist_s);

        //force on moon from earth
        double mdx_e = earth.x - moon.x;
        double mdy_e = earth.y - moon.y;
        double mdist_e = sqrt(mdx_e*mdx_e + mdy_e*mdy_e);
        double mforce_e = gravitational_force(moon,earth);
        double mfx_e = force*(mdx_e/mdist_e);
        double mfy_e = force*(mdy_e/mdist_e);

        update(&moon,mfx_e+mfx_s,mfy_e+mfy_s,dt);
        
        if(i%720==0){
            printf("Earth: Hour %2d: position: (%.3e, %.3e)\n",i+1,earth.x,earth.y);
            printf("Moon: Hour %2d: position: (%.3e, %.3e)\n",i+1,moon.x,moon.y);
        }
    }
    return 0;
}