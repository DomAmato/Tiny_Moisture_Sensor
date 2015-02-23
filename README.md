# Tiny Moisture Sensor

Using an ATTiny as a moisture Sensor that includes i2c communication and/or an indication LED

The i2c feature exists to support arrays of sensors hooked up to a master, the information can be parsed and displayed as desired. Designed to be compatible with home-made moisture sensors but any analog sensor will work (just don't include the resistors if you want to use a different analog sensor.) It uses switching poles to prevent electrolysis and with infrequent read times ~5 minutes though that can be customized.

Each has a simple view for breadboarding and also a PCB setup for etching your own circuit boards, just download fritzing to view the .fzz files.

#3 Different styles

##LED only

This version has no communication capabilities but does have an indication LED 

##I2C Only

This version has no indication LED but can communicate over I2C, needs a master controller

##I2C and LED

This version has both an indication LED and the I2C communication protocol, unfortunately it requires all the pins on the ATTiny45/85 including the RESET pin which makes it very difficult to reprogram. Only use this is you are certain you wont be making changes. Reprogramming the tiny will require High Voltage Programming which I won't cover here but just search for it for a tutorial.
