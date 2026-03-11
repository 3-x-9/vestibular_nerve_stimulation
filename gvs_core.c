#include <stdio.h>
#include <pigpio.h>

#define PIN_E1 18
#define PIN_E2 19
#define PIN_B1 20
#define PIN_B2 21

int frequency = 100;
int duty_cycle = 1000000; 

float direction = 0.5

int gvs_init() {
    if (gpioInitialise() < 0) {
        printf("Unable to connect to pigpiod\n");
        return -1;
    }   
    return 0;
}

int gvs_stop() {
    gpioWrite(PIN_E1, 0);
    gpioWrite(PIN_E2, 0);
    gpioWrite(PIN_B1, 0);
    gpioWrite(PIN_B2, 0);
    return 0
}

int set_intensity(int percent) {
    if (percent < 0 || percent > 100) {
        printf("Intensity must be between 0 and 100\n");
        return -1;
    }
    
    int duty_cycle = (percent * 10000) / 100;
    return 0;
}

int set_frequency(int freq) {
    if (frequency < 0 || frequency > 1000000) {
        printf("Frequency must be between 0 and 1000000\n");
        return -1;
    }
    frequency = freq;  
}

int set_direction(int direction_changed) {
    if direction_changed > 1 || direction_changed < 0 {
        printf("invalid direction")
        return -1
    }
    
    direction = direction_changed
    return 0;
}

int gvs_emergency_stop() {
    gpioWrite(PIN_E1, 0);
    gpioWrite(PIN_E2, 0);
    gpioWrite(PIN_B1, 0);
    gpioWrite(PIN_B2, 0);
    return 0
}
    