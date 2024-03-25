#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <iostream>



enum Direction { DOWN, LEFT, RIGHT, UP };
const float FPS = 30.0;			//klatki na sekunde gry
const float frames = 5.0;		//klatki animacji
float deltaTime = 1.0 / FPS;	//czas trwania klatki
const int mSpeed = 2;			//pr�dko�� ruchu gracza
//bool moving = false;



//skalowalny ekran gry
//wymiary rzeczywiste
#define O_DISP_W 640
#define O_DISP_H 360

ALLEGRO_MONITOR_INFO info;

//skala
//#define DISP_SCALE 4

//wymiary wy�wietlane
//#define S_DISP_W (O_DISP_W * DISP_SCALE)
//#define S_DISP_H (O_DISP_H * DISP_SCALE)

ALLEGRO_DISPLAY* display;
ALLEGRO_BITMAP* buffer;

void display_init()
{
	al_get_monitor_info(0, &info);

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_FRAMELESS);

	display = al_create_display(info.x2, info.y2);
	buffer = al_create_bitmap(O_DISP_W, O_DISP_H);
}

void display_deinit()
{
	al_destroy_bitmap(buffer);
	al_destroy_display(display);
}

void display_pre_draw()
{
	al_set_target_bitmap(buffer);
}

//Ta funkcja w zasadzie zast�puje al_flip_display() dla tej gry
void display_post_draw()
{
	al_set_target_backbuffer(display);
	al_draw_scaled_bitmap(buffer, 0, 0, O_DISP_W, O_DISP_H, 0, 0, info.x2, info.y2, 0);
	al_flip_display();
}

//Przygotowanie klawiatury

#define KEY_SEEN 1
#define KEY_RELEASED 2
unsigned char key[ALLEGRO_KEY_MAX];

void keyboard_init()
{
	memset(key, 0, sizeof(key));
}

void keyboard_update(ALLEGRO_EVENT* event)
{
	switch (event->type)
	{
	case ALLEGRO_EVENT_TIMER:
		for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
		{
			key[i] &= KEY_SEEN;
		}
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
		break;
	case ALLEGRO_EVENT_KEY_UP:
		key[event->keyboard.keycode] &= KEY_RELEASED;
		break;
	}
}



//animacje gracza, przenie�� w jakie� �adniejsze miejsce
float animSpeed = 10.0;
float animUpdateTime = 1.0 / animSpeed;
float timeSinceLastFrameSwap = 0.0;



static int run_battle_prototype()
{
	al_init();
	al_init_font_addon();
	al_init_native_dialog_addon();
	al_init_primitives_addon();
	al_init_image_addon();

	display_init();
	keyboard_init();

	al_install_keyboard();

	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_FONT* font;

	ALLEGRO_TIMER* timer = al_create_timer(deltaTime);
	ALLEGRO_TIMER* animFrames = al_create_timer(1.0 / frames);

	ALLEGRO_EVENT event;

	queue = al_create_event_queue();

	font = al_create_builtin_font();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool redraw = true;
	bool done = false;

	ALLEGRO_BITMAP* player_sprite = al_load_bitmap("assets/trainer sprite.png");
	ALLEGRO_BITMAP* enemy_sprite = al_load_bitmap("assets/charmander.png");

	int selection_state = 1;
	// 1 - fight
	// 2 - bag
	// 3 - pokemon
	// 4 - run

	if (!player_sprite || !enemy_sprite) {
		// handle image loading error
		fprintf(stderr, "Failed to load image\n");
		return -1;
	}

	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR red = al_map_rgb(255, 0, 0);

	//gameloop
	al_start_timer(timer);
	while (!done)
	{
		al_wait_for_event(queue, &event);
		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			// trainer.update_player(x, y);

			if (key[ALLEGRO_KEY_ESCAPE]) { done = true; }

			if (key[ALLEGRO_KEY_RIGHT]) {
				if (selection_state == 4) {
					selection_state = 1;
				}
				else {
					selection_state++;
				}
			
			}

			if (key[ALLEGRO_KEY_LEFT]) {
				if (selection_state == 1) {
					selection_state = 4;
				}
				else {
					selection_state--;
				}
				
			}

			redraw = true;
			break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		}

		if (done) { break; }

		keyboard_update(&event);

		if (redraw && al_is_event_queue_empty(queue))
		{
			display_pre_draw();
			al_clear_to_color(al_map_rgb(0, 0, 0));

			//trainer.draw_player(x, y);
			al_draw_bitmap(player_sprite, 50, 120, 0);
			al_draw_bitmap(enemy_sprite, 350, 40, 0);

			// buttony
			
			al_draw_rectangle(10, 270, 315, 305, white, 0);
			al_draw_rectangle(325, 270, 630, 305, white, 0);
			al_draw_rectangle(10, 315, 315, 350, white, 0);
			al_draw_rectangle(325, 315, 630, 350, white, 0);

			al_draw_textf(font, white, 15, 283, 0, "FIGHT");
			al_draw_textf(font, white, 330, 283, 0, "BAG");
			al_draw_textf(font, white, 15, 328, 0, "POKEMON");
			al_draw_textf(font, white, 330, 328, 0, "RUN");

			if (selection_state == 1) {
				al_draw_rectangle(10, 270, 315, 305, red, 0);
				al_draw_textf(font, red, 15, 283, 0, "FIGHT");
			}
			else if (selection_state == 2) {
				al_draw_rectangle(325, 270, 630, 305, red, 0);
				al_draw_textf(font, red, 330, 283, 0, "BAG");
			}
			else if (selection_state == 3) {
				al_draw_rectangle(10, 315, 315, 350, red, 0);
				al_draw_textf(font, red, 15, 328, 0, "POKEMON");
			}
			else if (selection_state == 4) {
				al_draw_rectangle(325, 315, 630, 350, red, 0);
				al_draw_textf(font, red, 330, 328, 0, "RUN");
			}

			//al_draw_rectangle(x, y, x+16, y+16, al_map_rgb(255, 255, 255), 0);

			display_post_draw();
			redraw = false;
		}
	}
	display_deinit();
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	return 0;
}