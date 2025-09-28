# Altimeters and GPS Trackers from EggtimerRocketry

_Author: Emma Robins — 2025-09-25_

## Background

To effectively control the parachute's deployment and record flight data, our rocket will need an altimeter and a GPS tracker. These devices range in number of outputs and cost, necessitating decisions by Avionics leads on which parts to use. Eggtimer offers a variety of kits which require assembly after purchase, and could be a more affordable option to other altimeters and trackers our team has been considering.

---

## Results

Here, some relevant data is provided for the Eggtimer modules best suited to our rocket. The best ones to consider are listed below with reasoning.

| Device         | Cost | Functionality                       | Power Needs   | Data Rates | Data Transfer   |
| -------------- | ---- | ----------------------------------- | ------------- | ---------- | --------------- |
| Quark          | $20  | Apogee beep-out                     | 7.4V          | 20 Hz      | RF              |
| ION            | $20  | Altitude, velocity                  | 3.7V          | 20 Hz      | WiFi, USB, RF   |
| Proton         | $80  | Altitude, velocity, acceleration    | 7.4V to 11.1V | 10-33 Hz   | WiFi, USB, RF   |
| Quasar         | $100 | Altitude, velocity, GPS data        | 7.4V          | 20 Hz      | WiFi, USB, RF   |
| TX Transmitter | $70  | GPS data, real time data transfer   | 7.4V          | 1 Hz       | RF, RX Receiver |
| RX Receiver    | $35  | Real time data transfer for mapping | Laptop Plugin | N/A        | N/A             |

-   Quark -> best option for an affordable, minimum functionality unit
-   Quasar -> best option for an integrated GPS unit
-   TX -> best stand-alone GPS from Eggtimer

---

## Discussion

The altimeters EggtimerRocketry offers come with a variety of features that make finding a suitable altimeter for a given rocket relatively easy. For a low cost, our team could assemble our own Eggtimer altimeter which could send recorded data, such as altitude and velocity, over WiFi. More expensive options include accelerometers and even built-in GPS functionality.

Eggtimer offers different options for independent GPS trackers as well. Their trackers run slightly more expensive than their altimeters, and have a range of output types to aid in recovery. A separate receiver module is available to receive real-time data to a laptop and is compatible with Google Earth and MapSphere.

Many of Eggtimer’s products are compatible with most software we would use to view real-time data of our rocket’s launch, so integration with our ground station would be simple and effective. All that is required with these kits is brief experience with soldering. The affordability and functionality of the Eggtimer altimeters make them the most promising option this company offers. Once our team assembled the module we could begin programming the device to integrate with the rest of our rocket.

---

## References

-   [Eggtimer Altimeter Comparison](https://eggtimerrocketry.com/wp-content/uploads/2023/08/Eggtimer-Altimeter-Comparison-2023-08.pdf)
-   [Information from the EggtimerRocketry website](https://eggtimerrocketry.com/)
-   See [Photos of Eggtimer Devices](https://docs.google.com/presentation/d/1L-nu7nlqws_XdME6_st4IZ6oD86k9ym0qWUJJlTB7yw/edit?usp=sharing)
