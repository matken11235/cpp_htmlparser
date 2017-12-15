#include <iostream>
#include <string>
#include <vector>

#include "htmlparser.hpp"

int main(int argc, char const *argv[]) {
	std::string input{ "<p>What do you do?<okokokokoko</p>\t<p>I'm university student.</p>\n<span class=\"user\">matken</span>" };
	std::cout << "input: " << input << std::endl;
	std::cout << std::endl;

	std::cout << "====== START htmlparser::find ======" << std::endl;
	std::string result1;
	if ( htmlparser::find(input.begin(), input.end(), result1, "p") )
		std::cout << result1 << std::endl;
	std::cout << "====== END htmlparser::find ======" << std::endl;

	std::cout << std::endl;

	std::cout << "====== START htmlparser::find_all ======" << std::endl;
	std::vector<std::string> result2;
	if ( htmlparser::find_all(input.begin(), input.end(), result2, "p") )
		for (std::string& r : result2)
			std::cout << r << std::endl;
	std::cout << "====== END htmlparser::find_all ======" << std::endl;

	std::cout << std::endl;

	std::cout << "====== START htmlparser::find_all class_ ======" << std::endl;
	std::vector<std::string> result3;
	if ( htmlparser::find_all(input.begin(), input.end(), result3, "span", "user") )
		for (std::string& r : result3)
			std::cout << r << std::endl;
	std::cout << "====== END htmlparser::find_all class_ ======" << std::endl;

	return 0;
}
