#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
#define LED_VERDE 7
#define LED_VERMELHO 5

#define BOTAO_DIFICULDADE 2
#define BOTAO_CATEGORIA 3
#define BOTAO_CONFIRMAR 4

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

struct ItemRFID {
  const char* nome;
  const char* uid;
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

const char* objetos[][2] = {
  {"Livro", "Estojo"},      // Facil
  {"Borracha"},             // Intermed.
  {"Lapis", "Bolsa"}        // Dificil
};

const char* numeros[][2] = {
  {"3", "2"},               // Facil
  {"6"},                   // Intermed.
  {"5", "8"}                // Dificil
};

const char* animais[][2] = {
  {"Peixe", "Gato"},
  {"Cachorro"},
  {"Cavalo", "Tartaruga"}
};

const char* dias[][2] = {
  {"Quarta-feira", "Terca-feira"},
  {"Quinta-feira"},
  {"Sabado", "Domingo"}
};

int indiceDificuldade = 0;
int indiceCategoria = 0;
const char* itemSorteado = nullptr;

bool aguardandoConfirmacao = false;

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
  mostrarInstrucoes();
}

void loop() {
  if (digitalRead(BOTAO_DIFICULDADE) == LOW) {
    delay(200);
    indiceDificuldade = (indiceDificuldade + 1) % 3;
    mostrarMenu();
  }

  if (digitalRead(BOTAO_CATEGORIA) == LOW) {
    delay(200);
    indiceCategoria = (indiceCategoria + 1) % 4;
    mostrarMenu();
  }

  if (digitalRead(BOTAO_CONFIRMAR) == LOW) {
    delay(200);
    sortearItem();
  }

  if (aguardandoConfirmacao) {
    verificarTag();
  }
}

void mostrarInstrucoes() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pressione botao");
  lcd.setCursor(0, 1);
  lcd.print("para comecar");
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

void sortearItem() {
  const char** lista = nullptr;
  int tamanho = 0;

  switch (indiceCategoria) {
    case 0: lista = objetos[indiceDificuldade]; tamanho = sizeof(objetos[indiceDificuldade]) / sizeof(char*); break;
    case 1: lista = numeros[indiceDificuldade]; tamanho = sizeof(numeros[indiceDificuldade]) / sizeof(char*); break;
    case 2: lista = animais[indiceDificuldade]; tamanho = sizeof(animais[indiceDificuldade]) / sizeof(char*); break;
    case 3: lista = dias[indiceDificuldade];    tamanho = sizeof(dias[indiceDificuldade]) / sizeof(char*); break;
  }

  if (tamanho > 0) {
    int indice = random(tamanho);
    itemSorteado = lista[indice];

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Encontre:");
    lcd.setCursor(0, 1);
    lcd.print(itemSorteado);
    aguardandoConfirmacao = true;

    Serial.print("Item sorteado: ");
    Serial.println(itemSorteado);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro ao sortear");
    aguardandoConfirmacao = false;
  }
}

void verificarTag() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) return;

  String lido = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) lido += "0";
    lido += String(mfrc522.uid.uidByte[i], HEX);
  }
  lido.toUpperCase();

  Serial.print("UID lido: ");
  Serial.println(lido);

  for (int i = 0; i < sizeof(itens) / sizeof(ItemRFID); i++) {
    if (String(itens[i].uid).equalsIgnoreCase(lido)) {
      if (String(itens[i].nome).equalsIgnoreCase(itemSorteado)) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Correto!");
        lcd.setCursor(0, 1);
        lcd.print(itemSorteado);
        digitalWrite(LED_VERDE, HIGH);
        digitalWrite(LED_VERMELHO, LOW);
      } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Errado!");
        lcd.setCursor(0, 1);
        lcd.print(itens[i].nome);
        digitalWrite(LED_VERDE, LOW);
        digitalWrite(LED_VERMELHO, HIGH);
      }

      delay(3000);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_VERMELHO, LOW);
      mostrarInstrucoes();
      aguardandoConfirmacao = false;
      return;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tag invalida");
  delay(2000);
  mostrarInstrucoes();
  aguardandoConfirmacao = false;
}
