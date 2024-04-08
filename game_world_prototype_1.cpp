//Prototyp projektu
//Poruszanie sie po swiecie
//Testowanie kolizji
//
//TODO: Kolizja do zrobienia, dodanie mapy
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "Engine.h"
#include "WorldEntities.h"
#include "WorldMap.h"
#include <iostream>
//Komentarze na razie zostawiam w razie czego, ale s¹ do usuniêcia

////enum Direction { DOWN, LEFT, RIGHT, UP };
//const float FPS = 30.0;			//klatki na sekunde gry
//const float frames = 5.0;		//klatki animacji
//float deltaTime = 1.0 / FPS;	//czas trwania klatki
//const int mSpeed = 2;			//prêdkoœæ ruchu gracza
//bool moving = false;			//mówi, czy gracz siê porusza
//
////skalowalny ekran gry
////wymiary rzeczywiste
//
//const int dispW = 640;
//const int dispH = 360;
//
//ALLEGRO_MONITOR_INFO info;
//
////skala
////#define DISP_SCALE 4
//
////wymiary wyœwietlane
////#define S_DISP_W (O_DISP_W * DISP_SCALE)
////#define S_DISP_H (O_DISP_H * DISP_SCALE)
//
//ALLEGRO_DISPLAY* display;
//ALLEGRO_BITMAP* buffer;
//
//void display_init()
//{
//	al_get_monitor_info(0, &info);
//
//	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW|ALLEGRO_FRAMELESS);
//
//	display = al_create_display(info.x2, info.y2);
//	buffer = al_create_bitmap(dispW, dispH);
//}
//
//void display_deinit()
//{
//	al_destroy_bitmap(buffer);
//	al_destroy_display(display);
//}
//
//void display_pre_draw()
//{
//	al_set_target_bitmap(buffer);
//}
//
////Ta funkcja w zasadzie zastêpuje al_flip_display() dla tej gry
//void display_post_draw()
//{
//	al_set_target_backbuffer(display);
//	al_draw_scaled_bitmap(buffer, 0, 0, dispW, dispH, 0, 0, info.x2, info.y2,0);
//	al_flip_display();
//}
//
////Przygotowanie klawiatury
//
//#define KEY_SEEN 1
//#define KEY_RELEASED 2
//unsigned char key[ALLEGRO_KEY_MAX];
//
//void keyboard_init()
//{
//	memset(key, 0, sizeof(key));
//}
//
//void keyboard_update(ALLEGRO_EVENT* event)
//{
//	switch(event->type)
//	{
//	case ALLEGRO_EVENT_TIMER:
//		for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
//		{
//			key[i] &= KEY_SEEN;
//		}
//		break;
//	case ALLEGRO_EVENT_KEY_DOWN:
//		key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
//		break;
//	case ALLEGRO_EVENT_KEY_UP:
//		key[event->keyboard.keycode] &= KEY_RELEASED;
//		break;
//	}
//}
//
////Kolizja
//bool collision(float& px1, float& py1, float px2, float py2, float ox1, float oy1, float ox2, float oy2)
//{
//	if (
//		px1 > ox1 + ox2 ||
//		px1 + px2 < ox1 ||
//		py1 > oy1 + oy2 ||
//		py1 + py2 < oy1) {
//		return false;
//	}
//	return true;
//}
////bool collision(float& px, float& py, float ex, float ey, float width, float hight)
////{
////	if (px + width <= ex || px >= ex + width || py + hight <= ey || py >= hight + ey)
////	{
////		return false;
////	}
////	return true;
////}
//
////animacje gracza, przenieœæ w jakieœ ³adniejsze miejsce
//float animSpeed = 10.0;
//float animUpdateTime = 1.0 / animSpeed;
//float timeSinceLastFrameSwap = 0.0;
//
//enum Direction { DOWN, LEFT, RIGHT, UP };
////Klasa gracza
//class Player
//{
//private:
//	float px;
//	float py;
//	int dir = DOWN;
//	int p_sourceX = 0;
//	bool moving = false;
//	ALLEGRO_BITMAP* player = al_load_bitmap("player_temp.png");
//public:
//	Player(float _px, float _py) { px = _px; py = _py; }
//	float getX()		{ return px; }
//	float getY()		{ return py; }
//	int getDIR()		{ return dir; }
//	void setX(float x)	{ px = x; }
//	void setY(float y)	{ py = y; }
//
//	void update_player(float &x, float &y)
//	{
//		moving = true;
//
//		//poruszanie gracza
//		if (key[ALLEGRO_KEY_UP]) { y -= mSpeed; dir = UP; }
//		else if (key[ALLEGRO_KEY_DOWN]) { y += mSpeed; dir = DOWN; }
//		else if (key[ALLEGRO_KEY_LEFT]) { x -= mSpeed; dir = LEFT; }
//		else if (key[ALLEGRO_KEY_RIGHT]) { x += mSpeed; dir = RIGHT; }
//		else { moving = false; }
//
//		if (collision(x, y, 16, 16, 300, 150,16,16))
//		{
//			if (key[ALLEGRO_KEY_UP]) { y += mSpeed; dir = UP; }
//			else if (key[ALLEGRO_KEY_DOWN]) { y -= mSpeed; dir = DOWN; }
//			else if (key[ALLEGRO_KEY_LEFT]) { x += mSpeed; dir = LEFT; }
//			else if (key[ALLEGRO_KEY_RIGHT]) { x -= mSpeed; dir = RIGHT; }
//		}
//		
//		if (y<=50) { y += mSpeed; dir = UP; }
//		else if (y>330) { y -= mSpeed; dir = DOWN; }
//		else if (x<=100) { x += mSpeed; dir = LEFT; }
//		else if (x>380) { x -= mSpeed; dir = RIGHT; }
//
//		//animacje gracza
//		if (moving)
//		{
//			timeSinceLastFrameSwap += deltaTime;
//			if (timeSinceLastFrameSwap > animUpdateTime)
//			{
//				p_sourceX += al_get_bitmap_width(player) / 4;
//				timeSinceLastFrameSwap = 0.0;
//			}
//			if (p_sourceX >= al_get_bitmap_width(player))
//			{
//				p_sourceX = 0;
//			}
//		}
//		else
//		{
//			p_sourceX = 16;
//			timeSinceLastFrameSwap = 0.0;
//		}
//	}
//
//	void draw_player(float x, float y)
//	{
//		al_draw_bitmap_region(player, p_sourceX, dir * al_get_bitmap_height(player) / 4, 16, 16, x, y, 0);
//	}
//};

