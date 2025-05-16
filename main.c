/* Linux, build: gcc "%f" -o "%e" -Wall -Wextra -lGL -lglfw -lm
   download: glfw 3.4
			 gcc 14
			 geany 2.0

   Windows, build: gcc "%f" -o "%e" -Wall -Wextra -I C:\glfw-3.4.bin.WIN64\include -L C:\glfw-3.4.bin.WIN64\lib-mingw-w64 -lglfw3dll -lopengl32
			run in terminal:  ./main-test.exe
   copy glfw3.dll from C:\glfw-3.4.bin.WIN64\lib-mingw-w64 to C:\Windows\System32
   download: glfw: glfw-3.4.bin.WIN64
			 gcc:  x86_64-15.1.0-release-win32-seh-ucrt-rt_v12-rev0
			 Setup your windows Path: in extended setup system/Variable environments/System variables
							   then select item: Path and click on button Change
							   button Add: C:\mingw64\bin
			 IDE:  geany-2.0_setup
*/
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

const unsigned int windowwidth = 800;
const unsigned int windowheight = 600;
const unsigned int pointSize = 5;
const unsigned int lineWidth = 2;
const float axesSize = 3.0;


//----- FUNCTIONS ------------------------------------------------------
void drawAxes();
void error(int error, const char * description);
void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear,
					GLdouble zFar );
void display(GLFWwindow * window);
int main();

//----------------------------------------------------------------------
void drawAxes(){
	glDisable(GL_TEXTURE_2D);
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-axesSize, 0.0, 0.0); glVertex3f(axesSize, 0.0, 0.0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, -axesSize, 0.0); glVertex3f(0.0, axesSize, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, -axesSize); glVertex3f(0.0, 0.0, axesSize);
	glEnd();	
}

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s (%d)\n", description, error);
}

void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar){
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;
	fH = tan( fovY / 360 * pi) * zNear;
	fW = fH * aspect;
	
	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void display(GLFWwindow * window){
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glClearColor(0.0, 0.0, 0.0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT); 
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspectiveGL(45.0, (float)width/height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0.0, -0.3, -5.0);
	glRotatef((float)glfwGetTime() * 50.f, 35.f, 20.f, 1.0f);
	
	// Draw List
	drawAxes();
}

int main(){
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(1);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    
	GLFWwindow * window = glfwCreateWindow(windowwidth, windowheight, "GLFW", NULL, NULL);

	if (!window){
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	      
	while (!glfwWindowShouldClose(window)){
		display(window);
		glfwSwapBuffers(window);
		
		// Key actions
		glfwPollEvents();		
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, GL_TRUE);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
