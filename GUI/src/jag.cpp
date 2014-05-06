#include "jag.hh"
#include "Utility/Graphic.hh"
#include "Ressource.hh"

#include <iostream>

namespace jag
{
  // Can't catch me mothafucka
  namespace
  {
    std::map<std::string, Theme	*>	_themes;
    std::map<std::string, sf::Image *>	_rsrcs;
    Theme				*_theme;
    CSimpleIniA				_ini;
  }

  void			init()
  {
    // Settings
    _ini.LoadFile(INI_FILE);

    // Predef color
    // sf::Color blue = sf::Color(78, 166, 234);
    sf::Color blue_focus = sf::Color(63, 146, 210);
    sf::Color blue_light = sf::Color(196, 216, 236);
    sf::Color gray = sf::Color(236, 236, 236);
    sf::Color gray_focus = sf::Color(216, 216, 216);
    sf::Color black_light = sf::Color(120, 120, 120);
    sf::Color black = sf::Color(100, 100, 100);

    // Setting the titlebar theme
    Theme		*theme = new Theme;
    _themes["Titlebar"] = theme;
    theme->c_background = sf::Color::Transparent;
    theme->c_background_focused = gray;
    theme->c_background_pressed = sf::Color::Transparent;
    theme->c_text = black_light;
    theme->c_text_focused = black_light;
    theme->c_text_pressed = black_light;

    // Setting the titlebar cross icon theme
    theme = new Theme;
    _themes["TitlebarCross"] = theme;
    *theme = *(_themes["Titlebar"]);
    theme->c_background_focused = sf::Color(236, 176, 176);
    theme->c_text_focused = sf::Color::White;

    theme = new Theme;
    _themes["White"] = theme;
    // Setting the menu theme
    theme->c_text = black;
    theme->c_text_focused = black;
    theme->c_text_pressed = sf::Color::White;
    theme->size_text = 12;
    theme->size_text_focused = 12;
    theme->size_text_pressed = 12;
    theme->c_background = sf::Color::White;
    theme->c_background_focused = gray;
    theme->c_background_pressed = black_light;
    theme->style_text = sf::Text::Regular;
    theme->style_text_focused = sf::Text::Regular;
    theme->style_text_pressed = sf::Text::Regular;
    theme->f_text.loadFromFile("rsrc/arial.ttf");
    theme->f_text_focused = theme->f_text;
    theme->f_text_pressed = theme->f_text;
    theme->c_border = gray;
    theme->c_border_focused = blue_light;
    theme->c_border_pressed = blue_focus;
    theme->size_border = 3;
    theme->size_border_focused = 3;
    theme->size_border_pressed = 3;
    _theme = theme;

    // Menu theme
    theme = new Theme;
    _themes["VerticalMenu"] = theme;
    *theme = *_themes["White"];
    theme->border = Border::Left;
    theme = new Theme;
    _themes["HorizontalMenu"] = theme;
    *theme = *_themes["White"];
    theme->border = Border::Bottom;
    theme = new Theme;
    _themes["CenteredMenu"] = theme;
    *theme = *_themes["White"];
    theme->alignment = Alignment::Center;

    // Button theme
    theme = new Theme;
    _themes["Button"] = theme;
    *theme = *_themes["White"];
    theme->c_background = gray;
    theme->c_background_focused = theme->c_background_pressed;
    theme->c_text_focused = theme->c_text_pressed;
    theme->c_border = theme->c_border_focused;
    theme->c_border_focused = theme->c_border_pressed;
    theme->border = Border::Left;
    theme->alignment = Alignment::Center;

    theme = new Theme;
    _themes["ItemListBox"] = theme;
    *theme = *_themes["Button"];
    theme->c_background_focused = gray_focus;
    theme->c_text_focused = _themes["White"]->c_text_focused;
    theme->alignment = Alignment::Center;

    theme = new Theme;
    _themes["Tooltip"] = theme;
    *theme = *_themes["White"];
    theme->c_background = theme->c_background_focused;
    theme->c_border = theme->c_border_focused;
    theme->alignment = Alignment::Center;

    theme = new Theme;
    _themes["Input"] = theme;
    *theme = *_themes["White"];
    theme->c_background = theme->c_background_focused;
    theme->c_border = gray_focus;
    theme->c_border_pressed = theme->c_border_focused;

    theme = new Theme;
    _themes["ModalMessageBox"] = theme;
    *theme = *_themes["White"];
    theme->c_text = theme->c_text_pressed;
    theme->c_text_focused = theme->c_text_pressed;
    theme->c_background = theme->c_background_pressed;
    theme->c_background_focused = theme->c_background_pressed;

    theme = new Theme;
    _themes["ModalMessageBoxTitle"] = theme;
    *theme = *_themes["ModalMessageBox"];
    theme->size_text = theme->size_text + 2;
    theme->size_text_focused = theme->size_text;
    theme->size_text_pressed = theme->size_text;
    theme->c_text = theme->c_text_pressed;
    theme->c_text_focused = theme->c_text_pressed;
    theme->c_background = black;
    theme->c_background_focused = black;
    theme->c_background_pressed = black;
    theme->c_border = theme->c_border_pressed;
    theme->c_border_focused = theme->c_border_pressed;
    theme->border = Border::Bottom;

    // Button theme
    theme = new Theme;
    _themes["ModalMessageBoxButton"] = theme;
    *theme = *_themes["Button"];
    theme->c_background = gray;
    theme->c_text_focused = theme->c_text_pressed;
    theme->c_border = theme->c_border_focused;
    theme->c_background_focused = theme->c_border;
    theme->c_border_focused = theme->c_background;

    // Transparent theme
    theme = new Theme;
    _themes["Transparent"] = theme;
    *theme = *_themes["White"];
    theme->c_background = sf::Color::Transparent;
    theme->c_background_focused = sf::Color::Transparent;
    theme->c_background_pressed = sf::Color::Transparent;
    theme->c_text_focused = theme->c_text;
    theme->c_text_pressed = theme->c_text;

    // Ping theme
    theme = new Theme;
    _themes["Ping"] = theme;
    *theme = *_themes["Transparent"];
    theme->c_border = blue_focus;
    theme->c_border_focused = blue_focus;
    theme->c_border_pressed = blue_focus;
    theme->border = Border::Top;
    theme->alignment = Alignment::Center;

    // ListItem
    theme = new Theme;
    _themes["ListItem"] = theme;
    *theme = *_themes["White"];
    theme->alignment = Alignment::Center;

    theme = new Theme;
    _themes["ItemListItem"] = theme;
    *theme = *_themes["White"];
    theme->alignment = Alignment::Center;

    // Item setting (game, input..)
    theme = new Theme;
    _themes["ItemSetting"] = theme;
    *theme = *_themes["Transparent"];
    theme->alignment = Alignment::Right;

    // Transparent Sprite
    theme = new Theme;
    _themes["TransparentSprite"] = theme;
    *theme = *_themes["Transparent"];
    theme->c_text = sf::Color::Transparent;
    theme->c_text_focused = sf::Color::Transparent;
    theme->c_text_pressed = sf::Color::Transparent;

    // Init ressources
    createRessourceFromArray("bird.png", bird.pixel_data, bird.width, bird.height);
    createRessourceFromArray("embleme.png", embleme.pixel_data, embleme.width, embleme.height);
    createRessourceFromArray("logo.png", logo.pixel_data, logo.width, logo.height);
    createRessourceFromArray("restore_window.png", restore.pixel_data, restore.width, restore.height);
    createRessourceFromArray("close_window.png", close.pixel_data, close.width, close.height);
    createRessourceFromArray("minimize_window.png", minimize.pixel_data, minimize.width, minimize.height);
  }

