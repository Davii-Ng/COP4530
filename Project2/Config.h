#ifndef CONFIG_H
#define CONFIG_H

// Shared constants. Weights in tons, money in dollars.
namespace Config {

// Train rules
constexpr int MAX_TRAIN_LENGTH = 12;
constexpr int SIDING_CAPACITY = 6;

// Locomotive
constexpr double LOCO_WEIGHT = 60.0;
constexpr double LOCO_PULL_CAPACITY = 300.0;

// Passenger car
constexpr double PASSENGER_TARE = 25.0;
constexpr double PASSENGER_WEIGHT_PER_PERSON = 0.08;
constexpr double TICKET_PRICE = 40.0;
constexpr int PASSENGER_MAX_SEATS = 80;

// Freight car
constexpr double FREIGHT_TARE = 20.0;
constexpr double FREIGHT_RATE_PER_TON = 15.0;
constexpr double FREIGHT_MAX_LOAD = 70.0;

// Tanker car
constexpr double TANKER_TARE = 30.0;
constexpr double TANKER_RATE_PER_TON = 25.0;
constexpr double TANKER_MAX_LOAD = 60.0;
constexpr double DANGEROUS_SURCHARGE = 1.5;

} // namespace Config

#endif