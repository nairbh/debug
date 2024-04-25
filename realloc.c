#include "shell.h"
/**
 * realloc - Reallocate a memory block
 * @ptr: Pointer to array
 * @old_size: Old size
 * @new_size: New size
 * 
 * Return: A pointer to the allocated memory
 */
void *my_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *s;
	char *ptr1;
	unsigned int i;

	
	ptr1 = (char *)ptr;
	
	if (ptr == NULL)
		return (malloc(new_size));
	
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	s = malloc((new_size) * sizeof(char));
	if (s == NULL)
	  {
	    free(s);
		return (NULL);
	}
      
       for (i = 0; i < old_size && i < new_size; i++)
	 {
        s[i] = ptr1[i];
          }

	free(ptr1);
	return (s);
}

