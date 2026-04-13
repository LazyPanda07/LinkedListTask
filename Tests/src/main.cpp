#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

constexpr std::string_view reference = "0: \"apple\" => \"carrot\"\n1: \"banana\" => \"nullptr\"\n2: \"carrot\" => \"banana\"\n";

TEST(LinkedList, Add)
{
#ifdef __LINUX__
	std::system("./LinkedListTask to_file");
#else
	std::system("LinkedListTask.exe to_file");
#endif
	std::ifstream list("list.txt", std::ios_base::binary);

	ASSERT_EQ((std::ostringstream() << list.rdbuf()).str(), reference);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
