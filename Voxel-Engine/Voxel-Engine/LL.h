#pragma once

#include "Types.h"
#include "PoolAllocator.h"

namespace LL {
	PoolAllocator<vec3_t> vec3_a;

	void log(vec3_t* vec) {
		std::cout << vec->x << " : " << vec->y << " : " << vec->z << std::endl;
	}

	void launch() {
		
		for (size_t i = 0; i < 1000; i++) {
			vec3_t* v1 = vec3_a.allocate();
		}

		for (size_t i = 0; i < 1000; i++) {
			vec3_t* v1 = vec3_a.allocate();
		}

		for (size_t i = 0; i < 1000; i++) {
			vec3_t* v1 = vec3_a.allocate();
		}

	}

}