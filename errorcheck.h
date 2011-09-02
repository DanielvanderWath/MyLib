#ifndef CHECK_ERROR_H
#define CHECK_ERROR_H

bool CheckMalloc(void *ptr, char *failMessage);
bool CheckGLError(char *string, int line, char *file);
void SDLErrorAndDie(char *string, int line, char *file);

#define CheckMalloc(A, B)	if(!A) \
				{ \
				printf("Failed to malloc %s\n", B); \
				return 1; \
				} \
				return 0; \
				


//ifndef CHECK_ERORR_H
#endif 
