//clang++  algoritmos_graficas.cpp -o algoritmos_graficas  -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 
#include<iostream> 
#include <stdio.h>
#include <SDL.h>
#include <cmath>
using namespace std;


void LineaPuntoMedio(SDL_Renderer* renderer ,int max);
void CircunferenciaSegundoOrden(SDL_Renderer* renderer,int max);
void Elipse(SDL_Renderer* renderer,int max);
void ParabolaPuntoMedio(SDL_Renderer*renderer,int max);
void HiperbolaPuntoMedio(SDL_Renderer* renderer,int max);
void pintarOchoPixeles(SDL_Renderer* renderer, int x, int y);

int main( int argc, char* args[] ){
    SDL_Event e;
    int max=600;
    int respuesta; 
         //MENU  
        
        cout<<endl<<"PRIMERA TAREA GRAFICACIÓN"<<endl;
        cout<<"Elija una opcion: "<<endl;
        cout<<"1) Linea"<<endl
            <<"2) Circunferencia por el algoritmo de diferencia de segundo orden"<<endl
            <<"3) Elipse"<<endl
            <<"4) Parabola"<<endl
            <<"5) Hiperbole"<<endl;
        do{
            cout<<"Respuesta: ";
            cin>>respuesta;
        }while(respuesta<0 || respuesta >5);

   if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Event event;
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(max, max, 0, &window, &renderer) == 0) {
            SDL_SetRenderDrawColor(renderer, 225, 225, 225, 0);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawLine(renderer, 300,0,300,600);
            SDL_RenderDrawLine(renderer, 0,300,600,300);
            SDL_SetRenderDrawColor(renderer, 48, 213,200, 255);
         
        switch(respuesta){
            case 1:
                LineaPuntoMedio(renderer,max);
                break;
            case 2:
                CircunferenciaSegundoOrden(renderer,max);
                break;
            case 3:
                Elipse(renderer,max);
                break;
            case 4:
                ParabolaPuntoMedio(renderer,max);
                break;
            case 5:
                HiperbolaPuntoMedio(renderer,max);
                break;
            default:
                cout<<"Opción no válida, elija una del 1 al 5"<<endl;
                break;
        }

        SDL_RenderPresent(renderer);
        while (1) {
            if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        }  

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
                }
        }
     }



    SDL_Quit();
    return 0;
}

void pintarOchoPixeles(SDL_Renderer*renderer, int x, int y){
    SDL_RenderDrawPoint(renderer, x+300, -y+300);
    SDL_RenderDrawPoint(renderer, x+300, y+300);
    SDL_RenderDrawPoint(renderer, -x+300, -y+300);
    SDL_RenderDrawPoint(renderer, -x+300, y+300);
}

// *************************** LINEA ****************************

 void LineaPuntoMedio(SDL_Renderer* renderer,int max){
         int X0, Y0, Xn, Yn;

         do{
             cout << "Introduzca el valor de X0: "; 
             cin >> X0; 
             cout  << endl << "introduzca el valor de Y0: ";
             cin >> Y0; 
             cout << endl << "Introduzca el valor de Xn: "; 
             cin >> Xn; 
             cout << endl << "Introduzca el valor de Yn: ";
             cin >> Yn;
         } while (X0 > max || Y0 > max || Xn > max || Yn > max); 
        
         int dy = Yn - Y0; 
         int dx = Xn - X0; 

         int x = Y0, y = X0; 

         int d = 2 * (dy - dx); 

         SDL_RenderDrawPoint(renderer, x+300, -y+300);

         while (x < Xn){
             ++x; 

             // Se elije E
             if (d < 0) d += 2 * dy; 
             // Se elije NE
             else{
                d+= 2 * (dy-dx);
                ++y; 
             }

            SDL_RenderDrawPoint(renderer, x+300, -y+300);
         }
     }

// *************************** Circunferencia ****************************

void CircunferenciaSegundoOrden(SDL_Renderer*renderer,int max){
     int r, d, dE, dSE; 
     double X,Y; 

     do{
         cout << "Introduzca el valor del radio: ";  
         cin >> r; 
     }while (r > max); 

     d = 1-r; 
     dE = 3; 
     dSE = -2*r+5; 

     int x = 0; 
     int y = r; 

     while (x<y){
         ++x; 

         if (d<0){
             d += dE; 
             dE += 2; 
             dSE += 2; 
         }else{
             d += dSE; 
             dE += 2; 
             dSE += 4; 
             --y; 
         }
         pintarOchoPixeles(renderer, x, y);
         pintarOchoPixeles(renderer, y, x);
     }
}

