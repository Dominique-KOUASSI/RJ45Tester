/*
  Titre        : Projet 1 - Testeur de cable RJ45
  Auteur       : Dominique KOUASSI.
  Date         : 13/03/2024.
  Description  : Class Tester
                 Permet d'instantier un objet Testeur. Cet objet recoit deux objets de type RJ45 dont l'un en emission
                 et le second en reception.
                 Le testeur active a tour de role dans l'ordre (de 1 a 8) les sorties du RJ45 emetteur puis lit sur le 
                 RJ45 recepteur la position (entre 1 et 8) qui est active. Les resultats sont enregistres dans un tableau de 8 entiers.
                 Le testeur compare ce tableau a deux tableaux predefinis qui decrivent les cables droit et croise comme suit:
                 const uint8_t STRAIGHT_CABLE_MAPPING[] = {1, 2, 3, 4, 5, 6, 7 ,8};  // cable droit
                 const uint8_t CROSS_CABLE_MAPPING[] = {3, 6, 1, 4, 5, 2, 7 ,8};     // cable croise
                 Toute disposition differente indique un cable defectueux ou pas de cable branche dans les connecteurs RJ45.
            
  Version      : 0.0.1
*/

#ifndef TESTER_H
#define TESTER_H

#include <Arduino.h>
#include "Rj45.hpp"

// Define a type for an Cable object.
enum cable_type {
    STRAIGHT_CABLE,
    CROSS_CABLE,
    UNKNOWN_CABLE
};

typedef enum cable_type cable_type_t;

class Tester {
    private: 
    uint8_t active_receiver_pin[8];         // Array of pin activated on the RJ45 receiver port.
    Rj45 rj45_sender, rj45_receiver;        // Define two RJ45 object, one as SENDER and the second as a RECEIVER.
    uint8_t read_active_receiver_pin();     // Look for the pin activated on the RJ45 receiver port.
    cable_type_t check_cable_type();        // Identify the cable type.
    void print_test_result(cable_type_t cable_type);

    public:
    Tester();
    Tester(Rj45 rj45_sender, Rj45 rj45_receiver);
    void start_test();
};
#endif // TESTER_H