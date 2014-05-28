#include "MenuButton.h"

MenuButton::MenuButton(const LoaderParams * params) : SDLGameObject(params)
{
  currentFrame = SELECT_OUT;
}

void MenuButton::draw(SDL_RendererFlip flags)
{
  SDLGameObject::draw(flags);
}

void MenuButton::update()
{
  SDL_Event event;

  SDL_PollEvent(&event);

  switch(event.type)
  {
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym)
      {
        case SDLK_RETURN:
          currentFrame = SELECTED;
          break;

        default:
          break;
      }

      break;

    default:
      break;
  }

  SDLGameObject::update();
}

void MenuButton::clean()
{
  SDLGameObject::clean();
}
