/*****************************************************************//**
 * @file   vector.h
 * @ingroup group_api
 * @brief  
 * 
 * @author RickNijhuis
 * @date   May 2022
 *********************************************************************/

 /**
 *@addtogroup group_api
 * @{
 */
#pragma once

#include "types.h"

#include <assert.h>

struct vector
{
	uint32_t size;
	uint32_t capacity;
	size_t data_size;
	void* data;
};

inline void vector_init(struct vector* vector, size_t data_size, uint32_t capacity)
{
	assert(vector);
	assert(data_size);

	if (capacity != 0)
	{
		vector->data = malloc(data_size * capacity);

		if (vector->data == NULL)
		{
			free(vector);
			return;
		}
	}

	vector->capacity = capacity;
	vector->data_size = data_size;
	vector->size = 0;
	vector->capacity = capacity;
}

inline struct vector* vector_create(size_t data_size, uint32_t capacity)
{
	assert(data_size);

	struct vector* vector = malloc(sizeof(*vector));

	if (vector == NULL)
		return NULL;

	vector_init(vector, data_size, capacity);

	return vector;
}

inline void vector_free(void* vector)
{
	free(((struct vector*)vector)->data);
	free(((struct vector*)vector));
}

inline void vector_reserve(struct vector* vector, uint32_t new_capacity)
{
	void* tmp = realloc(vector->data, vector->data_size * new_capacity);

	if (tmp)
	{
		vector->capacity = new_capacity;
		vector->data = tmp;
	}
}

inline void vector_resize(struct vector* vector, uint32_t new_count)
{
	if(vector->size > new_count)
		vector->size = new_count;
}

inline uint32_t vector_at(struct vector* vector, uint32_t index)
{
	if (!(index < vector->size))
		return 0;

	return index;
}

inline uint32_t vector_push_back(struct vector* vector)
{
	if (vector->size == vector->capacity)
		vector_reserve(vector, vector->size == 0 ? 1 : vector->size * 2);

	return vector->size++;
}

inline uint32_t vector_pop_back(struct vector* vector)
{
	if (vector->size == 0)
		return 0;

	return --vector->size;
}

inline uint32_t vector_assign(struct vector* vector, uint32_t index)
{
	assert(index < vector->size);
	return index;
}

#define VECTOR_DEFINE_TYPE(TYPE) VECTOR_DEFINE_NAME(TYPE, TYPE) 
#define VECTOR_DEFINE_NAME(TYPE, NAME)																\
struct vector_##NAME {																				\
	uint32_t size;																					\
	uint32_t capacity;																				\
	size_t	data_size;																				\
	TYPE *	data;																					\
};																									\
inline void vector_##NAME##_init(struct vector_##NAME *vector, uint32_t capacity)					\
{																									\
	vector_init((struct vector*)vector, sizeof(TYPE), capacity);									\
}																									\
inline struct vector_##NAME* vector_##NAME##_create(uint32_t capacity)								\
{																									\
	return (struct vector_##NAME *) vector_create(sizeof(TYPE), capacity);							\
}																									\
inline TYPE* vector_##NAME##_ptr_at(struct vector_##NAME *vector, uint32_t index)					\
{																									\
	return vector->data + vector_at((struct vector *)vector, index);								\
}																									\
inline TYPE vector_##NAME##_at(struct vector_##NAME *vector, uint32_t index)						\
{																									\
	return vector->data[vector_at((struct vector*)vector, index)];									\
}																									\
inline void vector_##NAME##_push_back(struct vector_##NAME *vector, TYPE value)						\
{																									\
	vector->data[vector_push_back((struct vector*)vector)] = value;									\
}																									\
inline TYPE* vector_##NAME##_emplace_back(struct vector_##NAME *vector)								\
{																									\
	return &vector->data[vector_push_back((struct vector*)vector)]; 								\
}																									\
inline void vector_##NAME##_assign(struct vector_##NAME *vector, uint32_t index, TYPE value)		\
{																									\
	vector->data[vector_assign((struct vector *)vector, index)] = value;							\
}																									\
inline void vector_##NAME##_pop_back(struct vector_##NAME *vector)									\
{																									\
	vector_pop_back((struct vector *) vector);														\
}																									\
inline void vector_##NAME##_clear(struct vector_##NAME* vector)										\
{																									\
	vector->size = 0;																				\
}																									\
inline TYPE vector_##NAME##_first(struct vector_##NAME* vector)										\
{																									\
	return vector->data[0];																			\
}																									\
inline TYPE vector_##NAME##_last(struct vector_##NAME* vector)										\
{																									\
	return vector->data[vector->size - 1];															\
}

/**@}*/
