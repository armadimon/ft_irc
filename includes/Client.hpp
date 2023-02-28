#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <map>
# include <string>
# include <iostream>
# include <sys/socket.h>
# include <unistd.h>
# include <vector>

#include "Utils.hpp"
#include "Command.hpp"

enum State
{
	DEFAULT,
	PWSET,
	READY,
	REGISTER,
	UNREGISTER,
};

class Server;
class Command;

class Client
{
    public : 
		std::map<std::string, void(*)(Command, int)> cmdList;
	
		Client();
		Client(int fd);
		~Client();
		char						*getBuf();
		int							getFD();
		int							parseMSG(Server *server, std::string tempStr);
		void						registerClient();
		void						excute(Command cmd);
		void						msgClear();
		void						setRealName(std::string str);
		void						setNickName(std::string str);
		void						setUserName(std::string str);
		void						setHostName(std::string str);
		void						setUserState(State state);
		std::string					getUserName();
		std::string 				getNickName();
		std::string 				getHostName();
		std::string 				getRealName();
		State						getUserState();
        std::vector<std::string>	getmyChannelList();
		int							addmyChannelList(std::string channel_name);
		void						removeChannelFromList(std::string channel_name);
		int							findChannelFromList(std::string chName);
		    // getter, setter
		// void	partMyChannel(); //vector.erase 클라이언트가 채널을 나갈 때 
		    //TODO : part명령어가 여러개의 채널을 동시에 떠날 수 있는지 체크하기
 
	private :
		// bool						isOperator; //방장이면 true
		int							fd;
		// int							passwd;
		State						userState;
		std::string					msg;
		std::string					hostName;
		std::string					nickName;
		std::string					userName;
		std::string					realName;
		char						bufRead[4096];
    // ...
		//TODO : 사용되는 이름 조사하기
		std::vector<std::string> myChannelList;
        //  char *_msgBuffer; //*클라이언트에게 보낼 메세지버퍼;
};

#endif