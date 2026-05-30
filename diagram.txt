=============================================================================
                      THE "BRAIN BOX" WIRING SCHEMATIC
=============================================================================

-----------------------------------------------------------------------------
1. MAIN POWER & BUS SYSTEM (Screw Terminal Blocks)
-----------------------------------------------------------------------------
USB-C Breakout Board (5V, 3A/4A Input)
  ├─ GND ───────────────────────────────────────> [ GND BUS ] (Black Terminals)
  └─ VBUS (5V) ───> [ 3A Glass Fuse ] ──────────> [ VCC BUS ] (Red Terminals)

1000µF 16V Capacitor
  ├─ Long Leg (+) ──────────────────────────────> [ VCC BUS ] (Red Terminals)
  └─ Short Leg (-) ─────────────────────────────> [ GND BUS ] (Black Terminals)

(Data Buses have no direct power input, they just link the components below)
  ├─ [ SDA BUS ] (Yellow Terminals)
  └─ [ SCL BUS ] (White Terminals)


-----------------------------------------------------------------------------
2. THE BRAINS (M5Stack NanoC6, PbHub, Ultrasonic Sensor)
-----------------------------------------------------------------------------
M5Stack NanoC6 (Grove Cable cut in half)
  ├─ Red Wire ──────────────────────────────────> [ VCC BUS ]
  ├─ Black Wire ────────────────────────────────> [ GND BUS ]
  ├─ Yellow Wire ───────────────────────────────> [ SDA BUS ]
  └─ White Wire ────────────────────────────────> [ SCL BUS ]

M5Stack PbHub v1.1 - Main Input Cable (Grove Cable cut in half)
  ├─ Red Wire ──────────────────────────────────> [ VCC BUS ]
  ├─ Black Wire ────────────────────────────────> [ GND BUS ]
  ├─ Yellow Wire ───────────────────────────────> [ SDA BUS ]
  └─ White Wire ────────────────────────────────> [ SCL BUS ]

M5Stack Ultrasonic Sensor (Grove Cable cut in half)
  ├─ Red Wire ──────────────────────────────────> [ VCC BUS ]
  ├─ Black Wire ────────────────────────────────> [ GND BUS ]
  ├─ Yellow Wire ───────────────────────────────> [ SDA BUS ]
  └─ White Wire ────────────────────────────────> [ SCL BUS ]


-----------------------------------------------------------------------------
3. THE WATERING UNITS
-----------------------------------------------------------------------------
These plug directly into the PbHub using their standard, uncut Grove cables.

M5Stack PbHub (v1.1) - Output Ports
  ├─ Port 1 ════> M5Stack Watering Unit 1
  ├─ Port 2 ════> M5Stack Watering Unit 2
  ├─ Port 3 ════> M5Stack Watering Unit 3
  └─ Port 4 ════> M5Stack Watering Unit 4


-----------------------------------------------------------------------------
4. OPTIONAL ZONE (For 3rd-Party Bare DC Pumps)
-----------------------------------------------------------------------------
Four 5mm Pitch PCB Screw Terminals. Keep this section physically separate.

Terminal 1
  ├─ Left Pin ───────────────> [ VCC BUS ]
  ├─ Right Pin ──────────────> [ GND BUS ]
  └─ 1N4001 Diode ───────────> Clamp Silver Stripe to Left Pin (VCC), 
                               other end to Right Pin (GND)

Terminal 2
  ├─ Left Pin ───────────────> [ VCC BUS ]
  ├─ Right Pin ──────────────> [ GND BUS ]
  └─ 1N4001 Diode ───────────> Clamp Silver Stripe to Left Pin (VCC), 
                               other end to Right Pin (GND)

Terminal 3
  ├─ Left Pin ───────────────> [ VCC BUS ]
  ├─ Right Pin ──────────────> [ GND BUS ]
  └─ 1N4001 Diode ───────────> Clamp Silver Stripe to Left Pin (VCC), 
                               other end to Right Pin (GND)

Terminal 4
  ├─ Left Pin ───────────────> [ VCC BUS ]
  ├─ Right Pin ──────────────> [ GND BUS ]
  └─ 1N4001 Diode ───────────> Clamp Silver Stripe to Left Pin (VCC), 
                               other end to Right Pin (GND)
=============================================================================
