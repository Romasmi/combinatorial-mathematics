#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

template <class T>
void Print(const std::vector<T>& v)
{
	copy(v.begin(), v.end(), std::ostream_iterator<T>(std::cout, " "));
	std::cout << '\n';
}
