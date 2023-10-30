# -HAMES-1-5
[현모임스] PJT1차 - 5조

## 프로젝트 소개

---

라즈베리파이와 아두이노를 통해 자동차 부품인 스마트 선루프 시스템을 구현한 프로젝트입니다. 각종 센서의 데이터를 라즈베리파이로 입력받아 최종 로직을 형성하고, UART 통신을 통해 아두이노롤 신호를 전달하여 모터와 부저, LED가 작동하도록 구성하여 선루프를 구현하였습니다.
   
## 환경 구축

---

1. Raspberry pi Imager를 통해 OS 설치
2. WiringPi 라이브러리 설치
    
    ```jsx
    cd /tmp
    wget https://project-downloads.drogon.net/wiringpi-latest.deb
    sudo dpkg -i wiringpi-latest.deb
    ```
    
3. QT 설치
    
    ```jsx
    sudo apt update
    sudo apt upgrade
    sudo apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
    sudo apt-get install build-essential perl python-is-python3 2to3
    sudo apt-get install qtcreator
    sudo apt-get install clang
    ```
    
4. QT 환경 WiringPi 라이브러리 Import
    1. 프로젝트 내 .pro 파일에서 Extern Library추가를 통해 WiringPi 추가
        - usr/lib/libwiringPi.so 경로 추가하면 설정 완료
      <img src="https://github.com/JINK004/HAMES_1_5/assets/87352996/59ee36f1-862a-4d1b-8921-0d4060656739.png" width="500" height="150"/>



## 소스코드 빌드 및 실행 방법

---

1. QTcreator 실행
    
    ```jsx
    pi@raspberrypi:~ $ qtcreator
    ```
    
2. Open Project를 선택
    ![1](https://github.com/JINK004/HAMES_1_5/assets/87352996/596079f4-9793-4a50-b312-d0ec0e9369fe)

    
3. 프로젝트 구성 파일 전부 선택 후 Open 클릭
    ![2](https://github.com/JINK004/HAMES_1_5/assets/87352996/79643711-de7d-4807-a9c2-f184779d3b69)

    
4. 왼쪽 하단 실행버튼 클릭 시, build 완료
   
    ![3](https://github.com/JINK004/HAMES_1_5/assets/87352996/4dac774a-428f-4de4-8e34-1c3809a46f31)
