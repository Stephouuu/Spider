//
// PluginManager.hpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Aug  9 03:08:32 2016 stephane galibert
// Last update Wed Oct 26 15:50:05 2016 stephane galibert
//

#pragma once

#include <string>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <memory>
#include <stdexcept>
#include <utility>

#include "IUserInterface.hpp"
#include "IDatabase.hpp"

#include "ServerConfig.hpp"
#include "PluginInfo.hpp"
#include "UnixDlLoader.hpp"
#include "PluginRegister.hpp"

class PluginManager
{
public:
  PluginManager(ServerConfig const& serverConfig);
  ~PluginManager(void);

  bool load(std::string const& fname);
  void close(std::string const& pluginName);
  std::vector<PluginInfo> const& getPluginsInfo(void) const;
  void closeAll(void);

  void startUserInterface(void);
  void closeUserInterface(void);

  void initDatabase(void);
  void closeDatabase(void);
  void newConnectionDatabase(std::string const& id);
  void lostConnectionDatabase(std::string const& id);
  std::string executeSQLDatabase(std::string const& stmt);
  void newKeyDatabase(std::string const& id, std::string const& key);

private:
  ServerConfig const& _serverConfig;

  std::vector<PluginInfo> _pluginsInfo; // erase
  std::vector<std::unique_ptr<UnixDlLoader> > _plugins; // erase
  std::unique_ptr<PluginRegister> _pluginRegister;


  //std::list<PluginInfo, UnixDlLoader>
};
