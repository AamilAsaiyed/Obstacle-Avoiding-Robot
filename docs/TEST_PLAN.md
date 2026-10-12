# Validation plan — ultrasonic proximity-stop controller

**Status:** Proposed tests only. No pass/fail results or quantitative measurements are claimed.

This plan is for controlled, supervised bench testing. Before tests, record the actual Arduino board, ultrasonic sensor, motor-driver model, supply voltages, wheel diameter, robot mass and firmware revision.

## Test setup

- Test on a clear bench with the wheels safely elevated first.
- Use a ruler/tape measure and flat target at known distances.
- Verify correct motor direction and an accessible physical power-off method.
- Check driver current/voltage ratings and sensor logic-level compatibility.
- Use the Arduino Serial Monitor at 9600 baud to record readings.
- For ground tests, clear the area and supervise the robot throughout.

## Test cases

| ID | Condition | Expected behavior | Observation/result |
|---|---|---|---|
| T01 | Power-on and initialization | Motor direction pins start in stopped state | Not run |
| T02 | Target approximately 30 cm away | Forward command issued on a valid echo | Not run |
| T03 | Target approximately 10 cm away | Stop command issued | Not run |
| T04 | Valid reading just below 20 cm | Stop command issued | Not run |
| T05 | Valid reading at/above 20 cm | Forward command issued | Not run |
| T06 | No echo within configured timeout | Motors stopped; diagnostic printed | Not run |
| T07 | Target repeatedly crosses threshold | Record switching/chatter behavior | Not run |
| T08 | Multiple target angles/surfaces | Record echo reliability and errors | Not run |
| T09 | Approach at several speeds on ground | Measure actual stopping distances | Not run |

## Results table to fill after testing

| Trial | Reference distance (cm) | Serial distance (cm) | Speed / PWM | Stop outcome | Notes |
|---|---:|---:|---|---|---|
| 1 | — | — | — | Not measured | |
| 2 | — | — | — | Not measured | |
| 3 | — | — | — | Not measured | |

For repeatability, collect multiple measurements at each reference distance and report mean error and spread. For stopping distance, mark the obstacle reference and record the robot's nearest position after a stop command.

## What this test plan does NOT establish

The `20 cm` threshold is not a guaranteed minimum clearance. Mechanical inertia, motor response, loop timing, missed echoes and sensor geometry can affect outcomes. This is a student prototype, not an independent emergency-stop or personnel-safety system.

## Evidence checklist

- [ ] Actual wiring image and component part numbers
- [ ] Recorded board model, driver model and supply
- [ ] Short video of controlled bench tests
- [ ] Raw observations for T01–T09
- [ ] Summary of failure cases and proposed improvements
