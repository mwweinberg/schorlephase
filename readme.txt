Everything works now.  There appear to be two wiring issues.  First, the stepper works intermitently becuase of a loose wire.  You can tell that  not all wires are connected properly because the stepper will grind instead of turn.  Second, something is wrong with the power to the neopixel.  This causes it to be a very dim blue when it is supposed to be on.  The wiring worked when it was on its own breadboard.  
_may2019 is the fully functional code for the upgraded servo.  The fritzing diagram is correct as of June 2019.

/background - attempt to figure out how to make the switch and seqencing work. can probably now be ignored

led_sequence - template for controlling three phases with the switch

led_sequence_servo - code to integrate the servo on shutdown

led_sequence_stepper - code to spin the stepper at startup and shutdown

led_sequence_neopixel_fade_two_color - code to turn on neopixel and manipulate it during the on phase

led_sequence_sound - code to make the piezo beep during startup

led_sequence_combined - all of the elements combined into one

led_sequence_combined_momentary - rewriting the led sequence for a momentary switch instead of a toggle. This also removes the servo.
