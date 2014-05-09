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
  text->setRect(Rect(_menu->getRect().left + _menu->getRect().width - 60, _menu->getRect().top +
	_menu->getRect().height + 8, 60, 26));
  add(text);

  CSimpleIniA	&ini = jag::getSettings();

  text = new String("AUDIO");
  _menu->add(text);
  _menu->update();

  text->addCallback([&] () { toggleMode(); });
  _menu->getPressed()->addCallback([&] () { toggleMode(); });

  int	size_item = _rec.width / 2 - MARGIN * 2;
  int	x_half = _rec.left + _rec.width / 2 + MARGIN * 2;
  int	y = _y_content;

  // Video mode
  text = new String("FullScreen", jag::getTheme("ItemSetting"));
  text->setRect(Rect(_rec.left, y, size_item, Input::HEIGHT));
  add(text);

  CheckBox	*cb = new CheckBox(new String("", jag::getTheme("Transparent")),
      jag::getTheme("CheckBoxTransparent"));
  cb->setRect(Rect(x_half + 50, y + Input::HEIGHT / 2 - 4, 10, 8));
  cb->setChecked(ini.GetBoolValue(INI_GROUP, "video_fullscreen", true));
  add(cb, "cbFullScreen");

  // Audio Mode
  text = new String("Music Volume", jag::getTheme("ItemSetting"));
  text->setRect(Rect(_rec.left, y, size_item, Input::HEIGHT));
  _dmanager_backup.add(text);

  ListItem	*list = new ListItem(new String("0"), jag::getTheme("ListItem"));
  list->setItemTheme(jag::getTheme("ItemListItem"));
  list->setRect(Rect(x_half, y, 128, Input::HEIGHT));
  std::stringstream	ss;
  int			ini_value = ini.GetLongValue(INI_GROUP, "audio_music", 100);
  for (int i = 10; i <= 100; i = i + 10)
  {
    ss << i;
    list->add(new String(ss.str()));

    // TODO - Clear ss
  }
  list->setSelectedIndex(ini_value / 10);
  _dmanager_backup.add(list, "liMusic");

  y += Input::HEIGHT + MARGIN / 2;

  // Audio Mode
  text = new String("SFX Volume", jag::getTheme("ItemSetting"));
  text->setRect(Rect(_rec.left, y, size_item, Input::HEIGHT));
  _dmanager_backup.add(text);

  list = new ListItem(new String("0"), jag::getTheme("ListItem"));
  list->setItemTheme(jag::getTheme("ItemListItem"));
  list->setRect(Rect(x_half, y, 128, Input::HEIGHT));
  ini_value = ini.GetLongValue(INI_GROUP, "audio_sfx", 100);
  for (int i = 10; i <= 100; i = i + 10)
  {
    ss << i;
    list->add(new String(ss.str()));

    // TODO - Clear ss
  }
  list->setSelectedIndex(ini_value / 10);
  _dmanager_backup.add(list, "liSFX");

  // Video mode
  text = new String("Resolution", jag::getTheme("ItemSetting"));
  text->setRect(Rect(_rec.left, y, size_item, 32));
  add(text);

  list = new ListItem(new String("Seewww"), jag::getTheme("ListItem"));
  list->setItemTheme(jag::getTheme("ItemListItem"));
  list->setRect(Rect(x_half, y, 128, Input::HEIGHT));
  list->add(new String("test"));
  list->add(new String("DASDASDASDASdasdasd"));
  add(list, "liResolution");

  y += Input::HEIGHT + MARGIN / 2;

  text = new String("Anti Aliasing", jag::getTheme("ItemSetting"));
  text->setRect(Rect(_rec.left, y, size_item, 32));
  add(text);

  list = new ListItem(new String("0"), jag::getTheme("ListItem"));
  list->setItemTheme(jag::getTheme("ItemListItem"));
  list->setRect(Rect(x_half, y, 128, Input::HEIGHT));
  list->add(new String("2"));
  list->add(new String("4"));
  list->add(new String("8"));
  add(list, "liAA");

  _dmanager_backup.add(_menu, "menu");

  y += Input::HEIGHT + MARGIN / 2;
  // Audio Mode
}

Multimedia::~Multimedia()
{
  _dmanager_backup.forget("menu");
}

void			Multimedia::mouseReleased(int x, int y)
{
  Layer::mouseReleased(x, y);
}

void			Multimedia::draw(sf::RenderWindow &win)
{
  Layer::draw(win);
}

void			Multimedia::mouseCaught(int x, int y)
{
  Layer::mouseCaught(x, y);
}

void			Multimedia::mouseLeft()
{
  Layer::mouseLeft();
}

void			Multimedia::toggleMode()
{
  _video_mode = !_video_mode;
  switchDrawables(_dmanager_backup);
}

Drawable		*Multimedia::getDrawable(const std::string &name)
{
  Drawable	*drawable;

  if ((drawable = get(name)) == NULL)
    drawable = _dmanager_backup.get(name);
  return (drawable);
}

void			Multimedia::applyChanges()
{
  CSimpleIniA	&ini = jag::getSettings();

  ini.SetBoolValue(INI_GROUP, "video_fullscreen", ((CheckBox *) getDrawable("cbFullScreen"))->isChecked());
  // ini.SetValue(INI_GROUP, "video_antialiasing",
  //     ((String *)((ListItem *) getDrawable("liAA"))->getSelectedItem())->getString().toStdString());
  // ini.SetValue(INI_GROUP, "video_resolution",
  //     ((String *)((ListItem *) getDrawable("liResolution"))->getSelectedItem())->getString().toStdString());
  // ini.SetValue(INI_GROUP, "audio_music",
  //     ((String *)((ListItem *) getDrawable("liMusic"))->getSelectedItem())->getString().toStdString());
  // ini.SetValue(INI_GROUP, "audio_sfx",
  //     ((String *)((ListItem *) getDrawable("liSFX"))->getSelectedItem())->getString().toStdString());
}
