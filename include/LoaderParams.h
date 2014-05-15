#ifndef LOADERPARAMS_H
#define LOADERPARAMS_H

#include <string>

using std::string;

class LoaderParams
{
  private:

    int m_x;
    int m_y;

    int m_w;
    int m_h;

    string m_textureID;


  public:
    LoaderParams(int x, int y, int w, int h, string textureID) : m_x(x), m_y(y), m_w(w), m_h(h), m_textureID(textureID)
    {

    }

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_w; }
    int getHeight() const { return m_h; }
    string getTextureID() const { return m_textureID; }
};

#endif
