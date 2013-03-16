#ifndef player_h
#define player_h
#include "incs.h"
#include "ModelLoader.h"
#include "Level.h"
class Player {
public:
	Player(int);
	bool init();
	void deinit();
	void prepSwitch();
	void prepSwitch(float, float, float);
	void switchLevel(int, bool);
	void Render();
	void Update(bool[]);
	bool canSwitch();
	bool LoadContent();
private:
	int clevel;
	float frame;
	float r, g, b;
	int u, v;
	float x, y;
	int playType;
	bool keys[256];
	bool oldkeys[256];
	bool ready;
	int charTexture;

	int coin, character;
	ModelLoader* modelLoader;

	Level* level1;
};
#endif