# ft_irc
Internet Relay Chat or IRC is a text-based communication protocol on the Internet. It offers real-time messaging that can be either public or private. Users can exchange direct messages and join group channels.

<br>

## ํ์
๐ฆ [juahn](https://github.com/armadimon) &emsp; ๐ง  [younjkim](https://github.com/objectio)

<br>

## ๊ตฌํ ๊ธฐ๊ฐ
2023/02/09 ~ 2023/03/03

<br>

## ๊ฐ๋ฐ ๊ณผ์ 

### 2์ 9์ผ (๋ชฉ)
* ๊ณต์  ๋ ํฌ์งํ ๋ฆฌ ์์ฑ
* ๊น ์ปจ๋ฒค์ ์ ๋ฆฌ
* irc ๊ฐ๋, ํ์ฉ ํจ์ ์ ๋ฆฌ
* ๋๋ต์ ์ธ ํ๋ก๊ทธ๋จ ๊ตฌ์กฐ ์ก๊ธฐ

### 2์ 10์ผ (๊ธ)
* ๋ฉ์ดํฌํ์ผ, ๋ฉ์ธํ์ผ, ํค๋ํ์ผ ์์ฑ
* reference IRC client ์ ํ๊ธฐ (irssi, **limechat**)
* ํด๋ผ์ด์ธํธ์ ์๋ฒ์ ์์ผ ํต์  ๋ถ์์  ์ฐ๊ฒฐ (polling - Select ์ด์ฉ)
* ์ฐ๊ฒฐ๋ ํด๋ผ์ด์ธํธ์์ ๋ณด๋ด๋ ๋ฉ์ธ์ง ์ถ๋ ฅ

### 2์ 11์ผ (ํ )
* ํด๋ผ์ด์ธํธ๊ฐ ๋ณด๋ด๋ ๋ฉ์ธ์ง ์ถ๋ ฅํ๋ ๊ณผ์ ์์ ์๊ธด ์ค๋ฅ ํด๊ฒฐ
* ์์ผ ํต์  ์์ ํ
* ์์ผ ํต์  ํ ๋ฉ์ธ์ง ๋ฐ์๋ณด๊ธฐ ๊ตฌํ ์๋ฃ!

### 2์ 13์ผ (์)
* Client - ๋ฉ์ธ์ง ํ์ฑ ๊ตฌํ
* PASS ๊ด๋ จ ๊ตฌํ ๋ด์ฉ ์์

### 2์ 14์ผ (ํ)
* Channel ํด๋์ค ์์ฑ
* ์ปค๋งจ๋ ์คํ์ ํจ์ ํฌ์ธํฐ๋ก ๊ตฌํ
* User state ์ถ๊ฐ

### 2์ 15์ผ (์)
* JOIN ์ปค๋งจ๋ ์์ ๊ตฌํ
* Server, Channel, Client์ ํ์ํ ๋ฉค๋ฒ ์ถ๊ฐํ๊ธฐ 

### 2์ 16์ผ (๋ชฉ)
* ํด๋ผ์ด์ธํธ ๋ชฉ๋ก ์๋ฐ์ดํธ
* KICK ์ปค๋งจ๋ ์์ ๊ตฌํ (channel operator command)
* trim Utility ํจ์ ์ถ๊ฐ

### 2์ 17์ผ (๊ธ)
* JOIN ์ปค๋งจ๋ ๊ตฌํ

### 2์ 18์ผ (ํ ) ~ 2์ 22์ผ (์)
* younjkim์ ์ผ๋ณธ์ฌํ์ผ๋ก ์ธํด ์ฌ์ด๊ฐ ๐ถโ๐ซ๏ธ

### 2์ 23์ผ (๋ชฉ)
* numeric reply
* Channel Class ์ผ๋ถ ๋ฆฌํฉํ ๋ง

### 2์ 24์ผ (๊ธ)
* Command ํด๋์ค ๊ตฌํ
* ๋ช๋ น์ด ๋ฆฌํฉํ ๋ง

### 2์ 25์ผ (ํ )
* KICK ์ปค๋งจ๋ ๊ตฌํ
* Command ํด๋์ค ์ ์ฉ
* ์ผ๋ถ Numeric Reply ๊ตฌํ

### 2์ 27์ผ (์)
* PART ์ปค๋งจ๋ ๊ตฌํ
* NOTICE ๊ตฌํ
* client ์ธ์ฆ ์์คํ ๋ณด์
* ๋์ด์ ๋ณด๋ธ ์ปค๋งจ๋ '\n' ๋ง๋  ๋๊น์ง ReadBuf์์ ์ด์ด๋ถ์ด๊ธฐ

### 2์ 28์ผ (ํ)
* reply ์ถ๊ฐ
* ์์ํ ๋ฆฌํฉํ ๋ง

### 3์ 1์ผ (์)
* ์ฑ๋ ์ญ์  ๊ด๋ฆฌ
* QUIT ๋ช๋ น์ด ๊ตฌํ

### 3์ 2์ผ (๋ชฉ)
* ์ฐ๊ฒฐ ๋๊ธฐ๋ ๋ฌธ์  ํด๊ฒฐ
* ๋ฆฌํฉํ ๋ง ๋ฐ ํด๋ฆฐ์
* ํ์คํธ
* ๊ฐ์ ์ข๋ฃ ํ leak ๊ฒ์ฌ

### 3์ 3์ผ (๊ธ)
* ํ๊ฐ ์ค๋น
* ํ๊ฐ ์๋ฃ
