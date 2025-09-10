#pragma warning(push)
#pragma warning(disable: 4275)
#include <SFML/Graphics.hpp>
#pragma warning(pop)

#include <iostream>
#include "graphic.hpp"
#include "settings.hpp"
#include "car.hpp"
#include "font.hpp"
#include "sound.hpp"
#include "test.hpp"
#include "lan.hpp"

void lan_config() {
  std::cout << "Game mode:\n";
  std::cout << "1 - Server/Single\n";
  std::cout << "2 - Client\n";
  std::string mode;
  std::getline(std::cin, mode);
  lan_start(mode == "1");
}

int main() {
    lan_config();
    load_settings();

    if (config["TEST"] == "1") {
        test();
        return 0;
    }

    // создать окно
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_X, WINDOW_Y)), GAME_NAME);
    window.setVerticalSyncEnabled(false); // выключить синхронизацию кадров экрана
    window.setFramerateLimit(MAX_FPS); // скорость игры
    sf::Clock clock;
    // проверка что окно создалось
	if (!window.setActive()) {
		std::cerr << "Failed to set the window as active" << std::endl;
		return EXIT_FAILURE;
	}

    load_fonts();
    load_textures();
    load_sounds();
    auto player = make_player();
    auto bot = make_bot();
    player.x = 100;
    player.y = 200;
    bot.x = 200;
    bot.y = 300;

    // главный цикл
    while (window.isOpen()) {
        if (game_work == false)
            break;

		// обработка событий
		while (auto event = window.pollEvent()) {
			// условия для выхода
			if (event->is<sf::Event::Closed>()) {
                game_work = false;
			}
		}

    // Выход через Esc
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
      game_work = false;

    float dt = clock.restart().asSeconds();
    update(player, dt);
    update_bot(bot, dt);
    collision_detect(player, bot);
    bound(player);
    bound(bot);
		window.clear(BG_COLOR); // заливка экрана
    draw(window, player, SCALE, player.anglerot);
    draw(window, bot, SCALE, bot.anglerot);
    draw_text(window, "hello", 50, 50, 50, sf::Color(255,255,0));
		window.display(); // показать кадр на экране
	}

  window.close();
}
