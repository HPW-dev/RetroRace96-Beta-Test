#include <sstream>
#include "util.hpp"

std::vector<std::string> split(const std::string& src, char separator) {
	std::vector<std::string> ret;
	std::string line;
	std::stringstream ss;
	ss << src;
	while (std::getline(ss, line, separator)) {
		ret.push_back(line);
	}
	return ret;
}
