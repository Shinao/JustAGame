#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <Box2D\Box2D.h>
#include <iostream>
#include <cmath>
#include "b2Separator.hh"
#include "gl.h"
#include <sstream>
#include <Thor/Particles.hpp>
#include <Thor/Animation.hpp>
#include <Thor/Graphics.hpp>
#include <Thor/Math.hpp>
#include <Thor/Time.hpp>
#include <Thor/Vectors.hpp>

class DebrisEmitter
{
  private:
    sf::Vector2f	mPosition;

  public:
    explicit DebrisEmitter(thor::EmissionInterface &system, sf::Vector2f position) : 
      mPosition(position)
  {
      sf::Vector2f		vector(1, 1);
      float			angle;
      int			nb_debris = 16;
      thor::Particle		particle;

      particle.position = mPosition;
      while (nb_debris-- > 0)
      {
	angle = thor::random(0, 360);
	thor::setPolarAngle(vector, angle);

	particle.rotation = angle;
	particle.rotationSpeed = thor::random(56.f, 256.f);
	float scale = thor::random(0.2f, 0.6f);
	particle.scale = sf::Vector2f(scale, scale);
	particle.velocity = vector * thor::random(40.f, 180.f);
	particle.totalLifetime = sf::milliseconds(thor::random(500, 1500) * (particle.scale.x + 0.4f));
	particle.textureIndex = thor::random(0, 9);

	system.emitParticle(particle);
      }
  }

    void operator() (thor::EmissionInterface& system, sf::Time dt)
    {
    }
};

class SparkEmitter
{
  private:
    sf::Vector2f	mPosition;

  public:
    explicit SparkEmitter(thor::EmissionInterface &system, sf::Vector2f position) : 
      mPosition(position)
  {
      sf::Vector2f		vector(1, 1);
      float			angle;
      int			nb_spark = 16;
      thor::Particle		particle;

      particle.position = mPosition;
      while (nb_spark-- > 0)
      {
	angle = thor::random(0, 360);
	thor::setPolarAngle(vector, angle - 180);

	particle.rotation = angle;
	particle.scale = sf::Vector2f(thor::random(0.2f, 0.6f), 0.5f);
	particle.velocity = vector * thor::random(60.f, 120.f);
	particle.totalLifetime = sf::milliseconds(thor::random(500, 1500) * (particle.scale.x + 0.4f));

	system.emitParticle(particle);
      }
  }

    void operator() (thor::EmissionInterface& system, sf::Time dt)
    {
    }
};


/** We need this to easily convert between pixel and real-world coordinates*/
static const float PIXELS_PER_METER = 32.f;
static const float BOX_HEIGHT = 1.f;
static const float BOX_WIDTH = 500.f;

sf::RectangleShape	shape_ground;
sf::Sprite		spr_ship;
sf::Sprite		spr_box;
sf::Sprite		spr_shader;
sf::Texture		tex_shader;
sf::Shader	shader;
sf::Sprite	spr;
sf::Texture	tex;
sf::Sprite	spr_explosion;
sf::Texture	tex_explosion;
bool		explosion = false;
sf::Clock	timer_explosion;
int		pos_explosion;
sf::Color pcolor(255, 0, 255);

void		loadShader();
void CreateGround(b2World& World, float X, float Y, float angle);
void CreateBox(b2World& World, int MouseX, int MouseY);
void createShip();
void drawShader();

b2Vec2 Gravity(0.f, 0.0f);
b2World World(Gravity);
sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test");
b2Body	*b_ship;
float torque = 88.5;
float global_time = 6;
bool debugShader[10] = { false };

class ShockAffector
{
  public:
    void operator() (thor::Particle& particle, sf::Time dt) 
    {
      std::cout << "affecotr" << std::endl;
    }
};

