# Altus Metrum Altimeters & Trackers - Research 

Author: Leonardo Herrera -- 2025-09-30

> Labels: TeleMega (flight computer), TeleBT (ground receiver), TeleMetrum (simpler/lighter flight computer), EasyMotor (flight support/ignition controller).  
> Deliverables: datasheets/specs (power, data rates, logging method, phone connection), pictures, and examples from member L1-L3 flights.

---

# Abstract:

### TeleMega

TeleMega is a high end dual-deploy flight computer with integrated GPS, IMU, barometer, and radio telemetry. It enables live tracking, records full flight logs, and provides multiple pyro channels for parachute deployment and staging.

### TeleBT

TeleBT is a portable ground station used to receive telemetry from TeleMega. It connects to laptops or phones via USB or Bluetooth, letting the team monitor live altitude, velocity, voltages, and GPS during flight.

### TeleMetrum (Backup Flight Computer)

TeleMetrum is a smaller altimeter with dual-deploy and integrated telemetry, designed for tight airframes. It offers fewer pyro channels than TeleMega but is ideal for lighter rockets or as a backup altimeter.

### EasyMotor (Ignition Controller)

EasyMotor is triggered by a flight computer like TeleMega/Metrum through an AUX output and is designed to deliver higher currents needed for motor igniters. EasyMotor can reliably light motors without causing droppage in voltage or resets. It is recommended for rockets needing staging ignition, and is safer and more dependable.

---

# Background:

### TeleMega

Complex flights may require GPS tracking, seperate deployment, and extra pyro channels for staging. TeleMega combines these in a single unit, simplifying integration while keeping flexibility.

### TeleBT

Telemetry is only useful if its reliably received. TeleBT bridges the rockets Radio Frequency link to whichever device we connect-by USB or Bluetooth-, giving us faster recovery along with live situational awareness and safety checks.

### TeleMetrum (Backup Flight Computer)

If TeleMegas channel count is overkill, TeleMetrum is a simpler version. TeleMetrum provides, dual-deploy, barosensor, radio telemetry in a compact board that fits smaller couplers and simplifies wiring. ( Typicaly used in certificate rockets, in our case would be a valuable backup if TeleMega fails )

### EasyMotor (Ignition Controller)

Air-starts and clustered ignition increase risk. A dedicated ignition controller like EasyMotor provides current capacity and safety sequencing beyond standard chute deployment channels.

---

# Methods:

### TeleMega

- Reviewed official documentation ( product page, system manual, schematics ).
- Compiled spec table ( power, channels, dimensions, telemetry behavio ).
- Summarized telemetry packet structure and typical update rates.
- Planned board handling for photos and wiring layout.
- Gathered member anecdotes on deployment settings and telemetry performance.

#### Links

- Product Page: https://altusmetrum.org/TeleMega/
- Telemetry Packet ( Behavior ): https://altusmetrum.org/AltOS/doc/telemetry.pdf
- Schematic?: https://altusmetrum.org/TeleMega/v4.0/telemega-sch.pdf

### TeleBT

- Reviewed docs for USB/Blueth behavior and radio parameters.
- Compiled connectivity and data-rate specs.
- Planned on pairing test with TeleMega at field sessions.

#### Links

- Product Page: https://altusmetrum.org/TeleBT/
- Schematic: https://altusmetrum.org/TeleBT/v4.0/telebt-sch.pdf

### TeleMetrum (Backup Flight Computer)

- Compared feature set vs. TeleMega ( channels, size, power ).
- Collected outline drawings and wiring references.
- Identified use cases where lighter altimeters are advantageous.

#### Links

- Product Page: https://altusmetrum.org/TeleMetrum/

### EasyMotor (Ignition Controller)

- Reviewed ignition current capability and safety interlocks.
- Mapped integration with TeleMega pyro/aux outputs.
- Outlined use cases for clustered or staged flights.

#### Links

- Product Page: https://altusmetrum.org/EasyMotor/

---

# Results:

### TeleMega-Key Specs

| Category        | Value / Notes                                                                 |
|-----------------|-------------------------------------------------------------------------------|
| Power (logic)   | 3.7 V LiPo (single-cell)                                                      |
| Pyro supply     | 3.7-12 V (shared with logic or separate pyro battery supported)               |
| Pyro channels   | Dual-deploy (Apogee, Main) + multiple AUX channels (for staging/aux events)   |
| Sensors         | Barometric altimeter, 3-axis accel, 3-axis gyro, 3-axis mag, GPS              |
| Logging         | On-board non-volatile flash; logs downloadable via USB                        |
| Telemetry       | 70 cm ham band; narrowband FSK; typical net ~38.4 kbps with packet framing    |
| PC/Phone        | USB serial to AltosUI (PC); Bluetooth/USB via ground station to AltosDroid    |
| Form factor     | ~1.25 in x 3.25 in PCB; hole pattern ~1.0 in x 3.0 in; fits 38 mm couplers    |

