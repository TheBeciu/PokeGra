#ifndef ENGINE
#define ENGINE

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
//#include "WorldEntities.h"
#include <iostream>

//unsigned char key[ALLEGRO_KEY_MAX];

class Engine
{
public:
	ALLEGRO_MONITOR_INFO info;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP* buffer;
	ALLEGRO_EVENT event;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_FONT* font;
	ALLEGRO_TIMER* timer;
	ALLEGRO_TIMER* animFrames;
private:
	const float FPS = 30.0;
	const float frames = 5.0;
	const int mSpeed = 2;
	float deltaTime = 1.0 / FPS;

	const int dispW = 640;
	const int dispH = 360;

	const int KEY_SEEN = 1;
	const int KEY_RELEASED = 2;

	float animSpeed = 10.0;
	float animUpdateTime = 1.0 / animSpeed;
	float timeSinceLastFrameSwap = 0.0;
public:
	float getFPS() { return FPS; }
	float getFrames() { return frames; }
	int getMSpeed() { return mSpeed; }
	float getDeltaTime() { return deltaTime; }

	int getDispW() { return dispW; }
	int getDispH() { return dispH; }

	float getAnimSpeed() { return animSpeed; }
	float getAnimUpdateTime() { return animUpdateTime; }
	float getTimeSinceLastFrameSwap() { return timeSinceLastFrameSwap; }

	void setAnimSpeed(float x) { animSpeed = x; }
	void setAnimUpdateTime(float x) { animUpdateTime = x; }
	void setTimeSinceLastFrameSwap(float x) { timeSinceLastFrameSwap = x; }
	
	void display_init();
	void display_deinit();
	void display_pre_draw();
	void display_post_draw();

	void keyboard_init();
	void keyboard_update(ALLEGRO_EVENT* event);

	//friend class Player;
};

#endif