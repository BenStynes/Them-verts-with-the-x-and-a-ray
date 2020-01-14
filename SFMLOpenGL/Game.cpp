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



		for (int i = 0; i < 24; i += 3)
		{


			vector3 localvect{ initialVertices[i],initialVertices[i + 1] ,initialVertices[i + 2] };
			vector3 answerVector = matrix.RotationX(rotation.getX()) * localvect;
			vertices[i] = answerVector.getX();
			vertices[i + 1] = answerVector.getY();
			vertices[i + 2] = answerVector.getZ();


		}
		




		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
		{
			for (int i = 0; i < 24; i+=3)
			{
				vector3 localvect{ vertices[i],vertices[i + 1] ,vertices[i + 2] };
		       vector3 answerVector	= matrix.RotationY(rotationAngle) * localvect;
			   vertices[i] = answerVector.getX();
			   vertices[i + 1] = answerVector.getY();
			   vertices[i + 2] = answerVector.getZ();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			for (int i = 0; i < 24; i+=3)
			{

				vector3 localvect{ vertices[i],vertices[i + 1] ,vertices[i + 2] };
				vector3 answerVector = matrix.RotationZ(rotationAngle) * localvect;
				vertices[i] = answerVector.getX();
				vertices[i + 1] = answerVector.getY();
				vertices[i + 2] = answerVector.getZ();

			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			for (int i = 0; i < 24; i+=3)
			{
				float localZ = vertices[i + 2];
				vertices[i+ 2] = 1;
				vector3 localvect{ vertices[i],vertices[i + 1] ,vertices[i + 2] };
				vector3 answerVector = matrix.Translate(0, -0.2) * localvect;
				
				
				vertices[i] = answerVector.getX();
				vertices[i + 1] =  answerVector.getY();
				vertices[i + 2] =localZ;

			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			for (int i = 0; i < 24; i+=3)
			{
				float localZ = vertices[i + 2];
				vertices[i + 2] = 1;
				vector3 localvect{ vertices[i],vertices[i + 1] ,vertices[i + 2] };
				vector3 answerVector = matrix.Translate(0, 0.2) * localvect;


				vertices[i] = answerVector.getX();
				vertices[i + 1] = answerVector.getY();
				vertices[i + 2] = localZ;

			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			for (int i = 0; i < 24; i+=3)
			{
				float localZ = vertices[i + 2];
				vertices[i + 2] = 1;
				vector3 localvect{ vertices[i],vertices[i + 1] ,vertices[i + 2] };
				vector3 answerVector = matrix.Translate(0.2, 0) * localvect;


				vertices[i] = answerVector.getX();
				vertices[i + 1] = answerVector.getY();
				vertices[i + 2] = localZ;

			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			for (int i = 0; i < 24; i+=3)
			{
				float localZ = vertices[i + 2];
				vertices[i + 2] = 1;
				vector3 localvect{ vertices[i],vertices[i + 1] ,vertices[i + 2] };
				vector3 answerVector = matrix.Translate(-0.2, 0) * localvect;


				vertices[i] = answerVector.getX();
				vertices[i + 1] = answerVector.getY();
				vertices[i + 2] = localZ;

			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			for (int i = 0; i < 24; i+=3)
			{
				vector3 localvect{ vertices[i],vertices[i + 1] ,vertices[i + 2] };
				vector3 answerVector = matrix.Scale3D(101) * localvect;
				vertices[i] = answerVector.getX();
				vertices[i +1]= answerVector.getY();
				vertices[i+2] = answerVector.getZ();

			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			for (int i = 0; i < 24; i+=3)
			{
				vector3 localvect{ vertices[i],vertices[i + 1] ,vertices[i + 2] };
				vector3 answerVector = matrix.Scale3D(99) * localvect;
				vertices[i] = answerVector.getX();
				vertices[i + 1] = answerVector.getY();
				vertices[i + 2] = answerVector.getZ();
			}
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

