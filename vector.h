#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#define vector( T ) (T*)ft_vector_init( sizeof(T) )
#define vector_reserve( T, capacity ) (T*)(ft_vector_reserve( sizeof(T), capacity ) + 1)
#define vector_init_from( T, src, size ) (T*)ft_vector_init_from( src, size, sizeof(T) )

#define vector_shrink_to_fit( vec ) ft_vector_shrink_to_fit( (void**)&(vec) )
#define vector_insert( vec, val, index ) ft_vector_insert( (void**)&(vec), val, index )

#define vector_free( vec ) ft_vector_free( (void**) &(vec) )

#define vector_push( vec, value ) ft_vector_push_back( (void**) &(vec), (value) )
#define vector_push_back( vec, value ) ft_vector_push_back( (void**) &(vec), (value) )
#define vector_pop_back( vec, out ) vector_pop( vec, out )

typedef struct {
	size_t size;
	size_t capacity;
	size_t elsize;
} t_vector;

void *ft_vector_init( size_t );
void *ft_vector_init_from( const void *, size_t, size_t );

bool ft_vector_push_back( void**, const void* );
bool vector_pop( void*, void* );
bool ft_vector_insert( void**, const void*, size_t );

void ft_vector_free( void ** );

bool vector_empty( void* );
void vector_clear( void* );

size_t vector_size( void* );
size_t vector_capacity( void* );

bool ft_vector_shrink_to_fit( void** );
void ft_vector_free( void ** );
t_vector* ft_vector_reserve( size_t elsize, size_t capacity );