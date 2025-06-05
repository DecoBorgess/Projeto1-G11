# Corrida de Sinais ☝️✌️

## Objetivo do Projeto

O jogo **Corrida de Sinais** é um jogo interativo acessível com o intuito de **promover a inclusão de pessoas surdas**. Por meio de um sistema físico com **Arduino**, **leitor RFID**, **LCD**, **LEDs**, e **botões**, os jogadores são incentivados a interagir com as cartas e sinais, reforçando seu aprendizado e a prática de **Libras** (Língua Brasileira de Sinais) de forma lúdica e educativa.

Este projeto foi desenvolvido como parte da temática **Acessibilidade e Jogos**, com foco em **deficientes auditivos**, buscando criar um ambiente de aprendizado **inclusivo, divertido e tecnológico**.

## Como Funciona

- O jogador escolhe a **dificuldade** e a **categoria** (Animais, Dias da Semana, Números ou Objetos).
- O sistema sorteia um item (ex: “Cachorro” ou “Terça-feira”).
- O jogador deve identificar e escanear no leitor RFID a **carta correta**, representando aquele item em Libras.
- O sistema verifica se o item está correto:
  - **LED verde** acende se a tag estiver certa.
  - **LED vermelho** acende se estiver errada.
  - A informação é exibida no **display LCD**.

## Tecnologias e Componentes Utilizados

- **Arduino UNO**
- **Leitor RFID RC522**
- **Tags RFID**
- **Display LCD I2C (16x2)**
- **3 botões (push-button)**
  - Seleção de dificuldade
  - Seleção de categoria
  - Confirmação
- **LEDs (verde e vermelho)**
- **Protoboard e jumpers**
- **Bibliotecas utilizadas no Arduino:**
  - `SPI.h`
  - `MFRC522.h`
  - `Wire.h`
  - `LiquidCrystal_I2C.h`

## Montagem do Circuito

Monte os componentes da seguinte forma:

- **Leitor RFID RC522**:
  - SDA -> pino 10 do Arduino
  - RST -> pino 9
  - Os outros pinos (SCK, MOSI, MISO) vão nos pinos 13, 11, 12 do Arduino

- **Display LCD I2C (16x2)**:
  - SDA -> A4
  - SCL -> A5

- **Botões**:
  - Dificuldade -> pino 2
  - Categoria -> pino 3
  - Confirmar -> pino 4

- **LEDs**:
  - LED verde -> pino 7
  - LED vermelho -> pino 5

> *Dica: use resistores de 220Ω nos LEDs e conecte os botões ao GND. No código, os botões já estão configurados com **INPUT_PULLUP**, então não vai precisar do resistor externo.

## Como Rodar o Código

### 1. Requisitos

- Arduino IDE instalada
- Bibliotecas:
  - [MFRC522]
  - [LiquidCrystal_I2C]

### 2. Passos

1. Conecte todos os componentes de acordo com a seção de montagem.
2. Abra o Arduino IDE.
3. Instale as bibliotecas necessárias na aba "Gerenciar Bibliotecas".
4. Copie e cole o código `CorridaDeSinais.ino` no editor.
5. Conecte a placa Arduino via USB.
6. Selecione a porta e a placa correta.
7. Clique em **"Upload"**.
8. O jogo iniciará após carregar.

## Sobre o Aprendizado

O projeto visa estimular o aprendizado de sinais em Libras, utilizando a tecnologia para associar palavras e categorias a movimentos manuais. Com pequenos testes e mostra ao publico, já pudemos perceber como contribuiu positivamente para o aprendizado.

## Contribuições

Este projeto foi desenvolvido por um grupo de estudantes com o propósito de **usar a tecnologia para a inclusão social**. Sugestões de melhoria, novas funcionalidades e contribuições são sempre bem-vindas!

## Autores do código

- [Lucas Bayma]
- [André Borges]
- [Gabriel Pereira]
- [Pedro David Baia]
- Todos estudantes da CESAR School

## Melhorias

Com potencial para ser usado em **escolas, oficinas e feiras educacionais**, o Corrida de Sinais pode ser expandido com:
- Pontuação por tempo
- Inclusão de mais cartas
- Refinamento do Manual físico
- Criação de um manual digital
