graph TD
    %% POWER SECTION
    subgraph "1. Power Input & Protection"
        USB[1. USB-C Breakout] -->|5V Wire| F[2. 3A Glass Fuse]
        USB -->|GND Wire| GND[BLACK GND BUS]
        F -->|5V Wire| VCC[RED 5V BUS]
        
        CAP[3. 1000uF Capacitor] ---|Long Leg| VCC
        CAP ---|Short Leg / Stripe| GND
    end

    %% BRAINS & SENSORS
    subgraph "2. Brains & Data (Custom Protoboard)"
        N[5. NanoC6] -->|Red| VCC
        N -->|Black| GND
        N -->|Yellow| Y[YELLOW DATA BUS]
        N -->|White| W[WHITE DATA BUS]

        S[7. Ultrasonic Sensor] -->|Red| VCC
        S -->|Black| GND
        S -->|Yellow| Y
        S -->|White| W
    end

    %% PORT EXPANDER & M5 PUMPS
    subgraph "3. Watering Units"
        H[6. PbHub Main Input] -->|Red| VCC
        H -->|Black| GND
        H -->|Yellow| Y
        H -->|White| W

        P1[9. M5 Watering Unit 1] ===|Standard 4-Wire Cable| H
        P2[9. M5 Watering Unit 2] ===|Standard 4-Wire Cable| H
        P3[9. M5 Watering Unit 3] ===|Standard 4-Wire Cable| H
        P4[9. M5 Watering Unit 4] ===|Standard 4-Wire Cable| H
    end

    %% OPTIONAL ZONE
    subgraph "4. OPTIONAL UPGRADE ZONE (For 3rd Party Pumps)"
        VCC -->|Red| T1[8. Screw Terminal 1]
        GND -->|Black| T1
        D1[10. Diode] ---|Stripe to 5V| T1

        VCC -->|Red| T2[8. Screw Terminal 2]
        GND -->|Black| T2
        D2[10. Diode] ---|Stripe to 5V| T2
        
        VCC -->|Red| T3[8. Screw Terminal 3]
        GND -->|Black| T3
        D3[10. Diode] ---|Stripe to 5V| T3
        
        VCC -->|Red| T4[8. Screw Terminal 4]
        GND -->|Black| T4
        D4[10. Diode] ---|Stripe to 5V| T4
    end