int main()
{
  Window.setMouseCursorVisible(false);

  sf::Texture		tex_particle;
  tex_particle.loadFromFile("particles.jpg");
  sf::Texture		tex_spark;
  tex_spark.loadFromFile("spark.png");

  // auto distri = thor::Distributions::uniform(0, 4);
  // for (int i = 0; i < 10; ++i)
  //   std::cout << distri() << std::endl;

  // auto distri_swap = thor::Distributions::uniform(10, 14);
  // distri.swap(distri_swap);

  // std::cout << "Error:" << std::endl;
  // for (int i = 0; i < 10; ++i)
  //   std::cout << distri_swap() << std::endl;

  // PMotor
  thor::ParticleSystem	ps_pmotor;
  ps_pmotor.setTexture(tex_spark);
  thor::UniversalEmitter pmotor_emitter;
  sf::Time pmotor_duration = sf::milliseconds(300);
  thor::FadeAnimation fader_pmotor(0.0f, 0.5f);
  ps_pmotor.addAffector(thor::AnimationAffector(thor::refAnimation(fader_pmotor)));
  ps_pmotor.addAffector(thor::ScaleAffector(sf::Vector2f(-0.8f, -0.8f)));
  thor::ForceAffector force_pmotor(sf::Vector2f(0.0f, 844.8f));
  ps_pmotor.addAffector(thor::refAffector(force_pmotor));
  pmotor_emitter.setParticleScale(sf::Vector2f(0.4, 0.4));
  pmotor_emitter.setParticleLifetime(sf::milliseconds(350));
  pmotor_emitter.setParticleColor(sf::Color(180, 50, 0));

  // SMotor
  thor::ParticleSystem	ps_smotor;
  ps_smotor.setTexture(tex_spark);
  thor::UniversalEmitter smotor_emitter;
  sf::Time smotor_duration = sf::milliseconds(200);
  thor::FadeAnimation fader_smotor(0.0f, 0.6f);
  ps_smotor.addAffector(thor::AnimationAffector(thor::refAnimation(fader_smotor)));
  ps_smotor.addAffector(thor::ScaleAffector(sf::Vector2f(0.4f, 0.4f)));
  thor::ForceAffector force_smotor(sf::Vector2f(0.0f, 600.0f));
  ps_smotor.addAffector(thor::refAffector(force_smotor));
  smotor_emitter.setParticleScale(sf::Vector2f(0.05, 0.05));
  smotor_emitter.setParticleLifetime(sf::milliseconds(300));
  smotor_emitter.setParticleColor(sf::Color(80, 80, 80));
   
  // Flash
  thor::ParticleSystem	ps_flash;
  ps_flash.setTexture(tex_particle);
  ps_flash.addTextureRect(sf::IntRect(212, 0, 106, 106));
  ps_flash.addTextureRect(sf::IntRect(318, 0, 106, 106));
  ps_flash.addTextureRect(sf::IntRect(212, 106, 106, 106));
  ps_flash.addTextureRect(sf::IntRect(318, 106, 106, 106));
  ps_flash.addAffector([] (thor::Particle& particle, sf::Time dt) {
      if (thor::getRemainingRatio(particle) > 0.5f)
      particle.scale += sf::Vector2f(dt.asMilliseconds() / 100.f, dt.asMilliseconds() / 100.f);
      else
      particle.scale -= sf::Vector2f(dt.asMilliseconds() / 120.f, dt.asMilliseconds() / 120.f);
      });
  sf::Time flash_duration = sf::milliseconds(200);
  sf::Clock	pclock;
  thor::UniversalEmitter flash_emitter;
  flash_emitter.setParticleTextureIndex(thor::Distributions::uniform(0, 3));
  flash_emitter.setEmissionRate(16);
  flash_emitter.setParticleScale(sf::Vector2f(0.8, 0.8));
  flash_emitter.setParticleLifetime(flash_duration);
  flash_emitter.setParticleRotation(thor::Distributions::uniform(0, 360));
  flash_emitter.setParticleColor(sf::Color(150, 90, 0));

  thor::ColorGradient gradient;
  gradient[0.0f] = sf::Color(180, 50, 0);
  gradient[0.5f] = sf::Color(180, 50, 0);
  gradient[1.0f] = pcolor;
  thor::ColorAnimation colorer(gradient);

  // Smoke
  thor::ParticleSystem	ps_smoke;
  ps_smoke.setTexture(tex_particle);
  thor::UniversalEmitter smoke_emitter;
  sf::Time smoke_duration = sf::milliseconds(500);
  ps_smoke.addTextureRect(sf::IntRect(0, 0, 106, 106));
  ps_smoke.addTextureRect(sf::IntRect(106, 0, 106, 106));
  ps_smoke.addTextureRect(sf::IntRect(0, 106, 106, 106));
  ps_smoke.addTextureRect(sf::IntRect(106, 106, 106, 106));
  ps_smoke.addAffector(thor::AnimationAffector(colorer));
  thor::FadeAnimation fader_smoke(0.1f, 0.5f);
  ps_smoke.addAffector(thor::AnimationAffector(thor::refAnimation(fader_smoke)));
  ps_smoke.addAffector(thor::ScaleAffector(sf::Vector2f(1.8f, 1.8f)));
  smoke_emitter.setParticleTextureIndex(thor::Distributions::uniform(0, 3));
  smoke_emitter.setEmissionRate(16);
  smoke_emitter.setParticleScale(sf::Vector2f(2, 2));
  smoke_emitter.setParticleLifetime(smoke_duration);
  smoke_emitter.setParticleRotation(thor::Distributions::uniform(0, 360));
  smoke_emitter.setParticleColor(sf::Color(180, 50, 0));

  // Shock
  thor::ParticleSystem	ps_shock;
  ps_shock.setTexture(tex_particle);
  sf::Time shock_duration = sf::milliseconds(750);
  ps_shock.addTextureRect(sf::IntRect(318, 212, 106, 106));
  ps_shock.addAffector(thor::AnimationAffector(colorer));
  thor::FadeAnimation fader_shock(0.1f, 0.8f);
  ps_shock.addAffector(thor::AnimationAffector(thor::refAnimation(fader_shock)));
  ps_shock.addAffector(thor::ScaleAffector(sf::Vector2f(3.5f, 3.5f)));
  thor::UniversalEmitter shock_emitter;
  shock_emitter.setEmissionRate(0);
  shock_emitter.setParticleScale(sf::Vector2f(1.4f, 1.4f));
  shock_emitter.setParticleLifetime(shock_duration);
  shock_emitter.setParticleRotation(thor::Distributions::uniform(0, 360));

  // Spark
  thor::ParticleSystem	ps_spark;
  ps_spark.setTexture(tex_particle);
  ps_spark.addTextureRect(sf::IntRect(321, 370, 106, 6));
  ps_spark.addAffector(thor::AnimationAffector(colorer));
  thor::FadeAnimation fader_spark(0.1f, 0.6f);
  ps_spark.addAffector(thor::AnimationAffector(thor::refAnimation(fader_spark)));

  // Steam
  thor::ParticleSystem	ps_steam;
  ps_steam.setTexture(tex_particle);
  thor::UniversalEmitter steam_emitter;
  sf::Time steam_duration = sf::milliseconds(560);
  ps_steam.addTextureRect(sf::IntRect(216, 318, 100, 106));
  ps_steam.addAffector(thor::AnimationAffector(colorer));
  thor::FadeAnimation fader_steam(0.1f, 0.5f);
  ps_steam.addAffector(thor::AnimationAffector(thor::refAnimation(fader_steam)));
  ps_steam.addAffector(thor::ScaleAffector(sf::Vector2f(1.8f, 1.8f)));
  steam_emitter.setEmissionRate(8);
  steam_emitter.setParticleScale(sf::Vector2f(1.3f, 1.3f));
  steam_emitter.setParticleLifetime(steam_duration);
  steam_emitter.setParticleRotation(thor::Distributions::uniform(0, 360));

  // Debris
  thor::ParticleSystem	ps_debris;
  sf::Time debris_duration = sf::milliseconds(750);
  for (int x = 212; x < 328; x += 35)
    for (int y = 212; y < 328; y += 35)
      ps_debris.addTextureRect(sf::IntRect(x, y, 35, 35));
  // thor::UniversalEmitter debris_emitter;
  // debris_emitter.setParticleTextureIndex(thor::Distributions::uniform(0, 9));
  ps_debris.setTexture(tex_particle);
  ps_debris.addAffector(thor::AnimationAffector(colorer));
  thor::FadeAnimation fader_debris(0.1f, 0.5f);
  ps_debris.addAffector(thor::AnimationAffector(thor::refAnimation(fader_debris)));
  // ps_debris.addAffector(thor::ScaleAffector(sf::Vector2f(1.2f, 1.2f)));
  // ps_debris.addAffector(thor::ForceAffector(sf::Vector2f(281.4f, 281.4f)));
  // ps_debris.addAffector(thor::TorqueAffector(284.f));
  // debris_emitter.setEmissionRate(8);
  // debris_emitter.setParticleScale(sf::Vector2f(0.4f, 0.4f));
  // debris_emitter.setParticleLifetime(debris_duration);
  // debris_emitter.setParticleRotation(thor::Distributions::uniform(0, 360));


  if (!tex_explosion.loadFromFile("explosion4.png"))
    std::cout << "cancer" << std::endl;
  spr_explosion.setTexture(tex_explosion);
  // Window.setFramerateLimit(60);
  std::srand(std::time(0));

  // Particle liquidfun
  const b2ParticleSystemDef particleSystemDef;
  b2ParticleSystem	*m_particleSystem = World.CreateParticleSystem(&particleSystemDef);

  float radius = 0.1;
  m_particleSystem->SetGravityScale(0.0f);
  m_particleSystem->SetDensity(0.1f);
  m_particleSystem->SetRadius(radius);

  float explo = 4.f;
  b2CircleShape shape;
  shape.m_radius = explo;

  b2ParticleGroupDef pd;
  pd.flags = b2_waterParticle;
  pd.shape = &shape;
  b2ParticleColor m_origColor;
  m_origColor.Set(rand() % 256, rand() % 256, rand() % 256, 255);
  pd.color = m_origColor;
  //

  /** Prepare textures */
  // CreateGround(World, 550.f, 675.f, 0.f);
  // CreateGround(World, 300.f, 850.f / 2, 90 * b2_pi / 180);
  // CreateGround(World, 800.f, 850.f / 2, 90 * b2_pi / 180);
  // CreateGround(World, 550.f, 350.f / 2, 180 * b2_pi / 180);
  sf::Texture GroundTexture;
  sf::Texture BoxTexture;
  GroundTexture.loadFromFile("ground.png");
  BoxTexture.loadFromFile("box.png");
  sf::Vector2i	camera;
  sf::Event	event;
  sf::Clock	timer;
  sf::Clock	b2_timer;
  int		fps = 0;
  bool		display = true;

  shape_ground.setSize(sf::Vector2f(BOX_WIDTH, BOX_HEIGHT));
  shape_ground.setFillColor(sf::Color(0, 200, 0 , 100));
  shape_ground.setOrigin(BOX_WIDTH / 2, BOX_HEIGHT / 2);

  sf::Texture tex1;
  tex1.loadFromFile("ship.png");
  spr_ship.setTexture(tex1);
  spr_ship.setColor(pcolor);
  spr_ship.setScale(sf::Vector2f(0.4f, 0.4f));

  sf::Texture tex2;
  tex2.loadFromFile("box.png");
  spr_box.setTexture(tex2);
  spr_box.setOrigin(tex2.getSize().x / 2, tex2.getSize().y / 2);
  spr_box.setColor(sf::Color(255, 255, 255, 10));

  sf::CircleShape circle;
  circle.setRadius(radius * PIXELS_PER_METER);
  circle.setOrigin(radius * PIXELS_PER_METER, radius * PIXELS_PER_METER);
  circle.setFillColor(sf::Color(200, 0, 0, 100));
  sf::Clock	timer_turn;

  createShip();

  sf::Vector2i old_camera;
  sf::Vector2i old_ship;


  bool	up = true;
  bool refreshed = true;
  loadShader();

  std::cout << sf::Texture::getMaximumSize() << std::endl;

  while (Window.isOpen())
  {
    Window.clear(sf::Color(50, 50, 50));

    if (b2_timer.getElapsedTime().asMilliseconds() > 1000 / 60)
    {
      // if (up && global_time > 16.01)
      // up = false;
      // else if (!up && global_time < 15.99)
      // up = true;
      // if (up)
      // global_time += 0.0002;
      // else
      // global_time -= 0.0002;

      global_time += 0.1;
      shader.setParameter("iGlobalTime", global_time);

      World.Step(1/60.f, 18, 3);
      b2_timer.restart();

      refreshed = true;
    }


    spr_ship.setOrigin(0, 0);

    // Camera and stuff
    sf::CircleShape	cursor_shape(4);
    cursor_shape.setOutlineColor(pcolor);
    cursor_shape.setFillColor(sf::Color::Transparent);
    cursor_shape.setOutlineThickness(1);
    sf::Vector2i cursor = sf::Mouse::getPosition(Window);
    cursor_shape.setPosition(cursor.x - 2, cursor.y - 2);
    sf::Vector2i padding_cursor = cursor;
    padding_cursor -= sf::Vector2i(Window.getSize().x / 2.f, Window.getSize().y / 2.f);
    sf::Vector2i cursor_sign(padding_cursor.x > 0 ? 1 : -1, padding_cursor.y > 0 ? 1 : -1); 
    padding_cursor = sf::Vector2i(std::abs(padding_cursor.x), std::abs(padding_cursor.y));

    // Using the center of mass as origin
    camera = sf::Vector2i(b_ship->GetWorldCenter().x * PIXELS_PER_METER - Window.getSize().x / 2,
	b_ship->GetWorldCenter().y * PIXELS_PER_METER - Window.getSize().y / 2);

    // Making the camera progressive
    padding_cursor = sf::Vector2i(padding_cursor.x / 1.5, padding_cursor.y / 1.5);

    // Pad the camera from the cursor
    if (padding_cursor.x > 0)
      camera.x += padding_cursor.x * cursor_sign.x;
    if (padding_cursor.y > 0)
      camera.y += padding_cursor.y * cursor_sign.y;

    if (display)
    {
      std::cout << "Ship POS: " << b_ship->GetWorldCenter().x * PIXELS_PER_METER << " / " << b_ship->GetWorldCenter().y * PIXELS_PER_METER << std::endl;
      std::cout << "Ship SIZE: " << spr_ship.getGlobalBounds().width << " / " << spr_ship.getGlobalBounds().height << std::endl;
      std::cout << "Cursor POS: " << cursor.x << " / " << cursor.y << std::endl;
      std::cout << "Camera POS: " << camera.x << " / " << camera.y << std::endl << std::endl;
    }


    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    //   camera.y += 1;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    //   camera.y -= 1;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    //   camera.x += 1;
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    //   camera.x -= 1;


    shader.setParameter("iCamera", camera.x, camera.y * -1);
    Window.draw(spr, &shader);

    if (timer.getElapsedTime().asSeconds() > 1)
    {
      timer.restart();
      std::cout << fps << std::endl;
      fps = 0;
      display = true;
    }
    else
    {
      ++fps;
      display = false;
    }


    while (Window.pollEvent(event))
      if (event.type == sf::Event::MouseMoved)
      {
	sf::Vector2i	cur = sf::Mouse::getPosition(Window);

	// camera = sf::Vector2i(cur.x % Window.getSize().x / 2 * -1, cur.y % Window.getSize().y / 2 * -1);
      }
      else if (event.type == sf::Event::GainedFocus)
	loadShader();
      else if (event.type == sf::Event::KeyPressed && event.key.code >= sf::Keyboard::Numpad0 && event.key.code <= sf::Keyboard::Numpad9)
      {
	int num = event.key.code - sf::Keyboard::Numpad0;
	std::stringstream	ss;
	ss  << "iDebug[" << num << "]";
	debugShader[num] = !debugShader[num];
	shader.setParameter(ss.str(), debugShader[num]);
      }
      else if (event.type == sf::Event::Closed)
	return (0);
      else if (event.type == sf::Event::MouseButtonPressed)
      {
	int MouseX = sf::Mouse::getPosition(Window).x;
	int MouseY = sf::Mouse::getPosition(Window).y;

	shock_emitter.setParticlePosition(sf::Vector2f(MouseX, MouseY));
	shock_emitter.emitParticle(ps_shock);
	flash_emitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(MouseX, MouseY), 0));
	ps_flash.addEmitter(thor::refEmitter(flash_emitter), flash_duration);
	smoke_emitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(MouseX, MouseY), 0));
	ps_smoke.addEmitter(thor::refEmitter(smoke_emitter), smoke_duration);
	SparkEmitter(ps_spark, sf::Vector2f(MouseX, MouseY));
	steam_emitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(MouseX, MouseY), 4));
	ps_steam.addEmitter(thor::refEmitter(steam_emitter), steam_duration);
	DebrisEmitter(ps_debris, sf::Vector2f(MouseX, MouseY));

	// shader.setParameter("center", (float) sf::Mouse::getPosition(Window).x / tex.getSize().x, (float) sf::Mouse::getPosition(Window).y / tex.getSize().y);
	// global_time = 0;

	// explosion = true;
	// timer_explosion.restart();
	// pos_explosion = 0;
	// spr_explosion.setPosition(sf::Mouse::getPosition(Window).x - 123, sf::Mouse::getPosition(Window).y - 123);

	// pd.position.Set(MouseX / PIXELS_PER_METER, MouseY / PIXELS_PER_METER);

	// for (int i = 0; i < 100; ++i)
	//   CreateBox(World, MouseX, MouseY);

	// Create a circle full of particles
	// b2ParticleGroup *m_pg = m_particleSystem->CreateParticleGroup(pd);
      }

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
    {
      timer_turn.restart();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	b_ship->SetAngularVelocity(-2.f);
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	b_ship->SetAngularVelocity(2.f);
      // Change Motor force
      b2Vec2 vec = b2Rot(b_ship->GetAngle()).GetYAxis() * 600;
      force_smotor.setAcceleration(sf::Vector2f(vec.x, vec.y));
      force_pmotor.setAcceleration(sf::Vector2f(vec.x, vec.y));
    }
    else
      b_ship->SetAngularVelocity(0.f);

    if (refreshed)
    {
      int forward_speed = 100;
      int backward_speed = 20;
      int deceleration_ratio = 2;

      b2Vec2 vec = b2Rot(b_ship->GetAngle()).GetYAxis();
      b2Vec2 vel = b_ship->GetLinearVelocity();
      float total_vel = std::abs(b_ship->GetLinearVelocity().x) + std::abs(b_ship->GetLinearVelocity().y);
      
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
      {
	// Motor
	b2Vec2 motor_pos = b_ship->GetWorldCenter() * PIXELS_PER_METER - b2Vec2(camera.x, camera.y) + (b2Rot(b_ship->GetAngle()).GetYAxis() * 24);
	pmotor_emitter.setParticlePosition(sf::Vector2f(motor_pos.x, motor_pos.y));
	pmotor_emitter.emitParticle(ps_pmotor, 1);

	// smotor_emitter.setParticlePosition(sf::Vector2f(50, 50));
	// smotor_emitter.emitParticle(ps_smotor, 1);

	b2Vec2 adjust = -vec * forward_speed - vel;
	b_ship->ApplyForce(adjust, b_ship->GetWorldCenter(), true);
      }
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
      {
	b2Vec2 adjust = vec * backward_speed - vel;
	b_ship->ApplyForce(adjust, b_ship->GetWorldCenter(), true);
      }
      else if (total_vel != 0)
      {
	if (total_vel < 0.25)
	  b_ship->SetLinearVelocity(b2Vec2(0, 0));
	else
	  b_ship->ApplyForce(-b_ship->GetLinearVelocity() * deceleration_ratio, b_ship->GetWorldCenter(), true);
      }
    }

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    //   b_ship->SetLinearVelocity(-b2Rot(b_ship->GetAngle()).GetYAxis() * 25);
    // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    //   b_ship->SetLinearVelocity(b2Rot(b_ship->GetAngle()).GetYAxis() * 10);
    // else
    //   b_ship->SetLinearVelocity(b2Vec2(0, 0));

    if (explosion)
    {
      int duration = 1000;
      int time = timer_explosion.getElapsedTime().asMilliseconds();
      spr_explosion.setColor(sf::Color(200, 200, 200, 200));

      if (time > duration / (16 * 16))
      {
	++pos_explosion;
	timer_explosion.restart();
      }

      if (pos_explosion > 16 * 16)
	explosion = false;
      else
      {
	spr_explosion.setTextureRect(sf::IntRect((pos_explosion % 16) * 256, (pos_explosion / 16 - 1) * 256, 256, 256));
	Window.draw(spr_explosion);
      }
    }

    // Camera changed - update with adjustment
    sf::Vector2f adjustment;
    if (camera.x != old_camera.x || camera.y != old_camera.y)
    {
      adjustment = sf::Vector2f(old_camera.x - camera.x, old_camera.y - camera.y);
      old_camera = camera;

      // Get explosion origin 
      // smoke_emitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(MouseX, MouseY), 0));
      // steam_emitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(MouseX, MouseY), 4));
      // flash_emitter.setParticlePosition(thor::Distributions::circle(sf::Vector2f(MouseX, MouseY), 0));
    }

    sf::Time elapsed_time = pclock.restart();
    ps_flash.update(elapsed_time, adjustment);
    ps_smoke.update(elapsed_time, adjustment);
    ps_steam.update(elapsed_time, adjustment);
    ps_shock.update(elapsed_time, adjustment);
    ps_spark.update(elapsed_time, adjustment);
    ps_debris.update(elapsed_time, adjustment);
    Window.draw(ps_flash, sf::BlendAdd);
    Window.draw(ps_smoke, sf::BlendAdd);
    Window.draw(ps_steam, sf::BlendAdd);
    Window.draw(ps_shock, sf::BlendAdd);
    Window.draw(ps_spark, sf::BlendAdd);
    Window.draw(ps_debris, sf::BlendAdd);

    // Camera changed - update with adjustment
    adjustment = sf::Vector2f(0, 0);
    sf::Vector2i dist_cam_ship = sf::Vector2i(b_ship->GetWorldCenter().x * PIXELS_PER_METER, b_ship->GetWorldCenter().y * PIXELS_PER_METER) - camera;
    if (dist_cam_ship.x != old_ship.x || dist_cam_ship.y != old_ship.y)
    {
      std::cout << "yep" << std::endl;
      adjustment = sf::Vector2f(dist_cam_ship.x - old_ship.x, dist_cam_ship.y - old_ship.y);
      old_ship = dist_cam_ship;
    }
    ps_pmotor.update(elapsed_time, adjustment);
    Window.draw(ps_pmotor, sf::BlendAdd);
    ps_smotor.update(elapsed_time, adjustment);
    Window.draw(ps_smotor, sf::BlendAdd);


    // Particle
    for (b2ParticleSystem *sys = World.GetParticleSystemList(); sys != NULL; sys = sys->GetNext())
    {
      b2Vec2	*particles = sys->GetPositionBuffer();
      // if (display)
	// std::cout << "Particles >> " << sys->GetParticleCount() << std::endl;

      for (int i = 0; i < sys->GetParticleCount(); ++i)
      {
	circle.setPosition(PIXELS_PER_METER * particles[i].x + camera.x, PIXELS_PER_METER * particles[i].y + camera.y);
	Window.draw(circle);
      }
    }

    int BodyCount = 0;
    for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
    {
      void	*data = BodyIterator->GetUserData();

      ((sf::Sprite *) data)->setPosition((int) PIXELS_PER_METER * BodyIterator->GetPosition().x - camera.x, (int) PIXELS_PER_METER * BodyIterator->GetPosition().y - camera.y);
      ((sf::Sprite *) data)->setRotation((int) thor::toDegree(BodyIterator->GetAngle()));
      Window.draw(*((sf::Drawable *) data));

      if (BodyIterator->GetType() == b2_staticBody)
	continue ;

      sf::Sprite *spr = (sf::Sprite *) data;
      // Draw each vertices
      continue ;
      b2PolygonShape *shape = (b2PolygonShape *) BodyIterator->GetFixtureList()->GetShape();
      int i;
      for (i = 0; i < shape->GetVertexCount() - 1; ++i)
      {
	sf::Vertex line[] =
	{
	  sf::Vertex(sf::Vector2f(spr->getPosition().x + shape->GetVertex(i).x * PIXELS_PER_METER, spr->getPosition().y + shape->GetVertex(i).y * PIXELS_PER_METER), sf::Color::Green),
	  sf::Vertex(sf::Vector2f(spr->getPosition().x + shape->GetVertex(i + 1).x * PIXELS_PER_METER, spr->getPosition().y + shape->GetVertex(i + 1).y * PIXELS_PER_METER), sf::Color::Red)
	};

	Window.draw(line, 2, sf::Lines);
      }
      sf::Vertex line[] =
      {
	sf::Vertex(sf::Vector2f(spr->getPosition().x + shape->GetVertex(i).x * PIXELS_PER_METER, spr->getPosition().y + shape->GetVertex(i).y * PIXELS_PER_METER), sf::Color::Red),
	sf::Vertex(sf::Vector2f(spr->getPosition().x + shape->GetVertex(0).x * PIXELS_PER_METER, spr->getPosition().y + shape->GetVertex(0).y * PIXELS_PER_METER), sf::Color::Green),
      };

      Window.draw(line, 2, sf::Lines);
    }

    Window.draw(cursor_shape);

    Window.display();

    refreshed = false;
  }

  return 0;
}

