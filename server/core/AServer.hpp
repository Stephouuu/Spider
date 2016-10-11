//
// AServer.hpp for server in /home/galibe_s/project/SpiderServer/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Aug 10 08:22:18 2016 stephane galibert
// Last update Tue Oct  4 21:13:20 2016 stephane galibert
//

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <signal.h>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>

#include "StaticTools.hpp"
#include "ServerConfig.hpp"
#include "PluginLoader.hpp"
#include "PluginManager.hpp"

class AServer : private boost::noncopyable
{
public:
  AServer(boost::asio::io_service &io_service, int port);
  ~AServer(void);

  virtual void init(void);
  virtual void open(void) = 0;
  virtual void close(void) = 0;

protected:
  boost::asio::io_service &_io_service;
  int _port;
  boost::asio::ssl::context _context;

  ServerConfig _config;
  PluginManager _pluginManager;
private:
  void signal(void);
  void do_signal(boost::system::error_code const& ec, int signo);

  boost::asio::signal_set _signals;
};
