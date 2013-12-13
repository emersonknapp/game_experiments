#pragma once

#include <string>

namespace StringUtils
{
	bool endswith(std::string source, std::string ending)
	{
		if (source.length() >= ending.length())
		{
			return 0 == source.compare(source.length()-ending.length(), ending.length(), ending);
		}
		else
			return false;
	}

}