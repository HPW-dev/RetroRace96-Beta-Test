
#include "client.hpp"
#include "lan.hpp"
#include "util.hpp"
#include "graphic.hpp"

void client_update(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))   send_message("KEY:L");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))  send_message("KEY:R");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))     send_message("KEY:U");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))   send_message("KEY:D");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) send_message("KEY:N");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) send_message("EXIT");
}

void client_draw(sf::RenderWindow& window) {
	auto messages = get_messages();
	if (messages.empty())
		return;

	//window.clear();
	for (const auto& msg : messages) {
		auto params = split(msg, ':');

		if (params.at(0) == "TEXTURE") {
			const auto x = std::stod(params.at(1));
			const auto y = std::stod(params.at(2));
			const std::string skin = params.at(3);
			const auto scale = std::stod(params.at(4));
			const auto angle = std::stod(params.at(5));
			draw_texture(window, x, y, skin, scale, angle);
		}
	}
	window.display();
}
