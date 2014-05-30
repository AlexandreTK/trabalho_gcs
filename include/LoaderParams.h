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
    int m_callbackID;
    int m_animSpeed;
    int m_numFrames;


  public:
    LoaderParams(int x, int y, int w, int h, string textureID, 
        int numFrames, int callbackID = 0, int animSpeed = 0) : 
    m_x(x), 
    m_y(y), 
    m_w(w), 
    m_h(h), 
    m_textureID(textureID),
    m_numFrames(numFrames),
    m_callbackID(callbackID),
    m_animSpeed(animSpeed)
    {

    }

    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getWidth() const { return m_w; }
    int getHeight() const { return m_h; }
    string getTextureID() const { return m_textureID; }
    int getNumFrames() const { return m_numFrames; }
    int getCallbackID() const { return m_callbackID; }
    int getAnimSpeed() const { return m_animSpeed; }
};

#endif
