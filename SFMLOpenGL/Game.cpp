#include <Game.h>

bool updatable = false;

MyVector3 v3;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube"),	
	startPoint{
		{ -1.0f, 1.0f, 1.0f },
		{ -1.0f, -1.0f, 1.0f },
		{ 1.0f, -1.0f, 1.0f },
		{ 1.0f, 1.0f, 1.0f },
		{ -1.0f, 1.0f, -1.0f },
		{ -1.0f, -1.0f, -1.0f },
		{ 1.0f, -1.0f, -1.0f },
		{ 1.0f, 1.0f, -1.0f }
	}
{
	for (int i = 0; i < 8; i++)
	{
		point[i] = startPoint[i];
	}
	index = glGenLists(1);
}

Game::~Game(){}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning)
	{

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Right)
				{
					rotationAngleY += 0.3f;

					if (rotationAngleY > 360.0f)
					{
						rotationAngleY -= 360.0f;
					}
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					rotationAngleX += 0.3f;

					if (rotationAngleX > 360.0f)
					{
						rotationAngleX -= 360.0f;
					}
				}
				else if (event.key.code == sf::Keyboard::Z)
				{
					rotationAngleZ += 0.3f;

					if (rotationAngleZ > 360.0f)
					{
						rotationAngleZ -= 360.0f;
					}
				}
			}
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	isRunning = true;
	displacmentV = { 0,0,-6 };

	//point[0] = { 1.0f, 1.0f, 1.0f };
	//point[1] = { 1.0f, 1.0f, -1.0f };
	//point[2] = { 1.0f, -1.0f, 1.0f };
	//point[3] = { 1.0f, -1.0f, -1.0f };
	//point[4] = { -1.0f, 1.0f, -1.0f };
	//point[5] = { -1.0f, 1.0f, 1.0f };
	//point[6] = { -1.0f, -1.0f, 1.0f };
	//point[7] = { -1.0f, -1.0f, -1.0f };

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	newlist();
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!updatable)
		{
			updatable = true;
		}
		else
			updatable = false;
	}


	for (int i = 0; i < 8; i++)
	{
		point[i] = MyMatrix3::rotationY(rotationAngleY) * startPoint[i];
		point[i] = MyMatrix3::rotationX(rotationAngleX) * point[i];
		point[i] = MyMatrix3::rotationZ(rotationAngleZ) * point[i];
		point[i] += displacmentV;
	}
	
}

void Game::draw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	newlist();

	glCallList(1);

	window.display();

}

void Game::unload()
{

}

void Game::newlist()
{
	glDeleteLists;

	glNewList(index, GL_COMPILE);
	glBegin(GL_QUADS);
	{
		//Back Face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(point[4].x, point[4].y, point[4].z);
		glVertex3f(point[5].x, point[5].y, point[5].z);
		glVertex3f(point[6].x, point[6].y, point[6].z);
		glVertex3f(point[7].x, point[7].y, point[7].z);


		//red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(point[7].x, point[7].y, point[7].z);
		glVertex3f(point[3].x, point[3].y, point[3].z);
		glVertex3f(point[0].x, point[0].y, point[0].z);
		glVertex3f(point[4].x, point[4].y, point[4].z);

		//yellow
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(point[2].x, point[2].y, point[2].z);
		glVertex3f(point[6].x, point[6].y, point[6].z);
		glVertex3f(point[5].x, point[5].y, point[5].z);
		glVertex3f(point[1].x, point[1].y, point[1].z);


		////pink
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(point[3].x, point[3].y, point[3].z);;
		glVertex3f(point[7].x, point[7].y, point[7].z);
		glVertex3f(point[6].x, point[6].y, point[6].z);
		glVertex3f(point[2].x, point[2].y, point[2].z);
		

		////white
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(point[0].x, point[0].y, point[0].z);
		glVertex3f(point[1].x, point[1].y, point[1].z);
		glVertex3f(point[5].x, point[5].y, point[5].z);
		glVertex3f(point[4].x, point[4].y, point[4].z);

		////Front Face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(point[0].x, point[0].y, point[0].z);
		glVertex3f(point[1].x, point[1].y, point[1].z);
		glVertex3f(point[2].x, point[2].y, point[2].z);
		glVertex3f(point[3].x, point[3].y, point[3].z);


		//Complete the faces of the Cube
	}
	glEnd();
	glEndList();
}

