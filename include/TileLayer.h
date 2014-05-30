#ifndef TILELAYER_H
#define TILELAYER_H

#include "Level.h"
#include "Vector2D.h"
#include <vector>

using std::vector;

class TileLayer : public Layer
{
public:
	TileLayer(int tileSize, const vector<Tileset> &tilesets);

	virtual void update();
	virtual void render();

	void setTileIDs(const vector< vector<int> >& data)
	{
		m_tileIDs = data;
	}

	void setTileSize(int tileSize)
	{
		m_tileSize = tileSize;
	}

	Tileset getTilesetByID(int tileID);

private:
	int m_numColumns;
	int m_numRows;
	int m_tileSize;

	Vector2D m_position;
	Vector2D m_velocity;

	const vector<Tileset> &m_tilesets;
	vector< vector<int> > m_tileIDs;
};

#endif
