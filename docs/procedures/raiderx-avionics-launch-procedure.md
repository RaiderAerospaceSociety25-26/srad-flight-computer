# RaiderX Avionics: Integrated Launch Procedure



**Subsystem:** Avionics  

**Rocket:** RaiderX  

**Date:** 2025-10-08



---



## Required materials and tools:



### Hardware

- PerfectFlite Stratologger altimeter  

- MissileWorks RRC3 altimeter  

- Eggtimer Quasar altimeter  

- Featherweight GPS module & Base-Station Tracer  

- Three 9 V batteries  

- Removable arming pin sets  

- Wiring harness & terminal blocks  

- Avionics sled & mounting hardware  

- Screwdrivers, hex keys & zip ties  

- Electrical tape, Loctite & strain reliefs



### Test equipment/PPE:

- Multimeter  

- Ground-station laptop with Featherweight Tracker software  

- Telemetry receiver antenna  

- Safety glasses and gloves



---



## Avionics assembly & integration:



### Preparation

1. Verify a clean, static-free workspace.  

2. Confirm all avionics components are labeled and logged.  

3. Inspect wiring harnesses for damage or frays.  

4. Record initial battery voltages (≥ 9.0 V).



### Mounting components

5. Mount Stratologger, RRC3, and Quasar on sleds with insulated standoffs.  

6. Ensure no components overlap or contact conductive surfaces.  

7. Route wiring through sled channels and secure with zip ties.  

8. Verify altimeter vent holes are unobstructed.



### Power and continuity

9. Connect independent 9 V batteries to each altimeter.  

10. Check voltage at terminals to confirm proper supply.  

11. Perform continuity checks on each e-match circuit.  

12. Label pyro outputs: **Drogue Primary**, **Drogue Backup**, **Main Primary**, **Main Backup**.



---



## Bench verification tests:



### Power-up and self-check

1. Insert arming pins to set all altimeters to **SAFE**.  

2. One at a time, remove arming pins; confirm audible beep and LED status.  

3. Verify Stratologger and RRC3 show **ready**; Quasar Wi-Fi available.  

4. Reinsert arming pins to return systems to **SAFE**.



### Pressure simulation test

- Power systems **ON** using arming pins.  

- Simulate apogee pressure drop; confirm drogue channel activation indicator.  

- Return pressure to ambient; confirm main channel activation.  

- Record activation timing; verify redundant altimeters trigger within **≤ 2–3s** of each other.



### Telemetry test

- Power Featherweight GPS module.  

- Verify Base-Station Tracer link established with laptop.  

- Confirm live coordinates, altitude, and RSSI in Featherweight Tracker.  

- Record data samples to verify logging.



---



## Carriage installation:



1. Confirm recovery and engine bulkheads are secured on threaded rods.  

2. Slide avionics sled into carriage along alignment rails.  

3. Ensure wiring is free from pinch points or tension.  

4. Connect e-match harnesses through bulkhead terminals.  

5. Verify wiring order matches schematic; primary/backup channels correctly assigned.  

6. Secure sled with standoffs and lock nuts.  

7. Inspect carriage for loose components or unsecured wires.  

8. Close housing; confirm arming-pin access holes align with airframe openings.



---



## Pad operations:



### T-60 min: Setup

1. Retrieve carriage from prep table; install in vehicle.  

2. Verify mechanical connections to recovery and engine bulkheads.  

3. Confirm all arming pins are inserted.



### T-45 min: Ground-station activation

4. Set up Featherweight Tracker software and antenna.  

5. Confirm GPS lock from Featherweight module.  

6. Verify telemetry stream on ground-station display.



### T-30 min: Pre-arming checks

7. Perform continuity test on all pyro channels.  

8. Confirm altimeter voltages remain **≥ 9.0 V**.  

9. Check arming-pin orientation for easy removal.



### T-15 min: Avionics arming

10. Remove arming pins in order: **Stratologger-RRC3-Quasar**.  

11. Confirm audible beeps from each unit indicating Armed.  

12. Ground station confirms live telemetry and GPS fix.  

13. Notify Range Safety that avionics are armed and transmitting.



### T-10 min: Final verification

14. Verify no faults or low-battery warnings.  

15. Confirm all pyro channels show continuity/armed state.  

16. Log arming time and operator initials.



### T-0: Launch

17. Confirm telemetry active and nominal.  

18. Ignition controller fires the motor on command.



---



## Post-flight procedure:



1. Await RS clearance before approaching rocket.  

2. Confirm no smoke, beeps, or armed indicators.  

3. Insert all arming pins to safe.  

4. Disconnect all batteries; verify 0 V at terminals.  

5. Retrieve avionics carriage; inspect for damage.  

6. Download data from Stratologger, RRC3, and Quasar.  

7. Save telemetry logs from Featherweight Tracker.  

8. Record anomalies, deployment timing, and GPS data.  

9. Store components in labeled containers for reuse or analysis.



---



