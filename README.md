# Water level monitor

## About project

The key of this project was to learn how to use analog input of ESP8266 with embedded ADC (at pin A0). The median of readed data is sended to [Smarthome API](https://github.com/SmartHomeUMG/SmartHomeAPI). I am using a median, because it is tolerant of maximum and minimum value errors.


### Hardware:

#### Water level sensor:
##### Pinouts:
![water level sensor pinouts](/images/Water-Level-Sensor-Pinout.png "water level sensor pinouts.")
##### Logic:
The series of exposed parallel conductors, together acts as a variable resistor (kind of like a potentiometer) whose resistance varies according to the water level.
![water level sensor work](/images/Water-Level-Sensor-Working.gif "water level sensor work.")

#### ESP8266:
##### Pinouts:


| ESP8266| Water Level sensor |
| ------------- |:-------------:|
| A0    | S    |
| 3.3      | +  |
| GND      | -    |


