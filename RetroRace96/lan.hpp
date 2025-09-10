#pragma once
#include <vector>
#include <string>

using Message = std::string;
using Messages = std::vector<Message>;

void lan_start(bool im_server);
Messages get_messages();
void send_message(const Message& msg);
