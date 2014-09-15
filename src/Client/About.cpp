#include "Client/About.hh"
#include "GUI/Screen.hh"

About::About() :
  MainMenuItem("ABOUT")
{
  // Apply button
  _visit = new String("Visit GitHub", jag::getTheme("Button"));
  _visit->autoRelease(true);
  _visit->addCallback([] ()
      {
      	Screen::openUrl("https://github.com/Shinao/JustAGame");
      });
  add(_visit);

  _area = new StringArea(""
      "The goal of JustAGame is to make a framework for easy-to-create 2D game modes.\n"
      "Libraries for the network and GUI are available to easily create new contents.\n\n\n"
      "Type : Multiplayer\n"
      "Mode : Multiple\n"
      "Language : C++11\n"
      "Libraries : SFML (Graphic) - Box2D (Physic) - SimpleIni (Setting)\n\n\n"
      "HOW TO\n\n"
      "Checkout the source code (GitHub) and see the TicTacToe sample. Should be easy enough.\n\n\n"
      "BUGS\n\n"
      "Create an issue on GitHub or make a pull request.\n\n\n"
      "CONTACT\n\n"
      "rmonnerat.pro@gmail.com"
      "", jag::getTheme("Transparent")); 
  add(_area);
}

About::~About()
{
}

void			About::settingChanged()
{
  MainMenuItem::settingChanged();

  _visit->setRect(Rect(_menu->getRect().left + _menu->getRect().width - 100,
	_menu->getRect().top + _menu->getRect().height + 8, 100, 26));
  _area->setRect(Rect(_rec.left, _y_content, _rec.width, _rec.height - 200));
}
