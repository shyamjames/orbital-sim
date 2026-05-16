#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define SCALE 5e9 // one pixel -> 5 billion meters
#define WIDTH 800
#define HEIGHT 800
#define CENTER_X 400
#define CENTER_Y 400
#define TRAIL_LENGTH 2000


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

int screen_x(double x) { return CENTER_X + (int)(x / SCALE); }
int screen_y(double y) { return CENTER_Y - (int)(y / SCALE); }

void draw_circle(SDL_Renderer *r, int cx, int cy, int radius){
    for(int dy=-radius;dy<=radius;dy++){
        for(int dx=-radius;dx<=radius;dx++){
            if(dx*dx+dy*dy <= radius*radius){
                SDL_RenderDrawPoint(r,cx+dx,cy+dy);
            }
        }
    }
}

typedef struct{
    int x,y;
} Point;

Point trail[TRAIL_LENGTH];
int trail_index = 0;
int trail_count = 0;

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Orbital Sim",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    struct Body sun = {"Sun",1.989e30,0,0,0,0};
    struct Body earth = {"Earth", 5.972e24, 0, 1.496e11, 29780, 0};

    double dt = 3600;
    int running = 1;
    int speed = 1;
    SDL_Event event;

    while(running){
        // quit
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT) running = 0;
        }

        //physics
        double dx = sun.x - earth.x; 
        double dy = sun.y  - earth.y;
        double dist =  sqrt(dx*dx + dy*dy); // actual distance
        double force = gravitational_force(earth,sun);
        double fx = force*(dx/dist); // force in x dir
        double fy = force*(dy/dist); // force in y dir
        update(&earth,fx,fy,dt+speed);

        trail[trail_index] = (Point){screen_x(earth.x),screen_y(earth.y)};
        trail_index = (trail_index+1)%TRAIL_LENGTH;
        if(trail_count < TRAIL_LENGTH) trail_count++;


        //draw
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        //draw grid
        SDL_SetRenderDrawColor(renderer,30,30,30,255);
        for(int i=0;i<=WIDTH;i+=WIDTH/10)
            SDL_RenderDrawLine(renderer,i,0,i,HEIGHT);
        for(int j=0;j<=HEIGHT;j+=HEIGHT/10)
            SDL_RenderDrawLine(renderer,0,j,WIDTH,j);

        //draw sun
        SDL_SetRenderDrawColor(renderer,255,255,0,255);
        draw_circle(renderer, screen_x(sun.x),screen_y(sun.y),10);

        //draw earth trail
        SDL_SetRenderDrawColor(renderer,0,50,150,255);
        for(int i=0;i<trail_count;i++){
            SDL_RenderDrawPoint(renderer, trail[i].x,trail[i].y);
        }

        //draw earth
        SDL_SetRenderDrawColor(renderer,0,10,255,255);
        draw_circle(renderer, screen_x(earth.x),screen_y(earth.y),4);

        SDL_RenderPresent(renderer);
        SDL_Delay(16); //~60fps
        
        if(event.type == SDL_KEYDOWN){
            if(event.key.keysym.sym==SDLK_UP){
                speed++;
            }else if(event.key.keysym.sym==SDLK_DOWN){
                speed--;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}