#ifndef MYLIB_H
#define MYLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <CL/opencl.h>
#define GL_GLEXT_PROTOTYPES 1
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "errorcheck.h"

#define GLERR(X) if(CheckGLError(X, __LINE__, __FILE__))return 1;
#define SDLERR(X) SDLErrorAndDie(X, __LINE__, __FILE__)


#define fori0to3 for(int i=0; i<3; i++)
const float PI=3.14159265f;
#define RADS(x) ((x*PI/180.0f)) //convert degrees to radians

const int AXIS_X=0;
const int AXIS_Y=1;
const int AXIS_Z=2;

void clamp3f(float lower, float *arr3f, float higher);
void clamp3i(int lower, int *arr3f, int higher);
void clamp(float lower, float *val, float higher);

void multMatrices4x4(const GLfloat *A, GLfloat *B);
void rotateMat4(float *matrix, float angle, int axis);

bool checkShaderCompileStatus(GLuint shader);
int checkProgramLinkStatus(GLuint program);
int loadShaderFromFile(const char* filename, GLuint *shader, GLuint shaderType);
int createProgramWith2Shaders(GLuint *program, GLuint *vert, GLuint *frag);
#endif
