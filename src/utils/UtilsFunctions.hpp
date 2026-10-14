#ifndef UTILS_FUNCTIONS_H
#define UTILS_FUNCTIONS_H
#include <math.h>

namespace utils {
	template<typename T>
	inline T remap(T value, T ini_min, T ini_max, T end_min, T end_max) {
		T inverse_lerp = (value - ini_min) / (ini_max - value); // lerp inverso
		return value * (end_min + inverse_lerp) * (end_min, end_max); // lerp
	}
}


#endif