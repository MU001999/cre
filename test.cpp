#include <iostream>
#include <cstdio>
#include <cassert>
#include "cre.hpp"


using namespace std;


void test_blank()
{
	assert(cre::match("", "") == 0);
	assert(cre::match("", "abcdefg") == 0);
}

void test_single_character()
{
	assert(cre::match("a", "a") == 0);
	assert(cre::match("a", "b") == 1);
	assert(cre::match("z", "z") == 0);
	assert(cre::match("z", "y") == 1);
	assert(cre::match("A", "A") == 0);
	assert(cre::match("A", "B") == 1);
	assert(cre::match("Z", "Z") == 0);
	assert(cre::match("Z", "Y") == 1);
	assert(cre::match("0", "0") == 0);
	assert(cre::match("0", "1") == 1);
	assert(cre::match("9", "9") == 0);
	assert(cre::match("9", "8") == 1);
}

void test_concatenate()
{
	assert(cre::match("ab", "ab") == 0);
	assert(cre::match("ab", "ac") == 1);
}

void test_select()
{
	assert(cre::match("a|b", "a") == 0);
	assert(cre::match("a|b", "b") == 0);
	assert(cre::match("ab|c", "ab") == 0);
	assert(cre::match("ab|c", "c") == 0);
}

void test_closure()
{
	assert(cre::match("a(b|c)*", "abbbbbc") == 0);
	assert(cre::match("a(b|c)*", "a") == 0);

	assert(cre::match("ab|c*", "ccc") == 0);

	assert(cre::match("abb*", "ab") == 0);
	assert(cre::match("abb*", "a") == 1);

	assert(cre::match("233+", "233") == 0);
	assert(cre::match("233+", "23") == 1);
}

void test_complex()
{
	auto pattern = cre::Pattern("(abcdefg|123456789)*|cyyzerono1|suchangdashabi|chaoqunlaogenb|(ab*c)");
	assert(pattern.match("abcdefgabcdefg") == 0);
	assert(pattern.match("12345668912345") == 1);
	assert(pattern.match("cyyzerono1") == 0);
	assert(pattern.match("cvvzerono1") == 1);
	assert(pattern.match("abbbbbbbbc") == 0);
	assert(pattern.match("ac") == 0);
}


int main(int argc, char *argv[])
{
	test_blank();
	test_single_character();
	test_concatenate();
	test_select();
	test_closure();
	test_complex();

	std::cout << "test pass" << std::endl;

	// system("pause"); // test on win.
	return 0;
}