// *************************** Elipse ****************************

void Elipse(SDL_Renderer* renderer, int max){
      int x1, y1; 
      double x,y,d1,d2,dx,dy; 

      do{
          cout << "Ingrese el valor de X1: "; 
          cin >> x1;
          cout << endl << "Ingrese el valor de Y1: "; 
          cin >> y1; 
      }while(x1 > max && y1 > max);

      x = 0; 
      y = y1; 

      d1 = pow(y1, 2) - (pow(x1,2) * y1) + (0.25 * pow(x1,2)); 
      pintarOchoPixeles(renderer, x, y); 

      while((pow(x1,2)*(y-(0.5)))>(pow(y1,2)*(x+1))){
        ++x;
        if(d1<0){
            d1=d1+pow(y1,2)*((2*x)+3);
        }else{
            d1=d1+pow(y1,2)*((2*x)+3) + pow(x1,2)*((-2*y)+2);
            --y;
        }
        pintarOchoPixeles(renderer,x,y);
    }

    d2=pow(y1,2)*pow((x+(0.5)),2)+(pow(x1,2)*pow((y-1),2))-(pow(x1,2)*pow(y1,2));

    while(y>0){
        --y;
        if(d2<0){
            d2=d2+pow(y1,2)*((2*x)+2) + pow(x1,2)*((-2*y)+3);
            ++x;
        }else{
            d2=d2+pow(x1,2)*((-2*y)+3);
        }
        pintarOchoPixeles(renderer,x,y);
    }
}

// *************************** Parabola ****************************

void ParabolaPuntoMedio(SDL_Renderer*renderer,int max){
      int x,y,d1,d2,p; 
      x = 0; 
      y = 0; 

      do{
          cout << "Favor de ingresar el valor de p: ";
          cin >> p; 
      } while(p > max);

      d1 = pow(x+1.0,2) - 4*(p * y + 0.5); 

      // region 1

      while (y < p && x <= max){
          ++x; 
          if (d1 <= 0){
              // E
              d1 += 2 * x - 3; 
          } else {
              // NE
              d1 += 2 * x + 3 - 4 * p;
              ++y;
          }
          pintarOchoPixeles(renderer,x,y); 
      }

      // region 2

      d2 = pow(x + 0.5, 2) - 4 * (p * (y + 1)); 
      while (x <= max){
          ++y; 
          if(d2 <= 0){
              //NE
              d2 += 2 * x - 4 * p + 2; 
              ++x; 
          } else {
              // N
              d2 += -4*p; 
          }
          pintarOchoPixeles(renderer,x,y); 
      }
}

// *************************** Hiperbola ****************************

void HiperbolaPuntoMedio(SDL_Renderer*renderer, int max){
    int x,y,a,b,aa,bb;
   double d1,d2;

    do{cout<<"Ingrese valor de a: ";
        cin>>a;
        cout<<"Ingrese valor de b: ";
        cin>>b;
    }while(a>max and b>max);
    
    x=a;
    y=0;
    aa = a*a;
    bb = b*b;

    d1=(bb*pow(x+0.5,2))-(aa*pow(y+1.0,2))-(aa*bb);

    //REGION I
    while(x<=max){
        y++;
        if(d1>0){
            //N
            d1 += -2*aa*y-3*aa;
        }else{
            //NE
            x++;     
            d1 += 2*bb*x+2*bb-2*aa*y-3*aa;
        }
    pintarOchoPixeles(renderer,x,y);
    }

    //REGION II
    if(b>a){
        d2=(bb*pow(x+1.0,2))-(aa*pow(y+0.5,2))-(aa*bb);
        while(x<=max){
            x++;
            if(d2>0){
              //NE
                y++;
                d2+=(2*bb*x)+(3*bb)-(3*aa*y)-(2*aa);
            }else{
                //E
                d2+=-2*bb*x-3*bb;
            }
        pintarOchoPixeles(renderer,x,y);
        }
    } 
}