  void			clear()
  {
    // Clear themes
    for (auto it : _themes)
      delete it.second;

    // Clear ressources
    for (auto it : _rsrcs)
      delete it.second;
  }

  void				createRessourceFromArray(const std::string &name,
      const unsigned char *data, unsigned int width, unsigned int height)
  {
    sf::Image		*img = new sf::Image;

    img->create(width, height, data);
    _rsrcs[RessourcePath + name] = img;
  }

  Theme			*getCurrentTheme()
  {
    return (_theme);
  }

  Theme			*getTheme(const std::string &name)
  {
    auto		it = _themes.find(name);

    if (it != _themes.end())
      return (it->second);

    return (_theme);
  }

  void			setTheme(Theme *theme)
  {
    _theme = theme;
  }

  void			addTheme(const std::string &name, Theme *theme)
  {
    _themes[name] = theme;
  }

  sf::Image		&getRessource(const std::string &name)
  {
    auto		it = _rsrcs.find(RessourcePath + name);

    if (it != _rsrcs.end())
      return (*(it->second));

    sf::Image		*img = new sf::Image;

    // No image found - fucking users deleting files !
    if (!img->loadFromFile(RessourcePath + name))
      img->create(16, 16);

    _rsrcs[RessourcePath + name] = img;
    return (*img);
  }

  CSimpleIniA		&getSettings()
  {
    return (_ini);
  }


