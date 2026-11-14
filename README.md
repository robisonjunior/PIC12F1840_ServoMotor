\# GoHobby Servo Converter (PIC12F1840)



Este projeto consiste em um firmware desenvolvido em C para o microcontrolador \*\*PIC12F1840\*\*, projetado para rotacionar o servo motor de 0 a 180 graus.



\## 📌 Funcionalidades

\* \*\*Leitura do botao de Entrada:\*\* 

Inicialmente, quando liga o uC, o software gira para 0 graus o servo motor.

Aguarda pressionar o botão para girar para 180 graus ou 0 graus.


\* \*\*Saída PWM Estabilizada:\*\* Gera o sinal de saída na frequência correta de operação dos servos (50Hz).

0 graus = pulso de 500us

180 graus = pulso de 2500us



\## 🛠️ Tecnologias e Ferramentas

\* \*\*Ambiente de Desenvolvimento:\*\* MPLAB X IDE

\* \*\*Compilador:\*\* Microchip XC8

\* \*\*Microcontrolador:\*\* Microchip PIC12F1840



\## 🔌 Conexões do Circuito (Pinagem)

\* \*\*VCC:\*\* 5V (Garantir alimentação regulada para o PIC)

\* \*\*GND:\*\* Terra comum (interligado com pic e o servo)

\* \*\*Entrada (Signal In):\*\* Pino RC\_IN \_\[Atualizar com o pino correto, ex: RA2]\_ <- Conectado ao receptor do Drone

\* \*\*Saída (Servo Out):\*\* Pino SERVO\_OUT \_\[Atualizar com o pino correto, ex: RA0]\_ -> Conectado ao sinal do Servo



\## 🚀 Como clonar e compilar

1\. Clone o repositório em sua pasta de projetos:

&#x20;  ```bash

&#x20;  git clone https://github.com

&#x20;  ```

2\. Abra o MPLAB X IDE.

3\. Vá em \*\*File > Open Project\*\* e selecione a pasta `PIC12F1840_ServoMotor\PIC12F1840_ServoMotor.X`.

4\. Certifique-se de ter o compilador XC8 instalado e configurado nas propriedades do projeto.

5\. Clique em \*\*Clean and Build\*\*.



