# getränke-tanke
Die Software für den Technischen teil eines Getränke-Zapfautomat's

# Wichtig
- Die Pumpensteuerung und Getränkeauswahl sind noch nicht Fertiggestellt

# Material
- Motor mit ULN2003-Controller
- Drehwinkelgeber
- Arduino

# Nachbau
1. ULN2003 pins Anschliessen:
- IN1 -> D11
- IN2 -> D10
- IN3 -> D9
- IN4 -> D8
- \+ -> 5V
- \- -> GND

2. Drehwinkelgeber anschliessen:
- GND -> GND
- \+ -> 5V
- SW -> D7
- DT -> D5
- CLK -> D6

3. Arduino mit der Software bespielen
