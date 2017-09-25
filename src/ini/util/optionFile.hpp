#ifndef OPTIONFILE_HPP
# define OPTIONFILE_HPP

# include <iostream>
# include <unordered_map>
# include <fstream>
# include <sstream>
# include <string>

class OptionFile
{
public:
	OptionFile();
	~OptionFile();
	
	bool save(const std::string &filePath);
	bool open(const std::string &filePath);

	void display() const;

	std::unordered_map<std::string, std::string> &get() {
		return options;
	}
protected:
	std::unordered_map<std::string, std::string> options;
};

#endif // !OPTIONFILE_HPP