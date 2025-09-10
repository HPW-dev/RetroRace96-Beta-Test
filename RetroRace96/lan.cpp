#include <SFML/Network.hpp>
#include <iostream>
#include "lan.hpp"

static const unsigned short SERVER_PORT = 50'400;
static std::optional<sf::IpAddress> target_ip {};
static unsigned short target_port {};
using Socket = sf::UdpSocket;
static Socket socket {};
static bool is_server {};

void lan_start(bool im_server) {
	is_server = im_server;

	if (im_server) {
		std::cout << "starting server...\n";
		if (socket.bind(SERVER_PORT) != sf::Socket::Status::Done) {
			std::cerr << "error while binding UDP socket\n";
			std::terminate();
		}
		std::cout << "server started\n";
	} else { // client
		std::cout << "starting client...\n";
		std::cout << "enter server ip << ";
		std::string ip;
		std::getline(std::cin, ip);
		target_ip = sf::IpAddress::resolve(ip);
		if (!target_ip) {
			std::cerr << "error while getting server ip address\n";
			std::terminate();
		}
		std::cout << "client started\n";
	}

	socket.setBlocking(false);
}

Messages get_messages() {
	Messages ret;

	while (true) {
		std::optional<sf::IpAddress> sender;
		unsigned short port;
		sf::Packet packet;

		if (socket.receive(packet, sender, port) != sf::Socket::Status::Done) {
			break;
		} else {
			if (is_server) {
				target_ip = sender;
				target_port = port;
			}

			std::string msg;
			while (packet >> msg) {
				ret.push_back(msg);
			}
		}
	} // while true

	return ret;
}

void send_message(const Message& msg) {
	sf::Packet packet;
	packet << msg;

	if (is_server) {
		if (!target_ip)
			return;
		if (socket.send(packet, *target_ip, target_port) != sf::Socket::Status::Done)
			std::cerr << "error while sending data to client\n";
	} else { // Client
		if (socket.send(packet, *target_ip, SERVER_PORT) != sf::Socket::Status::Done)
			std::cerr << "error while sending data to server\n";
	}
}

bool server_mode() { return is_server; }
