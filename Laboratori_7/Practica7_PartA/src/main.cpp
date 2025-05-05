#include <Arduino.h>
#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "sampleaac.h"

// Punter per gestionar la font, el decodificador i la sortida
AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;

void setup() {
  Serial.begin(115200);
  delay(500); // petit delay per estabilitzar el port sèrie

  Serial.println("Inicialitzant audio des de memòria interna...");

  // Inicialització dels components
  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();

  // Configuració de la sortida I2S
  out->SetPinout(18, 15, 21);  // BCLK, LRCLK, DIN
  out->SetGain(0.125);         // Volum de sortida (entre 0.0 i 1.0)

  // Iniciar la reproducció
  if (!aac->begin(in, out)) {
    Serial.println("Error en començar la reproducció AAC");
  }
}

void loop() {
  if (aac->isRunning()) {
    aac->loop();
  } else {
    aac->stop();
    Serial.println("Reproducció finalitzada.");
    delay(2000);
  }
}
