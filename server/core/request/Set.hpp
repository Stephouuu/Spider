//
// Set.hpp for server in /home/galibe_s/rendu/Spider/server/core/request
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Nov  5 15:54:53 2016 stephane galibert
// Last update Sat Nov  5 15:54:54 2016 stephane galibert
//

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

#include "ICommand.hpp"
#include "Privilege.hpp"

class Set : public ICommand
{
public:
  typedef std::vector<std::pair<std::string, std::string> > Params;
  typedef std::function<Packet *(AConnection::shared, Params const&)> Cmds;
public:
  Set(void);
  virtual ~Set(void);

  virtual void execute(AConnection::shared own, JSONReader const& reader,
		       Packet **reply);
private:
  Packet *privilege(AConnection::shared own, Params const& av);
  std::unordered_map<std::string, Cmds> _cmds;
};
