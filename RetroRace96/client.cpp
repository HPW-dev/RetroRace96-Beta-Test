
#include "client.hpp"
#include "lan.hpp"

void client_update(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))   send_message("KEY:L");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))  send_message("KEY:R");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))     send_message("KEY:U");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))   send_message("KEY:D");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) send_message("KEY:N");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) send_message("EXIT");
}

void client_draw(sf::RenderWindow& window) {
	// TODO
}
