/*
 * MAX7221.ino
 *
 * Created on 25/12/2020
 * Author Totof
 * Affichage de chiffres aléatoires sur une matrice de LED 8*8
 *
 */

#include <SPI.h>
#include <stdlib.h> 
#include "Chiffres.h"

// Broche 6 pour le CS du SPI
#define LOAD_PIN 6

/**
 * Transfer d'une valeur dans un registre du MAX7219/7221
 * 
 * @param pAddress Registre du circuit
 * @param pValue   Valeur a envoyer au registre
 * @param pLow     Indicateur pour passer la broche CS à LOW avant les commandes
 * @param pUp      Indicateur pour passer la broche CS à HIGH après les commandes
 * Les deux derniers paramètres permettent de regrouper des commandes pour chainer des circuits
 */
void maxTransfer(uint8_t pAddress, uint8_t pValue, bool pLow, bool pUp) {
	if(pLow) {
		digitalWrite(LOAD_PIN, LOW);
	}

	SPI.transfer(pAddress);
	SPI.transfer(pValue);

	if(pUp) {
		digitalWrite(LOAD_PIN, HIGH);
	}
}
  
// ***********************
// Remise à 0 des matrices
// ***********************
void reset() {
	// Enable mode B
	maxTransfer(0x09, 0x00, true, true);
	// Blank sur les 8 lignes
	maxTransfer(0x01, 0x00, true, true);
	maxTransfer(0x02, 0x00, true, true);
	maxTransfer(0x03, 0x00, true, true);
	maxTransfer(0x04, 0x00, true, true);
	maxTransfer(0x05, 0x00, true, true);
	maxTransfer(0x06, 0x00, true, true);
	maxTransfer(0x07, 0x00, true, true);
	maxTransfer(0x08, 0x00, true, true);
	// Derniers décalages aux trois derniers modules
	maxTransfer(0x00, 0x00, true, true);
	maxTransfer(0x00, 0x00, true, true);
	maxTransfer(0x00, 0x00, true, true);
}

/**
 * Donne le code d'une ligne d'une matrice pour l'affichage d'un chiffre
 *
 * @param le chiffre à afficher
 * @param la ligne du chiffre  
 */
uint8_t segment(uint8_t pValeur, uint8_t pLigne){
  switch(pValeur) {
    case 0: return(zero[pLigne]);
    case 1: return(un[pLigne]);
    case 2: return(deux[pLigne]);
    case 3: return(trois[pLigne]);
    case 4: return(quatre[pLigne]);
    case 5: return(cinq[pLigne]);
    case 6: return(six[pLigne]);
    case 7: return(sept[pLigne]);
    case 8: return(huit[pLigne]);
    case 9: return(neuf[pLigne]);
  }
}

/**
 * Donne le code d'une ligne d'une matrice pour l'affichage d'un chiffre avec deux points
 *
 * @param le chiffre à afficher
 * @param la ligne du chiffre  
 */
uint8_t segmentDp(uint8_t pValeur, uint8_t pLigne){
  switch(pValeur) {
    case 0: return(zeroDp[pLigne]);
    case 1: return(unDp[pLigne]);
    case 2: return(deuxDp[pLigne]);
    case 3: return(troisDp[pLigne]);
    case 4: return(quatreDp[pLigne]);
    case 5: return(cinqDp[pLigne]);
    case 6: return(sixDp[pLigne]);
    case 7: return(septDp[pLigne]);
    case 8: return(huitDp[pLigne]);
    case 9: return(neufDp[pLigne]);
  }
}

/**
 * Donne le code d'une ligne d'une matrice pour l'affichage d'un chiffre avec un décalage d'un rang
 *
 * @param le chiffre à afficher
 * @param la ligne du chiffre  
 */
uint8_t segmentDm(uint8_t pValeur, uint8_t pLigne){
  switch(pValeur) {
    case 0: return(zeroDm[pLigne]);
    case 1: return(unDm[pLigne]);
    case 2: return(deuxDm[pLigne]);
    case 3: return(troisDm[pLigne]);
    case 4: return(quatreDm[pLigne]);
    case 5: return(cinqDm[pLigne]);
    case 6: return(sixDm[pLigne]);
    case 7: return(septDm[pLigne]);
    case 8: return(huitDm[pLigne]);
    case 9: return(neufDm[pLigne]);
  }
}

