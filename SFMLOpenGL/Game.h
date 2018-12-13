#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "MyVector3.h"
#include "MyMatrix3.h"


using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void draw();
	void unload();
	void newlist();

	GLuint index;
	Clock clock;
	Time elapsed;

	float rotationAngleX = 0.0f;
	float rotationAngleY = 0.0f;
	float rotationAngleZ = 0.0f;

	MyVector3 startPoint[8];
	MyVector3 point[8];
	MyVector3 displacmentV;

};