#include "incs.h"
#include "Level.h"

Level::Level(int w, int h)
{
	width = w;
	height = h;
	blocks = new int[w * h];
}

void Level::Deinit()
{
	delete [] blocks;
	blocks = 0;
}

void Level::Block(int x, int y, bool n, bool e, bool s, bool w, float r, float g, float b)
{
	glColor3f(r, g, b);
	
	float size = 4.0f;
	x *= size;
	y *= size;

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x, y, 0);
	glVertex3f(x + size, y, 0);
	glVertex3f(x + size, y + size, 0);
	glVertex3f(x, y + size, 0);

	if(n) {
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(x, y, 0);
		glVertex3f(x + size, y, 0);
		glVertex3f(x + size, y, -size);
		glVertex3f(x, y, -size);
	}
	if(e) {
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(x + size, y, 0);
		glVertex3f(x + size, y, -size);
		glVertex3f(x + size, y + size, -size);
		glVertex3f(x + size, y + size, 0);
	}
	if(s) {
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(x, y + size, 0);
		glVertex3f(x + size, y + size, 0);
		glVertex3f(x + size, y + size, -size);
		glVertex3f(x, y + size, -size);
	}
	if(w) {
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(x, y, 0);
		glVertex3f(x, y, -size);
		glVertex3f(x, y + size, -size);
		glVertex3f(x, y + size, 0);
	}
}

void Level::FillQuad(int x0, int y0, int x1, int y1, int block)
{
	int temp = 0;
	if(x0 < 0 || x1 < 0 || y0 < 0 || y1 < 0) return;
	if(x0 + x0 > width - 1 || x1 + x1 > width - 1 || y0 + y0 > height - 1 || y1 + y1 > height - 1) return;
	for(int xo = 0; xo < x1; xo++)
	{
		for(int yo = 0; yo < y1; yo++)
		{
			blocks[(xo + x0) + (yo + y0) * width] = block;
		}
	}
}

void Level::Pixel(int x, int y, int block)
{
	if(x < 0 || y < 0 || x > width - 1 || y > height - 1) return;
	blocks[x + y * width] = block;
}

void Level::Init()
{
	for(int i = 0; i < width * height; i++) blocks[i] = 0;
<<<<<<< HEAD
	Pixel(0, 0, 1);
=======
	//FillQuad(3, 3, 5, 5, 1);
>>>>>>> 8f805c0667551295ef68916774dce51c5dbcffc7
	level = glGenLists(1);
	glNewList(level, GL_COMPILE);
		glBegin(GL_QUADS);
			int x, y;
			for(int i = 0; i < width * height; i++)
			{
				x = i % width;
				y = i / width;
				if(blocks[i] != 0) Block(i % width, i / width, getBlock(x, y - 1) == 0, getBlock(x + 1, y) == 0, getBlock(x, y + 1) == 0, getBlock(x - 1, y) == 0, 0.0f, 1.0f, 0.0f);
			}
		glEnd();
	glEndList();
}

void Level::Render() {
	glTranslatef(0.0f, 0.0f, -15.0f);
	glCallList(level);
}

int Level::getBlock(int x, int y)
{
	int i = x + y * width;
	if(i < 0 || i >= width * height) return 0;
	return blocks[i];
}