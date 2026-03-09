#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
class point{
public:
    double id;
    double x;
    double y;

    point(){id=0;x=0;y=0;}
    point(double i,double a,double b){
        id=i;
        x=a;
        y=b;
    }
};
class line{
    public:
    double id,indexp1,indexp2;
    line(){indexp1=0;indexp2=0;}
    line(double i,double n,double n1){
        indexp1=n;
        indexp2=n1;
        id=i;
    }
};
class InputHandler{
    friend point;
    friend line;
    std::fstream Nodes;
    public:
    void SetInputDocument(std::string Filename){
        Nodes.open(Filename,std::ios::in);
    }
    void GetInputByDocument(std::vector<point>*points,std::vector<line>*lines){
        bool node=false,elements=false;
        std::vector<double> input;
        std::string s="";
        while(getline(Nodes,s)){
        if(s[0]=='*'){
            s.erase(0,1);

            if(s=="NODE"){
                node=true;
                elements=false;
            }else{
                node=false;
                elements=true;
            }

        }else{

            std::stringstream ss(s);
            double value;

            while(ss>>value){
                input.push_back(value);
            }

            if(node){

                points->push_back(point(
                    input[0],
                    input[1],
                    -input[2]
                ));

            }else{

                double id=input.front();
                input.erase(input.begin());

                for(int i=0;i<input.size()-1;i++){
                    lines->push_back(line(id,input[i],input[i+1]));
                }
                    lines->push_back(line(id,input.front(),input.back()));
            }

            input.clear();
        }
    }

     }
};


int main(){

    std::vector<double> input;
    InputHandler UserInput;
    std::vector<point> points;
    std::vector<line> lines;
    UserInput.SetInputDocument("Nodes.txt");
    UserInput.GetInputByDocument(&points,&lines);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Mesh viewer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);

    bool quit=false;
    SDL_Event event;

    float zoom=30.0f;
    float camX=0;
    float camY=0;
    float cx = 320;
    float cy = 240;

    while(!quit){

        while(SDL_PollEvent(&event)){

            if(event.type==SDL_QUIT)
                quit=true;

            if(event.type==SDL_KEYDOWN){

                if(event.key.keysym.sym==SDLK_q)
                    zoom*=1.1f;

                if(event.key.keysym.sym==SDLK_e)
                    zoom*=0.9f;

                if(event.key.keysym.sym==SDLK_w)
                    camY-=10/zoom;

                if(event.key.keysym.sym==SDLK_s)
                    camY+=10/zoom;

                if(event.key.keysym.sym==SDLK_a)
                    camX-=10/zoom;

                if(event.key.keysym.sym==SDLK_d)
                    camX+=10/zoom;
                if(event.key.keysym.sym==SDLK_p){
                for(auto it:lines){
                    std::cout<<it.indexp1<< " "<<it.indexp2<<std::endl;
                    }
                    std::cout<<zoom<<std::endl;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer,242,242,242,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,0,0,0,255);

        for(auto it:points){

            float x=(it.x-camX)*zoom+cx;
            float y=(it.y-camY)*zoom+cy;

            SDL_RenderDrawPointF(renderer,x,y);
        }

        for(auto it:lines){

            float x1=(points[(int)it.indexp1-1].x-camX)*zoom+cx;
            float y1=(points[(int)it.indexp1-1].y-camY)*zoom+cy;

            float x2=(points[(int)it.indexp2-1].x-camX)*zoom+cx;
            float y2=(points[(int)it.indexp2-1].y-camY)*zoom+cy;

            SDL_RenderDrawLineF(renderer,x1,y1,x2,y2);
        }
        
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 120);
    SDL_RenderDrawLineF(renderer,(0 - camX) * zoom + cx, (-100000 - camY) * zoom + cy, (0 - camX) * zoom + cx,(100000 - camY) * zoom + cy);
    SDL_RenderDrawLineF(renderer,(-100000 - camX) * zoom + cx,(0 - camY) * zoom + cy,(100000 - camX) * zoom + cx,(0 - camY) * zoom + cy);    
    SDL_RenderPresent(renderer); 
}

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}