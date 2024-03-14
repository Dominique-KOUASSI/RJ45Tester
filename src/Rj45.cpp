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

#include <Arduino.h>
#include "Rj45.hpp"

Rj45::Rj45() {};

Rj45::Rj45(rj45_port_type_t rj45_port_type_,
            uint8_t rj45_pin1_num,
            uint8_t rj45_pin2_num,
            uint8_t rj45_pin3_num,
            uint8_t rj45_pin4_num,
            uint8_t rj45_pin5_num,
            uint8_t rj45_pin6_num,
            uint8_t rj45_pin7_num,
            uint8_t rj45_pin8_num) {

    rj45_port_type = rj45_port_type_;

    if (rj45_port_type == SENDER) {
        // Store microcontroler pin number in an array.
        // Define pins as OUTPUTS since this RJ45 port is a SENDER.
        rj45_pin[0] = rj45_pin1_num;
        pinMode(rj45_pin1_num, OUTPUT);

        rj45_pin[1] = rj45_pin2_num;
        pinMode(rj45_pin2_num, OUTPUT);

        rj45_pin[2] = rj45_pin3_num;
        pinMode(rj45_pin3_num, OUTPUT);

        rj45_pin[3] = rj45_pin4_num;
        pinMode(rj45_pin4_num, OUTPUT);

        rj45_pin[4] = rj45_pin5_num;
        pinMode(rj45_pin5_num, OUTPUT);

        rj45_pin[5] = rj45_pin6_num;
        pinMode(rj45_pin6_num, OUTPUT);

        rj45_pin[6] = rj45_pin7_num;
        pinMode(rj45_pin7_num, OUTPUT);

        rj45_pin[7] = rj45_pin8_num;
        pinMode(rj45_pin8_num, OUTPUT);

    } else {
        // Store microcontroler pin number in an array.
        // Define pins as INPUTS since this RJ45 port is a RECEIVER.
        // Define pins as INPUTS with PULLDOWN to avoid using external resistors.
        rj45_pin[0] = rj45_pin1_num;
        pinMode(rj45_pin1_num, INPUT_PULLDOWN);

        rj45_pin[1] = rj45_pin2_num;
        pinMode(rj45_pin2_num, INPUT_PULLDOWN);

        rj45_pin[2] = rj45_pin3_num;
        pinMode(rj45_pin3_num, INPUT_PULLDOWN);

        rj45_pin[3] = rj45_pin4_num;
        pinMode(rj45_pin4_num, INPUT_PULLDOWN);

        rj45_pin[4] = rj45_pin5_num;
        pinMode(rj45_pin5_num, INPUT_PULLDOWN);

        rj45_pin[5] = rj45_pin6_num;
        pinMode(rj45_pin6_num, INPUT_PULLDOWN);

        rj45_pin[6] = rj45_pin7_num;
        pinMode(rj45_pin7_num, INPUT_PULLDOWN);

        rj45_pin[7] = rj45_pin8_num;
        pinMode(rj45_pin8_num, INPUT_PULLDOWN);

    }
}

/**
 * @brief Set the the RJ45 pin number passed as argument to HIGH level.
 *        This is done for an RJ45 port defined as SENDER.
 * 
 * @param rj45_pin_ 
 */
void Rj45::set_rj45_pin(uint8_t rj45_pin_) {
    digitalWrite(rj45_pin[rj45_pin_ - 1], HIGH);
}

/**
 * @brief Clear the RJ45 pin number passed as argument (pin = LOW).
 *        This is done for an RJ45 port defined as SENDER.
 * 
 * @param rj45_pin_ 
 */
void Rj45::clear_rj45_pin(uint8_t rj45_pin_) {
    digitalWrite(rj45_pin[rj45_pin_ - 1], LOW);
}

/**
 * @brief Reads the value on the RJ45 pin passed as argument.
 *        This is done for an RJ45 port defined as RECEIVER.
 * 
 * @param rj45_pin_ 
 * @return uint8_t 
 */
uint8_t Rj45::read_rj45_pin(uint8_t rj45_pin_) {
    return(digitalRead(rj45_pin[rj45_pin_ - 1]));
}

/**
 * @brief Get the microcontroler pin number affected to the RJ45 pin.
 *        The pin is read from the pin array.
 * 
 * @param index 
 * @return uint8_t 
 */
uint8_t Rj45::get_rj45_pin_by_index(uint8_t index) {
    return  rj45_pin[index];
}