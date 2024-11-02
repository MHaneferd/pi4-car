import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)


class Motor():
    def __init__(self,Ena,In1,In2 ):
        # Venstre side
        self.Ena = Ena
        self.In1 = In1
        self.In2 = In2

        GPIO.setup(self.Ena, GPIO.OUT)
        GPIO.setup(self.In1, GPIO.OUT)
        GPIO.setup(self.In2, GPIO.OUT)

        self.pwma = GPIO.PWM(self.Ena, 100)

        self.pwma.start(0)

    def forover(self,hastighet = 50):
        GPIO.output(self.In1,GPIO.LOW) # Revers
        GPIO.output(self.In2,GPIO.HIGH) # Forover
        self.pwma.ChangeDutyCycle(hastighet) # Fart  
 
    def bakover(self,hastighet = 50):
        GPIO.output(self.In1,GPIO.HIGH) # Revers
        GPIO.output(self.In2,GPIO.LOW) # Forover
        self.pwma.ChangeDutyCycle(hastighet) # Fart    

    def stopp(self):
        self.pwma.ChangeDutyCycle(0) # Fart  

class Bil():
    def __init__(self):
        self.motor1 = Motor(2,3,4) # Venstre side
        self.motor2 = Motor(17,27,22) # Høyre side

    def forover(self,hastighet = 50,tid = 0):
        self.motor1.forover(hastighet)
        self.motor2.forover(hastighet)
        sleep(tid)
        
    def bakover(self,hastighet = 50,tid = 0):
        self.motor1.bakover(hastighet)
        self.motor2.bakover(hastighet)
        sleep(tid)
        
    def høyreF(self,hastighet = 50,tid = 0):
        self.motor1.forover(hastighet)
        self.motor2.bakover(hastighet//2)
        sleep(tid)

    def høyreB(self,hastighet = 50,tid = 0):
        self.motor1.bakover(hastighet)
        self.motor2.forover(hastighet//2)
        sleep(tid)

    def stopp(self):
        self.motor1.stopp()
        self.motor2.stopp()


bil = Bil()


while True:
    
    bil.forover(100,2)
    bil.stopp()
    sleep (2)     
    bil.høyreB(100,0.5)
    bil.stopp()
    sleep(2)




    
