//
// StaticTools.cpp for server in /home/galibe_s/project
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Aug  5 21:05:34 2016 stephane galibert
// Last update Mon Aug 22 19:22:18 2016 stephane galibert
//

#include "StaticTools.hpp"

std::string StaticTools::GetDate(void)
{
  std::stringstream ss;
  boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
  ss << std::right << now.date().day() << "/"
     << now.date().month() << "/"
		<< now.date().year() << " - "
     << std::setw(2) << std::setfill('0') << now.time_of_day().hours() << "h"
     << std::setw(2) << std::setfill('0') << now.time_of_day().minutes() << "m"
     << std::setw(2) << std::setfill('0') << now.time_of_day().seconds() << "s"
     << std::flush;
  return (ss.str());
}

std::string StaticTools::GetHour(void)
{
  std::stringstream ss;

  boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
  ss << std::setw(2) << std::setfill('0') << now.time_of_day().hours() << "h"
     << std::setw(2) << std::setfill('0') << now.time_of_day().minutes() << "m"
     << std::setw(2) << std::setfill('0') << now.time_of_day().seconds() << "s"
     << std::flush;
  return (ss.str());
}

void StaticTools::CreateFolder(std::string const& path)
{
  boost::filesystem::create_directory(path);
}

bool StaticTools::CheckMacValidity(std::string const& mac)
{
  return (mac.size() == 12);
}

void StaticTools::LoadPlugin(PluginManager &pm)
{
  PluginLoader pluginLoader;

  pluginLoader.parseDirectory("./plugins/");
  std::vector<std::string> const& plugins = pluginLoader.getPlugins();

  for (auto it : plugins) {
    pm.load(it);
  }
}
