#ifndef RESOLUTION_HPP_
#define RESOLUTION_HPP_

#include <iostream>

class Resolution
{
public:
	int width, height;
	

	Resolution(int t_width, int t_height);
	Resolution();
	Resolution operator+(Resolution t_other);
	Resolution operator-(Resolution t_other);
	Resolution operator*(Resolution t_other);
	Resolution operator/(Resolution t_other);
	bool operator==(Resolution t_other);
	bool operator!=(Resolution t_other);
	bool operator<(Resolution t_other);
	bool operator>(Resolution t_other);
	Resolution getAspectRatio();
	std::string getResolutionAsString();
};

#endif