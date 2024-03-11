//Prototyp projektu
//Poruszanie sie po swiecie
//Testowanie kolizji
//
//TODO: Zmieniæ/poprawiæ kolizje
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#define SCREEN_W 800
#define SCREEN_H 600

#define KEY_SEEN 1
#define KEY_RELEASED 2

bool collision(float& px, float& py, float ex, float ey, float width, float hight)
{
	if (px + width <= ex || px >= ex + width || py + hight <= ey || py >= hight + ey)
	{
		return false;
	}
	return true;
}

int main()
{
	al_init();
	al_init_font_addon();
	al_init_native_dialog_addon();
	al_init_primitives_addon();

	al_install_keyboard();

	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font;
	ALLEGRO_EVENT event;
	ALLEGRO_TIMER* timer;

	const float FPS = 30.0;
	const int mSpeed = 5;
	float x = 100;
	float y = 100;

	queue = al_create_event_queue();
	display = al_create_display(SCREEN_W, SCREEN_H);
	font = al_create_builtin_font();
	timer = al_create_timer(1.0 / FPS);

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool redraw = true;
	bool done = false;

	//czêœæ poruszania siê, podobno lepsze
	unsigned char key[ALLEGRO_KEY_MAX];
	memset(key, 0, sizeof(key));

	//gameloop
	al_start_timer(timer);
	while (!done)
	{
		al_wait_for_event(queue, &event);

		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			if (key[ALLEGRO_KEY_UP]) { y -= mSpeed; }
			if (key[ALLEGRO_KEY_DOWN]) { y += mSpeed; }
			if (key[ALLEGRO_KEY_LEFT]) { x -= mSpeed; }
			if (key[ALLEGRO_KEY_RIGHT]) { x += mSpeed; }

			//uwaga: psuje siê, jeœli obiekty s¹ ró¿nej wielkoœci
			//do przebudowy
			if (collision(x, y, 300, 300, 20, 20))
			{
				if (key[ALLEGRO_KEY_UP]) { y += mSpeed; }
				if (key[ALLEGRO_KEY_DOWN]) { y -= mSpeed; }
				if (key[ALLEGRO_KEY_LEFT]) { x += mSpeed; }
				if (key[ALLEGRO_KEY_RIGHT]) { x -= mSpeed; }
			}

			if (key[ALLEGRO_KEY_ESCAPE]) { done = true; }

			//to te¿ jest czêœæ poruszania siê
			for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
			{
				key[i] &= KEY_SEEN;
			}

			redraw = true;
			break;
			//te dwa case poni¿ej te¿, chyba trzeba to zmieniæ
		case ALLEGRO_EVENT_KEY_DOWN:
			key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
			break;
		case ALLEGRO_EVENT_KEY_UP:
			key[event.keyboard.keycode] &= KEY_RELEASED;
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			done = true;
			break;
		}

		if (redraw && al_is_event_queue_empty(queue))
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", x, y);
			al_draw_filled_rectangle(x, y, x + 20, y + 20, al_map_rgb(255, 255, 255));
			al_draw_rectangle(300, 300, 320, 320, al_map_rgb(255, 0, 0), 2);
			al_flip_display();

			redraw = false;
		}
	}
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	return 0;
}