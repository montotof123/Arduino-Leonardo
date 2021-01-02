/*!
 *   \file    GestionMatrices.h
 *   \brief   Entete de la classe de gestion des matrices à base de MAX7219.
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    01/01/2021
 */
 
#ifndef GESTIONMATRICES_H_
#define GESTIONMATRICES_H_

#include <stdint.h>
#include <TimeLib.h>

class GestionMatrices {
	public:
		GestionMatrices(uint8_t);
		
		void horloge(tmElements_t);
		void affichage(float);
		void affichageDeg(float);
		void affichagePourcent(float);
		
		void intensity(uint8_t);
		
		virtual ~GestionMatrices(void);
		
	private:
		void heure(uint8_t, uint8_t, uint8_t, uint8_t); 
		void millier(uint8_t, uint8_t, uint8_t, uint8_t); 
		void centaine(uint8_t, uint8_t, uint8_t, uint8_t); 
		void centaineDeg(uint8_t, uint8_t, uint8_t); 
		void centainePourcent(uint8_t, uint8_t, uint8_t); 
		void dizaine(uint8_t, uint8_t, uint8_t, uint8_t); 
		void dizaineDeg(uint8_t, uint8_t, uint8_t); 
		void dizainePourcent(uint8_t, uint8_t, uint8_t); 
		void unite(uint8_t, uint8_t, uint8_t, uint8_t); 
		void uniteDeg(uint8_t, uint8_t, uint8_t); 
		void unitePourcent(uint8_t, uint8_t, uint8_t); 
		void reset(void);
		void maxTransfer(uint8_t, uint8_t, bool, bool);
		uint8_t segment(uint8_t, uint8_t);
		uint8_t segmentDeg(uint8_t);
		uint8_t segmentPourcent(uint8_t);
		uint8_t segmentDp(uint8_t, uint8_t);
		uint8_t segmentDm(uint8_t, uint8_t);
		uint8_t segmentV(uint8_t, uint8_t);
		
		uint8_t cs;
};

#endif
