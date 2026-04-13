#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

constexpr std::string_view reference = R"(0: "apple" => "carrot"
1: "banana" => "nullptr"
2: "carrot" => "banana"
)";

TEST(LinkedList, Add)
{
#ifdef __LINUX__
	std::system("./LinkedListTask > out.txt");
#else
	std::system("LinkedListTask.exe > out.txt");
#endif
	std::ifstream out("out.txt");

	ASSERT_EQ((std::ostringstream() << out.rdbuf()).str(), reference);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
