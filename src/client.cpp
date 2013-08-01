#include <SFML/System.hpp>
#include <Thor/Graphics/ToString.hpp>
#include <Thor/Input.hpp>
#include "Screen/Screen.hh"
#include "Setting.hh"

class test : public Layer
{
  public:

    void onShoot()
    {
      std::cout << "SHOOT" << std::endl;
    }

    test()
    {
      _x = 0; _y = 0; _width = 100; _height = 100;

      int id = Screen::actionId();
      Screen::getMap()[id] = thor::Action(sf::Mouse::Left, thor::Action::PressOnce);
      Screen::getSystem().connect(id, std::bind(&test::onShoot, this));
    }

    bool	update(sf::RenderWindow &) { return (true); }
    void	draw(sf::RenderWindow &) { }
    void	mouseMoved(int x, int y) { std::cout << "IN" << std::endl; }
    bool	textEntered(sf::Uint32 unicode)
    {
      std::string str = "";
      sf::Utf<32>::encodeAnsi(unicode, std::back_inserter(str), '?');
      std::cout << "Entered: " << str << std::endl;
    }
};

// Once upon a main
int		main(int ac, char **av)
{
  bool		updated = false;
  sf::Clock	timer;
  sf::Time	sleeping_time = sf::milliseconds(Setting::FPS - Setting::MARGIN_FPS);

  Setting::init();
  Screen::init();
  Screen::add(new test);

  while (Screen::hasLayer())
  {
    Screen::update();

    // Sleep FPS minus MARGIN_FPS ms - keep FPS stable if lots of updates
    sf::sleep(sleeping_time);
  }

  Screen::clear();
  Setting::clear();

  return (EXIT_SUCCESS);
}
