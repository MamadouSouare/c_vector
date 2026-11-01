#include <string.h>
#include <stdio.h>
#include "vector.h"

#define INITIAL_DEFAULT_CAPACITY 10

inline t_vector* ft_vector_reserve( size_t elsize, size_t capacity ) {
	t_vector *v = (t_vector*) malloc(sizeof(t_vector) + capacity*elsize);
	v->size 	= 0;
	v->capacity = capacity;
	v->elsize   = elsize;
	return v;
}

inline void *ft_vector_init( size_t elsize ) {
	t_vector *v = ft_vector_reserve( elsize, INITIAL_DEFAULT_CAPACITY );
	return v + 1;
}

void *ft_vector_init_from( const void *src, size_t size, size_t elsize )
{
	if( src == NULL ) return NULL;

	t_vector *v = ft_vector_reserve( elsize, size );
	memcpy( (void*)(v+1), src, elsize*size );
	v->size = size;
	v->elsize = elsize;
	return v+1;
}

inline size_t vector_size( void* data ) {
	return ((t_vector*)(data)-1)->size;
}

inline size_t vector_capacity( void* data ) {
	return ((t_vector*)(data)-1)->capacity;
}

inline void vector_clear( void* data ) {
	((t_vector*)(data)-1)->size = 0;
}

inline bool vector_empty( void* data ) {
	return ((t_vector*)(data)-1)->size == 0;
}

bool ft_vector_push_back( void** data, const void* value ) {
	t_vector *v = (t_vector*)(*data) - 1;
	if( v->size == v->capacity ) {
		v->capacity *= 1.5;
		t_vector *t = realloc( v, sizeof(t_vector) + v->elsize * v->capacity );
		if( t == NULL ) {
			return false;
		}
		v = t;
		*data = (void*)(v + 1);
	}
	unsigned char* pos = (unsigned char*) (*data + v->size * v->elsize);
	memcpy( pos, value, v->elsize );
	v->size++;
	return true;
}

bool ft_vector_insert( void** data, const void* value, size_t index ) {
	t_vector *v = (t_vector*)(*data) - 1;
	if( index > v->size ) return false;
	if( v->size == v->capacity ) {
		v->capacity *= 1.5;
		t_vector *t = realloc( v, sizeof(t_vector) + v->elsize * v->capacity );
		if( t == NULL ) {
			return false;
		}
		v = t;
		*data = (void*)(v + 1);
	}
	unsigned char* pos = (unsigned char*) (*data + index * v->elsize);
	memmove( pos+v->elsize, pos, v->elsize*(v->size-index) );
	memcpy( pos, value, v->elsize );
	v->size++;
	return true;
}

bool vector_pop( void* data, void* out) {
	t_vector *v = (t_vector*) data - 1;
	if( v->size == 0 ) return false;
	if( out != NULL ) {
		unsigned char* pos = (unsigned char*) (data + (v->size-1) * v->elsize);
		memcpy( out, pos, v->elsize );
	}
	v->size--;
	return true;
}

inline bool ft_vector_shrink_to_fit( void** data ) {
	t_vector *v = (t_vector*)(*data) - 1;
	if( v->size == 0 ) return false;
	t_vector *t = realloc( v, v->elsize * v->size );
	if( t == NULL ) return false;
	v = t;
	*data = v+1;
	v->capacity = v->size;
	return true;
}

void ft_vector_free( void **data ) {
	if( data == NULL || *data == NULL ) return ;
	t_vector *v = (t_vector*) (*data) - 1;
	v->size = 0;
	v->capacity = 0;
	free( v );
	*data = NULL;
}