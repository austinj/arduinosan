# arduinosan
## Artisan-compatible arduino sketches and tutorial for sensing bean temp and environmental temp

It's extremely useful when roasting coffee to measure the temperature within the bean mass that you're roasting. Knowing the environmental temperature is nice too, since the ambient temperature will impact the corresponding energy and time that needs to be input into the roast. However, if you're using a roaster that lacks a thermocouple or thermistor, you need to roll your own solution. Arduino and some nice breakout boards make solving this pretty darn simple.

However, since you're collecting these data digitally, you probably also want to record and monitor them digitally as well. Artisan is open-source roasting software that facilitates the generation of roasting curves, which are the core tool for understanding and adjusting a roast as it happens. Getting data to Artisan is a little more challenging.

There are a handful of solutions out there for solving this fun little niche problem, but most of them aren't very well documented. So, this project is an effort to change that.

### Arduino sketches

Information on sketches here.

### Electronics configuration

#### Stuff you'll need
##### Core components
- Metro 328 [(Adafruit)](https://www.adafruit.com/product/2488)
- PT1000 RTD Temperature Sensor Amplifier - MAX31865 [(Adafruit)](https://www.adafruit.com/product/3648)
- Platinum RTD sensor [(Adafruit)](https://www.adafruit.com/product/3290)
- DHT11 basic temperature-humidity sensor + extras [(Adafruit)](https://www.adafruit.com/product/386)
-- You need a 4.7K or 10K resistor to pull it up, which is the "extra" that's included
##### Other stuff you'll probably need
- Breadboard [(Adafruit)](https://www.adafruit.com/product/64)
- Jumper wires or other wire for breadboarding [(Adafruit)](https://www.adafruit.com/product/153)
- Micro USB to (your USB flavor here, mine's USB C) for Metro 328 [(Adafruit)](https://www.adafruit.com/product/3878)
##### Optional but nice 
- Mounting plate for Metro 328 and breadboard [(Adafruit)](https://www.adafruit.com/product/275)
