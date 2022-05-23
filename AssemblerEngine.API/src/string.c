#include "core/string.h"

#include <string.h>
#include <stdlib.h>

struct string_header
{
	AE_STRING_SIZE_TYPE length;
	AE_STRING_SIZE_TYPE size;
	char buffer[1];
};

string string_create_empty(AE_STRING_SIZE_TYPE length)
{
	AE_STRING_SIZE_TYPE size = length + 1;
	struct string_header* header = malloc(sizeof(*header) + size);

	if (header)
	{
		header->buffer[0] = '\0';
		header->length = 0;
		header->size = size;
		return header->buffer;
	}

	return NULL;
}

string string_create(const char* str)
{
	if (!str)
		return NULL;

	AE_STRING_SIZE_TYPE size = (AE_STRING_SIZE_TYPE)strlen(str) + 1;

	struct string_header* header = malloc(sizeof(*header) + size);

	if (header)
	{
		memcpy(header->buffer, str, size);
		header->size = size;
		header->length = size - 1;

		return header->buffer;
	}

	return NULL;
}

string string_concat(string str1, string str2)
{
	if (!str1)
		return NULL;

	if (!str2)
		return NULL;

	AE_STRING_SIZE_TYPE length1 = string_get_length(str1);
	AE_STRING_SIZE_TYPE length2 = string_get_length(str2);
	AE_STRING_SIZE_TYPE size2 = length2 + 1;

	struct string_header* header = (struct string_header*)(str1 - sizeof(*header));
	struct string_header* tmp = realloc(str1 - sizeof(*tmp), sizeof(*tmp) + length1 + size2);

	if (tmp)
	{
		header = tmp;
		memcpy(header->buffer + length1, str2, length2);
		header->size = length1 + size2;
		header->length = length1 + length2;
		header->buffer[header->length] = '\0';

		return header->buffer;
	}

	return str1;
}

string string_append(string str, const char character)
{
	if (!str)
		return NULL;

	struct string_header* header = (struct string_header*)(str - sizeof(*header));

	if (header->length < header->size)
	{
		header->buffer[header->length] = character;
		header->buffer[++header->length] = '\0';
		return header->buffer;
	}

	return str;
}

string string_resize(string str, AE_STRING_SIZE_TYPE size)
{
	if (!str)
		return NULL;

	struct string_header* header = (struct string_header*)(str - sizeof(*header));
	struct string_header* tmp = realloc(header, sizeof(*header) + size);

	if (tmp)
	{
		header = tmp;
		header->size = size;
		return header->buffer;
	}

	return str;
}


string string_copy(string str)
{
	if (!str)
		return NULL;

	AE_STRING_SIZE_TYPE length = string_get_length(str);
	AE_STRING_SIZE_TYPE size = length + 1;

	struct string_header* header = malloc(sizeof(*header) + size);

	if (header)
	{
		memcpy(header->buffer, str, length);
		header->buffer[length] = '\0';
		header->size = size;
		header->length = length;

		return header->buffer;
	}

	return str;
}

string string_copy_to(string str, string dest)
{
	if (!str)
		return NULL;

	AE_STRING_SIZE_TYPE length = string_get_length(str);
	AE_STRING_SIZE_TYPE size = length + 1;

	struct string_header* header = realloc(dest, sizeof(*header) + size);

	if (header)
	{
		memcpy(header->buffer, str, length);
		header->buffer[length] = '\0';
		header->size = size;
		header->length = length;

		return header->buffer;
	}

	return str;
}

string string_substring(string str, AE_STRING_SIZE_TYPE startIndex, AE_STRING_SIZE_TYPE endIndex)
{
	if (!str)
		return NULL;

	AE_STRING_SIZE_TYPE length = endIndex - startIndex;

	if (length < 1)
		return NULL;

	AE_STRING_SIZE_TYPE size = length + 1;

	struct string_header* header = (struct string_header*)(str - sizeof(struct string_header));
	struct string_header* newHeader = malloc(sizeof(*newHeader) + size);

	if (newHeader)
	{
		memcpy(newHeader->buffer, header->buffer + startIndex, length);
		newHeader->buffer[length] = '\0';
		newHeader->length = length;
		newHeader->size = size;

		return newHeader->buffer;
	}

	return NULL;
}

bool string_is_null_or_empty(string str)
{
	return str ? (string_get_length(str) == 0 ? true : false) : true;
}

void string_free(string str)
{
	free(str - sizeof(struct string_header));
}

AE_STRING_SIZE_TYPE string_get_size(string str)
{
	return str ? ((struct string_header*)(str - sizeof(struct string_header)))->size : 0;
}

string string_set_length(string str, AE_STRING_SIZE_TYPE length)
{
	if (!str)
		return NULL;

	struct string_header* header = (struct string_header*)(str - sizeof(struct string_header));

	if (length < header->size)
		header->length = length;

	return str;
}

AE_STRING_SIZE_TYPE string_get_length(string str)
{
	return str ? ((struct string_header*)(str - sizeof(struct string_header)))->length : 0;
}