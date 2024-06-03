#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "Engine.h"

#include "WorldEntities.h"
#include "WorldMap.h"

#include "PokemonTrainer.h"
#include "Battle.h"
#include "ResourceCache.h"
#include "Item.h"



std::vector<PokemonAttack> createBasicPokemonAttacks(ResourceCache& resCache) {
	return std::vector<PokemonAttack>{
		PokemonAttack{ //-30 do ataku przeciwnika
			"Growl",
			0.0f, -30.0f, 0.0f,
			0.0f, 0.0f,
			resCache.bitmap("battle/growl.png"), resCache.soundSample("battle/growl.mp3")
		},
		PokemonAttack{ //-30 do obrony przeciwnika
			"Tail Whip",
			0.0f, 0.0f, -30.0f,
			0.0f, 0.0f,
			resCache.bitmap("battle/tailWhip.png"), resCache.soundSample("battle/tailWhip.mp3"),

		},
		PokemonAttack{ //przywraca do 15 punktów zdrowia
			"Wish",
			15.0f, 0.0f, 0.0f,
			0.0f, 0.0f,
			resCache.bitmap("battle/wish.png"), resCache.soundSample("battle/wish.mp3")
		}
	};
}


Pokemon createPikachu(ResourceCache& resCache) {
	Pokemon pokemon{
		"Pikachu",
		resCache.bitmap("battle/playerPikachu.png"), 
		0.0f, 0.0f,
		100.0f, 100.0f,
		60.0f, 60.0f,
		40.0f, 40.0f
	};
	pokemon.attacks = createBasicPokemonAttacks(resCache);
	pokemon.attacks.push_back(PokemonAttack{
		"Thunder",
		-50.0f, 0.0f, 0.0f,
		0.0f, 0.0f,
		resCache.bitmap("battle/thunderShock.png"), resCache.soundSample("battle/thunderShock.mp3")
	});

	return pokemon;
}


Pokemon createSquirtle(ResourceCache& resCache) {
	Pokemon pokemon{
		"Squirtle",
		resCache.bitmap("battle/playerSquirtle.png"), 
		0.0f, 0.0f,
		100.0f, 100.0f,
		60.0f, 60.0f,
		40.0f, 40.0f
	};
	pokemon.attacks = createBasicPokemonAttacks(resCache);
	pokemon.attacks.push_back(PokemonAttack{
		"Water Gun",
		-50.0f, 0.0f, 0.0f,
		0.0f, 0.0f,
		resCache.bitmap("battle/waterGun.png"), resCache.soundSample("battle/waterGun.mp3")
	});

	return pokemon;
}


Pokemon createGengar(ResourceCache& resCache) {
	Pokemon pokemon{
		"Gengar",
		resCache.bitmap("battle/enemyGengar.png"),
		0.0f, 0.0f,
		100.0f, 100.0f,
		60.0f, 60.0f,
		40.0f, 40.0f
	};
	pokemon.attacks = createBasicPokemonAttacks(resCache);
	pokemon.attacks.push_back(PokemonAttack{
		"Lick",
		-50.0f, 0.0f, 0.0f,
		0.0f, 0.0f,
		resCache.bitmap("battle/Lick.png"), resCache.soundSample("battle/Lick.mp3")
		});

	return pokemon;
}

Pokemon createArbok(ResourceCache& resCache) {
	Pokemon pokemon{
		"Arbok",
		resCache.bitmap("battle/enemyArbok.png"),
		0.0f, 0.0f,
		100.0f, 100.0f,
		60.0f, 60.0f,
		40.0f, 40.0f
	};
	pokemon.attacks = createBasicPokemonAttacks(resCache);
	pokemon.attacks.push_back(PokemonAttack{
		"Poison Sting",
		-50.0f, 0.0f, 0.0f,
		0.0f, 0.0f,
		resCache.bitmap("battle/PoisonSting.png"), resCache.soundSample("battle/PoisonFang.mp3")
		});

	return pokemon;
}




