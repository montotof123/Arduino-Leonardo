/*!
 *   \file    horloge.cpp
 *   \brief   Affichage d'une horloge et de données météo sur des matrices MAX7219
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    01/01/2021
 */
 
#include <Wire.h>

#include <TimeLib.h>

#include <DS1307RTC.h>
#include <BH1750.h>
#include <SparkFun_CAP1203_Registers.h>
#include <SparkFun_CAP1203_Types.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "GestionMatrices.h"

/**
 *   \brief   Broche 6 pour le CS du SPI des matrices
 */ 
#define LOAD_PIN 6

/**
 *   \brief   Thermomètre type DHT 22 (AM2302)
 */ 
#define DHTTYPE    DHT22

/**
 *   \brief   Digital pin connected to the DHT sensor
 */ 
#define DHTPIN 5

/**
 *   \brief   Altitude où est placé l'appareil
 *
 *   \details Permet le calcul correcte de la pression au niveau de la mer
 */ 
#define ALTITUDE 115
 
/**
 *   \brief   Matrice d'affichage
 */
GestionMatrices matrices(LOAD_PIN);

/**
 *   \brief   structure date et heure
 */ 
tmElements_t tm;

/**
 *   \brief   luxmètre BH1750
 */ 
BH1750 lightMeter;

/**
 *   \brief   Touches CAP1203
 */ 
CAP1203 sensor;

/**
 *   \brief   BMP180
 */ 
Adafruit_BMP085 bmp;

/**
 *   \brief   DHT22
 */ 
DHT_Unified dht(DHTPIN, DHTTYPE);
 
// *****************************************
//       ***** ***** ***** *   * *****
//       *     *       *   *   * *   *
//       ***** ****    *   *   * *****
//           * *       *   *   * *
//       ***** *****   *   ***** *
// *****************************************
void setup() {
	// Initialisation des mesureur
	// Les matrices sont initialisées dans le constructeur de la librairie
	lightMeter.begin();
	sensor.begin();
	bmp.begin();
	dht.begin();
}

// ****************************************
//         *     ***** ***** *****
//         *     *   * *   * *   *
//         *     *   * *   * *****
//         *     *   * *   * *
//         ***** ***** ***** *
// ****************************************
void loop() {
	// Réglage de l'intensité lumineuse des matrices avec le BH1750
	float lux = lightMeter.readLightLevel();
	// 0 lux = 0x00, 20000 lux ou plus = 0x0F, linéaire entre 0 et 20000, soit un pas de 1333 lux
	uint8_t intensity = lux / 1333;
	if(intensity > 0x0F) {
		intensity = 0x0F;
	}
	matrices.intensity(intensity);
	
	// Pression
	if (sensor.isLeftTouched() == true) {
		matrices.affichage((float)bmp.readSealevelPressure(ALTITUDE) / 100.0F);
		delay(4000);
	}

	// Température
	if (sensor.isMiddleTouched() == true) {
		matrices.affichageDeg(bmp.readTemperature()); 
		delay(4000);
		
		sensors_event_t event;
		dht.temperature().getEvent(&event);
		matrices.affichageDeg(event.temperature); 
		delay(4000);
	}

	// Humidité
	if (sensor.isRightTouched() == true) {
		sensors_event_t event;
		dht.humidity().getEvent(&event);
		matrices.affichagePourcent(event.relative_humidity); 
		delay(4000);
	}
 
	// Affichage horloge DS1307
	RTC.read(tm);
	matrices.horloge(tm); 
	delay(1000);
}
