//
// Key.cpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov  5 15:51:01 2016 stephane galibert
// Last update Wed Nov  9 04:00:36 2016 stephane galibert
//

#include "Key.hpp"

Key::Key(void)
{
}

Key::~Key(void)
{
}

void Key::execute(AConnection::shared own, std::string const& param,
		  Packet **reply)
{
  (void)reply;
  own->broadcast(param);
  own->addLog(param);
}
