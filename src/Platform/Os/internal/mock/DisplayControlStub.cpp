#include "DisplayControlStub.h"

#include <ng-log/logging.h>

void DisplayControlStub::turnOn() {
    LOG(INFO) << "DisplayControl: Turning display on";
}

void DisplayControlStub::turnOff() {
    LOG(INFO) << "DisplayControl: Turning display off";
}

void DisplayControlStub::dim(uint8_t level) {
    LOG(INFO) << "DisplayControl: Dimming display to level " << static_cast<int>(level);
}
