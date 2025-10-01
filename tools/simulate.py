"""RocketPy simulation configured from RaiderX_v1.8(boysRanch).ork.

The numbers below were extracted from the OpenRocket design included next to
this script. Update the placeholders (drag model, thrust curve, etc.) if the
rocket design changes.
"""
from math import pi

from rocketpy import Environment, Flight, Rocket, SolidMotor

# Launch site: Boys Ranch near Amarillo, TX
LAUNCH_LATITUDE = 35.5
LAUNCH_LONGITUDE = -102.3
LAUNCH_ELEVATION_M = 971.1  # m MSL from the OpenRocket setup
LAUNCH_DATETIME_UTC = (2025, 10, 12, 18)  # YYYY, MM, DD, HH (UTC)

# Simple approximation of the SRProp M1260 thrust curve exported from the
# OpenRocket "Boys Ranch" simulation (time in seconds, thrust in newtons).
THRUST_CURVE = [
    (0.0, 0.0),
    (0.05, 1079.788),
    (0.1, 1088.74),
    (0.15, 1097.568),
    (0.2, 1106.256),
    (0.25, 1114.817),
    (0.3, 1123.25),
    (0.35, 1131.537),
    (0.4, 1139.693),
    (0.45, 1147.717),
    (0.6, 1170.926),
    (0.75, 1192.838),
    (0.9, 1213.417),
    (1.05, 1232.629),
    (1.2, 1250.441),
    (1.35, 1266.824),
    (1.5, 1281.753),
    (1.65, 1295.201),
    (1.8, 1307.148),
    (1.95, 1317.574),
    (2.1, 1326.462),
    (2.25, 1333.799),
    (2.4, 1339.572),
    (2.55, 1343.772),
    (2.7, 1346.392),
    (2.85, 1347.429),
    (3.0, 1346.88),
    (3.15, 1344.745),
    (3.3, 1341.029),
    (3.45, 1335.738),
    (3.6, 1328.878),
    (3.75, 1320.462),
    (3.9, 1310.502),
    (4.05, 1299.015),
    (4.2, 1286.018),
    (4.35, 1271.533),
    (4.5, 1255.583),
    (4.53, 0.0),
]

# Motor data derived from the OpenRocket stack and basic geometry estimates.
MOTOR_DRY_MASS = 2.871  # kg, mass after burnout
PROP_MASS = 3.019  # kg, difference between liftoff and burnout motor mass
MOTOR_DRY_INERTIA = (0.0697, 0.0697, 0.0034)  # kg*m^2, solid cylinder approx
GRAIN_COUNT = 3
GRAIN_OUTER_RADIUS = 0.04  # m
GRAIN_INNER_RADIUS = 0.01  # m
GRAIN_LENGTH = 0.12  # m
GRAIN_DENSITY = PROP_MASS / (GRAIN_COUNT * pi * (GRAIN_OUTER_RADIUS**2 - GRAIN_INNER_RADIUS**2) * GRAIN_LENGTH)
GRAIN_SEPARATION = 0.005  # m
MOTOR_CG_FROM_NOZZLE = 0.267  # m, motor COM measured from nozzle plane
NOZZLE_RADIUS = 0.02  # m
THROAT_RADIUS = 0.011  # m
BURN_TIME = 4.53  # s

# Rocket geometry (tail at 0 m, nose tip near 2.5 m).
ROCKET_RADIUS = 0.051054  # m, 4 in airframe
ROCKET_LENGTH = 2.5  # m, nose tip position from tail
ROCKET_DRY_MASS = 10.984  # kg, rocket without motor (structure + payload)
ROCKET_DRY_INERTIA = (5.72, 5.72, 0.015)  # kg*m^2, uniform-cylinder estimate
ROCKET_DRY_CG_FROM_TAIL = 0.998  # m

FIN_ROOT_CHORD = 0.3334  # m
FIN_TIP_CHORD = 0.0510  # m
FIN_SPAN = 0.1270  # m
FIN_ROOT_LEADING_EDGE_FROM_TAIL = 0.38  # m (approximate placement)