void CreateBox(b2World& World, int MouseX, int MouseY)
{
  b2BodyDef BodyDef;
  BodyDef.position = b2Vec2(MouseX/PIXELS_PER_METER, MouseY/PIXELS_PER_METER);
  BodyDef.type = b2_dynamicBody;
  b2Body* Body = World.CreateBody(&BodyDef);

  b2PolygonShape Shape;
  Shape.SetAsBox((32.f/2)/PIXELS_PER_METER, (32.f/2)/PIXELS_PER_METER);
  b2FixtureDef FixtureDef;
  FixtureDef.density = 1.f;
  FixtureDef.friction = 0.7f;
  FixtureDef.shape = &Shape;
  Body->CreateFixture(&FixtureDef);
  Body->SetUserData(&spr_box);
}

void CreateGround(b2World& World, float X, float Y, float angle)
{
  b2BodyDef BodyDef;
  BodyDef.position = b2Vec2(X/PIXELS_PER_METER, Y/PIXELS_PER_METER);
  BodyDef.type = b2_staticBody;
  BodyDef.angle = angle;
  b2Body* Body = World.CreateBody(&BodyDef);

  b2PolygonShape Shape;
  Shape.SetAsBox((BOX_WIDTH/2)/PIXELS_PER_METER, (BOX_HEIGHT/2)/PIXELS_PER_METER);
  b2FixtureDef FixtureDef;
  FixtureDef.density = 0.f;
  FixtureDef.shape = &Shape;
  Body->CreateFixture(&FixtureDef);
  Body->SetUserData(&shape_ground);
}

