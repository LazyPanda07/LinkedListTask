#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

void runLinkedListTask(const std::vector<std::string>& parameters = {});

TEST(LinkedList, Add)
{
	constexpr std::string_view reference = "0: \"apple\" => \"carrot\"\n1: \"banana\" => \"nullptr\"\n2: \"carrot\" => \"banana\"\n";

	runLinkedListTask({ "to_file_as_print" });

	std::ifstream list("list.txt", std::ios_base::binary);

	ASSERT_EQ((std::ostringstream() << list.rdbuf()).str(), reference);
}

TEST(LinkedList, Serialization)
{
	runLinkedListTask({ "serialize" });

	std::ifstream reference("reference_outlet.out", std::ios::binary);
	std::ifstream in("outlet.out", std::ios::binary);

	ASSERT_EQ((std::ostringstream() << reference.rdbuf()).str(), (std::ostringstream() << in.rdbuf()).str());
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

void runLinkedListTask(const std::vector<std::string>& parameters)
{
	std::string additionalParameters = " ";

	for (const std::string& parameter : parameters)
	{
		additionalParameters += parameter + ' ';
	}

	additionalParameters.pop_back();

#ifdef __LINUX__
	std::system(("./LinkedListTask" + additionalParameters).data());
#else
	std::system(("LinkedListTask.exe" + additionalParameters).data());
#endif
}
