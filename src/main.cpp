#include <iostream>
#include <fstream>
#include <format>

#include "LinkedList.hpp"

list::LinkedList createLinkedListFromFile();

bool checkLinkedList(const std::unique_ptr<list::LinkedList>& list);

bool checkFile(const std::ofstream& file, std::string_view fileName);

int main(int argc, char** argv) try
{
	if (argc == 1)
	{
		std::unique_ptr<list::LinkedList> list;

		while (true)
		{
			std::cout << "Select action:" << std::endl;
			std::cout << "1: load LinkedList from inlet.in" << std::endl;
			std::cout << "2: print current LinkedList" << std::endl;
			std::cout << "3: save current LinkedList in out.txt file like print" << std::endl;
			std::cout << "4: save current LinkedList in outlet.out binary file" << std::endl;
			std::cout << "5: exit" << std::endl;

			int option;

			std::cin >> option;

			switch (option)
			{
			case 1:
				list = std::make_unique<list::LinkedList>(createLinkedListFromFile());

				break;

			case 2:
				if (!checkLinkedList(list))
				{
					break;
				}

				std::cout << *list;

				break;

			case 3:
				if (!checkLinkedList(list))
				{
					break;
				}

				{
					std::ofstream out("out.txt");

					if (!checkFile(out, "out.txt"))
					{
						break;
					}

					out << (std::ostringstream() << *list).str();
				}

				break;

			case 4:
			{
				std::ofstream out("outlet.out", std::ios_base::binary);

				if (!checkFile(out, "outlet.out"))
				{
					break;
				}

				out << *list;
			}

			break;

			case 5:
				return 0;

				break;

			default:
				std::cout << "Wrong option: " << option << std::endl;

				break;
			}

			std::cout << std::endl;
		}
	}
	else
	{
		list::LinkedList list = createLinkedListFromFile();

		if (std::string_view(argv[1]) == "to_file_as_print")
		{
			std::ostringstream stream;

			stream << list;

			std::ofstream("list.txt", std::ios_base::binary) << stream.str();
		}
		else if (std::string_view(argv[1]) == "serialize")
		{
			std::ofstream("outlet.out", std::ios_base::binary) << list;
		}
	}

	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;

	return 1;
}

list::LinkedList createLinkedListFromFile()
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

	return list;
}

bool checkLinkedList(const std::unique_ptr<list::LinkedList>& list)
{
	bool result = static_cast<bool>(list);

	if (!result)
	{
		std::cout << "LinkedList is invalid" << std::endl;
	}

	return result;
}

bool checkFile(const std::ofstream& file, std::string_view fileName)
{
	if (!file.is_open())
	{
		std::cout << std::format("Can't open {}", fileName) << std::endl;

		return false;
	}

	return true;
}