void createShip()
{
  b2BodyDef BodyDef;
  BodyDef.position = b2Vec2(Window.getSize().x / 2 /PIXELS_PER_METER, Window.getSize().y / 2 / PIXELS_PER_METER);
  BodyDef.type = b2_dynamicBody;
  BodyDef.angle = 0.f;
  b_ship = World.CreateBody(&BodyDef);

  // b2PolygonShape shape;
  vector<b2Vec2> vec;
  vec.push_back(b2Vec2(181.f / PIXELS_PER_METER * 0.4, 157.f / PIXELS_PER_METER * 0.4));
  vec.push_back(b2Vec2(16.f / PIXELS_PER_METER * 0.4, 158.f / PIXELS_PER_METER * 0.4));
  vec.push_back(b2Vec2(1.f / PIXELS_PER_METER * 0.4, 127.f / PIXELS_PER_METER * 0.4));
  vec.push_back(b2Vec2(69.f / PIXELS_PER_METER * 0.4, 68.f / PIXELS_PER_METER * 0.4));
  vec.push_back(b2Vec2(98.f / PIXELS_PER_METER * 0.4, 1.f / PIXELS_PER_METER * 0.4));
  vec.push_back(b2Vec2(126.f / PIXELS_PER_METER * 0.4, 67.f / PIXELS_PER_METER * 0.4));
  vec.push_back(b2Vec2(194.f / PIXELS_PER_METER * 0.4, 126.f / PIXELS_PER_METER * 0.4));

  // shape.Set(vertices, 7);
  b2FixtureDef FixtureDef;
  // FixtureDef.shape = &shape;
  FixtureDef.density = 1.f;
  FixtureDef.friction = 0.5;
  FixtureDef.restitution = 1.f;

  // Body->CreateFixture(&FixtureDef);
  b_ship->SetUserData(&spr_ship);
  b2Separator sep;
  sep.Separate(b_ship, &FixtureDef, &vec, PIXELS_PER_METER);
}