// *****************************************
//       ***** ***** ***** *   * *****
//       *     *       *   *   * *   *
//       ***** ****    *   *   * *****
//           * *       *   *   * *
//       ***** *****   *   ***** *
// *****************************************
void setup() {
	// Gestion broch CS
	pinMode(LOAD_PIN, OUTPUT);

	// Reverse the SPI transfer to send the MSB first  
	SPI.setBitOrder(MSBFIRST);

	// Start SPI
	SPI.begin();

	reset();

	// Run test
	// Allume toutes les LED une seconde
	maxTransfer(0x0F, 0x01, true, true);
	maxTransfer(0x0F, 0x01, true, true);
	maxTransfer(0x0F, 0x01, true, true);
	maxTransfer(0x0F, 0x01, true, true);
	delay(1000);
	maxTransfer(0x0F, 0x00, true, true);
	maxTransfer(0x0F, 0x00, true, true);
	maxTransfer(0x0F, 0x00, true, true);
	maxTransfer(0x0F, 0x00, true, true);
  
	// Disable mode B
	maxTransfer(0x09, 0x00, true, true);

	// Use lowest intensity
	maxTransfer(0x0A, 0x00, true, true);

	// Scan all digit
	maxTransfer(0x0B, 0x07, true, true);

	// Turn on chips
	maxTransfer(0x0C, 0x01, true, true);
	maxTransfer(0x0C, 0x01, true, true);
	maxTransfer(0x0C, 0x01, true, true);
	maxTransfer(0x0C, 0x01, true, true);
}

// ****************************************
//         *     ***** ***** *****
//         *     *   * *   * *   *
//         *     *   * *   * *****
//         *     *   * *   * *
//         ***** ***** ***** *
// ****************************************
void loop() {
	// Dizaine d'heures de 0 à 2
	uint8_t nbDizaineHeure = rand()% 3;
	// Heures
	uint8_t nbHeure;
	if(nbDizaineHeure == 2) {
		// Dizaine d'heure de 0 à 3 
		nbHeure = rand() % 4;
	} else {
		// Dizaine d'heure de 0 à 9
		nbHeure = rand() % 10;
	}
	// Dizaine de minutes
	uint8_t nbDizaineMinute = rand() % 6;
	// Minutes
	uint8_t nbMinute = rand() % 10;
  
	// Affichage des chiffres sur les 8 segments des 4 afficheurs
	// Peut être simplifié, mais c'est plus compréhensible comme ça
	for(uint8_t compteur = 0; compteur != 8 ; compteur++) {
		switch(compteur) {
		case 0:
			maxTransfer(0x01, segment(nbMinute, compteur), true, false);
			maxTransfer(0x01, segmentDm(nbDizaineMinute, compteur), false, false);
			maxTransfer(0x01, segmentDp(nbHeure, compteur), false, false);
			maxTransfer(0x01, segment(nbDizaineHeure, compteur), false, true);
			break;
		case 1:
			maxTransfer(0x02, segment(nbMinute, compteur), true, false);
			maxTransfer(0x02, segmentDm(nbDizaineMinute, compteur), false, false);
			maxTransfer(0x02, segmentDp(nbHeure, compteur), false, false);
			maxTransfer(0x02, segment(nbDizaineHeure, compteur), false, true);
			break;
		case 2:
			maxTransfer(0x03, segment(nbMinute, compteur), true, false);
			maxTransfer(0x03, segmentDm(nbDizaineMinute, compteur), false, false);
			maxTransfer(0x03, segmentDp(nbHeure, compteur), false, false);
			maxTransfer(0x03, segment(nbDizaineHeure, compteur), false, true);
			break;
		case 3:
			maxTransfer(0x04, segment(nbMinute, compteur), true, false);
			maxTransfer(0x04, segmentDm(nbDizaineMinute, compteur), false, false);
			maxTransfer(0x04, segmentDp(nbHeure, compteur), false, false);
			maxTransfer(0x04, segment(nbDizaineHeure, compteur), false, true);
			break;
		case 4:
			maxTransfer(0x05, segment(nbMinute, compteur), true, false);
			maxTransfer(0x05, segmentDm(nbDizaineMinute, compteur), false, false);
			maxTransfer(0x05, segmentDp(nbHeure, compteur), false, false);
			maxTransfer(0x05, segment(nbDizaineHeure, compteur), false, true);
			break;
		case 5:
			maxTransfer(0x06, segment(nbMinute, compteur), true, false);
			maxTransfer(0x06, segmentDm(nbDizaineMinute, compteur), false, false);
			maxTransfer(0x06, segmentDp(nbHeure, compteur), false, false);
			maxTransfer(0x06, segment(nbDizaineHeure, compteur), false, true);
			break;
		case 6:
			maxTransfer(0x07, segment(nbMinute, compteur), true, false);
			maxTransfer(0x07, segmentDm(nbDizaineMinute, compteur), false, false);
			maxTransfer(0x07, segmentDp(nbHeure, compteur), false, false);
			maxTransfer(0x07, segment(nbDizaineHeure, compteur), false, true);
			break;
		case 7:
			maxTransfer(0x08, segment(nbMinute, compteur), true, false);
			maxTransfer(0x08, segmentDm(nbDizaineMinute, compteur), false, false);
			maxTransfer(0x08, segmentDp(nbHeure, compteur), false, false);
			maxTransfer(0x08, segment(nbDizaineHeure, compteur), false, true);
			break;
		}
	}
	delay(1000);
}
