# arduinosan
## Artisan-compatible arduino sketches and tutorial for sensing bean temp and environmental temp

When you're roasting coffee, it's nice to be able to measure the temperature within the bean mass that you're roasting. Knowing the environmental temperature is nice too, since the ambient temperature will impact the corresponding energy and time that needs to be input into the roast. However, if you're using a roaster that lacks a thermocouple or thermistor, you need to roll your own solution. You can buy one off the shelf (except it won't have environmental temp, so come on), but where's the fun in that? Let's make our own!

Since you're collecting these temperature data digitally, you probably also want to record and monitor them digitally as well. Artisan is open-source roasting software that facilitates the generation of roasting curves, which are the core tool for understanding and adjusting a roast as it happens. Getting data to Artisan can be pretty tricky.

There are a handful of solutions out there for solving this fun little niche problem, but most of them aren't very well documented. So, here we go!

### Electronics configuration

#### Stuff you'll need
##### Core components
- Metro 328 [(Adafruit)](https://www.adafruit.com/product/2488)
- PT1000 RTD Temperature Sensor Amplifier - MAX31865 [(Adafruit)](https://www.adafruit.com/product/3648)
- Platinum RTD sensor [(Adafruit)](https://www.adafruit.com/product/3290)
- DHT11 basic temperature-humidity sensor + extras [(Adafruit)](https://www.adafruit.com/product/386)
  - You need a 4.7K or 10K resistor to pull it up, which is the "extra" that's included
##### Other stuff you'll probably need if you don't have it lying around
- Breadboard [(Adafruit)](https://www.adafruit.com/product/64)
- Jumper wires or other wire for breadboarding [(Adafruit)](https://www.adafruit.com/product/153)
- Micro USB to (your USB flavor here, mine's USB C) for Metro 328 [(Adafruit)](https://www.adafruit.com/product/3878)
  - Make sure the cable is *not* data-only if you want to run power through it instead of the DC jack
##### Optional but nice
- Mounting plate for Metro 328 and breadboard [(Adafruit)](https://www.adafruit.com/product/275)
##### If you've never done an electronics project before, you'll also have to get
- Soldering iron
- Solder
- Diagonal cutters
- X-Acto knife (because you have to cut a wire on the MAX31865)
- But really, just buy [this electronics starter kit](https://www.adafruit.com/product/136), which includes a half-size breadboard too, so hey, cross that off your list

#### Directions

##### A. Get the MAX31865 ready

A1. Configure the board for a 3-wire set-up

If you've never worked with a PCB before, this is going to be an adventure. Some PCBs you buy require actual physical changes to the board to make them work for your specific configuration. These are referred to as "jumpers". The MAX31865 has jumpers to configure the board for 2-, 3-, or 4-wire RTD sensors. We're using a 3-wire, so we've got to do two things.

First, we cut a wire between two pads. "Cutting a wire" on a board means you're straight up using a razor to slice through a tiny line of copper that's making a connection. You're cutting the wire that connects (a) the pad that is directly above the "24" text and (b) the pad to its right. So, take your x-acto, and cut that thing. Realize that you need to get down in there, so trust yourself to apply some pressure and slice that copper out.

![cutting](https://github.com/austinj/arduinosan/blob/master/images/adafruit_products_pinouts_wire.jpg "Cutting the wire")

Second, we solder two pads together in two separate places. You're soldering the (a) 2/3 wire pads and (b) the two right-most pads above the "24 3" text.

![jumping](https://github.com/austinj/arduinosan/blob/master/images/adafruit_products_pinouts_jumpers.jpg "Jumping the pads")

A2. Solder the headers and terminal blocks on

Use [this guide](https://learn.adafruit.com/adafruit-max31865-rtd-pt100-amplifier/assembly) from Adafruit; it walks you through this whole step with lots of lovely pictures.

##### B. Wire up everything
B1. Connect the RTD sensor to the MAX31865

Use [this guide](https://learn.adafruit.com/adafruit-max31865-rtd-pt100-amplifier/rtd-wiring-config#3-wire-sensors-4-10) from Adafruit to see how to get the wires from your 3-wire RTD sensor into the contacts. The terminals at the end of the wires are forked, but this makes them a really bad fit for the terminal blocks, so either snap one end of the terminal off (which is what I did) or I guess you could try and smash them together? I don't know, I just wiggled one end of the terminal on each wire back and forth with some needle-nose pliers until it snapped off.

B2. Wire up everything else, including your DHT11 environmental sensor. Just follow this fun diagram!

![fritzing](https://github.com/austinj/arduinosan/blob/master/images/arduinosan_bb.jpg "Fritzing diagram")

##### C. Upload the arduino sketch to the Metro 328

Download "max31865_dht_artisan.ino" from this repository. Open it up in Arduino and push it to your Metro 328. It's not sending anything to your serial monitor, so don't look for anything in there. It's time for some Artisan config screens.

##### D. Configure Artisan

Oh, this is fun. You'll be using MODBUS protocol.

1. Open Artisan
2. Go to Config \ Device...
3. Select Meter:MODBUS

![configdevice](https://github.com/austinj/arduinosan/blob/master/images/configdevice.png "Config \ Device")

4. After you press OK, you'll get sent to the Ports Configuration window.

5. Before we move on, we need to identify the path for your Metro 328's serial port.

6. Make sure your Metro 328 is on and talking to your computer.

7. If you're running OS X like me, open a terminal window and enter `ls /dev/tty.*`. From those entries listed, you gotta figure out which one is your port name. I used [this thread from StackOverflow](https://stackoverflow.com/questions/12254378/how-to-find-the-serial-port-number-on-mac-os-x). Mine was "/dev/tty.SLAB_USBtoUART" (note that you need the whole path name, including "/dev/"!). If you're not running OS X, or if you think you're doing this part wrong, just Google around for "serial port [your operating system here]", maybe add "arduino" or "metro 328" in there. You should be able to figure it out.

8. Pop your serial port name into "Comm Port" and then set everything else to match below.

![modbus](https://github.com/austinj/arduinosan/blob/master/images/modbus.png "Modbus")

9. Click OK, and start up a roast in Artisan! You should see values for ET and BT. You did it.

##### E. Roast some coffee!

May I suggest a [lovely East African dry process](https://www.sweetmarias.com/ethiopia-organic-dry-process-sidama-keramo-6287-2.html)?

### Credits

- [Lukeinator42's Artisan-friendly modbus arduino sketch](https://github.com/lukeinator42/coffee-roaster)
- [Adafruit's MAX31865 documentation](https://learn.adafruit.com/adafruit-max31865-rtd-pt100-amplifier/overview)
- [Adafruit's DHT11 documentation](https://learn.adafruit.com/dht/using-a-dhtxx-sensor)
- [This thread on home-barista.com](https://www.home-barista.com/home-roasting/getting-artisan-to-talk-to-arduino-t58234.html)
