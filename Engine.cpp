#include <allegro5/allegro.h>
#include "Engine.h"

enum GAMESTATE { MENU, WORLD, FIGHT, ENDSCREEN_WIN, ENDSCREEN_ESCAPE, ENDSCREEN_LOSE };

void Engine::display_init()
{
	al_get_monitor_info(0, &info);

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_FRAMELESS);

	display = al_create_display(info.x2, info.y2);
	buffer = al_create_bitmap(dispW, dispH);
	font = al_create_builtin_font();
}
void Engine::display_deinit()
{
	al_destroy_bitmap(buffer);
	al_destroy_display(display);
}
void Engine::display_pre_draw()
{
	al_set_target_bitmap(buffer);
}
void Engine::display_post_draw()
{
	al_set_target_backbuffer(display);
	al_draw_scaled_bitmap(buffer, 0, 0, dispW, dispH, 0, 0, info.x2, info.y2, 0);
	al_flip_display();
}

void Engine::keyboard_init()
{
	memset(key, 0, sizeof(key));
}
void Engine::keyboard_update(ALLEGRO_EVENT* event)
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
void Engine::changeState(int& state, int nState)
{
	//pre-proccess
	switch (state)
	{
	case MENU:
		std::cout << "leaving MENU\n";
		break;
	case WORLD:
		std::cout << "leaving WORLD\n";
		break;
	case FIGHT:
		std::cout << "leaving FIGHT\n";
		break;
	case ENDSCREEN_WIN:
		std::cout << "leaving ENDSCREEN_WIN\n";
		break;
	case ENDSCREEN_ESCAPE:
		std::cout << "leaving ENDSCREEN_ESCAPE\n";
		break;
	case ENDSCREEN_LOSE:
		std::cout << "leaving ENDSCREEN_LOSE\n";
		break;
	}

	state = nState;

	//post-proccess
	switch (state)
	{
	case MENU:
		std::cout << "entering MENU\n";
		break;
	case WORLD:
		std::cout << "entering WORLD\n";
		break;
	case FIGHT:
		std::cout << "entering FIGHT\n";
		break;
	case ENDSCREEN_WIN:
		std::cout << "entering ENDSCREEN_WIN\n";
		break;
	case ENDSCREEN_ESCAPE:
		std::cout << "entering ENDSCREEN_ESCAPE\n";
		break;
	case ENDSCREEN_LOSE:
		std::cout << "entering ENDSCREEN_LOSE\n";
		break;
	}

}
bool Engine::betterHS(int y)
{
	std::ifstream odczyt;
	odczyt.open("highscore.txt");
	std::string x;
	getline(odczyt, x);
	int z = stoi(x);
	odczyt.close();
	if (z == 0)
	{
		return true;
	}
	if (y < z)
	{
		return true;
	}
	return false;
}