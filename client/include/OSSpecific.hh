#ifndef OSSPECIFIC_HH_
# define OSSPECIFIC_HH_

# include <SFML/Window.hpp>

void			minimizeImpl(sf::WindowHandle handle);
void			setCursorImpl(sf::WindowHandle handle, CursorType type);
void			openUrlImpl(const std::string &url);

#endif
