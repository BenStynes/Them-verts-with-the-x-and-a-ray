#include <Game.h>

bool flip = false;
int current = 1;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube")
{

}

Game::~Game() {}


// Vertices for one Triangle
float initialVertices[] = { -1.0f,-1.0f,1.0f ,  1.0f,-1.0f,1.0f ,  1.0f,1.0f,1.0f ,
 -1.0f,1.0f,1.0f ,  -1.0f,-1.0f,-1.0f ,  1.0f,-1.0f,-1.0f ,
 1.0f,1.0f,-1.0f ,  -1.0f,1.0f,-1.0f };
Matrix3 matrix;
// Colors for those vertices
float colors[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };
float vertices[24];
// Index to be drawn
unsigned int vertex_index[] = { 0, 1, 2,
								2,3,0,
								4,7,6,
								6,5,4,
								3,2,6,
								6,7,3,
								4,5,1,
								1,0,4,
								1,5,6,
								6,2,1,
								0,3,7,
								7,4,0 
					
										
										};

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {


		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

void Game::initialize()
{
	isRunning = true;
	glEnable(GL_CULL_FACE);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0, 0, -8);
	for (int i = 0; i < 24; i++)
	{
		vertices[i] = initialVertices[i];
	}
}

void Game::update()
{
	elapsed = clock.getElapsedTime();
	if (elapsed.asSeconds() >= 1.0f / 60)
	{
		clock.restart();


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		{
			rotation.setX(rotation.getX() + rotationAngle);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			rotation.setY(rotation.getY() + rotationAngle);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			rotation.setZ(rotation.getZ() + rotationAngle);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			translation.setY(translation.getY() - 0.2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			translation.setY(translation.getY() + 0.2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			translation.setX(translation.getX() - 0.2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			translation.setX(translation.getX() + 0.2);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{ 
			scale+=10;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			scale -= 10;
		}

		Matrix3 identity{ 1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f };

		identity = identity * matrix.Scale(scale, scale);

		identity = identity * matrix.RotationX(rotation.getX());
		identity = identity * matrix.RotationY(rotation.getY());
		identity = identity * matrix.RotationZ(rotation.getZ());
		
		for (int i = 0; i < 24; i += 3)
		{


			vector3 localvect{ initialVertices[i],initialVertices[i + 1] ,initialVertices[i + 2] };
			vector3 answerVector = identity * localvect;
			vertices[i + 2] = answerVector.getZ();
			
			answerVector.setZ(1);
			vector3 secondAnswer = identity.Translate(translation.getX(), translation.getY()) * answerVector;
			vertices[i] = secondAnswer.getX();
			vertices[i + 1]=  secondAnswer.getY();

		}
				
		
	}

}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);

  //glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}

void Game::unload()
{
}

