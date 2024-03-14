/*
  Titre        : Projet 1 - Testeur de cable RJ45
  Auteur       : Dominique KOUASSI.
  Date         : 13/03/2024.
  Description  : Definit 8 broches connectes au port RJ45 emetteur et 8 broches connectes au port RJ45 recepteur.
                 Instantie ensuite deux objets de type RJ45 en passant en parametre les broches emmetrices et les broches receptrices.
                 Attention: les broches emetrices doivent pouvoir etre configurees en SORTIE et les broches receptrices doivent
                 pouvoir etre configurees en ENTREE avec la function PULL_DOWN pour eviter de connecter des resistance externes.
                 En effet certaines broches du ESP32 ne peuvent pas etre configurees en sorties. Sur le ESP32, les broches 
                 GPI34, GPI35, GPI36 et GPI39 sont des entrees uniquement et ne possedent pas de fonction PULL_UP et PULL_DOWN

                 Un objet testeur qui recoit les deux objets RJ45 en parametre est instantier. Le testeur ecriera un 1 a tour de role
                 sur chaque sortie de RJ45 emetteur et verifiera la position active sur le port RJ45 en reception. Le resultat de 
                 l'operation determine le type de cable DROIT, CROISE ou INCONNU.
                 La methode start_tester() de l'objet Tester, test le cable branche sur les deux ports RJ45 en boucle dans le loop
                 toute les secondes.
                 Le resultat eest affiche a l'utilisateur sur le port Serial suivant le format suivant:
                
                --------------------------
                CABLE DROIT
                TX  ->   RX
                1   ->   1
                2   ->   2
                3   ->   3
                4   ->   4
                5   ->   5
                6   ->   6
                7   ->   7
                8   ->   8
                --------------------------

  Version      : 0.0.1
*/

#include <Arduino.h>
#include "Rj45.hpp"
#include "Tester.hpp"

// Define RJ45 Transmitter pins
#define RJ45_TX_PIN1  15        // White Orange
#define RJ45_TX_PIN2  2         // Orange
#define RJ45_TX_PIN3  4         // White Green
#define RJ45_TX_PIN4  5         // Blue
#define RJ45_TX_PIN5  18        // White Blue
#define RJ45_TX_PIN6  19        // Green
#define RJ45_TX_PIN7  21        // White Brown
#define RJ45_TX_PIN8  22        // Brown

// Define RJ45 Receiver pins
#define RJ45_RX_PIN1  13        // White Orange
#define RJ45_RX_PIN2  14        // Orange
#define RJ45_RX_PIN3  27        // White Green
#define RJ45_RX_PIN4  26        // Blue
#define RJ45_RX_PIN5  25        // White Blue
#define RJ45_RX_PIN6  33        // Green
#define RJ45_RX_PIN7  32        // White Brown
#define RJ45_RX_PIN8  12        // Brown

// Instantiate two RJ45 Objects
Rj45 rj45_sender(SENDER, RJ45_TX_PIN1, RJ45_TX_PIN2, RJ45_TX_PIN3, RJ45_TX_PIN4, RJ45_TX_PIN5, RJ45_TX_PIN6, RJ45_TX_PIN7, RJ45_TX_PIN8);
Rj45 rj45_receiver(RECEIVER, RJ45_RX_PIN1, RJ45_RX_PIN2, RJ45_RX_PIN3, RJ45_RX_PIN4, RJ45_RX_PIN5, RJ45_RX_PIN6, RJ45_RX_PIN7, RJ45_RX_PIN8);

// Instantiate a Tester Object
Tester  tester(rj45_sender, rj45_receiver);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Start the tester
  tester.start_test();

  delay(1000);

}
