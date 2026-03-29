#include <stdio.h>
#include <pigpio.h>

#define PIN_B1 18
#define PIN_B2 19

typedef struct {
    int frequency;
    int duty_cycle;
    int direction;
    int running;
} GVSState;

GVSState state;

int gvs_init() {
    if (gpioInitialise() < 0) {
        printf("Unable to connect to pigpiod\n");
        return -1;
    }

    gpioSetMode(PIN_B1, PI_OUTPUT);
    gpioSetMode(PIN_B2, PI_OUTPUT);

    state.frequency = 100;
    state.duty_cycle = 1000000;
    state.direction = 0;
    state.running = 0;

    return 0;
}

int gvs_start() {
    if (state.direction == 0) {
        gpioHardwarePWM(PIN_B1, state.frequency, state.duty_cycle);
        gpioHardwarePWM(PIN_B2, state.frequency, 0);
    } else {
        gpioHardwarePWM(PIN_B1, state.frequency, 0);
        gpioHardwarePWM(PIN_B2, state.frequency, state.duty_cycle);
    }

    state.running = 1;
    return 0;
}

int gvs_stop() {
    gpioHardwarePWM(PIN_B1, 0, 0);
    gpioHardwarePWM(PIN_B2, 0, 0);
    state.running = 0;
    return 0;
}

int set_intensity(int percent) {
    if (percent < 0 || percent > 100) {
        printf("Intensity must be between 0 and 100\n");
        return -1;
    }
    
    state.duty_cycle = percent * 10000;
    if (state.running) {
        gvs_start();
    }
    return 0;
}

int set_frequency(int frequency) {
    if (frequency < 0 || frequency > 1000000) {
        printf("Frequency must be between 0 and 1000000\n");
        return -1;
    }
    state.frequency = frequency;
    if (state.running) {
        gvs_start();
    }
    return 0;
}

int set_direction(int direction) {
    if (direction > 1 || direction < 0) {
        printf("invalid direction");
        return -1;
    }
    
    state.direction = direction;
    if (state.running) {
        gvs_start();
    }
    return 0;
}

int gvs_emergency_stop() {
    gvs_stop();
    return 0;
}
