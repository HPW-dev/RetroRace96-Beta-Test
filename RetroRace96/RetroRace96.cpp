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
#include "client.hpp"

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

    std::vector<Car> players;
    if (server_mode()) {
      players.push_back(make_player(true));
      players.push_back(make_player(false));
      players.push_back(make_bot());
      players.at(0).x = 100;
      players.at(0).y = 200;
      players.at(1).x = 200;
      players.at(1).y = 300;
      players.at(2).x = 300;
      players.at(2).y = 400;
    }

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

    if (server_mode()) {
      for (auto& p : players) {
        if (p.type == Type::server) update(p, dt);
        if (p.type == Type::client) update_client(p, dt);
        if (p.type == Type::bot) update_bot(p, dt);
        bound(p);
      }

      for (auto& a : players)
        for (auto& b : players) {
          if (&a == &b)
            continue;
          collision_detect(a, b);
        }
    } else {
      client_update(dt);
    }

    if (server_mode()) {
		  window.clear(BG_COLOR); // заливка экрана
      for (auto& p : players)
        draw(window, p, SCALE, p.anglerot);
		  window.display(); // показать кадр на экране
    } else {
      client_draw(window);
    }
	}

  window.close();
}
