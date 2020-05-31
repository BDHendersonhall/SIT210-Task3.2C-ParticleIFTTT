
int Data = 0;
char DataStr[1];

int led = D6; // the pin the LED is connected to
int photodiode = A0; // the pin the Photodiode is connected to

int analogvalue; //variable to hold the Photodiode readings
char analogvalueStr[30];

int SunlightOn = 50; // threshold value for when Sunlight is considered on the Terrarium, note for a photodiode the reading increases as light increases

void setup() 
{
    pinMode(led, OUTPUT);
    digitalWrite(led, HIGH); // Turn the LED on, we will use a physical barrier in between the LED and Photodiode to control light to the Photodiode
    
    analogvalue = analogRead(photodiode); // get the initial state

    if (Data == 0 and analogvalue >= SunlightOn) // if Data = 0; 'program start' and analogvalue >= sunlight threshold then Sunlight is on the Terrarium (on program start-up)
    {
        Data = 1; // light
    }
    else // if Data = 0; 'program start' and analogvalue < sunlight threshold then Sunlight is off the Terrarium (on program start-up)
    {
        Data = 2; // dark
    }
}

void loop() 
{

    analogvalue = analogRead(photodiode);

    if (Data == 1 and analogvalue < SunlightOn) // if Data = 1; 'light' and analogvalue < sunlight threshold - transition from light to dark
    {
        Particle.publish("SunlightOnTerrarium", "No");
        Data = 2; // dark
    }
    else if (Data == 2 and analogvalue >= SunlightOn) // if Data = 2; 'dark' and analogvalue >= sunlight threshold - transition from dark to light
    {
        Particle.publish("SunlightOnTerrarium", "Yes");
        Data = 1; // light
    }

    sprintf(analogvalueStr,"%d", analogvalue);
    Particle.publish("Photodiode",analogvalueStr);
    
    delay(1000); // delay for 1 seconds; in a real life situation this could/would be made longer but for demonstration purposes use 1 sec
}