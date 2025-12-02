# 🤖 Projeto Robô Multitarefas com Arduino (OLED, LCD, Servo e Semáforo)

Este projeto demonstra a **multitarefa cooperativa** em um microcontrolador Arduino, utilizando a função `millis()` para gerenciar o tempo de forma não-bloqueante. O sistema integra dois displays I2C, dois servos motores e um conjunto de LEDs que simulam um semáforo, todos funcionando **simultaneamente** e de forma coordenada.

---

## ⚙️ Componentes Necessários

| Componente | Quantidade | Observações |
| :--- | :---: | :--- |
| **Arduino** Uno/Nano | 1 | Placa principal. |
| **Display OLED** I2C (SSD1306) | 1 | 128x64 pixels (Conteúdo estático: Imagem). |
| **Display LCD** I2C (16x2) | 1 | Com módulo I2C (Conteúdo estático: Olhos customizados). |
| **Servo Motores** (SG90 ou similar) | 2 | Para os "braços" do robô (Movimento lento e contínuo). |
| **LED Vermelho, Amarelo, Verde** | 1 de cada | Simulação de Semáforo. |
| **Resistores** (220 $\Omega$ ou 330 $\Omega$) | 3 | Para proteger os LEDs. |

---

## 🔌 Conexões de Hardware

### 1. Comunicação I2C (Displays)

Ambos os displays compartilham os mesmos pinos de comunicação:

| Pino do Componente | Pino do Arduino (Uno/Nano) |
| :---: | :--- |
| **SDA** (Dados) | **A4** (Analógico 4) |
| **SCL** (Clock) | **A5** (Analógico 5) |
| **VCC/GND** | **+5V/GND** |

### 2. Servo Motores

Conectados a pinos com capacidade **PWM** (Sinal Laranja/Amarelo):

| Servo | Pino do Arduino |
| :--- | :---: |
| **Esquerdo** | **Digital 9** |
| **Direito** | **Digital 10** |

### 3. Semáforo (LEDs)

Conecte os LEDs aos pinos digitais, utilizando um resistor em série:

| Cor do LED | Pino do Arduino |
| :--- | :---: |
| **Vermelho** | **Digital 7** |
| **Amarelo** | **Digital 6** |
| **Verde** | **Digital 5** |



[Image of Arduino LED connection with resistor]


---

## 📚 Bibliotecas Necessárias

Instale as seguintes bibliotecas no seu Arduino IDE (via Gerenciador de Bibliotecas):

1.  **`Adafruit GFX Library`**
2.  **`Adafruit SSD1306`**
3.  **`LiquidCrystal I2C`**
4.  **`Servo`** (Geralmente nativa no IDE)

---

## 🧠 Funcionamento do Código

O segredo para o **funcionamento simultâneo** (LEDs mudando enquanto Servos se movem) é a eliminação da função `delay()` e a implementação de duas máquinas de tempo independentes na função `loop()`, baseadas em `millis()`.

### 1. Conteúdo Estático (Setup)

* Todo o código de desenho para o **OLED** (imagem) e para o **LCD** (olho customizado) é executado apenas no `setup()`.
* O conteúdo dos displays permanece fixo durante toda a execução do programa.

### 2. Lógica do Semáforo (Não-Bloqueante)

* Utiliza a variável `semaphoreState` (`0` a `3`) para saber a fase atual (Vermelho, Amarelo, Verde).
* A cada ciclo do `loop()`, o código verifica se o tempo alocado para o estado atual (`RED_TIME`, `GREEN_TIME`, etc.) já passou usando: `if (millis() - lastSemaphoreChange >= duration)`.
* Se o tempo esgotou, ele avança para o próximo estado e acende o LED correspondente, reiniciando o cronômetro.

### 3. Lógica dos Servos (Movimento Contínuo e Lento)

* O movimento é feito em **passos de 1 grau**, a cada **15ms** (`SERVO_INTERVAL`).
* O código usa a mesma lógica `millis()`: `if (millis() - lastServoMove >= SERVO_INTERVAL)`.
* **Movimento Oposto:** O `servoEsquerdo` avança de `0°` a `180°`, enquanto o `servoDireito` avança de `180°` a `0°` (`servoDireito.write(180 - servoPosition)`), criando o movimento de braços de forma espelhada e uniforme.