#pragma once

#include "Types.h"

#include "PoolAllocator.h"
#include "AllocatedVariables.h"

#include "Renderer.h"

namespace LL {

	void launch() {
		initAllocatores();

		Renderer::init();
	}

	void terminate() {
		Renderer::terminate();

		terminateAllocatores();
	}
}