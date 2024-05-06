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
#include <iostream>
#include <vector>

#include "Engine.h"

#include "WorldEntities.h"
#include "WorldMap.h"

#include "Battle.h"
#include"Potion.h"
#include"Pokemon.h"

const float start_posx = 234.0;
const float start_posy = 38.0;

int main()
{
	al_init();
	al_init_font_addon();
	al_init_native_dialog_addon();
	al_init_primitives_addon();
	al_init_image_addon();

	game.display_init();
	game.keyboard_init();
	sprites_init();

	ALLEGRO_BITMAP* meowthBitmap = al_load_bitmap("meowth.png");
	ALLEGRO_BITMAP* pikachuBitmap = al_load_bitmap("pikachu.png");
	ALLEGRO_BITMAP* rattataBitmap = al_load_bitmap("rattata.png");
	ALLEGRO_BITMAP* squirtleBitmap = al_load_bitmap("squirtle.png");
	ALLEGRO_BITMAP* charmanderBitmap = al_load_bitmap("charmander.png");

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

	Battle battle(game);
	std::vector<Potion> playerPotions{
		{1.0f, "Potion 1"}, {2.0f, "Potion 2"}, {3.0f, "Potion 3"},
		{4.0f, "Potion 4"}, {5.0f, "Potion 5"} };
	std::vector<Pokemon> playerPokemons{
		{"Meowth 100", meowthBitmap, 100.0f, {{101.0f,"Attack 101"}, {102.0f,"Attack 102"},
			{103.0f,"Attack 103"}, {104.0f,"Attack 104"}, {105.0f,"Attack 105"}}},
		{"Pikachu 200", pikachuBitmap, 200.0f, {{201.0f,"Attack 201"}, {202.0f,"Attack 202"},
			{203.0f,"Attack 203"}, {204.0f,"Attack 204"}, {205.0f,"Attack 205"}}},
		{"Rattata 300", rattataBitmap, 300.0f, {{301.0f,"Attack 301"}, {302.0f,"Attack 302"},
			{303.0f,"Attack 303"}, {304.0f,"Attack 304"}, {305.0f,"Attack 305"}}},
		{"Squirtle 400", squirtleBitmap, 400.0f, {{401.0f,"Attack 401"}, {402.0f,"Attack 402"},
			{403.0f,"Attack 403"}, {404.0f,"Attack 404"}, {405.0f,"Attack 405"}}},
		{"Charmander 500", charmanderBitmap, 500.0f, {{501.0f,"Attack 501"}, {502.0f,"Attack 502"},
			{503.0f,"Attack 503"}, {504.0f,"Attack 504"}, {505.0f,"Attack 505"}}}, };

	Player trainer(start_posx, start_posy);

	bool redraw = true;
	bool done = false;

	TileMap test1("test_tile_map_0.txt");
	test1.LoadTileMap();

	enum GAMESTATE { MENU, WORLD, FIGHT, ENDSCREEN };

	int state = -1;

	game.changeState(state, MENU);
	//gameloop
	al_start_timer(timer);
	while (!done)
	{
		//update
		al_wait_for_event(queue, &event);
		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			if(state == WORLD)
			{
				//trainer.update_player();
			}
			else if (state == FIGHT)
			{
				if(battle.isStarted())
					battle.handleKeyboardEvents();
			}
			
			if (game.checkKeyDownOnce(ALLEGRO_KEY_ESCAPE)) 
			{ 
				std::cout << "DONE"; done = true; 
			}

			if (state == MENU)
			{
				if (game.checkKeyDownOnce(ALLEGRO_KEY_ENTER))
					game.changeState(state, WORLD);
			}

			else if (state == WORLD)
			{
				if (game.checkKeyDownOnce(ALLEGRO_KEY_F))
				{
					battle.start(&playerPokemons, &playerPotions);
					game.changeState(state, FIGHT);
					if (!battle.isStarted())
						return -5;
				}
			}
			else if (state == FIGHT)
			{
				if (game.checkKeyDownOnce(ALLEGRO_KEY_F))
				{
					game.changeState(state, WORLD);
				}
				else if (game.checkKeyDownOnce(ALLEGRO_KEY_SPACE))
				{
					game.changeState(state, ENDSCREEN);
				}
			}
			else if (state == ENDSCREEN)
			{
				if (game.checkKeyDownOnce(ALLEGRO_KEY_SPACE))
				{
					game.changeState(state, MENU);
				}
			}

			redraw = true;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		}

		if (done) { break; }

		game.keyboard_update(&event);

		//render
		if (redraw && al_is_event_queue_empty(queue))
		{
			game.display_pre_draw();
			if (state == MENU)
			{
				al_clear_to_color(al_map_rgb(100, 50, 100));
				al_draw_textf(font, al_map_rgb(255, 255, 255), game.getDispW()/2, game.getDispH() / 2, 0, "WORLD (ENTER)");
			}
			else if (state == WORLD)
			{
				al_clear_to_color(al_map_rgb(10, 50, 10));
				trainer.update_player();
				test1.DrawTileMap();

				if (test1.isColliding(trainer) == 1)
				{
					al_draw_textf(font, al_map_rgb(255, 255, 255), 0, (game.getDispH() - 20), 0, "Kolizja");
					if (game.key[ALLEGRO_KEY_UP]) { trainer.setY(trainer.getY() + game.getMSpeed()); trainer.setDIR(UP); }
					else if (game.key[ALLEGRO_KEY_DOWN]) { trainer.setY(trainer.getY() - game.getMSpeed()); trainer.setDIR(DOWN); }
					else if (game.key[ALLEGRO_KEY_LEFT]) { trainer.setX(trainer.getX() + game.getMSpeed()); trainer.setDIR(LEFT); }
					else if (game.key[ALLEGRO_KEY_RIGHT]) { trainer.setX(trainer.getX() - game.getMSpeed()); trainer.setDIR(RIGHT); }
				}
				else if (test1.isColliding(trainer) == 2)
				{
					game.changeState(state, FIGHT);
					battle.start(&playerPokemons, &playerPotions);
					//gra powinna po walce rozwarzyc dwa przypadki
					//1. gracz wygral i usuwa przeciwnika
					//2. gracz przegral, koniec gry i wraca na miejsce poczatkowe
					//
					//na ten moment wejscie tak w walke blokuje nas w walce, poniewaz teoretycznie dalej jestesmy w przeciwniku
					//moze da sie zrobic funkcje przesuwajaca gracza, ale nie wiem, czy ma to sens
					//te dwie ponizsze linie kodu sa absolutnie paskude, ale musza na razie starczec
					trainer.setX(300);
					trainer.setY(300);
				}

				trainer.draw_player();
			}
			else if (state == FIGHT)
			{
				al_clear_to_color(al_map_rgb(50, 50, 10));
				if (battle.isStarted())
					battle.draw();
				else
				{
					game.changeState(state, WORLD);
				}
			}
			else if (state == ENDSCREEN)
			{
				al_clear_to_color(al_map_rgb(100, 100, 100));
				al_draw_textf(font, al_map_rgb(255, 255, 255), game.getDispW() / 2, game.getDispH() / 2, 0, "MENU (SPACE)");
				trainer.change_pos(start_posx, start_posy, DOWN);
			}
			
			//test1.DrawTileMap();

			//informacje, które mog¹ siê przydaæ
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", trainer.getX(), trainer.getY());
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 10, 0, "FPS: %.1f", game.getFPS());
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 20, 0, "Speed: %i", game.getMSpeed());
			al_draw_textf(font, al_map_rgb(255, 255, 255), (game.getDispW() - 100), (game.getDispH() - 20), 0, "%i x %i", game.info.x2, game.info.y2);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 30, 0, "Direction: %i  0:DOWN 1:LEFT 2:RIGHT 3:UP", trainer.getDIR());

			game.display_post_draw();
			redraw = false;
		}
	}

	game.display_deinit();
	al_destroy_bitmap(meowthBitmap);
	al_destroy_bitmap(pikachuBitmap);
	al_destroy_bitmap(rattataBitmap);
	al_destroy_bitmap(squirtleBitmap);
	al_destroy_bitmap(charmanderBitmap);
	sprites_deinit();
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	return 0;
}