float field(vec3 p)
{
  float strength = 7.;
  float accum = 0.;
  float prev = 0.;
  float tw = 0.;
  for (int i = 0; i < 32; ++i) {
    float mag = dot(p, p);
    p = abs(p) / mag + vec3(-.5, -.4, -1.5);
    float w = exp(-float(i) / 7.);
    accum += w * exp(-strength * pow(abs(mag - prev), 2.3));
    tw += w;
    prev = mag;
  }
  return max(0., 5. * accum / tw - .7);
}

void	drawShader()
{
  vec2 iResolution = vec2(Window.getSize().x, Window.getSize().y);
  vec4 gl_FragColor;
  sf::Image image;
  image.create(Window.getSize().x, Window.getSize().y, sf::Color::Red);

  for (int y = 0; y < Window.getSize().y; ++y)
  {
    for (int x = 0; x < Window.getSize().x; ++x)
    {
      vec2 gl_FragCoord = vec2(x, y);
      vec2 uv = 2. * gl_FragCoord / iResolution - 1.;
      vec2 uvs = uv * iResolution / max(gl_FragCoord.x, gl_FragCoord.y);
      vec3 p = vec3(uvs / 4., 0) + vec3(1., -1.3, 0.);
      p += .2 * vec3(sin(global_time / 16.), sin(global_time / 12.),  sin(global_time / 128.));
      float t = field(p);
      float v = (1. - exp((abs(uv.x) - 1.) * 6.)) * (1. - exp((abs(uv.y) - 1.) * 6.));
      gl_FragColor = vec4(1.8 * t * t * t, 1.4 * t * t, t, 1.0);
      image.setPixel(x, y, sf::Color(gl_FragColor.r * 1000, gl_FragColor.g * 1000, gl_FragColor.b * 1000));
    }

  }

  tex_shader.loadFromImage(image);
  spr_shader.setTexture(tex_shader);
  spr_shader.setPosition(0, 0);
}

