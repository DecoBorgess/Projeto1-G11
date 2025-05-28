#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_VERDE 7
#define LED_VERMELHO 6

#define BOTAO_DIFICULDADE 2
#define BOTAO_CATEGORIA 3
#define BOTAO_CONFIRMAR 4

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

struct ItemRFID {
  String nome;
  String uid;
};

ItemRFID itens[] = {
  {"3", "048165F5270289"}, {"2", "04612404270289"}, {"5", "04D146F5270289"}, {"8", "04712304270289"},
  {"Quarta-feira", "04A10604270289"}, {"Terca-feira", "04A10804270289"}, {"Quinta-feira", "045126F5270289"},
  {"Domingo", "04612504270289"}, {"Sabado", "04D145F5270289"},
  {"Livro", "04612704270289"}, {"Estojo", "04214004270289"}, {"Borracha", "04D147F5270289"},
  {"Lapis", "04E144F5270289"}, {"Bolsa", "04712204270289"},
  {"Peixe", "04612604270289"}, {"Gato", "04A10904270289"}, {"Cachorro", "04D148F5270289"},
  {"Cavalo", "048166F5270289"}, {"Tartaruga", "04E143F5270289"}
};

const char* dificuldades[] = {"Facil", "Intermed.", "Dificil"};
const char* categorias[] = {"Objetos", "Numeros", "Animais", "Dias"};

const char* objetosFacil[] = {"Livro", "Estojo"};
const char* objetosIntermed[] = {"Borracha"};
const char* objetosDificil[] = {"Lapis", "Bolsa"};

const char* numerosFacil[] = {"3", "2"};
const char* numerosIntermed[] = {"6"};
const char* numerosDificil[] = {"5", "8"};

const char* diaFacil[] = {"Quarta-feira", "Terca-feira"};
const char* diaIntermed[] = {"Quinta-feira"};
const char* diaDificil[] = {"Sabado", "Domingo"};

const char* animalFacil[] = {"Peixe", "Gato"};
const char* animalIntermed[] = {"Cachorro"};
const char* animalDificil[] = {"Cavalo", "Tartaruga"};

int indiceDificuldade = 0;
int indiceCategoria = 0;
int indiceEsperado = 0;

bool estadoAnteriorBotao1 = HIGH;
bool estadoAnteriorBotao2 = HIGH;
bool estadoAnteriorBotao3 = HIGH;

unsigned long ultimaLeituraBotao1 = 0;
unsigned long ultimaLeituraBotao2 = 0;
unsigned long ultimaLeituraBotao3 = 0;
const unsigned long debounceDelay = 100;

bool prontoParaComecar = false;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  pinMode(BOTAO_DIFICULDADE, INPUT_PULLUP);
  pinMode(BOTAO_CATEGORIA, INPUT_PULLUP);
  pinMode(BOTAO_CONFIRMAR, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  randomSeed(analogRead(0));
  mostrarMensagemInicial();
}

void loop() {
  gerenciarBotoes();
  if (prontoParaComecar) {
    verificarCartao();
  }
}

void mostrarMensagemInicial() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Clique ENTER p/");
  lcd.setCursor(0, 1);
  lcd.print("comecar");
}

void mostrarMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dif: ");
  lcd.print(dificuldades[indiceDificuldade]);
  lcd.setCursor(0, 1);
  lcd.print("Categ: ");
  lcd.print(categorias[indiceCategoria]);
}

void mostrarItemSorteado(int categoria, int dificuldade) {
  const char** lista = nullptr;
  int tamanho = 0;
  switch (categoria) {
    case 0: if (dificuldade == 0) { lista = objetosFacil; tamanho = 2; }
            else if (dificuldade == 1) { lista = objetosIntermed; tamanho = 1; }
            else { lista = objetosDificil; tamanho = 2; } break;
    case 1: if (dificuldade == 0) { lista = numerosFacil; tamanho = 2; }
            else if (dificuldade == 1) { lista = numerosIntermed; tamanho = 1; }
            else { lista = numerosDificil; tamanho = 2; } break;
    case 2: if (dificuldade == 0) { lista = animalFacil; tamanho = 2; }
            else if (dificuldade == 1) { lista = animalIntermed; tamanho = 1; }
            else { lista = animalDificil; tamanho = 2; } break;
    case 3: if (dificuldade == 0) { lista = diaFacil; tamanho = 2; }
            else if (dificuldade == 1) { lista = diaIntermed; tamanho = 1; }
            else { lista = diaDificil; tamanho = 2; } break;
  }
  if (lista && tamanho > 0) {
    int indice = random(tamanho);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Item:");
    lcd.setCursor(0, 1);
    lcd.print(lista[indice]);
    // Atualiza item esperado
    for (int i = 0; i < sizeof(itens)/sizeof(itens[0]); i++) {
      if (itens[i].nome == lista[indice]) {
        indiceEsperado = i;
        break;
      }
    }
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro ao sortear");
  }
}

void verificarCartao() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  String conteudo = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    byte b = mfrc522.uid.uidByte[i];
    if (b < 0x10) conteudo += "0";
    conteudo += String(b, HEX);
  }
  conteudo.toUpperCase();

  Serial.print("UID lido: ");
  Serial.println(conteudo);

  if (conteudo == itens[indiceEsperado].uid) {
    Serial.println("✅ CORRETO! Item: " + itens[indiceEsperado].nome);
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
  } else {
    Serial.println("❌ INCORRETO!");
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
  }

  delay(3000);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  mostrarMensagemInicial();
  prontoParaComecar = false;
}

void gerenciarBotoes() {
  unsigned long tempoAtual = millis();

  bool leituraBotao1 = digitalRead(BOTAO_DIFICULDADE);
  if (leituraBotao1 == LOW && estadoAnteriorBotao1 == HIGH && (tempoAtual - ultimaLeituraBotao1) > debounceDelay) {
    if (prontoParaComecar) {
      indiceDificuldade = (indiceDificuldade + 1) % 3;
      mostrarMenu();
    }
    ultimaLeituraBotao1 = tempoAtual;
  }
  estadoAnteriorBotao1 = leituraBotao1;

  bool leituraBotao2 = digitalRead(BOTAO_CATEGORIA);
  if (leituraBotao2 == LOW && estadoAnteriorBotao2 == HIGH && (tempoAtual - ultimaLeituraBotao2) > debounceDelay) {
    if (prontoParaComecar) {
      indiceCategoria = (indiceCategoria + 1) % 4;
      mostrarMenu();
    }
    ultimaLeituraBotao2 = tempoAtual;
  }
  estadoAnteriorBotao2 = leituraBotao2;

  bool leituraBotao3 = digitalRead(BOTAO_CONFIRMAR);
  if (leituraBotao3 == LOW && estadoAnteriorBotao3 == HIGH && (tempoAtual - ultimaLeituraBotao3) > debounceDelay) {
    if (!prontoParaComecar) {
      prontoParaComecar = true;
      mostrarMenu();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sorteando...");
      delay(1000);
      mostrarItemSorteado(indiceCategoria, indiceDificuldade);
    }
    ultimaLeituraBotao3 = tempoAtual;
  }
  estadoAnteriorBotao3 = leituraBotao3;
}
