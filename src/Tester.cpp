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

#include <Arduino.h>
#include "Tester.hpp"
#include "Rj45.hpp"

const uint8_t STRAIGHT_CABLE_MAPPING[] = {1, 2, 3, 4, 5, 6, 7 ,8};
const uint8_t CROSS_CABLE_MAPPING[] = {3, 6, 1, 4, 5, 2, 7 ,8};

Tester::Tester() {}

Tester::Tester(Rj45 rj45_sender, Rj45 rj45_receiver) {
    this->rj45_sender = rj45_sender;
    this->rj45_receiver = rj45_receiver;
}

/**
 * @brief look for the position activated on the RJ45 RECEIVER port after
 * writing a HIGH logic to one pin on the RJ45 SENDER port.
 * Returns 0 in case no position activated found. This is usually the case
 * when the two RJ45 ports are empty meaning no cable for testing is connected or
 * one line within the cable is broken.
 * 
 * @return uint8_t 
 */
uint8_t Tester::read_active_receiver_pin() {

    uint8_t active_receiver_pin = 0;        // No pin is active by default.

    for(uint8_t i = 0; i < 8; i++)
    {
        active_receiver_pin = digitalRead(rj45_receiver.get_rj45_pin_by_index(i));

        if(active_receiver_pin == 1)
        {
            active_receiver_pin = i + 1;    // Get the RJ45 line activated number.
            break;
        }
    }

    return active_receiver_pin;

}

/**
 * @brief test the cable connected to the RJ45 ports.
 * Will activate (write 1 logic) to every pin of the RJ45 SENDER port, then look for the
 * activated pin on the RJ45 RECEIVER port. the result is stored in an array which indicates
 * the cable type.
 */
void Tester::start_test() {
   // Clear all OUTPUT pins prior to start the test.
    for(uint8_t i = 1; i <= 8; i++)
    {
        rj45_sender.clear_rj45_pin(i);
    }

    // Set each RJ45 sender pin and read the RJ45 receiver pin activated.
    for(uint8_t i = 1; i <= 8; i++)
    {
        // Set the RJ45 sender pin.
        rj45_sender.set_rj45_pin(i);
        // Save the RJ45 receiver pin activated.
        active_receiver_pin[i - 1] = read_active_receiver_pin();
        // Clear the current RJ45 sender pin prior to continue.
        rj45_sender.clear_rj45_pin(i);

    }

    cable_type_t cable_type = check_cable_type();

    print_test_result(cable_type);

}

/**
 * @brief Compares the result array of int table against two predifined
 * tables and returns the cable type.
 * 
 * @return cable_type_t 
 */
cable_type_t Tester::check_cable_type() {
    // Use memcmp function to compare two arrays of bytes
    // int memcmp(const void *buf1, const void *buf2, size_t count);
    if(memcmp((uint8_t *)active_receiver_pin, (uint8_t *)STRAIGHT_CABLE_MAPPING, 8) == 0 )
    {      
        //Serial.println("STRAIGHT_CABLE");
        return STRAIGHT_CABLE;

    } else if (memcmp((uint8_t *)active_receiver_pin, (uint8_t *)CROSS_CABLE_MAPPING, 8) == 0)
    {
        //Serial.println("CROSS_CABLE");
        return CROSS_CABLE;

    }

    //Serial.println("UNKNOWN_CABLE");
    return UNKNOWN_CABLE;

}

void Tester::print_test_result(cable_type_t cable_type) {

    switch (cable_type) {
        case STRAIGHT_CABLE:
            Serial.println("CABLE DROIT");
            break;
        case CROSS_CABLE:
            Serial.println("CABLE CROISE");
            break;
        case UNKNOWN_CABLE:
            Serial.println("CABLE non BRANCHE ou DEFECTUEUX");
            break;
    }

    // Print result on the Serial port
    Serial.print("TX");
    Serial.print(" ");
    Serial.print(" ->");
    Serial.print("   ");
    Serial.println("RX");

    for(uint8_t i = 1; i <= 8; i++) {
        Serial.print(i);
        Serial.print(" ");
        Serial.print("  ->");
        Serial.print("   ");
        Serial.println(active_receiver_pin[i - 1]);

    }

    Serial.println("--------------------------");
    Serial.println("");

}