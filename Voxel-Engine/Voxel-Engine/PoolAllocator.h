#pragma once

#include <iostream>

namespace LL {
	template <typename T>
	union PoolChunk {
		T value;
		PoolChunk<T>* nextPoolChunk;
	};

	template <typename T>
	class PoolAllocator {
	private:
		static const size_t POOLALLOCATORDEFAULTSIZE = 2048;

		size_t m_size = 0;

		PoolChunk<T>* m_data = nullptr;
		PoolChunk<T>* m_head = nullptr;

	public:
		explicit PoolAllocator(size_t size = POOLALLOCATORDEFAULTSIZE) 
		: m_size (size) {
			m_data = new PoolChunk<T>[size];
			m_head = m_data;

			for (size_t i = 0; i < m_size - 1; i++)
			{
				m_data[i].nextPoolChunk = &(m_data[i + 1]);
			}

			m_data[m_size - 1].nextPoolChunk = nullptr;
		}

		PoolAllocator(const PoolAllocator& other) = delete;
		PoolAllocator(const PoolAllocator&& other) = delete;
		PoolAllocator& operator=(const PoolAllocator& other) = delete;
		PoolAllocator& operator=(const PoolAllocator&& other) = delete;

		~PoolAllocator() {
			delete[] m_data;

			m_data = nullptr;
			m_head = nullptr;
		}

		template <typename... arguments>
		T* allocate(arguments&&... args) {
			if (m_head == nullptr) {
				
				return nullptr;
			}

			PoolChunk<T>* poolChunk = m_head;
			m_head = m_head->nextPoolChunk;

			T* retValue = new (std::addressof(poolChunk->value)) T(std::forward<arguments>(args)...);
			return retValue;
		}

		void deallocate(T* data) {
			data->~T();
			PoolChunk<T>* poolChunk = reinterpret_cast<PoolChunk<T>*>(data);
			poolChunk->nextPoolChunk = m_head;
			m_head = poolChunk;
		}
	};
}