int main()
{
	al_init();
	al_init_font_addon();
	al_init_native_dialog_addon();
	al_init_primitives_addon();
	al_init_image_addon();

	//Engine game;

	game.display_init();
	game.keyboard_init();
	sprites_init();

	al_install_keyboard();

	ALLEGRO_EVENT event;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_FONT* font;

	ALLEGRO_TIMER* timer = al_create_timer(game.getDeltaTime());
	ALLEGRO_TIMER *animFrames = al_create_timer(1.0 / game.getFrames());

	//Pozycja startowa gracza

	queue = al_create_event_queue();
	
	font = al_create_builtin_font();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(game.display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	Player trainer(234.0, 18.0);

	bool redraw = true;
	bool done = false;

	TileMap test1("test_tile_map_0.txt");
	test1.LoadTileMap();
	
	ObjectMap test11("test_object_map_0.txt");
	test11.LoadObjectMap();

	//gameloop
	al_start_timer(timer);
	while (!done)
	{
		al_wait_for_event(queue, &event);
		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			trainer.update_player();
			
			if (game.key[ALLEGRO_KEY_ESCAPE]) { std::cout << "DONE"; done = true; }

			redraw = true;
			break;
			
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		}

		if (done) { break; }

		game.keyboard_update(&event);

		if (redraw && al_is_event_queue_empty(queue))
		{
			game.display_pre_draw();
			al_clear_to_color(al_map_rgb(0, 0, 40));

			test1.DrawTileMap();
			test11.DrawObjectMap();

			//informacje, które mog¹ siê przydaæ
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", trainer.getX(), trainer.getY());
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 10, 0, "FPS: %.1f", game.getFPS());
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 20, 0, "Speed: %i", game.getMSpeed());
			al_draw_textf(font, al_map_rgb(255, 255, 255), (game.getDispW() - 100), (game.getDispH() - 20), 0, "%i x %i", game.info.x2, game.info.y2);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 30, 0, "Direction: %i  0:DOWN 1:LEFT 2:RIGHT 3:UP", trainer.getDIR());
			
			trainer.draw_player();
			//al_draw_rectangle(100, 100, 116, 116, al_map_rgb(255, 0, 0),0);
			//al_draw_rectangle(x, y, x+16, y+16, al_map_rgb(255, 255, 255), 0);

			game.display_post_draw();
			redraw = false;
		}
	}
	game.display_deinit();
	sprites_deinit();
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	return 0;
}