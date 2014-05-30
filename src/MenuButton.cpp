#include "MenuButton.h"

MenuButton::MenuButton(const LoaderParams * params, void(*callback)()) : SDLGameObject(), m_callback(callback)
{
  currentFrame = SELECT_OUT;
}

void MenuButton::draw()
{
  SDLGameObject::draw();
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

void MenuButton::load(const LoaderParams * params)
{
  SDLGameObject::load(params);
  m_callbackID = params->getCallbackID();
  currentFrame = SELECT_OUT;
}
