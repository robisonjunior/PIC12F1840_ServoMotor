# Controle de Servomotor com PIC e MCC (Timer1 e Debounce)

Firmware desenvolvido para microcontroladores PIC utilizando o **Microchip Code Configurator (MCC)**, implementando o controle preciso de um servomotor (como SG90 ou equivalentes) acionado por botão físico com debouncing por software e temporização via **Timer1** (50 Hz / 20 ms).

---

## 📋 Funcionalidades

- **Geração de PWM por Software/Timer:** Utiliza o Timer1 configurado para disparar a cada 20 ms (50 Hz), controlando os pulsos em nível alto no pino **RA2**.
- **Alternância de Posições:** Um botão conectado ao pino **RA4** permite alternar entre duas posições pré-definidas (0° e 180°).
- **Debounce por Software:** Filtro integrado para evitar leituras falsas causadas pelo ruído mecânico do botão.
- **Configuração via MCC:** Gerado utilizando as bibliotecas de sistema do ecossistema MPLAB X / MCC.

---

## 🛠️ Especificações Técnicas e Pinos

| Parâmetro / Periférico | Descrição / Conexão |
| :--- | :--- |
| **Clock do Sistema** | 16 MHz |
| **Pino de Saída (Servo)** | `RA2` (Gera o pulso de controle PWM) |
| **Pino de Entrada (Botão)** | `RA4` (Com resistor *Pull-Up* externo de 10k: Pressionado = `LOW` / `0`) |
| **Base de Tempo** | Timer1 (Período de interrupção de 20 ms) |
| **Posição 0°** | Pulso de ~550 µs |
| **Posição 180°** | Pulso de ~2500 µs |

---

## ⚙️ Lógica de Funcionamento

1. **Inicialização (`main`):**
   - O sistema inicializa os osciladores e periféricos através de `SYSTEM_Initialize()`.
   - O pino `RA4` é configurado explicitamente como entrada digital.
   - O *callback* do Timer1 é registrado (`Servo_Pulse_Handler`) e a contagem de 50 Hz é iniciada.

2. **Geração de Pulsos (`Servo_Pulse_Handler`):**
   - A cada estouro do Timer1 (20 ms), o pino `RA2` vai para nível alto (`High`).
   - Dependendo da variável global `posicao_servo` (`0` ou `1`), o firmware aguarda o tempo correspondente (`__delay_us`) e retorna o pino para nível baixo (`Low`).

3. **Leitura do Botão (`while(1)`):**
   - O loop principal monitora continuamente o estado do pino `RA4`.
   - Ao detectar o acionamento (`LOW`), aguarda 40 ms para estabilização (*debounce*), inverte o estado da variável `posicao_servo` e trava a execução até que o botão seja solto.

---

## 📁 Estrutura do Projeto

```text
├── mcc_generated_files/    # Arquivos gerados pelo Microchip Code Configurator (System, Pin Manager, Timer1)
├── main.c                  # Código principal da aplicação e rotina de interrupção do servo
└── README.md               # Documentação do projeto
 para o PIC)

\* \*\*GND:\*\* Terra comum (interligado com pic e o servo)

\* \*\*Entrada (Signal In):\*\* Pino RC\_IN \_\[Atualizar com o pino correto, ex: RA2]\_ <- Conectado ao receptor do Drone

\* \*\*Saída (Servo Out):\*\* Pino SERVO\_OUT \_\[Atualizar com o pino correto, ex: RA0]\_ -> Conectado ao sinal do Servo



\## 🚀 Como clonar e compilar

1\. Clone o repositório em sua pasta de projetos:

&#x20;  ```bash

&#x20;  git clone https://github.com

&#x20;  ```

2\. Abra o MPLAB X IDE.

3\. Vá em \*\*File > Open Project\*\* e selecione a pasta `PIC12F1840_ServoMotor\SERVOMOTOR.X`.

4\. Certifique-se de ter o compilador XC8 instalado e configurado nas propriedades do projeto.

5\. Clique em \*\*Clean and Build\*\*.



