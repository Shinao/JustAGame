#include "About.hh"
#include "String.hh"
#include "Screen.hh"
#include "StringArea.hh"

About::About() :
  MainMenuItem("ABOUT")
{
  // Apply button
  String	*text = new String("Visit GitHub", jag::getTheme("Button"));
  text->autoRelease(true);
  text->addCallback([] ()
      {
      	Screen::openUrl("https://github.com/Shinao/JustAGame");
      });
  text->setRect(Rect(_menu->getRect().left + _menu->getRect().width - 100, _menu->getRect().top +
	_menu->getRect().height + 8, 100, 26));
  add(text);

  StringArea *area = new StringArea(""
      "The goal of JustAGame is to make a framework for easy-to-create 2D game modes.\n"
      "Libraries for the network and GUI are available to create easily new contents.\n\n\n"
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
  area->setRect(Rect(_rec.left, _y_content, _rec.width, _rec.height - 200));
  add(area);
}

About::~About()
{
}
