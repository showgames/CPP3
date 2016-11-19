#include <iostream>
#include "Stage.hpp"
using namespace std;

Stage::Stage(const char* stageData, int sizeX, int sizeY)
{
	mWidth  = sizeX;
	mHeight = sizeY;

	mObjects.setSize(sizeX, sizeY);
	mGoalFlags.setSize(sizeX, sizeY);

	for (int y = 0; y < sizeY; ++y) {
		for (int x = 0; x < sizeX; ++x) {
			mObjects(x, y) = OBJ_WALL;
			mGoalFlags(x, y) = false;
		}
	}

	for (int y = 0; y < sizeY; ++y) {
		for (int x = 0; x < sizeX; ++x) {
			Object t;
			bool goalFlag = false;
			switch(stageData[y * sizeX + x]) {
			case '#': t = OBJ_WALL; break;
			case ' ': t = OBJ_SPACE; break;
			case 'o': t = OBJ_BLOCK; break;
			case 'O': t = OBJ_BLOCK; goalFlag = true; break;
			case '.': t = OBJ_SPACE; goalFlag = true; break;
			case 'p': t = OBJ_MAN; break;
			case 'P': t = OBJ_MAN; goalFlag = true; break;
			}
			mObjects(x, y) = t;
			mGoalFlags(x, y) = goalFlag;
		}
	}
}

void Stage::draw() const {
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			Object o = mObjects( x, y );
			bool goalFlag = mGoalFlags( x, y );
			if (goalFlag) {
				switch(o) {
				case OBJ_SPACE: cout << '.'; break;
				case OBJ_WALL: cout << '#'; break;
				case OBJ_BLOCK: cout << 'O'; break;
				case OBJ_MAN: cout << 'P'; break;
				}
			} else {
				switch(o) {
				case OBJ_SPACE: cout << ' '; break;
				case OBJ_WALL: cout << '#'; break;
				case OBJ_BLOCK: cout << 'o'; break;
				case OBJ_MAN: cout << 'p'; break;
				}
			}
		}
		cout << endl;
	}
}

void Stage::update(char dir) {
	int dx = 0, dy = 0;
	switch (dir) {
	case 'w': dy = -1; break;// up
	case 'z': dy = 1;  break;// down
	case 'a': dx = -1; break;// left
	case 's': dx = 1;  break; // right
	}
	int w = mWidth, h = mHeight;
	Array2D<Object>& o = mObjects;
	int x, y;
	bool found = false;
	for (y = 0; y < mHeight; ++y) {
		for (x = 0; x < mWidth; ++x) {
			if (o(x, y) == OBJ_MAN) {
				found = true;
				break;
			}
		}
		if (found) {
			break;
		}
	}
	int tx = x + dx;
	int ty = y + dy;
	if (tx < 0 || ty < 0 || tx >= w || ty >= h) {
		return;
	}
	if (o(tx, ty) == OBJ_SPACE) {
		o(tx, ty) = OBJ_MAN;
		o(x, y) = OBJ_SPACE;
	} else if (o(tx, ty) == OBJ_BLOCK) {
		int tx2 = tx + dx;
		int ty2 = ty + dy;
		if (tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h) {
			return;
		}
		if (o(tx2, ty2) == OBJ_SPACE) {
			o(tx2, ty2) = OBJ_BLOCK;
			o(tx, ty) = OBJ_MAN;
			o(x, y) = OBJ_SPACE;
		}
	}
}

bool Stage::hasCleared() const {
	for (int y = 0; y < mHeight; ++y) {
		for (int x = 0; x < mWidth; ++x) {
			if (mObjects(x, y) == OBJ_BLOCK) {
				if (mGoalFlags(x, y) == false) {
					return false;
				}
			}
		}
	}
	return true;
}