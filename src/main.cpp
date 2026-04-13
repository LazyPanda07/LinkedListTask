#include <iostream>
#include <fstream>

#include "LinkedList.hpp"

int main(int argc, char** argv) try
{
	std::ifstream in("inlet.in");

	if (!in.is_open())
	{
		throw std::runtime_error("Can't open inlet.in");
	}

	list::LinkedList list;
	std::string line;

	while (std::getline(in, line))
	{
		size_t delimiterIndex = line.find(';');
		int randIndex = std::stoi(line.substr(delimiterIndex + 1));

		list.addNode
		(
			std::string_view(line.data(), delimiterIndex),
			randIndex
		);
	}

	if (argc == 2 && std::string_view(argv[1]) == "to_file")
	{
		std::ofstream("list.txt", std::ios_base::binary) << list;
	}
	else
	{
		std::cout << list;
	}
	
	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;

	return 1;
}
