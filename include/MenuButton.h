#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include "SDLGameObject.h"

class MenuButton : public SDLGameObject
{
  public:
    MenuButton(const LoaderParams* params);

    virtual void draw(SDL_RendererFlip flags=SDL_FLIP_NONE);
    virtual void update();
    virtual void clean();

  private:
    enum button_state
    {
      SELECT_OUT = 0,
      SELECT_OVER = 1,
      SELECTED = 2
    };

};

#endif
