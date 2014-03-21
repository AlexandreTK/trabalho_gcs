// Importação de bibliotecas do SDL e I/O do C++
#include <SDL.h>
#include <iostream>

// Utilizando diretivas
using namespace std::cout;

// Constantes para dimensões da tela
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char** args) 
{
  // A janela a ser renderizada
  SDL_Window* window = NULL;

  // A superfície contida na janela
  SDL_Surface* screenSurface = NULL;

  // Inicialização do SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    cout << "SDL não pode inicializar! SDL_Error: %s\n", SDL_GetError();
  }
}
