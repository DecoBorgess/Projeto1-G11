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
