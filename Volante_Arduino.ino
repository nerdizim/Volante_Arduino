#include <Joystick.h>

// Configura o joystick com 3 eixos: volante (X), acelerador (Z), freio (RX)
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
                   JOYSTICK_TYPE_GAMEPAD,
                   0, 0,
                   true,   // X  → volante
                   false, 
                   true,   // Z  → acelerador
                   true,   // RX → freio
                   false, false, 
                   false, false,
                   false, false, false);

// Ajuste fino da calibração do centro do volante
const int CENTRO_REAL_VOLANTE = 594;
const int CENTRO_DESEJADO_VOLANTE = 512;
const int ZONA_MORTA_VOLANTE = 4;
const int ZONA_MORTA_PEDAL = 100; // zona morta para freio e acelerador

void setup() {
  Joystick.begin();
  Joystick.setXAxisRange(0, 1023);
  Joystick.setZAxisRange(0, 1023);
  Joystick.setRxAxisRange(0, 1023);
}

// Aplica correção de centralização do volante
int calibrarVolante(int leitura) {
  int diferenca = CENTRO_REAL_VOLANTE - CENTRO_DESEJADO_VOLANTE;
  int corrigido = leitura - diferenca;
  return constrain(corrigido, 0, 1023);
}

// Suaviza o volante com média móvel
int suavizarVolante(int novaLeitura) {
  static int buffer[5] = {0};
  static int index = 0;
  static int soma = 0;

  soma -= buffer[index];
  buffer[index] = novaLeitura;
  soma += novaLeitura;

  index = (index + 1) % 5;

  return soma / 5;
}

// Aplica zona morta no volante
int aplicarZonaMortaVolante(int valor, int centro, int zona) {
  if (abs(valor - centro) <= zona) return centro;
  return valor;
}

// Aplica zona morta para pedais
int aplicarZonaMortaPedal(int valor, int limiar) {
  if (valor < limiar) return 0;
  return valor;
}

void loop() {
  // Volante
  int rawVolante = analogRead(A0);
  int volante = 1023 - rawVolante;                          // Inverte direção
  volante = calibrarVolante(volante);                       // Corrige centro
  volante = suavizarVolante(volante);                       // Suaviza
  volante = aplicarZonaMortaVolante(volante, 512, ZONA_MORTA_VOLANTE);

  // Acelerador
  int acelerador = 1023 - analogRead(A1);                   // Inverte se necessário
  acelerador = aplicarZonaMortaPedal(acelerador, ZONA_MORTA_PEDAL);

  // Freio
  int freio = 1023 - analogRead(A2);                        // Inverte se necessário
  freio = aplicarZonaMortaPedal(freio, ZONA_MORTA_PEDAL);

  // Envia para o PC
  Joystick.setXAxis(volante);
  Joystick.setZAxis(acelerador);
  Joystick.setRxAxis(freio);

  delay(10);
}

