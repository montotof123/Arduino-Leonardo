/*!
 *   \file    GestionMatrices.cpp
 *   \brief   Classe de gestion des matrices à base de MAX7219.
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    01/01/2021
 */

#include <SPI.h>
#include <stdlib.h> 
#include "Chiffres.h"
#include "GestionMatrices.h"

/**
 * \brief   Constructeur. 
 *
 * \details Constructeur standard.
 *
 * \note    Initialise le SPI et les MAX7219
 *
 * \param   pCs La broche utilisée pour le CS SPI.
 */
GestionMatrices::GestionMatrices(uint8_t pCs)
{
	// Mémorise la broche CS
	cs = pCs;
	
	// Gestion broche CS
	pinMode(cs, OUTPUT);

	// Reverse the SPI transfer to send the MSB first  
	SPI.setBitOrder(MSBFIRST);

	// Start SPI
	SPI.begin();

	reset();

	// Pas de test
	maxTransfer(0x0F, 0x00, true, true);
	maxTransfer(0x0F, 0x00, true, true);
	maxTransfer(0x0F, 0x00, true, true);
	maxTransfer(0x0F, 0x00, true, true);
  
	// Disable mode B
	maxTransfer(0x09, 0x00, true, true);

	// Init lowest intensity
	maxTransfer(0x0A, 0x00, true, true);

	// Scan all digit
	maxTransfer(0x0B, 0x07, true, true);

	// Turn on chips
	maxTransfer(0x0C, 0x01, true, true);
	maxTransfer(0x0C, 0x01, true, true);
	maxTransfer(0x0C, 0x01, true, true);
	maxTransfer(0x0C, 0x01, true, true);
}

/**
 * \brief   Réglage de l'intensité. 
 *
 * \param   pIntensity L'intensité.
 *
 * \attention intensité entre 0x00 et 0x0F
 */
void GestionMatrices::intensity(uint8_t pIntensity)
{
	maxTransfer(0x0A, pIntensity, true, false);
	maxTransfer(0x0A, pIntensity, false, false);
	maxTransfer(0x0A, pIntensity, false, false);
	maxTransfer(0x0A, pIntensity, false, true);
}

/**
 * \brief Donne le code d'une ligne d'une matrice pour l'affichage du degré
 *
 * \param pLigne la ligne du degré  
 *
 * \return renvoi l'octet correspondant au segment à afficher
 */
uint8_t GestionMatrices::segmentDeg(uint8_t pLigne)
{
	return(degre[pLigne]);
}

/**
 * \brief Donne le code d'une ligne d'une matrice pour l'affichage du poucent
 *
 * \param pLigne la ligne du pourcent  
 *
 * \return renvoi l'octet correspondant au segment à afficher
 */
uint8_t GestionMatrices::segmentPourcent(uint8_t pLigne)
{
	return(pourcent[pLigne]);
}

/**
 * \brief Donne le code d'une ligne d'une matrice pour l'affichage d'un chiffre
 *
 * \param pValeur le chiffre à afficher
 * \param pLigne la ligne du chiffre  
 *
 * \return renvoi l'octet correspondant au segment à afficher
 */
