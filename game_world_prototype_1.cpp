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

//Przygotowania do gry, rozbiæ póŸniej na oddzielne pliki

enum Direction { DOWN, LEFT, RIGHT, UP };
const float FPS = 30.0;			//klatki na sekunde gry
const float frames = 5.0;		//klatki animacji
float deltaTime = 1.0 / FPS;	//czas trwania klatki
const int mSpeed = 2;			//prêdkoœæ ruchu gracza
bool moving = false;			//mówi, czy gracz siê porusza

//skalowalny ekran gry
//wymiary rzeczywiste
#define O_DISP_W 400
#define O_DISP_H 300

//skala
#define DISP_SCALE 3

//wymiary wyœwietlane
#define S_DISP_W (O_DISP_W * DISP_SCALE)
#define S_DISP_H (O_DISP_H * DISP_SCALE)

ALLEGRO_DISPLAY* display;
ALLEGRO_BITMAP* buffer;

void display_init()
{
	display = al_create_display(S_DISP_W, S_DISP_H);
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

//Ta funkcja w zasadzie zastêpuje al_flip_display() dla tej gry
void display_post_draw()
{
	al_set_target_backbuffer(display);
	al_draw_scaled_bitmap(buffer, 0, 0, O_DISP_W, O_DISP_H, 0, 0, S_DISP_W, S_DISP_H,0);
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
	switch(event->type)
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

//Kolizja
bool collision(float& px, float& py, float ex, float ey, float width, float hight)
{
	if (px + width <= ex || px >= ex + width || py + hight <= ey || py >= hight + ey)
	{
		return false;
	}
	return true;
}

//animacje gracza, przenieœæ w jakieœ ³adniejsze miejsce
float animSpeed = 10.0;
float animUpdateTime = 1.0 / animSpeed;
float timeSinceLastFrameSwap = 0.0;


//Klasa gracza
//px,py - wrzucilem je wrazie czego, ale nie wydaj¹ siê teraz po¿yteczne
class Player
{
private:
	float px;
	float py;
	int dir = DOWN;
	int p_sourceX = 16;
	ALLEGRO_BITMAP* player = al_load_bitmap("player_temp.png");
public:
	Player(float _px, float _py) { px = _px; py = _py; }
	float getX()		{ return px; }
	float getY()		{ return py; }
	int getDIR()		{ return dir; }
	void setX(float x)	{ px = x; }
	void setY(float y)	{ py = y; }

	void update_player(float &x, float &y)
	{
		moving = true;

		//poruszanie gracza
		if (key[ALLEGRO_KEY_UP]) { y -= mSpeed; dir = UP; }
		else if (key[ALLEGRO_KEY_DOWN]) { y += mSpeed; dir = DOWN; }
		else if (key[ALLEGRO_KEY_LEFT]) { x -= mSpeed; dir = LEFT; }
		else if (key[ALLEGRO_KEY_RIGHT]) { x += mSpeed; dir = RIGHT; }
		else { moving = false; }

		if (collision(x, y, 100, 100, 16, 16))
		{
			if (key[ALLEGRO_KEY_UP]) { y += mSpeed; dir = UP; }
			else if (key[ALLEGRO_KEY_DOWN]) { y -= mSpeed; dir = DOWN; }
			else if (key[ALLEGRO_KEY_LEFT]) { x += mSpeed; dir = LEFT; }
			else if (key[ALLEGRO_KEY_RIGHT]) { x -= mSpeed; dir = RIGHT; }
		}
		
		if (y<=0) { y += mSpeed; dir = UP; }
		else if (y>O_DISP_H-16) { y -= mSpeed; dir = DOWN; }
		else if (x<=0) { x += mSpeed; dir = LEFT; }
		else if (x>O_DISP_W-16) { x -= mSpeed; dir = RIGHT; }

		//animacje gracza
		if (moving)
		{
			timeSinceLastFrameSwap += deltaTime;
			if (timeSinceLastFrameSwap > animUpdateTime)
			{
				p_sourceX += al_get_bitmap_width(player) / 4;
				timeSinceLastFrameSwap = 0.0;
			}
			if (p_sourceX >= al_get_bitmap_width(player))
			{
				p_sourceX = 0;
			}
		}
		else
		{
			p_sourceX = 16;
			timeSinceLastFrameSwap = 0.0;
		}
	}

	void draw_player(float x, float y)
	{
		al_draw_bitmap_region(player, p_sourceX, dir * al_get_bitmap_height(player) / 4, 16, 16, x, y, 0);
	}
};

int main()
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

	//Pozycja startowa gracza
	float x = 10;
	float y = 10;

	queue = al_create_event_queue();
	
	font = al_create_builtin_font();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool redraw = true;
	bool done = false;

	Player trainer(x, y);

	//gameloop
	al_start_timer(timer);
	while (!done)
	{
		al_wait_for_event(queue, &event);
		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			trainer.update_player(x,y);

			if (key[ALLEGRO_KEY_ESCAPE]) { done = true; }
			
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

			//informacje, które mog¹ siê przydaæ
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", x, y);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 10, 0, "FPS: %.1f", FPS);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 20, 0, "Speed: %i", mSpeed);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 30, 0, "Direction: %i  0:DOWN 1:LEFT 2:RIGHT 3:UP", trainer.getDIR());
			
			trainer.draw_player(x, y);
			al_draw_rectangle(100, 100, 116, 116, al_map_rgb(255, 0, 0),0);
			al_draw_rectangle(x, y, x+16, y+16, al_map_rgb(255, 255, 255), 0);

			display_post_draw();
			redraw = false;
		}
	}
	display_deinit();
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	return 0;
}