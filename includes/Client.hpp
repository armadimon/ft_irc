#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <map>
# include <string>
# include <iostream>
# include <sys/socket.h>
# include <unistd.h>
# include <vector>

enum State
{
	DEFAULT,
	PWSET,
	REGISTER,
	UNREGISTER,
};

class Server;

class Client
{
    public : 
		std::map<std::string, void(*)(Server *, int, std::vector<std::string>)> cmdList;
	
		Client();
		Client(int fd);
		~Client();
		char		*getBuf();
		int			getFD();
		int			parseMSG(std::string tempStr);
		void		registerClient();
		void		excute(Server *server);
		void		setRealName(std::string str);
		void		setNickName(std::string str);
		void		setUserName(std::string str);
		void		setHostName(std::string str);
		void		setUserState();
		std::string	getUserName();
		std::string getNickName();
		std::string getHostName();
		std::string getRealName();
		State		getUserState();
        // Channel	getmyChannelList();
		// void	setmyChannelList();
		    // getter, setter
		// void	partMyChannel(); //vector.erase 클라이언트가 채널을 나갈 때 
		    //TODO : part명령어가 여러개의 채널을 동시에 떠날 수 있는지 체크하기
 
	private :
		bool						isOperator; //방장이면 true
		int							fd;
		int							passwd;
		State						userState;
		std::vector<std::string>	msg;
		std::string					hostName;
		std::string					nickName;
		std::string					userName;
		std::string					realName;
		char						bufRead[4096];
    // ...
		//TODO : 사용되는 이름 조사하기
		// std::vector<Channel> _myChannelList;
        //  char *_msgBuffer; //*클라이언트에게 보낼 메세지버퍼;
};

#endif