  // SFML Keys
  namespace
  {
    std::map<std::string, sf::Keyboard::Key>		_keys =
    {
      { "A", sf::Keyboard::A },
      { "B", sf::Keyboard::B },
      { "C", sf::Keyboard::C },
      { "D", sf::Keyboard::D },
      { "E", sf::Keyboard::E },
      { "F", sf::Keyboard::F },
      { "G", sf::Keyboard::G },
      { "H", sf::Keyboard::H },
      { "I", sf::Keyboard::I },
      { "J", sf::Keyboard::J },
      { "K", sf::Keyboard::K },
      { "L", sf::Keyboard::L },
      { "M", sf::Keyboard::M },
      { "N", sf::Keyboard::N },
      { "O", sf::Keyboard::O },
      { "P", sf::Keyboard::P },
      { "Q", sf::Keyboard::Q },
      { "R", sf::Keyboard::R },
      { "S", sf::Keyboard::S },
      { "T", sf::Keyboard::T },
      { "U", sf::Keyboard::U },
      { "V", sf::Keyboard::V },
      { "W", sf::Keyboard::W },
      { "X", sf::Keyboard::X },
      { "Y", sf::Keyboard::Y },
      { "Z", sf::Keyboard::Z },
      { "Num0", sf::Keyboard::Num0 },
      { "Num1", sf::Keyboard::Num1 },
      { "Num2", sf::Keyboard::Num2 },
      { "Num3", sf::Keyboard::Num3 },
      { "Num4", sf::Keyboard::Num4 },
      { "Num5", sf::Keyboard::Num5 },
      { "Num6", sf::Keyboard::Num6 },
      { "Num7", sf::Keyboard::Num7 },
      { "Num8", sf::Keyboard::Num8 },
      { "Num9", sf::Keyboard::Num9 },
      { "Escape", sf::Keyboard::Escape },
      { "LControl", sf::Keyboard::LControl },
      { "LShift", sf::Keyboard::LShift },
      { "LAlt", sf::Keyboard::LAlt },
      { "LSystem", sf::Keyboard::LSystem },
      { "RControl", sf::Keyboard::RControl },
      { "RShift", sf::Keyboard::RShift },
      { "RAlt", sf::Keyboard::RAlt },
      { "RSystem", sf::Keyboard::RSystem },
      { "Menu", sf::Keyboard::Menu },
      { "LBracket", sf::Keyboard::LBracket },
      { "RBracket", sf::Keyboard::RBracket },
      { "SemiColon", sf::Keyboard::SemiColon },
      { "Comma", sf::Keyboard::Comma },
      { "Period", sf::Keyboard::Period },
      { "Quote", sf::Keyboard::Quote },
      { "Slash", sf::Keyboard::Slash },
      { "BackSlash", sf::Keyboard::BackSlash },
      { "Tilde", sf::Keyboard::Tilde },
      { "Equal", sf::Keyboard::Equal },
      { "Dash", sf::Keyboard::Dash },
      { "Space", sf::Keyboard::Space },
      { "Return", sf::Keyboard::Return },
      { "BackSpace", sf::Keyboard::BackSpace },
      { "Tab", sf::Keyboard::Tab },
      { "PageUp", sf::Keyboard::PageUp },
      { "PageDown", sf::Keyboard::PageDown },
      { "End", sf::Keyboard::End },
      { "Home", sf::Keyboard::Home },
      { "Insert", sf::Keyboard::Insert },
      { "Delete", sf::Keyboard::Delete },
      { "Add", sf::Keyboard::Add },
      { "Subtract", sf::Keyboard::Subtract },
      { "Multiply", sf::Keyboard::Multiply },
      { "Divide", sf::Keyboard::Divide },
      { "Left", sf::Keyboard::Left },
      { "Right", sf::Keyboard::Right },
      { "Up", sf::Keyboard::Up },
      { "Down", sf::Keyboard::Down },
      { "Numpad0", sf::Keyboard::Numpad0 },
      { "Numpad1", sf::Keyboard::Numpad1 },
      { "Numpad2", sf::Keyboard::Numpad2 },
      { "Numpad3", sf::Keyboard::Numpad3 },
      { "Numpad4", sf::Keyboard::Numpad4 },
      { "Numpad5", sf::Keyboard::Numpad5 },
      { "Numpad6", sf::Keyboard::Numpad6 },
      { "Numpad7", sf::Keyboard::Numpad7 },
      { "Numpad8", sf::Keyboard::Numpad8 },
      { "Numpad9", sf::Keyboard::Numpad9 },
      { "F1", sf::Keyboard::F1 },
      { "F2", sf::Keyboard::F2 },
      { "F3", sf::Keyboard::F3 },
      { "F4", sf::Keyboard::F4 },
      { "F5", sf::Keyboard::F5 },
      { "F6", sf::Keyboard::F6 },
      { "F7", sf::Keyboard::F7 },
      { "F8", sf::Keyboard::F8 },
      { "F9", sf::Keyboard::F9 },
      { "F10", sf::Keyboard::F10 },
      { "F11", sf::Keyboard::F11 },
      { "F12", sf::Keyboard::F12 },
      { "F13", sf::Keyboard::F13 },
      { "F14", sf::Keyboard::F14 },
      { "F15", sf::Keyboard::F15 },
      { "Pause", sf::Keyboard::Pause },
    };
  }

  std::map<std::string, sf::Keyboard::Key>		&getKeys()
  {
    return (_keys);
  }
}
