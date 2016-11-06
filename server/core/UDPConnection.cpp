//
// UDPConnection.cpp for server in /home/galibe_s/rendu/Spider/server/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Nov  6 17:57:27 2016 stephane galibert
// Last update Sun Nov  6 20:17:30 2016 stephane galibert
//

#include "UDPConnection.hpp"
#include "RequestHandler.hpp"

UDPConnection::UDPConnection(boost::asio::io_service &io_service,
			     RequestHandler &reqHandler,
			     PluginManager &pluginManager,
			     ServerConfig &config,
			     int port)
  : AConnection(io_service, reqHandler, pluginManager, config),
    _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
}

UDPConnection::~UDPConnection(void)
{
}

void UDPConnection::start(void)
{
  try {
    _running = true;
    read();
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
  }
}

void UDPConnection::write(Packet *packet)
{
  bool write_in_progress = !_toWrites.empty();

  _toWrites.push(packet);

  if (!write_in_progress) {
    write();
  }
}

void UDPConnection::addLog(std::string const& toadd)
{
  if (toadd.size() > 11) {
    std::string mac = toadd.substr(0, 12);
    std::string data = toadd.substr(13, toadd.size() - 13);

    std::clog << "mac: '" << mac << "'" << std::endl;
    std::clog << "data: '" << data << "'" << std::endl;

    _pluginManager.newKeyDatabase(mac, data);
  }
}

void UDPConnection::write(void)
{
  Packet *packet = _toWrites.front();
  _socket.async_send_to(boost::asio::buffer(packet, sizeof(Packet) + packet->size),
			_endpoint,
			boost::bind(&UDPConnection::do_write, this,
				    boost::asio::placeholders::error,
				    boost::asio::placeholders::bytes_transferred));
}

void UDPConnection::read(void)
{
  _socket.async_receive_from(_read.prepare(2048), _endpoint,
			     boost::bind(&UDPConnection::do_read, this,
					 boost::asio::placeholders::error,
					 boost::asio::placeholders::bytes_transferred));
}

void UDPConnection::do_write(boost::system::error_code const& ec, size_t)
{
  if (!ec) {

    Packet *packet = _toWrites.front();
    free(packet);

    _toWrites.pop();

    if (!_toWrites.empty()) {
      write();
    }
  }
}

void UDPConnection::do_read(boost::system::error_code const& ec, size_t /* len */)
{
  if (!ec) {
    Packet const* packet = boost::asio::buffer_cast<Packet const *>(_read.data());
    _read.consume(sizeof(Packet) + (packet->size * sizeof(char)));

    Packet *reply = NULL;
    _reqHandler.request(shared_from_this(), packet, &reply);

    if (reply) {
      write(reply);
    }

    if (_running) {
      read();
    }
  }
  else {
    _running = false;
  }
}

void UDPConnection::do_handshake(boost::system::error_code const& ec)
{
  (void)ec;
}
