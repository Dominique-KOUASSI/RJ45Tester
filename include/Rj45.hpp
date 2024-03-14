/*
  Titre        : Projet 1 - Testeur de cable RJ45
  Auteur       : Dominique KOUASSI.
  Date         : 13/03/2024.
  Description  : Class RJ45
                 Le testeur RJ45 possede deux ports RJ45. Un port doit etre defini en emission tandis que le second
                 doit etre defini en reception.
                 Chaque port possede 8 broches qui seront connectes au microcontroleur. les numeros de broches
                 sont enregistres dans un tableau de 8 entiers. Le tableau servira a activer les broches a tour de
                 role et verifier le signal recu sur les broches receptrices.
            
  Version      : 0.0.1
*/

#ifndef RJ45_H
#define RJ45_H

#include <Arduino.h>

// Define a type for an RJ45 object.
enum rj45_port {
    SENDER,
    RECEIVER
};

typedef enum rj45_port rj45_port_type_t;

class Rj45 {
    private:
        // RJ45 port type: SENDER --> define pins as OUPUTS / RECEIVER --> define pins as INPUTS.
        rj45_port_type_t rj45_port_type;
        // Array of microcontroler pin numbers.
        uint8_t rj45_pin[8];  

    public:
        Rj45();
        Rj45(rj45_port_type_t rj45_port_type_,
            uint8_t rj45_pin1_num,
            uint8_t rj45_pin2_num,
            uint8_t rj45_pin3_num,
            uint8_t rj45_pin4_num,
            uint8_t rj45_pin5_num,
            uint8_t rj45_pin6_num,
            uint8_t rj45_pin7_num,
            uint8_t rj45_pin8_num);

        void set_rj45_pin(uint8_t rj45_pin_);
        void clear_rj45_pin(uint8_t rj45_pin_);
        uint8_t read_rj45_pin(uint8_t rj45_pin_);
        uint8_t get_rj45_pin_by_index(uint8_t index);

};
#endif // RJ45_H