🤖 Projeto: Olhos Robóticos e Braços com Arduino

Este projeto foi criado para aprender conceitos de robótica, eletrônica
e programação com Arduino.
Ele mostra como controlar olhos animados em um display OLED e dois
braços com servos motores, de forma sincronizada e sem travar o código.

------------------------------------------------------------------------

🎯 Objetivos de Aprendizado

1.  Entender como usar um display OLED para mostrar animações.
2.  Aprender a controlar servos motores com precisão.
3.  Usar millis() no lugar de delay() para criar movimentos suaves e
    simultâneos.
4.  Criar um ciclo de animação que faz o robô parecer vivo.

------------------------------------------------------------------------

🛠️ Materiais Necessários

-   1x Arduino Nano R3 (pode usar Uno ou outro compatível).
-   1x Display OLED I2C (SSD1306).
-   2x Servos motores pequenos (9g).
-   1x Protoboard.
-   Jumpers (fios de conexão).

  Dica: se os servos forem grandes, use uma fonte externa para evitar
  sobrecarregar o Arduino.

------------------------------------------------------------------------

🚀 Funcionamento do Código

🔹 1. Início (Setup)

-   O display OLED é iniciado.
-   Os olhos começam fechados.
-   Os braços começam na posição para baixo.

🔹 2. Movimento dos braços (Loop)

-   O Arduino verifica o tempo usando millis().
-   A cada pequeno intervalo, os servos se movem 1 grau por vez até
    chegarem na posição final.
-   Isso deixa o movimento suave e realista.

🔹 3. Animação dos olhos e braços (Sequência)

O robô passa por várias fases, repetindo em um ciclo:

  Tempo (segundos)   Ação
  ------------------ -----------------------------------------------------------
  2s                 Olhos abrem, braços sobem até o meio.
  4s                 Robô fica feliz, começa a rir, braços levantam para cima.
  6s                 Robô fica cansado, braços descem para baixo.
  8s                 Olhos fecham e tudo reinicia.

------------------------------------------------------------------------

📊 Conceitos Importantes

✅ Programação não bloqueante → permite que várias coisas aconteçam ao
mesmo tempo.
✅ Controle gradual de servos → movimentos mais naturais.
✅ Uso de flags (verdadeiro/falso) → garante que cada evento só acontece
no tempo certo.
✅ Integração de hardware → display + servos funcionando juntos.

------------------------------------------------------------------------

🎬 Imagine o Robô…

-   No começo está dormindo 😴 (olhos fechados, braços baixos).
-   Depois acorda feliz 😀 (olhos abertos, braços levantados).
-   Mais tarde fica cansado 💤 (olhos semicerrados, braços descendo).
-   Por fim, volta a dormir.

E o ciclo se repete sem parar.

------------------------------------------------------------------------

📚 Bibliotecas Usadas

Essas bibliotecas devem ser instaladas na IDE Arduino:

-   Adafruit_SSD1306 → controla o display OLED.
-   Servo → controla os motores servo.
-   FluxGarage_RoboEyes → animações dos olhos.

------------------------------------------------------------------------

⚙️ Ligações dos Componentes

-   OLED → conectado ao I2C do Arduino:
    -   SDA → A4
    -   SCL → A5
-   Servo Esquerdo → pino 9
-   Servo Direito → pino 10
-   Todos os servos → 5V e GND

------------------------------------------------------------------------

