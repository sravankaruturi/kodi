#pragma once
#include <crtdbg.h>
#include <cstdint>
#include <GL/glew.h>

// https://www.gamedev.net/articles/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010

class Allocator
{

protected:

	void * start;
	size_t size;
	size_t usedMemory;
	size_t numberOfAllocations;

public:

	/* The allocator takes in the size of the memory block and the start memory address*/
	Allocator(size_t _size, void * _start)
	{
		start = _start;
		size = _size;
		usedMemory = 0;
		numberOfAllocations = 0;
	}

	virtual ~Allocator()
	{
		_ASSERT(numberOfAllocations == 0 && usedMemory == 0);
		start = nullptr;
		size = 0;
	}

	virtual void* Allocate(size_t _size, uint8_t _alignment = 4) = 0;
	virtual void DeAllocate(void * _pointer) = 0;
	void * GetStart() const { return start; }
	size_t GetSize() const { return size; }
	size_t GetUsedMemoory() const { return usedMemory; }
	size_t GetNumberOfAllocations() const { return numberOfAllocations; }
	
};

namespace kodi
{
	namespace allocator
	{
		template <class T> T* AllocateNew(Allocator& _allocator)
		{
			return new (_allocator.Allocate(sizeof(T), __alignof(T))) T;
		}

		template <class T> T* AllocateNew(Allocator& _allocator, const T& _t)
		{
			return new (_allocator.Allocate(sizeof(T), __alignof(T))) T(_t);
		}

		template <class T> void DeAllocateDelete(Allocator& _allocator, T& _object)
		{
			_object.~T();
			_allocator.DeAllocate(&_object);
		}

		template <class T> T* AllocateArray(Allocator& _allocator, size_t _length)
		{
			_ASSERT(_length != 0);

			uint8_t header_size = sizeof(size_t) / sizeof(T);

			if (sizeof(size_t) % sizeof(T) > 0) header_size += 1;

			// Allocate the extra space to store the array length in the bytes before the array...
			T* pointer = ((T*)_allocator.Allocate(sizeof(T) * (_length + header_size), __alignof(T))) + header_size;

			// Store the Length in there.
			*(((size_t*)p) - 1) = _length;

			for ( size_t i = 0 ; i < _length ; i++)
			{
				new (&pointer) T;
			}

			return pointer;
		}

		template <class T> void DeAllocateArray(Allocator& _allocator, T* _array)
		{
			_ASSERT(_array != nullptr);

			size_t length = *(((size_t*)_array) - 1);

			for (size_t i = 0; i < length; i++) {
				_array.~T();
			}

			uint8_t header_size = sizeof(size_t) / sizeof(T);
			if ( sizeof(size_t) % sizeof(T) > 0 )
			{
				header_size += 1;
			}
			_allocator.DeAllocate(_array - header_size);
		}
	}
}