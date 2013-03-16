#include "Player.h"
//#define Fly

Player::Player(int level)
{
	modelLoader = 0;
	x = y = 0;
	clevel = level;
	playType = 0;
	ready = false;
	frame = 0.0f;
	level1 = 0;
}

bool Player::init()
{
	modelLoader = new ModelLoader();

	coin = modelLoader->Load("coin.ngm", false);
	if(coin == -1) {
		MessageBox(NULL,"Can't load Coin Model", "ERROR",MB_OK|MB_ICONERROR);
		return false;
	}

	character = modelLoader->Load("char.ngm", true);
	if(character == -1) {
		MessageBox(NULL,"Can't load Character Model", "ERROR",MB_OK|MB_ICONERROR);
		return false;
	}

	level1 = new Level(100, 50);
	level1->Init();

	bool result = true;
	result = LoadContent();
	if(result == false) return false;
	return true;
}

void Player::deinit()
{
	delete modelLoader;
	modelLoader = 0;
}
void Player::prepSwitch()
{
	r = g = b = 1.0f;
	frame = 0.0f;
	playType = 1;
}
void Player::prepSwitch(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	frame = 0.0f;
	playType = 1;
}
void Player::switchLevel(int level, bool respawn)
{
	clevel = level;
	playType = 2;
}
void Player::Update(bool nkeys[])
{
	for(int i = 0; i < 255; i++)
	{
		keys[i] = nkeys[i];
	}

	if(ready)
	{
		if(!keys[VK_UP] && oldkeys[VK_UP]) prepSwitch();
		if(!keys[VK_DOWN] && oldkeys[VK_DOWN]) switchLevel(0, false);
		float xa = 0;
		float ya = 0;
		if(!keys[VK_A]) xa -= 0.1f;
		if(!keys[VK_D]) xa += 0.1f;
		if(!keys[VK_W]) ya += 0.1f;
		if(!keys[VK_S]) ya -= 0.1f;
		x += xa;
		y += ya;
	}

	if(frame <= 0.0f && playType == 2) playType = 0;
	if(playType == 1) frame += 0.2f;
	if(playType == 2) frame -= 0.1f;
	if(frame > 1.0f) frame = 1.0f;
}

bool Player::LoadContent()
{
	charTexture = SOIL_load_OGL_texture("Textures/character.dds", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_DDS_LOAD_DIRECT);
	if(charTexture == 0) {
		//MessageBox(NULL, "Failed to Load Character Texture", "ERROR", MB_OK);
		return false;
	}
	glBindTexture(GL_TEXTURE_2D, charTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	return true;
}

void Player::Render()
{
	glLoadIdentity();
	glTranslatef(x, y, -15.0f);
	glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
	/*glColor3f(0.8f, 0.55f, 0.0f);
	glTranslatef(-1.0f, 0.0f, -15.0f);
	glRotatef((float)GetTickCount() / 10.0f, 0.0f, 1.0f, 0.0f);
	glCallList(coin);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -15.0f);
	glRotatef((float)GetTickCount() / 10.0f, 0.0f, 1.0f, 0.0f);
	glCallList(coin);
	glLoadIdentity();
	glTranslatef(1.0f, 0.0f, -15.0f);
	glRotatef((float)GetTickCount() / 10.0f, 0.0f, 1.0f, 0.0f);
	glCallList(coin);*/
	level1->Render();
	
	glDisable(GL_LIGHTING);
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, charTexture);
	glTranslatef(0.0f, 0.0f, -14.0f);
	glCallList(character);

	glLoadIdentity();
	glBegin(GL_QUADS);
	glColor4f(r, g, b, frame);
	glVertex3f(-100.0f, -100.0f, -2.0f);
	glVertex3f(100.0f, -100.0f, -2.0f);
	glVertex3f(100.0f, 100.0f, -2.0f);
	glVertex3f(-100.0f, 100.0f, -2.0f);
	glEnd();
	glEnable(GL_LIGHTING);

	for(int i = 0; i < 255; i++)
	{
		oldkeys[i] = keys[i];
	}
	ready = true;
}
bool Player::canSwitch()
{
	if(frame >= 1.0f) return true;
	return false;
}