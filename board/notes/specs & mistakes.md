Specs:
- mosfet: needs 1ms to turn off (from 5V to 0) (no load), switches back on instantly (no load)
 - but: switches instantly off aswell once there is a load -> no ghosting
- all TLC data lines switch instantly, only very small impacts on other lines
- 5V: on last TLC 5V pin, 0.25V ripple -> 5% power ripple, great for TLC
- no ripple on GND pin

Blank (on TLC) 1µS to switch on, switches off immediately
   -> (on µ-C) 1µS to switch off, switches on immediately
   -> delay due transistor inversion
   -> options: remove/short transitor, mosfets provide enough protection
	-replace R2 with 1k

mistakes:
    - TLC blank inverter (obsulete)
    - no debounce capazitor for switches
    - log instead of linear pot
    - too big capacitors (1000µF)
    - 22pf capacitor for 20 mhz crystal seems to break it
    - no usart serial port for debugging
    - n-channel mosfet would be better
    - no readout for TLC error register (useful for debugging)
