#ifndef Level_h
#define Level_h
class Level {
public:
	Level(int, int);
	void Init();
	void Deinit();
	void Render();

	int getBlock(int, int);
private:
	void FillQuad(int, int, int, int, int);
	void Pixel(int, int, int);
	void Block(int, int, bool, bool, bool, bool, float, float, float);

	int* blocks;
	int width, height;
	int level;
};
#endif