uint8_t GestionMatrices::segment(uint8_t pValeur, uint8_t pLigne)
{
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
 * \brief Donne le code d'une ligne d'une matrice pour l'affichage d'un chiffre avec deux points
 *
 * \param pValeur le chiffre à afficher
 * \param pLigne la ligne du chiffre  
 *
 * \return renvoi l'octet correspondant au segment à afficher
 */
uint8_t GestionMatrices::segmentDp(uint8_t pValeur, uint8_t pLigne)
{
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
 * \brief Donne le code d'une ligne d'une matrice pour l'affichage d'un chiffre avec un décalage d'un rang
 *
 * \param pValeur le chiffre à afficher
 * \param pLigne la ligne du chiffre  
 *
 * \return renvoi l'octet correspondant au segment à afficher
 */
uint8_t GestionMatrices::segmentDm(uint8_t pValeur, uint8_t pLigne)
{
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

/**
 * \brief Donne le code d'une ligne d'une matrice pour l'affichage d'un chiffre avec virgule
 *
 * \param pValeur le chiffre à afficher
 * \param pLigne la ligne du chiffre  
 *
 * \return renvoi l'octet correspondant au segment à afficher
 */
uint8_t GestionMatrices::segmentV(uint8_t pValeur, uint8_t pLigne)
{
	switch(pValeur) {
		case 0: return(zeroV[pLigne]);
		case 1: return(unV[pLigne]);
		case 2: return(deuxV[pLigne]);
		case 3: return(troisV[pLigne]);
		case 4: return(quatreV[pLigne]);
		case 5: return(cinqV[pLigne]);
		case 6: return(sixV[pLigne]);
		case 7: return(septV[pLigne]);
		case 8: return(huitV[pLigne]);
		case 9: return(neufV[pLigne]);
	}
}

/**
 * \brief Eteint toutes les matrices
 *
 */
void GestionMatrices::reset(void)
{
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
 * \brief Transfert une valeur vers un registre du MAX7219
 *
 * \details Gère aussi la broche CS pour pouvoir coupler des commandes
 *
 * \param pAddress registre du MAX7219
 * \param pValue valeur à transférer 
 * \param pValue valeur à transférer 
 * \param pValue valeur à transférer 
 */
void GestionMatrices::maxTransfer(uint8_t pAddress, uint8_t pValue, bool pLow, bool pUp)
{
	if(pLow) {
		digitalWrite(cs, LOW);
	}

	SPI.transfer(pAddress);
	SPI.transfer(pValue);

	if(pUp) {
		digitalWrite(cs, HIGH);
	}
}

/**
 * \brief Affichage de l'horloge d'une structure tm
 *
 * \param pTm structure tm jour et heure
*/
void GestionMatrices::horloge(tmElements_t pTm)
{
	// Dizaine d'heures
	uint8_t nbDizaineHeure = pTm.Hour / 10;
	// Heures
	uint8_t nbHeure = pTm.Hour % 10;
	// Dizaine de minutes
	uint8_t nbDizaineMinute = pTm.Minute / 10;
	// Minutes
	uint8_t nbMinute = pTm.Minute % 10;

	heure(nbDizaineHeure, nbHeure, nbDizaineMinute, nbMinute); 
}

/**
 * \brief Affichage d'un nombre réel
 *
 * \param pValeur la valeur à afficher
 */
void GestionMatrices::affichage(float pValeur)
{
	uint8_t unites;
	uint8_t dizaines;
	uint8_t centaines;
	uint8_t milliers;
	uint8_t diziemes;
	uint8_t centiemes;
	uint8_t milliemes;
	if(pValeur >= 1000.0F) {
		unites = (int)pValeur % 10;
		dizaines = ((int)pValeur % 100) / 10;
		centaines = ((int)pValeur % 1000) / 100;
		milliers = (int)pValeur / 1000;
		millier(milliers, centaines, dizaines, unites); 
	} else if(pValeur >= 100.0F) {
		unites = (int)pValeur % 10;
		dizaines = ((int)pValeur % 100) / 10;
		centaines = ((int)pValeur % 1000) / 100;
		diziemes = ((int)(pValeur * 10)) % 10;
		centaine( centaines, dizaines, unites, diziemes); 		
	} else if(pValeur >= 10.0F) {
		unites = (int)pValeur % 10;
		dizaines = ((int)pValeur % 100) / 10;
		diziemes = ((int)(pValeur * 10)) % 10;
		centiemes = ((int)(pValeur * 100)) % 10;
		dizaine(dizaines, unites, diziemes, centiemes); 		
	} else {
		unites = (int)pValeur % 10;
		diziemes = ((int)(pValeur * 10)) % 10;
		centiemes = ((int)(pValeur * 100)) % 10;
		milliemes = ((int)(pValeur * 1000)) % 10;
		unite(unites, diziemes, centiemes, milliemes); 		
	}
}

/**
 * \brief Affichage d'un nombre réel avec degré
 *
 * \param pValeur la valeur à afficher
 */
void GestionMatrices::affichageDeg(float pValeur)
{
	uint8_t unites;
	uint8_t dizaines;
	uint8_t centaines;
	uint8_t milliers;
	uint8_t diziemes;
	uint8_t centiemes;
	if(pValeur >= 1000.0F) {
		unites = (int)pValeur % 10;
		dizaines = ((int)pValeur % 100) / 10;
		centaines = ((int)pValeur % 1000) / 100;
		milliers = (int)pValeur / 1000;
		millier(milliers, centaines, dizaines, unites); 
	} else if(pValeur >= 100.0F) {
		unites = (int)pValeur % 10;
		dizaines = ((int)pValeur % 100) / 10;
		centaines = ((int)pValeur % 1000) / 100;
		centaineDeg( centaines, dizaines, unites); 		
	} else if(pValeur >= 10.0F) {
		unites = (int)pValeur % 10;
		dizaines = ((int)pValeur % 100) / 10;
		diziemes = ((int)(pValeur * 10)) % 10;
		dizaineDeg(dizaines, unites, diziemes); 		
	} else {
		unites = (int)pValeur % 10;
		diziemes = ((int)(pValeur * 10)) % 10;
		centiemes = ((int)(pValeur * 100)) % 10;
		uniteDeg(unites, diziemes, centiemes); 		
	}
}

/**
 * \brief Affichage d'un nombre réel avec pourcent
 *
 * \param pValeur la valeur à afficher
 */
void GestionMatrices::affichagePourcent(float pValeur)
{
	uint8_t unites;
	uint8_t dizaines;
	uint8_t centaines;
	uint8_t milliers;
	uint8_t diziemes;
	uint8_t centiemes;
	if(pValeur >= 1000.0F) {
		unites = (int)pValeur % 10;
		dizaines = ((int)pValeur % 100) / 10;
		centaines = ((int)pValeur % 1000) / 100;
		milliers = (int)pValeur / 1000;
		millier(milliers, centaines, dizaines, unites); 
	} else if(pValeur >= 100.0F) {
		unites = (int)pValeur % 10;
		dizaines = ((int)pValeur % 100) / 10;
		centaines = ((int)pValeur % 1000) / 100;
		centainePourcent( centaines, dizaines, unites); 		
	} else if(pValeur >= 10.0F) {
		unites = (int)pValeur % 10;
		dizaines = ((int)pValeur % 100) / 10;
		diziemes = ((int)(pValeur * 10)) % 10;
		dizainePourcent(dizaines, unites, diziemes); 		
	} else {
		unites = (int)pValeur % 10;
		diziemes = ((int)(pValeur * 10)) % 10;
		centiemes = ((int)(pValeur * 100)) % 10;
		unitePourcent(unites, diziemes, centiemes); 		
	}
}

/**
 * \brief   Affichage de l'heure. 
 *
 * \details Affichage des chiffres sur les 8 segments des 4 matrices
 *
 * \param   pNbDizaineHeure Les dizaines d'heures (entre 0 et 2)
 * \param   pNbHeure Les heures (entre 0 et 9 ou entre 0 et 3 si les dizaines d'heures sont à 2)
 * \param   pNbDizaineMinute Les dizaines de minute (entre 0 et 5)
 * \param   pNbMinute Les minutes (entre 0 et 9)
 */
void GestionMatrices::heure(uint8_t pNbDizaineHeure, uint8_t pNbHeure, uint8_t pNbDizaineMinute, uint8_t pNbMinute) 
{
	// Affichage des chiffres sur les 8 segments des 4 afficheurs
	// Peut être simplifié, mais c'est plus compréhensible comme ça
	for(uint8_t compteur = 0; compteur != 8; compteur++) {
		switch(compteur) {
		case 0:
			maxTransfer(0x01, segment(pNbMinute, compteur), true, false);
			maxTransfer(0x01, segmentDm(pNbDizaineMinute, compteur), false, false);
			maxTransfer(0x01, segmentDp(pNbHeure, compteur), false, false);
			maxTransfer(0x01, segment(pNbDizaineHeure, compteur), false, true);
			break;
		case 1:
			maxTransfer(0x02, segment(pNbMinute, compteur), true, false);
			maxTransfer(0x02, segmentDm(pNbDizaineMinute, compteur), false, false);
			maxTransfer(0x02, segmentDp(pNbHeure, compteur), false, false);
			maxTransfer(0x02, segment(pNbDizaineHeure, compteur), false, true);
			break;
		case 2:
			maxTransfer(0x03, segment(pNbMinute, compteur), true, false);
			maxTransfer(0x03, segmentDm(pNbDizaineMinute, compteur), false, false);
			maxTransfer(0x03, segmentDp(pNbHeure, compteur), false, false);
			maxTransfer(0x03, segment(pNbDizaineHeure, compteur), false, true);
			break;
		case 3:
			maxTransfer(0x04, segment(pNbMinute, compteur), true, false);
			maxTransfer(0x04, segmentDm(pNbDizaineMinute, compteur), false, false);
			maxTransfer(0x04, segmentDp(pNbHeure, compteur), false, false);
			maxTransfer(0x04, segment(pNbDizaineHeure, compteur), false, true);
			break;
		case 4:
			maxTransfer(0x05, segment(pNbMinute, compteur), true, false);
			maxTransfer(0x05, segmentDm(pNbDizaineMinute, compteur), false, false);
			maxTransfer(0x05, segmentDp(pNbHeure, compteur), false, false);
			maxTransfer(0x05, segment(pNbDizaineHeure, compteur), false, true);
			break;
		case 5:
			maxTransfer(0x06, segment(pNbMinute, compteur), true, false);
			maxTransfer(0x06, segmentDm(pNbDizaineMinute, compteur), false, false);
			maxTransfer(0x06, segmentDp(pNbHeure, compteur), false, false);
			maxTransfer(0x06, segment(pNbDizaineHeure, compteur), false, true);
			break;
		case 6:
			maxTransfer(0x07, segment(pNbMinute, compteur), true, false);
			maxTransfer(0x07, segmentDm(pNbDizaineMinute, compteur), false, false);
			maxTransfer(0x07, segmentDp(pNbHeure, compteur), false, false);
			maxTransfer(0x07, segment(pNbDizaineHeure, compteur), false, true);
			break;
		case 7:
			maxTransfer(0x08, segment(pNbMinute, compteur), true, false);
			maxTransfer(0x08, segmentDm(pNbDizaineMinute, compteur), false, false);
			maxTransfer(0x08, segmentDp(pNbHeure, compteur), false, false);
			maxTransfer(0x08, segment(pNbDizaineHeure, compteur), false, true);
			break;
		}
	}
}

/**
 * \brief   Affichage d'un nombre sans virgule. 
 *
 * \details Affichage des chiffres sur les 8 segments des 4 matrices
 *
 * \param   pMillier
 * \param   pCentaine
 * \param   pDizaine
 * \param   pUnite
 */
void GestionMatrices::millier(uint8_t pMillier, uint8_t pCentaine, uint8_t pDizaine, uint8_t pUnite) 
{
	// Affichage des chiffres sur les 8 segments des 4 afficheurs
	// Peut être simplifié, mais c'est plus compréhensible comme ça
	for(uint8_t compteur = 0; compteur != 8; compteur++) {
		switch(compteur) {
		case 0:
			maxTransfer(0x01, segment(pUnite, compteur), true, false);
			maxTransfer(0x01, segment(pDizaine, compteur), false, false);
			maxTransfer(0x01, segment(pCentaine, compteur), false, false);
			maxTransfer(0x01, segment(pMillier, compteur), false, true);
			break;
		case 1:
			maxTransfer(0x02, segment(pUnite, compteur), true, false);
			maxTransfer(0x02, segment(pDizaine, compteur), false, false);
			maxTransfer(0x02, segment(pCentaine, compteur), false, false);
			maxTransfer(0x02, segment(pMillier, compteur), false, true);
			break;
		case 2:
			maxTransfer(0x03, segment(pUnite, compteur), true, false);
			maxTransfer(0x03, segment(pDizaine, compteur), false, false);
			maxTransfer(0x03, segment(pCentaine, compteur), false, false);
			maxTransfer(0x03, segment(pMillier, compteur), false, true);
			break;
		case 3:
			maxTransfer(0x04, segment(pUnite, compteur), true, false);
			maxTransfer(0x04, segment(pDizaine, compteur), false, false);
			maxTransfer(0x04, segment(pCentaine, compteur), false, false);
			maxTransfer(0x04, segment(pMillier, compteur), false, true);
			break;
		case 4:
			maxTransfer(0x05, segment(pUnite, compteur), true, false);
			maxTransfer(0x05, segment(pDizaine, compteur), false, false);
			maxTransfer(0x05, segment(pCentaine, compteur), false, false);
			maxTransfer(0x05, segment(pMillier, compteur), false, true);
			break;
		case 5:
			maxTransfer(0x06, segment(pUnite, compteur), true, false);
			maxTransfer(0x06, segment(pDizaine, compteur), false, false);
			maxTransfer(0x06, segment(pCentaine, compteur), false, false);
			maxTransfer(0x06, segment(pMillier, compteur), false, true);
			break;
		case 6:
			maxTransfer(0x07, segment(pUnite, compteur), true, false);
			maxTransfer(0x07, segment(pDizaine, compteur), false, false);
			maxTransfer(0x07, segment(pCentaine, compteur), false, false);
			maxTransfer(0x07, segment(pMillier, compteur), false, true);
			break;
		case 7:
			maxTransfer(0x08, segment(pUnite, compteur), true, false);
			maxTransfer(0x08, segment(pDizaine, compteur), false, false);
			maxTransfer(0x08, segment(pCentaine, compteur), false, false);
			maxTransfer(0x08, segment(pMillier, compteur), false, true);
			break;
		}
	}
}

/**
 * \brief   Affichage d'un nombre avec un chiffre après la virgule. 
 *
 * \details Affichage des chiffres sur les 8 segments des 4 matrices
 *
 * \param   pCentaine
 * \param   pDizaine
 * \param   pUnite
 * \param   pDizieme
 */
void GestionMatrices::centaine(uint8_t pCentaine, uint8_t pDizaine, uint8_t pUnite, uint8_t pDizieme) 
{
	// Affichage des chiffres sur les 8 segments des 4 afficheurs
	// Peut être simplifié, mais c'est plus compréhensible comme ça
	for(uint8_t compteur = 0; compteur != 8; compteur++) {
		switch(compteur) {
		case 0:
			maxTransfer(0x01, segment(pDizieme, compteur), true, false);
			maxTransfer(0x01, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x01, segment(pDizaine, compteur), false, false);
			maxTransfer(0x01, segment(pCentaine, compteur), false, true);
			break;
		case 1:
			maxTransfer(0x02, segment(pDizieme, compteur), true, false);
			maxTransfer(0x02, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x02, segment(pDizaine, compteur), false, false);
			maxTransfer(0x02, segment(pCentaine, compteur), false, true);
			break;
		case 2:
			maxTransfer(0x03, segment(pDizieme, compteur), true, false);
			maxTransfer(0x03, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x03, segment(pDizaine, compteur), false, false);
			maxTransfer(0x03, segment(pCentaine, compteur), false, true);
			break;
		case 3:
			maxTransfer(0x04, segment(pDizieme, compteur), true, false);
			maxTransfer(0x04, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x04, segment(pDizaine, compteur), false, false);
			maxTransfer(0x04, segment(pCentaine, compteur), false, true);
			break;
		case 4:
			maxTransfer(0x05, segment(pDizieme, compteur), true, false);
			maxTransfer(0x05, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x05, segment(pDizaine, compteur), false, false);
			maxTransfer(0x05, segment(pCentaine, compteur), false, true);
			break;
		case 5:
			maxTransfer(0x06, segment(pDizieme, compteur), true, false);
			maxTransfer(0x06, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x06, segment(pDizaine, compteur), false, false);
			maxTransfer(0x06, segment(pCentaine, compteur), false, true);
			break;
		case 6:
			maxTransfer(0x07, segment(pDizieme, compteur), true, false);
			maxTransfer(0x07, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x07, segment(pDizaine, compteur), false, false);
			maxTransfer(0x07, segment(pCentaine, compteur), false, true);
			break;
		case 7:
			maxTransfer(0x08, segment(pDizieme, compteur), true, false);
			maxTransfer(0x08, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x08, segment(pDizaine, compteur), false, false);
			maxTransfer(0x08, segment(pCentaine, compteur), false, true);
			break;
		}
	}
}

/**
 * \brief   Affichage d'un nombre avec degré. 
 *
 * \details Affichage des chiffres sur les 8 segments des 3 matrices et degré à la fin
 *
 * \param   pCentaine
 * \param   pDizaine
 * \param   pUnite
 */
void GestionMatrices::centaineDeg(uint8_t pCentaine, uint8_t pDizaine, uint8_t pUnite) 
{
	// Affichage des caractères sur les 8 segments des 4 afficheurs
	// Peut être simplifié, mais c'est plus compréhensible comme ça
	for(uint8_t compteur = 0; compteur != 8; compteur++) {
		switch(compteur) {
		case 0:
			maxTransfer(0x01, segmentDeg(compteur), true, false);
			maxTransfer(0x01, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x01, segment(pDizaine, compteur), false, false);
			maxTransfer(0x01, segment(pCentaine, compteur), false, true);
			break;
		case 1:
			maxTransfer(0x02, segmentDeg(compteur), true, false);
			maxTransfer(0x02, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x02, segment(pDizaine, compteur), false, false);
			maxTransfer(0x02, segment(pCentaine, compteur), false, true);
			break;
		case 2:
			maxTransfer(0x03, segmentDeg(compteur), true, false);
			maxTransfer(0x03, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x03, segment(pDizaine, compteur), false, false);
			maxTransfer(0x03, segment(pCentaine, compteur), false, true);
			break;
		case 3:
			maxTransfer(0x04, segmentDeg(compteur), true, false);
			maxTransfer(0x04, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x04, segment(pDizaine, compteur), false, false);
			maxTransfer(0x04, segment(pCentaine, compteur), false, true);
			break;
		case 4:
			maxTransfer(0x05, segmentDeg(compteur), true, false);
			maxTransfer(0x05, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x05, segment(pDizaine, compteur), false, false);
			maxTransfer(0x05, segment(pCentaine, compteur), false, true);
			break;
		case 5:
			maxTransfer(0x06, segmentDeg(compteur), true, false);
			maxTransfer(0x06, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x06, segment(pDizaine, compteur), false, false);
			maxTransfer(0x06, segment(pCentaine, compteur), false, true);
			break;
		case 6:
			maxTransfer(0x07, segmentDeg(compteur), true, false);
			maxTransfer(0x07, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x07, segment(pDizaine, compteur), false, false);
			maxTransfer(0x07, segment(pCentaine, compteur), false, true);
			break;
		case 7:
			maxTransfer(0x08, segmentDeg(compteur), true, false);
			maxTransfer(0x08, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x08, segment(pDizaine, compteur), false, false);
			maxTransfer(0x08, segment(pCentaine, compteur), false, true);
			break;
		}
	}
}

/**
 * \brief   Affichage d'un nombre avec pourcent. 
 *
 * \details Affichage des chiffres sur les 8 segments des 3 matrices et pourcent à la fin
 *
 * \param   pCentaine
 * \param   pDizaine
 * \param   pUnite
 */
void GestionMatrices::centainePourcent(uint8_t pCentaine, uint8_t pDizaine, uint8_t pUnite) 
{
	// Affichage des caractères sur les 8 segments des 4 afficheurs
	// Peut être simplifié, mais c'est plus compréhensible comme ça
	for(uint8_t compteur = 0; compteur != 8; compteur++) {
		switch(compteur) {
		case 0:
			maxTransfer(0x01, segmentPourcent(compteur), true, false);
			maxTransfer(0x01, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x01, segment(pDizaine, compteur), false, false);
			maxTransfer(0x01, segment(pCentaine, compteur), false, true);
			break;
		case 1:
			maxTransfer(0x02, segmentPourcent(compteur), true, false);
			maxTransfer(0x02, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x02, segment(pDizaine, compteur), false, false);
			maxTransfer(0x02, segment(pCentaine, compteur), false, true);
			break;
		case 2:
			maxTransfer(0x03, segmentPourcent(compteur), true, false);
			maxTransfer(0x03, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x03, segment(pDizaine, compteur), false, false);
			maxTransfer(0x03, segment(pCentaine, compteur), false, true);
			break;
		case 3:
			maxTransfer(0x04, segmentPourcent(compteur), true, false);
			maxTransfer(0x04, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x04, segment(pDizaine, compteur), false, false);
			maxTransfer(0x04, segment(pCentaine, compteur), false, true);
			break;
		case 4:
			maxTransfer(0x05, segmentPourcent(compteur), true, false);
			maxTransfer(0x05, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x05, segment(pDizaine, compteur), false, false);
			maxTransfer(0x05, segment(pCentaine, compteur), false, true);
			break;
		case 5:
			maxTransfer(0x06, segmentPourcent(compteur), true, false);
			maxTransfer(0x06, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x06, segment(pDizaine, compteur), false, false);
			maxTransfer(0x06, segment(pCentaine, compteur), false, true);
			break;
		case 6:
			maxTransfer(0x07, segmentPourcent(compteur), true, false);
			maxTransfer(0x07, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x07, segment(pDizaine, compteur), false, false);
			maxTransfer(0x07, segment(pCentaine, compteur), false, true);
			break;
		case 7:
			maxTransfer(0x08, segmentPourcent(compteur), true, false);
			maxTransfer(0x08, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x08, segment(pDizaine, compteur), false, false);
			maxTransfer(0x08, segment(pCentaine, compteur), false, true);
			break;
		}
	}
}

/**
 * \brief   Affichage d'un nombre avec deux chiffres après la virgule. 
 *
 * \details Affichage des chiffres sur les 8 segments des 4 matrices
 *
 * \param   pDizaine
 * \param   pUnite
 * \param   pDizieme
 * \param   pCentieme
 */
void GestionMatrices::dizaine(uint8_t pDizaine, uint8_t pUnite, uint8_t pDizieme, uint8_t pCentieme) 
{
	// Affichage des chiffres sur les 8 segments des 4 afficheurs
	// Peut être simplifié, mais c'est plus compréhensible comme ça
	for(uint8_t compteur = 0; compteur != 8; compteur++) {
		switch(compteur) {
		case 0:
			maxTransfer(0x01, segment(pCentieme, compteur), true, false);
			maxTransfer(0x01, segment(pDizieme, compteur), false, false);
			maxTransfer(0x01, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x01, segment(pDizaine, compteur), false, true);
			break;
		case 1:
			maxTransfer(0x02, segment(pCentieme, compteur), true, false);
			maxTransfer(0x02, segment(pDizieme, compteur), false, false);
			maxTransfer(0x02, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x02, segment(pDizaine, compteur), false, true);
			break;
		case 2:
			maxTransfer(0x03, segment(pCentieme, compteur), true, false);
			maxTransfer(0x03, segment(pDizieme, compteur), false, false);
			maxTransfer(0x03, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x03, segment(pDizaine, compteur), false, true);
			break;
		case 3:
			maxTransfer(0x04, segment(pCentieme, compteur), true, false);
			maxTransfer(0x04, segment(pDizieme, compteur), false, false);
			maxTransfer(0x04, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x04, segment(pDizaine, compteur), false, true);
			break;
		case 4:
			maxTransfer(0x05, segment(pCentieme, compteur), true, false);
			maxTransfer(0x05, segment(pDizieme, compteur), false, false);
			maxTransfer(0x05, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x05, segment(pDizaine, compteur), false, true);
			break;
		case 5:
			maxTransfer(0x06, segment(pCentieme, compteur), true, false);
			maxTransfer(0x06, segment(pDizieme, compteur), false, false);
			maxTransfer(0x06, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x06, segment(pDizaine, compteur), false, true);
			break;
		case 6:
			maxTransfer(0x07, segment(pCentieme, compteur), true, false);
			maxTransfer(0x07, segment(pDizieme, compteur), false, false);
			maxTransfer(0x07, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x07, segment(pDizaine, compteur), false, true);
			break;
		case 7:
			maxTransfer(0x08, segment(pCentieme, compteur), true, false);
			maxTransfer(0x08, segment(pDizieme, compteur), false, false);
			maxTransfer(0x08, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x08, segment(pDizaine, compteur), false, true);
			break;
		}
	}
}

/**
 * \brief   Affichage d'un nombre avec un chiffres après la virgule et degré. 
 *
 * \details Affichage des chiffres sur les 8 segments des 3 matrices et degré à la fin
 *
 * \param   pDizaine
 * \param   pUnite
 * \param   pDizieme
 */
void GestionMatrices::dizaineDeg(uint8_t pDizaine, uint8_t pUnite, uint8_t pDizieme) 
{
	// Affichage des caractères sur les 8 segments des 4 afficheurs
	// Peut être simplifié, mais c'est plus compréhensible comme ça
	for(uint8_t compteur = 0; compteur != 8; compteur++) {
		switch(compteur) {
		case 0:
			maxTransfer(0x01, segmentDeg(compteur), true, false);
			maxTransfer(0x01, segment(pDizieme, compteur), false, false);
			maxTransfer(0x01, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x01, segment(pDizaine, compteur), false, true);
			break;
		case 1:
			maxTransfer(0x02, segmentDeg(compteur), true, false);
			maxTransfer(0x02, segment(pDizieme, compteur), false, false);
			maxTransfer(0x02, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x02, segment(pDizaine, compteur), false, true);
			break;
		case 2:
			maxTransfer(0x03, segmentDeg(compteur), true, false);
			maxTransfer(0x03, segment(pDizieme, compteur), false, false);
			maxTransfer(0x03, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x03, segment(pDizaine, compteur), false, true);
			break;
		case 3:
			maxTransfer(0x04, segmentDeg(compteur), true, false);
			maxTransfer(0x04, segment(pDizieme, compteur), false, false);
			maxTransfer(0x04, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x04, segment(pDizaine, compteur), false, true);
			break;
		case 4:
			maxTransfer(0x05, segmentDeg(compteur), true, false);
			maxTransfer(0x05, segment(pDizieme, compteur), false, false);
			maxTransfer(0x05, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x05, segment(pDizaine, compteur), false, true);
			break;
		case 5:
			maxTransfer(0x06, segmentDeg(compteur), true, false);
			maxTransfer(0x06, segment(pDizieme, compteur), false, false);
			maxTransfer(0x06, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x06, segment(pDizaine, compteur), false, true);
			break;
		case 6:
			maxTransfer(0x07, segmentDeg(compteur), true, false);
			maxTransfer(0x07, segment(pDizieme, compteur), false, false);
			maxTransfer(0x07, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x07, segment(pDizaine, compteur), false, true);
			break;
		case 7:
			maxTransfer(0x08, segmentDeg(compteur), true, false);
			maxTransfer(0x08, segment(pDizieme, compteur), false, false);
			maxTransfer(0x08, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x08, segment(pDizaine, compteur), false, true);
			break;
		}
	}
}

/**
 * \brief   Affichage d'un nombre avec un chiffres après la virgule et pourcent. 
 *
 * \details Affichage des chiffres sur les 8 segments des 3 matrices et pourcent à la fin
 *
 * \param   pDizaine
 * \param   pUnite
 * \param   pDizieme
 */
void GestionMatrices::dizainePourcent(uint8_t pDizaine, uint8_t pUnite, uint8_t pDizieme) 
{
	// Affichage des caractères sur les 8 segments des 4 afficheurs
	// Peut être simplifié, mais c'est plus compréhensible comme ça
	for(uint8_t compteur = 0; compteur != 8; compteur++) {
		switch(compteur) {
		case 0:
			maxTransfer(0x01, segmentPourcent(compteur), true, false);
			maxTransfer(0x01, segment(pDizieme, compteur), false, false);
			maxTransfer(0x01, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x01, segment(pDizaine, compteur), false, true);
			break;
		case 1:
			maxTransfer(0x02, segmentPourcent(compteur), true, false);
			maxTransfer(0x02, segment(pDizieme, compteur), false, false);
			maxTransfer(0x02, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x02, segment(pDizaine, compteur), false, true);
			break;
		case 2:
			maxTransfer(0x03, segmentPourcent(compteur), true, false);
			maxTransfer(0x03, segment(pDizieme, compteur), false, false);
			maxTransfer(0x03, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x03, segment(pDizaine, compteur), false, true);
			break;
		case 3:
			maxTransfer(0x04, segmentPourcent(compteur), true, false);
			maxTransfer(0x04, segment(pDizieme, compteur), false, false);
			maxTransfer(0x04, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x04, segment(pDizaine, compteur), false, true);
			break;
		case 4:
			maxTransfer(0x05, segmentPourcent(compteur), true, false);
			maxTransfer(0x05, segment(pDizieme, compteur), false, false);
			maxTransfer(0x05, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x05, segment(pDizaine, compteur), false, true);
			break;
		case 5:
			maxTransfer(0x06, segmentPourcent(compteur), true, false);
			maxTransfer(0x06, segment(pDizieme, compteur), false, false);
			maxTransfer(0x06, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x06, segment(pDizaine, compteur), false, true);
			break;
		case 6:
			maxTransfer(0x07, segmentPourcent(compteur), true, false);
			maxTransfer(0x07, segment(pDizieme, compteur), false, false);
			maxTransfer(0x07, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x07, segment(pDizaine, compteur), false, true);
			break;
		case 7:
			maxTransfer(0x08, segmentPourcent(compteur), true, false);
			maxTransfer(0x08, segment(pDizieme, compteur), false, false);
			maxTransfer(0x08, segmentV(pUnite, compteur), false, false);
			maxTransfer(0x08, segment(pDizaine, compteur), false, true);
			break;
		}
	}
}

/**
 * \brief   Affichage d'un nombre avec trois chiffres après la virgule. 
 *
 * \details Affichage des chiffres sur les 8 segments des 4 matrices
 *
 * \param   pUnite
 * \param   pDizieme
 * \param   pCentieme
 * \param   pMillieme
 */
void GestionMatrices::unite(uint8_t pUnite, uint8_t pDizieme, uint8_t pCentieme, uint8_t pMillieme) 
{
	// Affichage des chiffres sur les 8 segments des 4 afficheurs
	// Peut être simplifié, mais c'est plus compréhensible comme ça
	for(uint8_t compteur = 0; compteur != 8; compteur++) {
		switch(compteur) {
		case 0:
			maxTransfer(0x01, segment(pMillieme, compteur), true, false);
			maxTransfer(0x01, segment(pCentieme, compteur), false, false);
			maxTransfer(0x01, segment(pDizieme, compteur), false, false);
			maxTransfer(0x01, segmentV(pUnite, compteur), false, true);
			break;
		case 1:
			maxTransfer(0x02, segment(pMillieme, compteur), true, false);
			maxTransfer(0x02, segment(pCentieme, compteur), false, false);
			maxTransfer(0x02, segment(pDizieme, compteur), false, false);
			maxTransfer(0x02, segmentV(pUnite, compteur), false, true);
			break;
		case 2:
			maxTransfer(0x03, segment(pMillieme, compteur), true, false);
			maxTransfer(0x03, segment(pCentieme, compteur), false, false);
			maxTransfer(0x03, segment(pDizieme, compteur), false, false);
			maxTransfer(0x03, segmentV(pUnite, compteur), false, true);
			break;
		case 3:
			maxTransfer(0x04, segment(pMillieme, compteur), true, false);
			maxTransfer(0x04, segment(pCentieme, compteur), false, false);
			maxTransfer(0x04, segment(pDizieme, compteur), false, false);
			maxTransfer(0x04, segmentV(pUnite, compteur), false, true);
			break;
		case 4:
			maxTransfer(0x05, segment(pMillieme, compteur), true, false);
			maxTransfer(0x05, segment(pCentieme, compteur), false, false);
			maxTransfer(0x05, segment(pDizieme, compteur), false, false);
			maxTransfer(0x05, segmentV(pUnite, compteur), false, true);
			break;
		case 5:
			maxTransfer(0x06, segment(pMillieme, compteur), true, false);
			maxTransfer(0x06, segment(pCentieme, compteur), false, false);
			maxTransfer(0x06, segment(pDizieme, compteur), false, false);
			maxTransfer(0x06, segmentV(pUnite, compteur), false, true);
			break;
		case 6:
			maxTransfer(0x07, segment(pMillieme, compteur), true, false);
			maxTransfer(0x07, segment(pCentieme, compteur), false, false);
			maxTransfer(0x07, segment(pDizieme, compteur), false, false);
			maxTransfer(0x07, segmentV(pUnite, compteur), false, true);
			break;
		case 7:
			maxTransfer(0x08, segment(pMillieme, compteur), true, false);
			maxTransfer(0x08, segment(pCentieme, compteur), false, false);
			maxTransfer(0x08, segment(pDizieme, compteur), false, false);
			maxTransfer(0x08, segmentV(pUnite, compteur), false, true);
			break;
		}
	}
}

/**
 * \brief   Affichage d'un nombre avec deux chiffres après la virgule et dégré. 
 *
 * \details Affichage des chiffres sur les 8 segments des 3 matrices et degré à la fin
 *
 * \param   pUnite
 * \param   pDizieme
 * \param   pCentieme
 */
void GestionMatrices::uniteDeg(uint8_t pUnite, uint8_t pDizieme, uint8_t pCentieme) 
{
	// Affichage des caractères sur les 8 segments des 4 afficheurs
	// Peut être simplifié, mais c'est plus compréhensible comme ça
	for(uint8_t compteur = 0; compteur != 8; compteur++) {
		switch(compteur) {
		case 0:
			maxTransfer(0x01, segmentDeg(compteur), true, false);
			maxTransfer(0x01, segment(pCentieme, compteur), false, false);
			maxTransfer(0x01, segment(pDizieme, compteur), false, false);
			maxTransfer(0x01, segmentV(pUnite, compteur), false, true);
			break;
		case 1:
			maxTransfer(0x02, segmentDeg(compteur), true, false);
			maxTransfer(0x02, segment(pCentieme, compteur), false, false);
			maxTransfer(0x02, segment(pDizieme, compteur), false, false);
			maxTransfer(0x02, segmentV(pUnite, compteur), false, true);
			break;
		case 2:
			maxTransfer(0x03, segmentDeg(compteur), true, false);
			maxTransfer(0x03, segment(pCentieme, compteur), false, false);
			maxTransfer(0x03, segment(pDizieme, compteur), false, false);
			maxTransfer(0x03, segmentV(pUnite, compteur), false, true);
			break;
		case 3:
			maxTransfer(0x04, segmentDeg(compteur), true, false);
			maxTransfer(0x04, segment(pCentieme, compteur), false, false);
			maxTransfer(0x04, segment(pDizieme, compteur), false, false);
			maxTransfer(0x04, segmentV(pUnite, compteur), false, true);
			break;
		case 4:
			maxTransfer(0x05, segmentDeg(compteur), true, false);
			maxTransfer(0x05, segment(pCentieme, compteur), false, false);
			maxTransfer(0x05, segment(pDizieme, compteur), false, false);
			maxTransfer(0x05, segmentV(pUnite, compteur), false, true);
			break;
		case 5:
			maxTransfer(0x06, segmentDeg(compteur), true, false);
			maxTransfer(0x06, segment(pCentieme, compteur), false, false);
			maxTransfer(0x06, segment(pDizieme, compteur), false, false);
			maxTransfer(0x06, segmentV(pUnite, compteur), false, true);
			break;
		case 6:
			maxTransfer(0x07, segmentDeg(compteur), true, false);
			maxTransfer(0x07, segment(pCentieme, compteur), false, false);
			maxTransfer(0x07, segment(pDizieme, compteur), false, false);
			maxTransfer(0x07, segmentV(pUnite, compteur), false, true);
			break;
		case 7:
			maxTransfer(0x08, segmentDeg(compteur), true, false);
			maxTransfer(0x08, segment(pCentieme, compteur), false, false);
			maxTransfer(0x08, segment(pDizieme, compteur), false, false);
			maxTransfer(0x08, segmentV(pUnite, compteur), false, true);
			break;
		}
	}
}

/**
 * \brief   Affichage d'un nombre avec deux chiffres après la virgule et pourcent. 
 *
 * \details Affichage des chiffres sur les 8 segments des 3 matrices et pourcent à la fin
 *
 * \param   pUnite
 * \param   pDizieme
 * \param   pCentieme
 */
void GestionMatrices::unitePourcent(uint8_t pUnite, uint8_t pDizieme, uint8_t pCentieme) 
{
	// Affichage des caractères sur les 8 segments des 4 afficheurs
	// Peut être simplifié, mais c'est plus compréhensible comme ça
	for(uint8_t compteur = 0; compteur != 8; compteur++) {
		switch(compteur) {
		case 0:
			maxTransfer(0x01, segmentPourcent(compteur), true, false);
			maxTransfer(0x01, segment(pCentieme, compteur), false, false);
			maxTransfer(0x01, segment(pDizieme, compteur), false, false);
			maxTransfer(0x01, segmentV(pUnite, compteur), false, true);
			break;
		case 1:
			maxTransfer(0x02, segmentPourcent(compteur), true, false);
			maxTransfer(0x02, segment(pCentieme, compteur), false, false);
			maxTransfer(0x02, segment(pDizieme, compteur), false, false);
			maxTransfer(0x02, segmentV(pUnite, compteur), false, true);
			break;
		case 2:
			maxTransfer(0x03, segmentPourcent(compteur), true, false);
			maxTransfer(0x03, segment(pCentieme, compteur), false, false);
			maxTransfer(0x03, segment(pDizieme, compteur), false, false);
			maxTransfer(0x03, segmentV(pUnite, compteur), false, true);
			break;
		case 3:
			maxTransfer(0x04, segmentPourcent(compteur), true, false);
			maxTransfer(0x04, segment(pCentieme, compteur), false, false);
			maxTransfer(0x04, segment(pDizieme, compteur), false, false);
			maxTransfer(0x04, segmentV(pUnite, compteur), false, true);
			break;
		case 4:
			maxTransfer(0x05, segmentPourcent(compteur), true, false);
			maxTransfer(0x05, segment(pCentieme, compteur), false, false);
			maxTransfer(0x05, segment(pDizieme, compteur), false, false);
			maxTransfer(0x05, segmentV(pUnite, compteur), false, true);
			break;
		case 5:
			maxTransfer(0x06, segmentPourcent(compteur), true, false);
			maxTransfer(0x06, segment(pCentieme, compteur), false, false);
			maxTransfer(0x06, segment(pDizieme, compteur), false, false);
			maxTransfer(0x06, segmentV(pUnite, compteur), false, true);
			break;
		case 6:
			maxTransfer(0x07, segmentPourcent(compteur), true, false);
			maxTransfer(0x07, segment(pCentieme, compteur), false, false);
			maxTransfer(0x07, segment(pDizieme, compteur), false, false);
			maxTransfer(0x07, segmentV(pUnite, compteur), false, true);
			break;
		case 7:
			maxTransfer(0x08, segmentPourcent(compteur), true, false);
			maxTransfer(0x08, segment(pCentieme, compteur), false, false);
			maxTransfer(0x08, segment(pDizieme, compteur), false, false);
			maxTransfer(0x08, segmentV(pUnite, compteur), false, true);
			break;
		}
	}
}

/**
 * \brief   Destructeur. 
 *
 * \note    Appelé automatiquement à la fin du programme
 */
GestionMatrices::~GestionMatrices(void)
{
}

/*! \class GestionMatrices 
 *  \brief Class pour l'affichage sur les matrices à base de MAX7219.
 *
 */
