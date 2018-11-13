#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

#define OK 0
#define ERROR -1

int exec(std::string command, std::vector <char> *data)
{
	char buffer = 0;
	FILE *output_file = NULL;

	output_file = popen(command.c_str(), "r");
	if (!output_file) {
		std::cout << "file_error" << std::endl;
		return ERROR;
	}

	while ((buffer = fgetc(output_file)) != EOF) {
		(*data).push_back(buffer);
	}

	return OK;
}

int files_end_with(std::string dir, std::string ending, std::vector <std::string> result)
{
	std::vector <char> data;
	std::vector <std::string> split_data;
	std::string str_buff;

	exec("find " + dir, &data);

	str_buff = std::string(data.begin(), data.end());
	
	// Divide into lines
	boost::split(
		split_data,
		str_buff,
		boost::is_any_of("\n")
	);
	
	for (std::vector<std::string>::iterator i = split_data.begin(); i != split_data.end(); ++i) {
		str_buff = std::string((*i).begin(), (*i).end());
		if (boost::algorithm::ends_with(str_buff, ending)) {
			result.push_back(str_buff);
		}
	}

	return OK;
}

int main()
{
	std::vector <std::string> c_files;

	files_end_with("$HOME", ".c", c_files);

	return 0;
}