void		loadShader()
{
  // Shader
  if (!shader.loadFromFile("universe.frag", sf::Shader::Fragment) || !tex.loadFromFile("t3.jpg"))
    std::cout << "Cancer shader/tex" << std::endl;
  spr.setTexture(tex);
  shader.setParameter("iChannel0", sf::Shader::CurrentTexture);
  shader.setParameter("iDebug", 0);
  // shader.setParameter("iChannel1", sf::Shader::CurrentTexture);
  // shader.setParameter("iChannel2", sf::Shader::CurrentTexture);
  shader.setParameter("iResolution", Window.getSize().x, Window.getSize().y, 0);
  // shader.setParameter("mouse", Window.getSize().x / 2, Window.getSize().y / 2);
  // shader.setParameter("iChannelResolution[0]", tex.getSize().x, tex.getSize().y, 800 * 600);
  // shader.setParameter("iChannelResolution[1]", tex.getSize().x, tex.getSize().y, 800 * 600);
  // shader.setParameter("iChannelResolution[2]", tex.getSize().x, tex.getSize().y, 800 * 600);
  // shader.setParameter("shockParams", 10.0, 0.2, 0.01);
  spr.setPosition(0, 0);

  for (int i = 0; i < 10; ++i)
  {
    std::stringstream ss;
    ss  << "iDebug[" << i << "]";
    shader.setParameter(ss.str(), debugShader[i]);
    // std::cout << "iDebug[" << i << "] = " << debugShader[i] << std::endl;
  }
}
