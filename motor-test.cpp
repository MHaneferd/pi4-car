#include <pigpio.h>
#include <unistd.h>

class Motor {
public:
    Motor(int Ena, int In1, int In2) : Ena(Ena), In1(In1), In2(In2) {
        // Initialiser GPIO
        gpioSetMode(Ena, PI_OUTPUT);
        gpioSetMode(In1, PI_OUTPUT);
        gpioSetMode(In2, PI_OUTPUT);

        // Sett PWM-frekvens og start PWM på Ena-pinnen
        gpioPWM(Ena, 0); // Start PWM med duty cycle 0
    }

    void forover(int hastighet = 50) {
        gpioWrite(In1, PI_LOW);     // Revers
        gpioWrite(In2, PI_HIGH);    // Forover
        gpioPWM(Ena, hastighet * 2.55); // Fart, konverter til 0-255
    }

    void bakover(int hastighet = 50) {
        gpioWrite(In1, PI_HIGH);    // Revers
        gpioWrite(In2, PI_LOW);     // Forover
        gpioPWM(Ena, hastighet * 2.55); // Fart
    }

    void stopp() {
        gpioPWM(Ena, 0); // Stopp motoren
    }

private:
    int Ena, In1, In2;
};

class Bil {
public:
    Bil() : motor1(2, 3, 4), motor2(17, 27, 22) {}

    void forover(int hastighet = 50, float tid = 0) {
        motor1.forover(hastighet);
        motor2.forover(hastighet);
        usleep(tid * 1000000);
    }

    void bakover(int hastighet = 50, float tid = 0) {
        motor1.bakover(hastighet);
        motor2.bakover(hastighet);
        usleep(tid * 1000000);
    }

    void høyreF(int hastighet = 50, float tid = 0) {
        motor1.forover(hastighet);
        motor2.bakover((int)(hastighet / 2));
        usleep(tid * 1000000);
    }

    void høyreB(int hastighet = 50, float tid = 0) {
        motor1.bakover(hastighet);
        motor2.forover((int)(hastighet / 2));
        usleep(tid * 1000000);
    }

    void stopp() {
        motor1.stopp();
        motor2.stopp();
    }

private:
    Motor motor1;
    Motor motor2;
};

int main() {
    if (gpioInitialise() < 0) {
        // Sjekk om initialisering feilet
        return -1;
    }

    Bil bil;

    while (true) {
        bil.forover(100, 2);
        bil.stopp();
        sleep(2);
        bil.høyreB(100, 0.5);
        bil.stopp();
        sleep(2);
    }

    gpioTerminate(); // Avslutter pigpio-biblioteket
    return 0;
}
