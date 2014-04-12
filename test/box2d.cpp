#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

/** We need this to easily convert between pixel and real-world coordinates*/
static const float SCALE = 30.f;

//class member variable to keep track of three bodies
b2Body* bodies[3];

/** Create the base for the boxes to land */
void CreateGround(b2World& World, float X, float Y);

/** Create the boxes */
b2Body *CreateBox(b2World& World, int MouseX, int MouseY);

void FooTest();

b2World *m_world = new b2World(b2Vec2(0.f, 9.8f));

int main()
{
  /** Prepare the window */
  sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test");
  Window.setFramerateLimit(60);

  /** Prepare the world */
  b2Vec2 Gravity(0.f, 9.8f);
  b2World World(Gravity);
  // CreateGround(World, 400.f, 500.f);

  /** Prepare textures */
  sf::Texture GroundTexture;
  sf::Texture BoxTexture;
  GroundTexture.loadFromFile("ground.png");
  BoxTexture.loadFromFile("box.png");

  FooTest();

  while (Window.isOpen())
  {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
      bodies[0]->ApplyForce( b2Vec2(0,50), bodies[0]->GetWorldCenter() );
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      bodies[1]->ApplyLinearImpulse( b2Vec2(0,50), bodies[1]->GetWorldCenter() );
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
      bodies[2]->SetTransform( b2Vec2(10,20), 0 );

    World.Step(1/60.f, 8, 3);

    Window.clear(sf::Color::White);
    int BodyCount = 0;
    for (b2Body* BodyIterator = m_world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
    {
      if (BodyIterator->GetType() == b2_dynamicBody)
      {
	sf::Sprite Sprite;
	Sprite.setTexture(BoxTexture);
	Sprite.setOrigin(16.f, 16.f);
	Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
	Sprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
	Window.draw(Sprite);
	++BodyCount;
      }
      else
      {
	sf::Sprite GroundSprite;
	GroundSprite.setTexture(GroundTexture);
	GroundSprite.setOrigin(400.f, 8.f);
	GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
	GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
	Window.draw(GroundSprite);
      }
    }
    Window.display();
  }

  return 0;
}

void FooTest() {
  //body definition
  b2BodyDef myBodyDef;
  myBodyDef.type = b2_dynamicBody;

  //shape definition
  b2PolygonShape polygonShape;
  polygonShape.SetAsBox(1, 1); //a 2x2 rectangle

  //fixture definition
  b2FixtureDef myFixtureDef;
  myFixtureDef.shape = &polygonShape;
  myFixtureDef.density = 1;

  //create identical bodies in different positions
  for (int i = 0; i < 3; i++) {
    myBodyDef.position.Set(-10+i*10, 20);
    bodies[i] = m_world->CreateBody(&myBodyDef);
    bodies[i]->CreateFixture(&myFixtureDef);
  }

  //a static floor to drop things on
  myBodyDef.type = b2_staticBody;
  myBodyDef.position.Set(0, 0);
  // polygonShape.SetAsEdge( b2Vec2(-15,0), b2Vec2(15,0) );
  m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
}

b2Body *CreateBox(b2World& World, int MouseX, int MouseY)
{
  b2BodyDef BodyDef;
  BodyDef.position = b2Vec2(MouseX/SCALE, MouseY/SCALE);
  BodyDef.type = b2_dynamicBody;
  b2Body* Body = World.CreateBody(&BodyDef);

  b2PolygonShape Shape;
  Shape.SetAsBox((32.f/2)/SCALE, (32.f/2)/SCALE);
  b2FixtureDef FixtureDef;
  FixtureDef.density = 1.f;
  FixtureDef.friction = 0.7f;
  FixtureDef.shape = &Shape;
  Body->CreateFixture(&FixtureDef);
}

void CreateGround(b2World& World, float X, float Y)
{
  b2BodyDef BodyDef;
  BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
  BodyDef.type = b2_staticBody;
  b2Body* Body = World.CreateBody(&BodyDef);

  b2PolygonShape Shape;
  Shape.SetAsBox((800.f/2)/SCALE, (16.f/2)/SCALE);
  b2FixtureDef FixtureDef;
  FixtureDef.density = 0.f;
  FixtureDef.shape = &Shape;
  Body->CreateFixture(&FixtureDef);
}