# Parachute parameters translated from OpenRocket
REEFED_CD = 1.2
REEFED_DIAMETER = 1.2192  # m
REEFED_CD_S = REEFED_CD * pi * (REEFED_DIAMETER / 2) ** 2
MAIN_CD = 1.5
MAIN_DIAMETER = 2.7432  # m
MAIN_CD_S = MAIN_CD * pi * (MAIN_DIAMETER / 2) ** 2


def build_environment() -> Environment:
    env = Environment(
        latitude=LAUNCH_LATITUDE,
        longitude=LAUNCH_LONGITUDE,
        elevation=LAUNCH_ELEVATION_M,
    )
    env.set_date(LAUNCH_DATETIME_UTC)
    try:
        env.set_atmospheric_model(type="Forecast", file="GFS")
    except Exception as exc:  # pragma: no cover - depends on network availability
        print(f"Warning: could not download forecast data ({exc}). Using ISA instead.")
        env.set_atmospheric_model(type="standard_atmosphere")
    return env


def build_motor() -> SolidMotor:
    return SolidMotor(
        thrust_source=THRUST_CURVE,
        dry_mass=MOTOR_DRY_MASS,
        dry_inertia=MOTOR_DRY_INERTIA,
        nozzle_radius=NOZZLE_RADIUS,
        grain_number=GRAIN_COUNT,
        grain_density=GRAIN_DENSITY,
        grain_outer_radius=GRAIN_OUTER_RADIUS,
        grain_initial_inner_radius=GRAIN_INNER_RADIUS,
        grain_initial_height=GRAIN_LENGTH,
        grain_separation=GRAIN_SEPARATION,
        grains_center_of_mass_position=MOTOR_CG_FROM_NOZZLE,
        center_of_dry_mass_position=MOTOR_CG_FROM_NOZZLE,
        nozzle_position=0.0,
        burn_time=BURN_TIME,
        throat_radius=THROAT_RADIUS,
    )


def build_rocket(motor: SolidMotor) -> Rocket:
    rocket = Rocket(
        radius=ROCKET_RADIUS,
        mass=ROCKET_DRY_MASS,
        inertia=ROCKET_DRY_INERTIA,
        power_off_drag=0.6,  # TODO: replace with measured Cd vs Mach curve
        power_on_drag=0.5,  # TODO: replace with measured Cd vs Mach curve under thrust
        center_of_mass_without_motor=ROCKET_DRY_CG_FROM_TAIL,
        coordinate_system_orientation="tail_to_nose",
    )

    rocket.add_motor(motor=motor, position=0.0)

    rocket.add_nose(
        length=0.4953,
        kind="ogive",
        position=ROCKET_LENGTH,
        name="Fiberglass Nose",
    )

    rocket.add_trapezoidal_fins(
        n=3,
        root_chord=FIN_ROOT_CHORD,
        tip_chord=FIN_TIP_CHORD,
        span=FIN_SPAN,
        position=FIN_ROOT_LEADING_EDGE_FROM_TAIL,
        cant_angle=0.0,
        name="Aluminum Fins",
    )

    rocket.add_parachute(
        name="reefed",
        cd_s=REEFED_CD_S,
        trigger="apogee",
        sampling_rate=105,
        lag=1.5,
        noise=(0, 8.3, 0.5),
    )

    rocket.add_parachute(
        name="main",
        cd_s=MAIN_CD_S,
        trigger=305.0,  # m AGL, 1000 ft deployment target
        sampling_rate=105,
        lag=1.5,
        noise=(0, 8.3, 0.5),
    )

    return rocket


def run():
    env = build_environment()
    motor = build_motor()
    rocket = build_rocket(motor)

    flight = Flight(
        rocket=rocket,
        environment=env,
        rail_length=5.1816,
        inclination=84.0,  # 6 deg tilt from vertical
        heading=90.0,  # east
        max_time=600,
    )

    flight.info()
    flight.all_info()
    flight.export_data(
        "boys_ranch_flight.csv",
        "z",
        "mach_number",
        "angle_of_attack",
    )
    flight.plots.trajectory_3d(filename="boys_ranch_trajectory.png")


if __name__ == "__main__":
    run()
