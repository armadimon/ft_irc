#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <map>
# include <string>
# include <iostream>
# include <sys/socket.h>
# include <unistd.h>

class Client
{
    public : 
		Client();
		Client(int fd);
		~Client();
		void clientRead();
        // Channel	getmyChannelList();
		// void	setmyChannelList();
		    // getter, setter
		// void	partMyChannel(); //vector.erase 클라이언트가 채널을 나갈 때 
		    //TODO : part명령어가 여러개의 채널을 동시에 떠날 수 있는지 체크하기 
	private :
		// bool	_isOperator; //방장이면 true
		int		fd;
		char	*bufRead[4096];
    // ...
		//TODO : 사용되는 이름 조사하기
		// std::vector<Channel> _myChannelList;
        //  char *_msgBuffer; //*클라이언트에게 보낼 메세지버퍼;
};

#endif