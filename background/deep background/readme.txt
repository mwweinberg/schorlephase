simplesweep - just a program to test servos

simple-ledcoundown-debounce - the original program to test the switch. I'm keeping it now mostly because it had an early version of the handling an interrupted  HIGH state logic.

statechange_to_switch_countdown - this will turn on the LED and do the 3 second countdown for HIGH, keep it off for LOW

statechange_to_switch_conntdown_offsequence - this is designed to integrate an off sequence to simulate what happens in an interrupt. However 1. there is no way to interrupt so it doesn't work, and 2. when it should be triggering LOW tracker 0 it is reading LOW tracker 1

statechange_to_switch_countdown_object - moves the contdown to a function - simple OOP example

led_sequence - functioning template to control the three phases - starup, on, off.  this is the result of all of this folder and was copied to the main project folder
