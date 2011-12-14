#include "mylib.h"

void clamp3i(int lower, int *arr3f, int higher)
{//clamp each value in a 1x3 array
	for(int i=0; i<3; i++)
		if(arr3f[i] < lower)
			arr3f[i]=lower;
		else if(arr3f[i] > higher)
			arr3f[i]=higher;
}

void clamp3f(float lower, float *arr3f, float higher)
{//clamp each value in a 1x3 array
	for(int i=0; i<3; i++)
		if(arr3f[i] < lower)
			arr3f[i]=lower;
		else if(arr3f[i] > higher)
			arr3f[i]=higher;
}

void clamp(float lower, float *val, float higher)
{//clamp a single value
	if(*val < lower)
		*val=lower;
	else if(*val > higher)
		*val=higher;

}

void multMatrices4x4(const GLfloat *A, GLfloat *B)
{
	float temp[16];

	temp[0] =A[0]*B[0] + A[4]*B[1] + A[8] *B[2] + A[12]*B[3];
	temp[1] =A[1]*B[0] + A[5]*B[1] + A[9] *B[2] + A[13]*B[3];
	temp[2] =A[2]*B[0] + A[6]*B[1] + A[10]*B[2] + A[14]*B[3];
	temp[3] =A[3]*B[0] + A[7]*B[1] + A[11]*B[2] + A[15]*B[3];

	temp[4] =A[0]*B[4] + A[4]*B[5] + A[8] *B[6] + A[12]*B[7];
	temp[5] =A[1]*B[4] + A[5]*B[5] + A[9] *B[6] + A[13]*B[7];
	temp[6] =A[2]*B[4] + A[6]*B[5] + A[10]*B[6] + A[14]*B[7];
	temp[7] =A[3]*B[4] + A[7]*B[5] + A[11]*B[6] + A[15]*B[7];

	temp[8] =A[0]*B[8] + A[4]*B[9] + A[8] *B[10] + A[12]*B[11];
	temp[9] =A[1]*B[8] + A[5]*B[9] + A[9] *B[10] + A[13]*B[11];
	temp[10]=A[2]*B[8] + A[6]*B[9] + A[10]*B[10] + A[14]*B[11];
	temp[11]=A[3]*B[8] + A[7]*B[9] + A[11]*B[10] + A[15]*B[11];
	
	temp[12]=A[0]*B[12] + A[4]*B[13] + A[8] *B[14] + A[12]*B[15];
	temp[13]=A[1]*B[12] + A[5]*B[13] + A[9] *B[14] + A[13]*B[15];
	temp[14]=A[2]*B[12] + A[6]*B[13] + A[10]*B[14] + A[14]*B[15];
	temp[15]=A[3]*B[12] + A[7]*B[13] + A[11]*B[14] + A[15]*B[15];

	for(int i=0; i< 16; i++)
		B[i]=temp[i];
}

void rotateMat4(float *matrix, float angle, int axis)
{
	/*switch(axis)
	{
		case AXIS_X:
			
	}*/
}

bool checkShaderCompileStatus(GLuint shader)
{//check for a failed compile, and print the log
	int status;
	
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		GLERR("glGetShaderiv shader compile status");

	if(status==GL_FALSE)
	{
		int loglength;
		char *log=NULL;
		
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &loglength);
			GLERR("glGetShaderiv GL_INFO_LOG_LENGTH");
		
		log=(char*)malloc(sizeof(char)*loglength);
		if(log)
		{
			glGetShaderInfoLog(shader, loglength, NULL, log);
				GLERR("glGetShaderInfoLog");
			printf("shader failed to compile: %s", log);
			free(log);
		}
		else
			printf("not enough memory to print info log");
	}	
	return true;
}

int checkProgramLinkStatus(GLuint program)
{
	//see if it linked properly
	{
		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
			GLERR("glGetProgramiv");

		if(status==GL_FALSE)
		{
			GLint loglength;
			char *log=NULL;	
			printf("Program linking failed\n");
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &loglength);
				GLERR("glGetProgramiv loglength");

			log=(char*)malloc(sizeof(char)*loglength);
			if(log)
			{
				glGetProgramInfoLog(program, loglength, NULL, log);
					GLERR("glGetProgramInfoLog");

				printf("program info log:%s\n", log);

				free(log);
			}
		}
	}
	return 0;
}

int loadShaderFromFile(const char* filename, GLuint *shader, GLuint shaderType)
{//load a shader from filename.
	FILE *file;
	char *source=NULL;
	int length;

	if(filename)
	{
		file=fopen(filename, "r");
		if(file)
		{
			fseek(file, 0, SEEK_END);
			length=ftell(file);
			source=(char*)malloc(sizeof(char)*(length+1));
			if(!source)
			{
				printf("not enough memory to load shader: %s\n", filename);
				fclose(file);
				return 1;
			}
			rewind(file);
			fread(source, 1, length, file);
			fclose(file);
			
			//NULL terminator for the shader source
			source[length]=0;
		}
		else
		{
			printf("couldn't find %s shader file: %s", shaderType==GL_VERTEX_SHADER ? "vertex" : "fragment", filename);
		}
		*shader= glCreateShader(shaderType);
			GLERR("glCreateShader");
		
		glShaderSource(*shader, 1, (const GLchar**)&source, NULL);
			GLERR("glShaderSource");

		glCompileShader(*shader);
			GLERR("glCompilerShader"); 
		checkShaderCompileStatus(*shader);
		free(source);
	}		
	else
		return 1;
	return 0;
}

int createProgramWith2Shaders(GLuint *program, GLuint *vert, GLuint *frag)
{
	//program
	*program=glCreateProgram();
		GLERR("glCreateProgram");

	glAttachShader(*program, *vert);
		GLERR("glAttachShader(vertex)");

	glAttachShader(*program, *frag);
		GLERR("glAttachShader(fragment)");

	//link and check for errors
	glLinkProgram(*program);
		GLERR("glLinkProgram");
	if(checkProgramLinkStatus(*program)) {printf("program failed to link\n"); return 1;}
		
	glUseProgram(*program);
		GLERR("glUseProgram");

	return 0;
}