Summary: The specs show why TeleMega is considered a full featured flight computer. It combines altimeter functions with GPS, IMU, and multiple pyro channels    ( unlike TeleMetrum's 2 ), making it capable of dual-deploy and staging events. The 3.7-12 V pyro supply option allows flexibility for igniter firing, while the onboard logging and telemetry ensure real time monitoring and detailed post flight analysis. Its size fits standard 38 mm couplers, which makes it optimal for mid/high power rockets.

### TeleBT-Key Specs

| Category     | Value / Notes                                                        |
|--------------|--------------------------------------------------------------------- |
| Role         | Ground receiver / gateway for Altus Metrum telemetry                 |
| Power        | On-board LiPo (850 mAh) and USB charging                            |
| Interfaces   | USB (data/power), Bluetooth LE to phone/tablet, RF antenna (SMA/whip)|
| Data rate    | Matches flight computer (38.4 kbps GFSK with FEC typical)           |
| Apps         | AltosUI (Windows/Linux), AltosDroid (Android)                        |

Summary: TeleBTs specs highlight its role as the bridge between the rocket and the ground crew. With both USB and Bluetooth connection, it can link to laptops for stable for portable tracking/logging. The fact that its Radio Frequency (RF) data rate matches the flight computer guarantees reliable telemetry reception, while its onboard LiPo battery makes it fully portable for field operations. Overall, TeleBT allows live flight monitoring and quick recovery coordination.

### TeleMetrum (Backup Flight Computer)-Key Specs

| Category     | Value / Notes                                       |
|--------------|-----------------------------------------------------|
| Role         | Compact altimeter + telemetry                       |
| Power        | 3.7 V LiPo                                          |
| Channels     | 2 (Apogee, Main)                                    |
| Sensors      | Baro; some revisions include/accept GPS             |
| Logging      | On-board flash                                      |
| Form factor  | Fits typical 38 mm couplers; smaller than TeleMega  |

Summary: The TeleMetrum specs confirm its compact and simplified build. It only has two pyro channels, it is designed mainly for dual-deploy recovery, which makes it ideal for certification flights or as a backup in more complex rockets. Its onboard flash memory provides reliable flight logging, and the optional GPS support expands its utility. The small form factor means it can fit where larger boards like TeleMega would be excessive, offering a good balance of simplicity and functionality. **Valuable Backup Flight Computer**

### EasyMotor (Ignition Controller)-Key Specs

| Category        | Value / Notes                                                       |
|-----------------|-------------------------------------------------------------------- |
| Role            | Motor cluster/staging ignition controller                           |
| Ignition current| High-current per channel (10 A-class capability; check variant)    |
| Channels        | Multiple igniter outputs for boosters/stages                        |
| Interlocks      | Arming/inhibit logic; continuity checks recommended                 |
| Wiring          | Triggered by TeleMega/TeleMetrum AUX/pyro outputs                   |

Summary: EasyMotors specs define its role as a dedicated ignition controller rather than an altimeter. Its high current output is specifically intended for motor igniters, making it suitable for staged rockets where TeleMegas channels would fall short. The systems safety features and continuity checks minimize the chance of unintended ignition along with its integration with AUX outputs from TeleMega/Metrum ensures it only fires when commanded in flight. This makes EasyMotor a specialized but powerful addition for advanced flight profiles. **Potential Valuable Asset**

---

# Discussion:

### TeleMega

Robust option for complex missions: multiple pyro channels, full sensor suite, GPS, and telemetry in one. Watch antenna placement, RF licensing, and consider separate pyro battery to isolate surges from logic power.

### TeleBT

Makes telemetry practical and user friendly. USB is good for laptops, Blueth is convenient for phones. Range is antenna dependent. ( Yagi can significantly improve SNR/packet yield in long-range flights )

#### Yagi Antenna

- Extending range: Provides stronger reception of telemetry signals from rockets at high altitudes or long horizontal distances.
- Improving reliability: Reduces packet loss compared to a stock whip antenna, especially in noisy RF environments.
- Tracking: By physically pointing the Yagi toward the rocket during flight and descent, ground crews can maintain a stronger link for real-time altitude, velocity, and GPS position.

The Yagi connects to TeleBTs SMA antenna port as a replacement for the stock whip. Before launch aim the antenna in the rockets expected flight direction. During flight, the Yagi can be adjusted to stay aligned with the rockets trajectory, which maximizes signal strength and reduces packet loss.

### TeleMetrum (Backup Flight Computer)

Ideal when you only need dual-deploy and want a lighter/smaller package. Great for certifacate flights and as a backup altimeter. Two channels means less flexibility for staging or complex AUX events.

#### Redundancy & Backup Altimeters

Redundancy in high power rocketry is very recommended. A backup altimeter ensures that parachute deployment still occurs if any primary systems fail ( wiring issues, firmware errors, battery faults )

**Primary (TeleMega):** Handles telemetry, logging, dual-deploy, optional staging 
**Backup (TeleMetrum or equivalent):** Provides a simpler, independent dual-deploy system powered by its own battery  
**Charge wiring:** Apogee and main charges should be wired so either Tele can fire them  
**Practice Test:** Test both systems separately before flight, and confirm that simultaneous firing does not cause issues

**( This approach reduces the risk recovery failure )**

### EasyMotor (Ignition Controller)

Best for staged rockets. Provides reliable, high current ignition with built in safeguards preventing pre-expected ignition. Requires proper arming & sequencing aswell as thorough continuity checks.

---

# Application Towards 10k SRAD:

The 10k SRAD competition rocket wth How Altus Metrum products shoul(d/dn't) be integrated into the avionics plan.

### TeleMega-Primary Flight Computer

**Mandatory**  
- Provides full sensor kit (baro, IMU, GPS) for performance analysis.  
- Multiple pyro channels allow dual-deploy and backup charges
- Data logging is valuable for post flight reporting and competition scoring.  

### TeleBT-Ground Station

**Mandatory**  
- Critical for live monitoring of altitude, velocity, battery voltage, and GPS location.  
- Enables ability to track descent and recovery quickly after landing.  
- Advantageous in competition setting  

### TeleMetrum-Backup / Secondary Altimeter

**Coul Be Valuable For Backup**  
- Acts as a simpler backup altimeter in case TeleMega fails.  
- Provides independent dual-deploy capability, ensuring parachute events occur.  
- Fits easily in a smaller bay and reduces wiring complexity for backup systems.  

### EasyMotor-Ignition Controller

**Could Bennifet**  
- Use if the SRAD design involves staging  
- Provides higher ignition current and safer sequencing compared to using TeleMega AUX channels.  
- **If the rocket is single stage: Uneccesary**

### Integration Matrix for 10k SRAD

| Component    | Role                        | Integration Status | Notes |
|--------------|-----------------------------|--------------------|-------|
| **TeleMega** | Primary flight computer      | **Required**       | Runs dual-deploy, logging, GPS, and telemetry. Multiple pyro channels for backup/staging. |
| **TeleBT**   | Ground station receiver      | **Required**       | Needed for real time telemetry to laptop. Aids recovery and monitoring. |
| **TeleMetrum** | Backup / secondary altimeter | **Recommended**    | Provides independent dual-deploy redundancy. Improves reliability. |
| **EasyMotor** | Ignition controller (staging/clusters) | **Optional** | Would benefit if rocket uses multi stage motors. If not unnecessary. |

---

# Appendices:

### A. Wiring & Mounting Quick-References

- **TeleMega:** Screw terminals for Apogee/Main/AUX; LiPo logic supply; optional separate pyro supply; mount aligned with rocket axis; keep antenna clear of carbon fiber where possible.  
- **TeleBT:** Charge via USB; pair to phone (AltosDroid) or connect via USB (AltosUI); verify packets before arming.  
- **TeleMetrum:** 2-channel wiring similar to TeleMegas Apogee/Main; simpler harness; compact mounting.  
- **EasyMotor:** Dedicated igniter leads; hard interlocks; continuity checks; staged timing coordinated from flight computer.

### B. Checklists

- **Pre-flight:** continuity, GPS lock, telemetry link test, battery levels, arming order verified.  
- **Post-flight:** safe power-down, log download, wiring inspection, note anomalies for the repo.

---

## References ( Some Previousley Linked ):

- TeleMega product & docs: https://altusmetrum.org/TeleMega/  
- TeleMega outline (mounting): https://altusmetrum.org/AltOS/doc/telemega-outline.pdf  
- Telemetry format/rates: https://altusmetrum.org/AltOS/doc/telemetry.pdf  
- TeleBT product & schematic: https://altusmetrum.org/TeleBT/ , https://altusmetrum.org/TeleBT/v4.0/telebt-sch.pdf  
- TeleMetrum product: https://altusmetrum.org/TeleMetrum/  
- EasyMotor product: https://altusmetrum.org/EasyMotor/


