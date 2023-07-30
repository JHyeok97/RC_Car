# **RC Car (Remote Control Car)**

RC Car는 **블루투스 통신**으로 원격으로 조종 하고 데이터를 **CAN 통신**으로 주고 받는 프로젝트

## 목차
[1.프로젝트 목적](#프로젝트-목적)

[2.프로젝트 설명](#프로젝트-설명)

[3.개발 환경](#개발-환경)

[4.회로도](#회로도)

[5.결과](#결과)

## 프로젝트 목적
- CAN 통신과 블루투스 모듈을 사용하여 자동차 모터를 제어한다.

## 프로젝트 설명
- 핸드폰 어플을 통해 블루투스를 연결하여 서브 아두이노에 데이터 전송
  
- 서브 아두이노에서 CAN 통신을 통해 메인 아두이노에 데이터 전송

- 메인 아두이노에서 데이터를 받고 모터 제어 (전진, 후진, 좌회전, 우회전, 정지)

- 후진 시 서브 아두이노에 있는 초음파 센서로 거리를 측정해 CAN 통신으로 메인 아두이노에 거리 데이터를 보내고 부저를 울려 물체가 가까이 있음을 알림

- 후진 시 특정 거리 이내로 장애물을 만났을 경우 정지

## 개발 환경

 Language : C++
 
 TOOL : VS Code, Arduino IDE
 
 HW :
     Arduino Uno, L298N(모터 드라이버),DC 모터, 피에조 부저,
     MCP2515 (CAN통신 모듈),HC-06 (블루투스 모듈)

Sensor : HC-SR04(초음파 센서)

     




## 회로도

</br>

<img width="396" alt="image" src="https://github.com/JHyeok97/RC_Car/assets/92672351/e27a2a4d-f7b2-4904-a598-9dd60651c093">

</br>



## 결과

<div>
  
<img width="396" alt="image" src="https://github.com/JHyeok97/RC_Car/assets/92672351/f63e7a79-0c4e-42d7-9101-3496e03ff60e">

</div>


</br>

<div>
  
<img width="396" alt="image" src="https://github.com/JHyeok97/RC_Car/assets/92672351/0db341d1-b9e5-4a41-97da-3e238103bc98">

</div>

</br>

<div>

<img width="396" alt="image" src="https://github.com/JHyeok97/RC_Car/assets/92672351/096cb913-db9a-4d5d-ba58-3cfef323b272">

</div>






