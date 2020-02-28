#pragma once

#include "Types.h"
#include "PoolAllocator.h"

namespace LL {

	PoolAllocator<vec2_t>* vec2_a;
	PoolAllocator<vec3_t>* vec3_a;
	PoolAllocator<vec4_t>* vec4_a;

	PoolAllocator<rgb_t>*	rgb_a;
	PoolAllocator<rgba_t>*	rgba_a;

	void initAllocatores() {
		vec2_a = new PoolAllocator<vec2_t>();
		vec3_a = new PoolAllocator<vec3_t>();
		vec4_a = new PoolAllocator<vec4_t>();

		rgb_a = new PoolAllocator<rgb_t>();
		rgba_a = new PoolAllocator<rgba_t>();
	}

	void terminateAllocatores() {
		delete vec2_a;
		delete vec3_a;
		delete vec4_a;
		
		delete rgb_a;
		delete rgba_a;
	}

}