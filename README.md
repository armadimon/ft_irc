# ft_irc
Internet Relay Chat or IRC is a text-based communication protocol on the Internet. It offers real-time messaging that can be either public or private. Users can exchange direct messages and join group channels.

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
