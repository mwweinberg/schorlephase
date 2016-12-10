led_sequence_neopixel just turns the neopixel on a static color

led_sequence_neopixel_fade fades out the neopixel over the course of the countdown. It only uses one value (it goes from 255,0,0 to 0,0,0 by decreasing r in response to the counter state).

led_sequence_neopixel_face_two_color fades to a second color by manipulating both the r and the g in response to the counter state
