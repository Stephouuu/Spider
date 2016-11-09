//
// UDPServer.cpp for server in /home/galibe_s/rendu/Spider/server/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Nov  6 17:57:31 2016 stephane galibert
// Last update Wed Nov  9 00:08:06 2016 stephane galibert
//

#include "UDPServer.hpp"

UDPServer::UDPServer(boost::asio::io_service &ios, int port, RequestHandler &req,
		     ServerConfig &config, PluginManager &pm, ConnectionManager &cm)
  : AServer(ios, port, req, config, pm, cm)
    //_running(false)
{
  _connection = std::make_shared<UDPConnection>(ios, req, pm, cm, config, port);
}

UDPServer::~UDPServer(void)
{
}

void UDPServer::init(void)
{
}

void UDPServer::open(void)
{
  _connection->start();
}

void UDPServer::close(void)
{
  //_running = false;
  std::clog << "shuting down UDP server ..." << std::endl;
  std::clog << "UDP server shutdown success" << std::endl;
}
