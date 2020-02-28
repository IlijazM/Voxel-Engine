#pragma once

#include "Types.h"

#include "PoolAllocator.h"
#include "AllocatedVariables.h"

#include "Renderer.h"

namespace LL {

	void launch() {
		initAllocatores();

		LLR::init();
	}

	void terminate() {
		LLR::terminate();

		terminateAllocatores();
	}
}