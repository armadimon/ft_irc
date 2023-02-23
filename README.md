# ft_irc
Internet Relay Chat or IRC is a text-based communication protocol on the Internet. It offers real-time messaging that can be either public or private. Users can exchange direct messages and join group channels.

<br>

## 팀원
🦔 [juahn](https://github.com/armadimon) &emsp; 🧠 [younjkim](https://github.com/objectio)

<br>

## 구현 기간
2023/02/09 ~

<br>

## 개발 과정

### 2월 9일 (목)
* 공유 레포지토리 생성
* 깃 컨벤션 정리
* irc 개념, 허용 함수 정리
* 대략적인 프로그램 구조 잡기

### 2월 10일 (금)
* 메이크파일, 메인파일, 헤더파일 생성
* reference IRC client 정하기 (irssi, **limechat**)
* 클라이언트와 서버의 소켓 통신 불완전 연결 (polling - Select 이용)
* 연결된 클라이언트에서 보내는 메세지 출력

### 2월 11일 (토)
* 클라이언트가 보내는 메세지 출력하는 과정에서 생긴 오류 해결
* 소켓 통신 안정화
* 소켓 통신 후 메세지 받아보기 구현 완료!

### 2월 13일 (월)
* Client - 메세지 파싱 구현
* PASS 관련 구현 내용 상의

### 2월 14일 (화)
* Channel 클래스 작성
* 커맨드 실행을 함수 포인터로 구현
* User state 추가

### 2월 15일 (수)
* JOIN 커맨드 임시 구현
* Server, Channel, Client에 필요한 멤버 추가하기 

### 2월 16일 (목)
* 클라이언트 목록 업데이트
* KICK 커맨드 임시 구현 (channel operator command)
* trim Utility 함수 추가

### 2월 17일 (금)
* JOIN 커맨드 

### 2월 18일 (토) ~ 2월 22일 (수)
* younjkim의 일본여행으로 인해 쉬어감 😶‍🌫️

### 2월 23일 (목)
* numeric reply
* Channel Class 일부 리팩토링

### TODO

* client 인증 시스템 보완 - 현재 state는
   1. DEFAULT,
   2.	PWSET,
   3.	REGISTER,
   4.	UNREGISTER,


   4개로 구성되어있고, 커맨드 구현하면서 state에 대한 구분을 더 세부적으로 해야할 수도있음.

* 프라이빗 메시지, JOIN 완성, 채널 기능 완성
* NOTICE 구현
* KICK 구현
* reply 구현
* 리팩토링
* 강제종료 후 leak 검사
