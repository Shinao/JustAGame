#include "ChatBox.hh"

ChatBox::ChatBox()
{
  _input = new Input();
  add(_input);
}

ChatBox::~ChatBox()
{
}

void			ChatBox::settingChanged()
{
  _rec = Rect(MARGIN, Screen::getSize().y - INPUT_HEIGHT - MESSAGES_HEIGHT - MARGIN, WIDTH,
      MESSAGES_HEIGHT + INPUT_HEIGHT);
  _input->setRect(Rect(_rec.left, _rec.top + MESSAGES_HEIGHT, WIDTH, INPUT_HEIGHT));
}
