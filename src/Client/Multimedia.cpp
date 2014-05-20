#include "Multimedia.hh"
#include "CheckBox.hh"
#include "ListItem.hh"
#include "Input.hh"
#include <sstream>

Multimedia::Multimedia() :
  MainMenuItem("VIDEO"),
  _video_mode(true)
{
  // Apply button
  String	*text = new String("Apply", jag::getTheme("Button"));
  text->autoRelease(true);
  text->addCallback(std::bind(&Multimedia::applyChanges, this));
  add(text, "apply");
  _dmanager_backup.add(text, "apply");

  CSimpleIniA	&ini = jag::getSettings();

  text = new String("AUDIO");
  _menu->add(text);
  _menu->update();

  text->addCallback([&] () { toggleMode(false); });
  _menu->getPressed()->addCallback([&] () { toggleMode(true); });

  // Video mode
  text = new String("FullScreen", jag::getTheme("ItemSetting"));
  add(text, "fullscreen");

  CheckBox	*cb = new CheckBox(new String("", jag::getTheme("Transparent")),
      jag::getTheme("CheckBoxTransparent"));
  cb->setChecked(ini.GetBoolValue(INI_GROUP, "video_fullscreen", true));
  add(cb, "cbFullScreen");

  // Audio Mode
  text = new String("Music Volume", jag::getTheme("ItemSetting"));
  _dmanager_backup.add(text, "music");

  ListItem	*list = new ListItem(jag::getTheme("ListItem"));
  list->setItemTheme(jag::getTheme("ItemListItem"));
  std::stringstream	ss;
  int			ini_value = ini.GetLongValue(INI_GROUP, "audio_music", 100);
  for (int i = 0; i <= 100; i = i + 10)
  {
    ss << i;
    list->add(new String(ss.str()));

    ss.str("");
  }
  list->setSelectedIndex(ini_value / 10);
  _dmanager_backup.add(list, "liMusic");

  // Audio Mode
  text = new String("SFX Volume", jag::getTheme("ItemSetting"));
  _dmanager_backup.add(text, "sfx");

  list = new ListItem(jag::getTheme("ListItem"));
  list->setItemTheme(jag::getTheme("ItemListItem"));
  ini_value = ini.GetLongValue(INI_GROUP, "audio_sfx", 100);
  for (int i = 0; i <= 100; i = i + 10)
  {
    ss << i;
    list->add(new String(ss.str()));
    ss.str("");
  }
  list->setSelectedIndex(ini_value / 10);
  _dmanager_backup.add(list, "liSFX");

  // Video mode
  text = new String("Resolution", jag::getTheme("ItemSetting"));
  add(text, "resolution");

  list = new ListItem(jag::getTheme("ListItem"));
  list->setItemTheme(jag::getTheme("ItemListItem"));
  auto &modes = sf::VideoMode::getFullscreenModes();
  std::string	res = ini.GetValue(INI_GROUP, "video_resolution", "");
  for (std::size_t i = 0; i < modes.size(); ++i)
  {
    if (i != 0 && modes[i - 1].bitsPerPixel != modes[i].bitsPerPixel)
      break ;

    ss << modes[i].width << "x" << modes[i].height;
    list->add(new String(ss.str()));

    if (ss.str() == res)
      list->setSelectedIndex(i);

    ss.str("");
  }
  add(list, "liResolution");

  text = new String("Anti Aliasing", jag::getTheme("ItemSetting"));
  add(text, "aa");

  list = new ListItem(jag::getTheme("ListItem"));
  list->setItemTheme(jag::getTheme("ItemListItem"));
  ini_value = ini.GetLongValue(INI_GROUP, "video_antialiasing", 0);
  for (int i = 0; i <= 8; i = i + 2)
  {
    ss << i;
    list->add(new String(ss.str()));
    ss.str("");
  }
  list->setSelectedIndex(ini_value / 2);
  add(list, "liAA");

  _dmanager_backup.add(_menu, "menu");

  settingChanged();
}

Multimedia::~Multimedia()
{
  _dmanager_backup.forget("menu");
  _dmanager_backup.forget("apply");
}

void			Multimedia::toggleMode(bool video_mode)
{
  if (_video_mode != video_mode)
  {
    _video_mode = video_mode;
    switchDrawables(_dmanager_backup);
  }
}

Drawable		*Multimedia::getDrawable(const std::string &name)
{
  Drawable	*drawable = get(name);

  if (drawable == NULL)
    drawable = _dmanager_backup.get(name);

  return (drawable);
}

void			Multimedia::applyChanges()
{
  CSimpleIniA	&ini = jag::getSettings();

  ini.SetBoolValue(INI_GROUP, "video_fullscreen", ((CheckBox *) getDrawable("cbFullScreen"))->isChecked());
  ini.SetValue(INI_GROUP, "video_antialiasing", ((String *)((ListItem *) getDrawable("liAA"))->getSelectedItem())->getString().toAnsiString().c_str());
  ini.SetValue(INI_GROUP, "video_resolution", ((String *)((ListItem *) getDrawable("liResolution"))->getSelectedItem())->getString().toAnsiString().c_str());
  ini.SetValue(INI_GROUP, "audio_music", ((String *)((ListItem *) getDrawable("liMusic"))->getSelectedItem())->getString().toAnsiString().c_str());
  ini.SetValue(INI_GROUP, "audio_sfx", ((String *)((ListItem *) getDrawable("liSFX"))->getSelectedItem())->getString().toAnsiString().c_str());

  ini.SaveFile(INI_FILE);
}

void			Multimedia::settingChanged()
{
  MainMenuItem::settingChanged();

  int	size_item = _rec.width / 2 - MARGIN * 2;
  int	x_half = _rec.left + _rec.width / 2 + MARGIN * 2;
  int	y = _y_content;

  getDrawable("apply")->setRect(Rect(_menu->getRect().left + _menu->getRect().width - 60,
	_menu->getRect().top +_menu->getRect().height + 8, 60, 26));
  getDrawable("fullscreen")->setRect(Rect(_rec.left, y, size_item, Input::HEIGHT));
  getDrawable("cbFullScreen")->setRect(Rect(x_half + 50, y + Input::HEIGHT / 2 - 4, 10, 8));
  getDrawable("music")->setRect(Rect(_rec.left, y, size_item, Input::HEIGHT));
  getDrawable("liMusic")->setRect(Rect(x_half, y, 128, Input::HEIGHT));
  y += Input::HEIGHT + MARGIN / 2;
  getDrawable("sfx")->setRect(Rect(_rec.left, y, size_item, Input::HEIGHT));
  getDrawable("liSFX")->setRect(Rect(x_half, y, 128, Input::HEIGHT));
  getDrawable("resolution")->setRect(Rect(_rec.left, y, size_item, 32));
  getDrawable("liResolution")->setRect(Rect(x_half, y, 128, Input::HEIGHT));
  y += Input::HEIGHT + MARGIN / 2;
  getDrawable("aa")->setRect(Rect(_rec.left, y, size_item, 32));
  getDrawable("liAA")->setRect(Rect(x_half, y, 128, Input::HEIGHT));
}
