#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

#include <boost/core/noncopyable.hpp>

#include "Protocol.h"

#include "IRequest.h"
#include "Kill.h"
#include "Stealer.h"

class RequestBuilder : private boost::noncopyable
{
public:
	typedef std::function<std::unique_ptr<IRequest>(void)> Cmds;
public:
	RequestBuilder(void);
	~RequestBuilder(void);

	std::unique_ptr<IRequest> create(PacketType type) const;
private:
	std::unique_ptr<IRequest> kill(void) const;
	std::unique_ptr<IRequest> stealer(void) const;

	std::unordered_map<PacketType, Cmds> _cmds;
};
