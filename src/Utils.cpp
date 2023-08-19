#include "Utils.h"

std::string StrToLower(std::string str) {
	std::string copy_str = str;
	std::transform(copy_str.begin(), copy_str.end(), copy_str.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return copy_str;
}

std::string StrToUpper(std::string str) {
	std::string copy_str = str;
	std::transform(copy_str.begin(), copy_str.end(), copy_str.begin(),
		[](unsigned char c) { return std::toupper(c); });
	return copy_str;
}

Vector2 SumVector2(Vector2 a, Vector2 b) {
	return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 SubVector2(Vector2 a, Vector2 b) {
	return Vector2(a.x - b.x, a.y - b.y);
}