Pokemon createBulbasaur(ResourceCache& resCache) {
	Pokemon pokemon{
		"Bulbasaur",
		resCache.bitmap("battle/enemyBulbasaur.png"), 
		0.0f, 0.0f,
		100.0f, 100.0f,
		60.0f, 60.0f,
		40.0f, 40.0f
	};
	pokemon.attacks = createBasicPokemonAttacks(resCache);
	pokemon.attacks.push_back(PokemonAttack{
		"Vine Whip",
		-50.0f, 0.0f, 0.0f,
		0.0f, 0.0f,
		resCache.bitmap("battle/vineWhip.png"), resCache.soundSample("battle/vineWhip.mp3")
	});

	return pokemon;
}


Pokemon createCharmander(ResourceCache& resCache) {
	Pokemon pokemon{
		"Charmander",
		resCache.bitmap("battle/enemyCharmander.png"), 
		0.0f, 0.0f,
		100.0f, 100.0f,
		60.0f, 60.0f,
		40.0f, 40.0f
	};
	pokemon.attacks = createBasicPokemonAttacks(resCache);
	pokemon.attacks.push_back(PokemonAttack{
		"Ember",
		-50.0f, 0.0f, 0.0f,
		0.0f, 0.0f,
		resCache.bitmap("battle/ember.png"), resCache.soundSample("battle/ember.mp3")
	});

	return pokemon;
}


std::unique_ptr<PokemonTrainer> createEnemy1(ResourceCache& resCache) {
	std::unique_ptr<PokemonTrainer> enemy{new PokemonTrainer{
		"Lance",
		resCache.bitmap("enemyLance.png"),  332.0f, 60.0f,
		resCache.bitmap("battle/enemyLance.png"),  0.0f, 0.0f,
		100.0f
	}};
	enemy->pokemons.push_back(createBulbasaur(resCache));
	enemy->pokemons.push_back(createCharmander(resCache));
	enemy->items.push_back(Item{ "Potion", 75.0f, 0.0f, 0.0f });
	return enemy;
}

std::unique_ptr<PokemonTrainer> createEnemy2(ResourceCache& resCache) {
	std::unique_ptr<PokemonTrainer> enemy{ new PokemonTrainer{
		"Lance",
		resCache.bitmap("enemyLance.png"),  332.0f, 60.0f,
		resCache.bitmap("battle/enemyLance.png"),  0.0f, 0.0f,
		100.0f
	} };
	enemy->pokemons.push_back(createGengar(resCache));
	enemy->pokemons.push_back(createBulbasaur(resCache));
	enemy->items.push_back(Item{ "Potion", 75.0f, 0.0f, 0.0f });
	return enemy;
}

std::unique_ptr<PokemonTrainer> createEnemy3(ResourceCache& resCache) {
	std::unique_ptr<PokemonTrainer> enemy{ new PokemonTrainer{
		"Lance",
		resCache.bitmap("enemyLance.png"),  332.0f, 60.0f,
		resCache.bitmap("battle/enemyLance.png"),  0.0f, 0.0f,
		100.0f
	} };
	enemy->pokemons.push_back(createArbok(resCache));
	enemy->pokemons.push_back(createCharmander(resCache));
	enemy->items.push_back(Item{ "Potion", 75.0f, 0.0f, 0.0f });
	return enemy;
}



