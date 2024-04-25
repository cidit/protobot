/*--- Entête principale -- information sur le programme
    
Programme:        AlphaBot2_Touche.ino
Date:             18 avril 2024
Auteur:           Claude Bouchard
Pltform matériel: Arduino UNO
Pltform develop : Arduino 2.2.1
Description:      Démonstration des touches du AlphaBot2-Ar
Fonctionnalités:  Permet de lire les 5 boutons de la manette et les deux pare-chocs avant
Notes:            Aucune
  
-- Inspirations et credits: --
https://www.waveshare.com/wiki/AlphaBot2-Ar

*/
 
/* --- Materiel et composants -------------------------------------------
Robot AlphaBot2-Ar
*/


/* --- HISTORIQUE de développement --------------------------------------
 * v0.1.0 Version d'esssai
 */

 // Déclaration des libraires et des objets
#include "AlphaBot2.h"
Touches touches(&Wire); //Les touches sont lues via une communication Wire

void setup() {
  Wire.begin();
  touches.begin();
  Serial.begin(115200);
}

void loop() {
  touches.refresh();
  montrerEtatDe(&touches.gauche,"gauche");
  montrerEtatDe(&touches.droite,"droite");
  montrerEtatDe(&touches.haut,"haut");
  montrerEtatDe(&touches.bas,"bas");
  montrerEtatDe(&touches.selection,"selection");
  montrerEtatDe(&touches.parechocGauche,"pare-choc gauche");
  montrerEtatDe(&touches.parechocDroite,"pare-choc droite");
}


// fonction générique pour afficher l'état d'une touche de type BoutonBase
void montrerEtatDe(BoutonBase* bouton, String nomTouche) {
  if (bouton->isPressed()) {
    log(nomTouche, "appuyé");
  } else if (bouton->isLongPressed()) {
    log(nomTouche, "appuyé longuement");
  } else if (bouton->isReleased()) {
    log(nomTouche, "relâché");
  }
}

// Affichage d'un message générique via le port Série
void log(String nomTouche, String action) {
  Serial.print("La touche ");
  Serial.print(nomTouche);
  Serial.print(" est ");
  Serial.print(action);
  Serial.println('.');
}