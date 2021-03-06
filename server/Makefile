NAME		=	./bin/server

CXX		=	g++

RM		=	rm -f

SRCS		+=	main.cpp
SRCS		+=	core/Configuration.cpp
SRCS		+=	core/ServerConfig.cpp
SRCS		+=	core/AServer.cpp
SRCS		+=	core/TCPServer.cpp
SRCS		+=	core/UDPServer.cpp
SRCS		+=	core/AConnection.cpp
SRCS		+=	core/TCPConnection.cpp
SRCS		+=	core/UDPConnection.cpp
SRCS		+=	core/ConnectionManager.cpp
SRCS		+=	core/PluginManager.cpp
SRCS		+=	core/PluginLoader.cpp
SRCS		+=	core/ftp/FTPServer.cpp
SRCS		+=	core/ftp/FTPConnection.cpp
SRCS		+=	core/ftp/FTPSession.cpp
SRCS		+=	core/request/RequestHandler.cpp
SRCS		+=	core/request/RequestBuilder.cpp
SRCS		+=	core/request/CommandBuilder.cpp
SRCS		+=	core/request/Help.cpp
SRCS		+=	core/request/Nc.cpp
SRCS		+=	core/request/Dump.cpp
SRCS		+=	core/request/Exit.cpp
SRCS		+=	core/request/Set.cpp
SRCS		+=	core/request/Get.cpp
SRCS		+=	core/request/SQL.cpp
SRCS		+=	core/request/Key.cpp
SRCS		+=	core/request/Reload.cpp
SRCS		+=	core/request/Close.cpp
SRCS		+=	core/request/Listen.cpp
SRCS		+=	core/request/Stealer.cpp
SRCS		+=	core/request/DeleteFTP.cpp
SRCS		+=	core/request/Kill.cpp
SRCS		+=	utils/ADlLoader.cpp
SRCS		+=	utils/UnixDlLoader.cpp
SRCS		+=	utils/StaticTools.cpp
SRCS		+=	utils/JSONBuilder.cpp
SRCS		+=	utils/JSONReader.cpp
SRCS		+=	utils/XMLReader.cpp

OBJS		=	$(SRCS:.cpp=.o)

CXXFLAGS	+=	-g
CXXFLAGS	+=	-std=c++11
CXXFLAGS	+=	-Wall -Wextra -Werror

CXXFLAGS	+=	-I./core/
CXXFLAGS	+=	-I./core/request/
CXXFLAGS	+=	-I./core/ftp/
CXXFLAGS	+=	-I./utils/
CXXFLAGS	+=	-I./shared/plugin/include/

LDFLAGS		+=	-lpthread
LDFLAGS		+=	-lboost_system
LDFLAGS		+=	-lboost_filesystem
LDFLAGS		+=	-lssl -lcrypto
LDFLAGS		+=	-ldl
LDFLAGS		+=	-L./shared/plugin/bin -lplugin


all:		CCLIB $(NAME) CCPLUGIN

CCLIB:		
		make -C ./shared/plugin/

$(NAME):	$(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)
		cp ./utils/JSONBuilder.hpp ./utils/JSONBuilder.cpp ./plugins/Database/utils/
		cp ./shared/plugin/include/PluginRegister.hpp ./plugins/Database/lib/
		cp ./shared/plugin/include/IPlugin.hpp ./plugins/Database/lib/
		cp ./shared/plugin/include/IDatabase.hpp ./plugins/Database/lib/
		cp ./shared/plugin/include/PluginInfo.hpp ./plugins/Database/lib/
		cp ./shared/plugin/bin/libplugin.a ./plugins/Database/lib/

CCPLUGIN:
		make -C ./plugins/Database/


re:		fclean all
		make re -C ./shared/plugin/
		make re -C ./plugins/Database/

clean:
		$(RM) $(OBJS)
		make clean -C ./shared/plugin/
		make clean -C ./plugins/Database/

fclean:		clean
		$(RM) $(NAME)
		make fclean -C ./shared/plugin/
		make fclean -C ./plugins/Database/
