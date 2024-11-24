#include <Adafruit_AMG88xx.h>
#include <Adafruit_NeoPixel.h>

// Configuración del AMG8833
Adafruit_AMG88xx amg;
float pixels[64]; // Almacena las lecturas del sensor 8x8

// Configuración de la matriz LED
#define DATA_PIN 2        // Pin conectado a la matriz LED
#define NUM_LEDS 64       // Número total de LEDs
Adafruit_NeoPixel matrix = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Inicializa el serial para depuración
  Serial.begin(9600);
  Serial.println("Inicializando AMG8833...");

  // Inicializa el sensor AMG8833
  if (!amg.begin()) {
    Serial.println("No se pudo inicializar el AMG8833. Verifica las conexiones.");
    while (1); // Detiene la ejecución si falla el sensor
  }
  Serial.println("AMG8833 inicializado correctamente.");

  // Inicializa la matriz LED
  matrix.begin();
  matrix.setBrightness(50); // Ajusta el brillo de los LEDs (0-255)
  matrix.show(); // Apaga todos los LEDs
}

void loop() {
  // Lee las temperaturas del AMG8833
  amg.readPixels(pixels);

  // Mapear temperaturas a colores y mostrarlas en la matriz LED
  for (int i = 0; i < 64; i++) {
    // Mapear temperaturas de un rango (por ejemplo, 20-30°C) a brillo de LED
    float temp = pixels[i];
    uint32_t color;

    if (temp <= 20.0) {
      color = matrix.Color(0, 0, 255); // Azul para temperaturas bajas
    } else if (temp > 20.0 && temp <= 25.0) {
      color = matrix.Color(0, 255, 0); // Verde para temperaturas medias
    } else if (temp > 25.0 && temp <= 30.0) {
      color = matrix.Color(255, 255, 0); // Amarillo para temperaturas altas
    } else {
      color = matrix.Color(255, 0, 0); // Rojo para temperaturas muy altas
    }

    matrix.setPixelColor(i, color); // Asigna el color al LED correspondiente
  }

  matrix.show(); // Actualiza la matriz LED

  delay(100); // Breve retraso entre actualizaciones
}
