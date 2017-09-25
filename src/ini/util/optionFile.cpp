#include "optionFile.hpp"

OptionFile::OptionFile() {

}

OptionFile::~OptionFile() {

}

bool OptionFile::save(const std::string &filePath) {
	std::ofstream file(filePath.c_str(), std::ios::out | std::ios::trunc);

	if (!file) {
		std::cerr << "Erreur à l'ouverture !" << std::endl;
		return false;
	}

	for (const auto& n : options) {
		file << n.first << "=" << n.second << std::endl;
	}

	file.close();
	return true;
}

bool OptionFile::open(const std::string &filePath) {
	std::ifstream file(filePath.c_str(), std::ios::in);

	if (!file) {
		std::cerr << "Erreur à l'ouverture !" << std::endl;
		return false;
	}

	std::string line;

	std::string key;
	int value;

	while (std::getline(file, line)) {
		std::istringstream is_line(line);
		std::string key;
		if (std::getline(is_line, key, '='))
		{
			std::string value;
			if (std::getline(is_line, value))
				options[key] = value;
		}
	}

	file.close();
	return true;
}

void OptionFile::display() const {
	for (const auto& n : options) {
		std::cout << n.first << ": " << n.second << std::endl;
	}
}