int main()
{
	std::srand(std::time(nullptr));
	
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_native_dialog_addon();
	al_init_primitives_addon();
	al_init_image_addon();

	al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(10);

	game.display_init();
	game.keyboard_init();
	sprites_init();

	ALLEGRO_SAMPLE* song = al_load_sample("GameMusic.mp3");

	ALLEGRO_SAMPLE_INSTANCE* songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	ALLEGRO_BITMAP* player_worldbitmap = al_load_bitmap("player_temp.png");
	ALLEGRO_BITMAP* enemy_worldbitmap = al_load_bitmap("enemy_temp.png");
	ALLEGRO_BITMAP* portal_texture = al_load_bitmap("portal.png");
	ALLEGRO_BITMAP* item_potion = al_load_bitmap("potion.png");

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

	ResourceCache resCache;
	Battle battle{game, resCache};
	PokemonTrainer player{
		"Bonifacy",
		resCache.bitmap("enemyLance.png"),  0.0f, 0.0f,
		resCache.bitmap("battle/player.png"),  0.0f, 0.0f,
		100.0f
	};
	player.pokemons.push_back(createPikachu(resCache));
	player.pokemons.push_back(createSquirtle(resCache));
	player.items.push_back(Item{"Potion", 75.0f, 0.0f, 0.0f});

	std::unique_ptr<PokemonTrainer> enemy;

	//TileMap test1("test_tile_map_0.txt", 3, 3);
	//TileMap test2("test_tile_map_1.txt", 15, 15);
	TileMap test1;
	test1.LoadListOfMaps();
	//test1.LoadTileMap("test_tile_map_0.txt");

	bool redraw = true;
	bool done = false;

	enum GAMESTATE { MENU, WORLD, FIGHT, ENDSCREEN };
	enum MAP {OVERWORLD, DESERT, CAVE, ENDHALL};

	int state = -1;

	game.changeState(state, MENU);

	Player trainer(test1.getSpawnX(), test1.getSpawnY(), player_worldbitmap);
	Enemy enemy1(7 * block_size + offset, 22 * block_size, 1, DOWN, enemy_worldbitmap);
	Enemy enemy2(23 * block_size + offset, 9 * block_size, 0, DOWN, enemy_worldbitmap);
	Enemy enemy3(15 * block_size + offset, 26 * block_size, 0, RIGHT, enemy_worldbitmap);
	Enemy enemy4(1 * block_size + offset, 11 * block_size, 2, DOWN, enemy_worldbitmap);
	Enemy enemy5(20 * block_size + offset, 11 * block_size, 3, RIGHT, enemy_worldbitmap);
	Object portal(25, 5, portal_texture, PORTAL);
	Object potion(11, 7, item_potion, POTION);
	Object potion2(15, 28, item_potion, POTION);

	al_play_sample_instance(songInstance);

	//gameloop
	al_start_timer(timer);
	while (!done)
	{
		//update
		al_wait_for_event(queue, &event);
		switch (event.type)
		{
		case ALLEGRO_EVENT_TIMER:
			if (game.checkKeyDownOnce(ALLEGRO_KEY_ESCAPE)) 
			{ 
				std::cout << "DONE"; done = true; 
			}

			if (state == MENU)
			{
				if (game.checkKeyDownOnce(ALLEGRO_KEY_ENTER))
				{
					game.changeState(state, WORLD);
					test1.changeMap(OVERWORLD);
				}
			}

			else if (state == WORLD)
			{
				al_play_sample_instance(songInstance);
				trainer.update_player();
				if (test1.current() == OVERWORLD)
				{
					enemy1.update_enemy();
					if (enemy1.isEnemyColliding(trainer) == 1)
					{
						enemy = createEnemy1(resCache);
						battle.start(&player, enemy.get());
						enemy1.setONMAP(false);
						game.changeState(state, FIGHT);
						al_stop_sample_instance(songInstance);
					}
					enemy2.update_enemy();
					if (enemy2.isEnemyColliding(trainer) == 1)
					{
						enemy = createEnemy2(resCache);
						battle.start(&player, enemy.get());
						enemy2.setONMAP(false);
						game.changeState(state, FIGHT);
						al_stop_sample_instance(songInstance);
					}
				}
				else if(test1.current() == DESERT)
				{
					al_play_sample_instance(songInstance);
					enemy3.update_enemy();
					if (enemy3.isEnemyColliding(trainer) == 1)
					{
						enemy = createEnemy2(resCache);
						battle.start(&player, enemy.get());
						enemy3.setONMAP(false);
						game.changeState(state, FIGHT);
						al_stop_sample_instance(songInstance);
					}
					enemy4.update_enemy();
					if (enemy4.isEnemyColliding(trainer) == 1)
					{
						enemy = createEnemy1(resCache);
						battle.start(&player, enemy.get());
						enemy4.setONMAP(false);
						game.changeState(state, FIGHT);
						al_stop_sample_instance(songInstance);
					}
					enemy5.update_enemy();
					if (enemy5.isEnemyColliding(trainer) == 1)
					{
						enemy = createEnemy2(resCache);
						battle.start(&player, enemy.get());
						enemy5.setONMAP(false);
						game.changeState(state, FIGHT);
						al_stop_sample_instance(songInstance);
					}
				}

				if (test1.isTileColliding(trainer) == 1)
				{
					if (game.key[ALLEGRO_KEY_UP]) { trainer.setY(trainer.getY() + game.getMSpeed()); trainer.setDIR(UP); }
					else if (game.key[ALLEGRO_KEY_DOWN]) { trainer.setY(trainer.getY() - game.getMSpeed()); trainer.setDIR(DOWN); }
					else if (game.key[ALLEGRO_KEY_LEFT]) { trainer.setX(trainer.getX() + game.getMSpeed()); trainer.setDIR(LEFT); }
					else if (game.key[ALLEGRO_KEY_RIGHT]) { trainer.setX(trainer.getX() - game.getMSpeed()); trainer.setDIR(RIGHT); }
				}
				if (portal.isObjectColliding(trainer))
				{
					if (test1.current() == OVERWORLD)
					{
						test1.changeMap(DESERT);
						portal.changePos(13, 25);
						trainer.change_pos(15, 3, LEFT);
						potion.changePos(14, 3);
						potion.setONMAP(true);
					}
					else if (test1.current() == DESERT)
					{
						game.changeState(state, ENDSCREEN);
					}
				}
				if (potion.isObjectColliding(trainer))
				{
					player.items.push_back(Item{ "Potion", 75.0f, 0.0f, 0.0f });
					potion.setONMAP(false);
				}
				if (potion2.isObjectColliding(trainer))
				{
					player.items.push_back(Item{ "Potion", 75.0f, 0.0f, 0.0f });
					potion2.setONMAP(false);
				}
			}
			else if (state == FIGHT)
			{
				if (battle.isStarted())
				{
					battle.handleKeyboardEvents();
				}
				
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
					test1.changeMap(-1);
					portal.changePos(25, 5);
					enemy1.setONMAP(true);
					enemy2.setONMAP(true);
					enemy3.setONMAP(true);
					enemy4.setONMAP(true);
					enemy5.setONMAP(true);
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
				if (test1.current() == OVERWORLD)
				{
					al_clear_to_color(al_map_rgb(10, 50, 10));
					test1.DrawTileMap();
					if (enemy1.isThere())
						enemy1.draw_enemy();
					if (enemy2.isThere())
						enemy2.draw_enemy();
					if (portal.isThere())
						portal.drawObject();
					if (potion.isThere())
						potion.drawObject();
				}
				else if (test1.current() == DESERT)
				{
					al_clear_to_color(al_map_rgb(100, 50, 10));
					test1.DrawTileMap();
					if (enemy3.isThere())
						enemy3.draw_enemy();
					if (enemy4.isThere())
						enemy4.draw_enemy();
					if (enemy5.isThere())
						enemy5.draw_enemy();
					if (portal.isThere())
						portal.drawObject();
					if (potion.isThere())
						potion.drawObject();
					if (potion2.isThere())
						potion2.drawObject();
				}

				trainer.draw_player();
			}
			else if (state == FIGHT)
			{
				
				al_clear_to_color(al_map_rgb(255, 255, 255));
				if(battle.isStarting())
				{
					al_clear_to_color(al_map_rgb(0, 0, 0));
					test1.DrawTileMap();
					battle.updateStarting();
				}
				else if (battle.isStarted())
				{
					battle.update();
				}
				else
				{
					game.changeState(state, WORLD);
				}
			}
			else if (state == ENDSCREEN)
			{
				al_clear_to_color(al_map_rgb(100, 100, 100));
				al_draw_textf(font, al_map_rgb(255, 255, 255), game.getDispW() / 2, game.getDispH() / 2, 0, "MENU (SPACE)");
				trainer.change_pos(test1.getSpawnX(), test1.getSpawnY(), DOWN);
			}

			//informacje, które mog¹ siê przydaæ
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", trainer.getX(), trainer.getY());
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 10, 0, "Map: %i", test1.current());
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 20, 0, "Speed: %i", game.getMSpeed());
			al_draw_textf(font, al_map_rgb(255, 255, 255), (game.getDispW() - 100), (game.getDispH() - 20), 0, "%i x %i", game.info.x2, game.info.y2);
			al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 30, 0, "Direction: %i  0:DOWN 1:LEFT 2:RIGHT 3:UP", trainer.getDIR());

			game.display_post_draw();
			redraw = false;
		}
	}

	game.display_deinit();
	sprites_deinit();
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);
	return 0;
}