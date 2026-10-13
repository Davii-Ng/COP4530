#include "CarFactory.h"
#include "Locomotive.h"
#include "PassengerCar.h"
#include "FreightCar.h"
#include "TankerCar.h"

CarPtr makeCar(CarKind kind, int id, double amount, bool dangerous) {
    switch (kind) {
        case CarKind::Locomotive:
            return CarPtr(new Locomotive(id));
        case CarKind::Passenger:
            return CarPtr(new PassengerCar(id, static_cast<int>(amount)));
        case CarKind::Freight:
            return CarPtr(new FreightCar(id, amount));
        case CarKind::Tanker:
            return CarPtr(new TankerCar(id, amount, dangerous));
    }
    return nullptr;
}
