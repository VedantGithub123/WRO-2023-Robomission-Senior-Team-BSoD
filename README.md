# Project Overview

The goal of this project is to develop an Autonomous Block Collection and Sorting Robot to compete in the World Robot Olympiad Robomission Senior catergory (Competition rules here: <https://wro-association.org/wp-content/uploads/WRO-2023-RoboMission-Senior.pdf>). Our robot uses a grab-and-lift arm to collect blocks and store them in the robot. It uses an indexer to place the blocks in the target positions, which is geared to an mechanism to grab a ship. When both mechanisms are active, a rear arm deploys to grab the other ship.

## Getting Started

Robot is built with EV3 LEGO Mindstorms and a HiTechnic Color Sensor. The build instructions can be found in `build`. They contains the required pieces

Install ROBOTC for LEGO MINDSTORMS at: <https://www.robotc.net/>. Set up RobotC onto the EV3 Hub by downloading the firmware through the RobotC software.

Ensure Git is installed and setup to work with he repository

Clone the project repository to your local machine and navigate into the directory:
```
git clone https://github.com/VedantGithub123/WRO-2023-Robomission-Senior-Team-BSoD.git
cd WRO-2023-Robomission-Senior-Team-BSoD
```

## Repository Structure

The `main` branch is the organized working branch. Below is an overview of the folder structure for the `main` branch of this repository
```
WRO-2023-Robomission-Senior-Team-BSoD/
├── build/
├── media/
├── src/
│   ├── headers/
│   ├── scripts/
│   └── zones/
│   └── run.c
└── README.md
```

### Folder Descriptions

`build/`: Contains files relating to the physical construction of the robot

&emsp;&emsp;`design.io`: CAD of the robot, can be opened in Studio 2.0

`media/`: Contains videos, photos, and renders of the robot

`src/`: Contains all source code

&emsp;&emsp;`headers`: Header files used for the HiTechnic Color Sensor

&emsp;&emsp;`scripts`: Scripts containing functions references in the executable program

&emsp;&emsp;`zones`: Files containing subsections of the executable

&emsp;&emsp;`run.c`: Executable program, must be downloaded to the EV3 hub using RobotC

`README.md`: Project repository documentation

## Major Scripts

The most important functions are found in `src/scripts/movement_functions.c`

### `movePID`
A function to move the robot for a set distance, measured in motor degrees.
- Stopping condition: Each motor must be within 5 degrees of its target or 5 seconds must have passed
- Speed calculation: Each motors speed is calculated independently. The default motor speed is based on a PD algorithm, this also ensures the robot moves in the correct direction. This is limited so that its magnitude can't exceed the maximum allowed speed. It is again limited so that its magnitude can't exceed the ramp-up speed, which is proportional to the time elapsed, allowing for smooth acceleration. Then a minimum magnitude is applied, which acts instead of the integral term to prevent stall.

### `lfPID`
A function to follow the edge of a line.
- Stopping condition: Depends on the `state` parameter. 1 for time, 2 for until a sensor measures a reflective value greater than the threshold, 3 for until a sensor measures a reflective value less than the threshold, 4 for a set distance
- Speed calculation: To calculate how much the robot must turn, we apply a PID onto the difference between the sensor reflection and target value. The result is added to the speed for one motor and subtracted from the other.

### `lsPID`
A function to alight the robot perpendicular to a line
- Stopping condition: Until a certain time as passed
- Speed calculation: Each motors speed is calculated independently. It as set as the result of a PD onto the difference between the sensor reflection on the same side as the motor and target value.

## Robot Design Process

### Capability Evaluation
We started by discussing the capabilties we wanted for the robot. The robot needs to drive forward and turn quickly. It must be able to sense colors on the mat. It must be able to sense blocks beside it. It must be able to collect blocks and store them in the robot. Ideally, the robot should be able to pick up the block without moving after it senses its color. It must be able to drop the blocks onto the ships in the collected order. It must be able to grab the small and large ship individually and move them across the field.

### Block Collection
Before deciding how to collect the blocks, we needed a way to store the blocks in the robot. We decided on using a slide/tray where blocks will slide to the bottom. Thus, we needed a way to grab the blocks and place them at the top of the tray. This was done using a grab-and-lift mechanism, powered by one motor. To make the collection more consistent, we made the sides of the tray taller near the grab-and-lift and added a back-plate to keep the blocks as high up as possible.

Grab-and-lift mechanism: \
<img width="400" height="300" alt="grab-and-lift" src="https://github.com/user-attachments/assets/2c18763b-bdbb-47fa-9e41-a6f02bb241f9" />


### Block Deposition
To deploy the blocks, we need something to take one block from the tray. This was done with an additional ramp that had a curve to stop blocks from sliding down. When the deposition ramp was active, the selected block slides down it, guided by walls, to consistently go on the ship.

Deposition ramp:\
<img width="400" height="300" alt="deposition-ramp" src="https://github.com/user-attachments/assets/ec9adbdd-d810-4465-b7b2-5d9ff7efed73" />


### Ship Manipulation

To manipulate the small ship, we had an arm in the front, which was able to cover and hold the ship. Due to motor limitations, we had to gear it to the block deposition since both could be operated independently. To manipulate the large ship, we had a rubber band deployed arm, similar to the one for the small ship. This could not be geared to any other mechanism since we didn't want it to interfere with the rest of the run. To solve this, we added two stoppers. One stopper went away whenever the deposition ramp was deployed. The other stopper went away whenever the grab-and-lift arm was down. Thus, when any one mechanism was deployed, one stopper remains, preventing the arm from deploying. Only when both mechanisms are deployed can the rear arm deploy. This acts as a mechanical "AND" gate.

Small ship arm:\
<img width="400" height="300" alt="small-ship-arm" src="https://github.com/user-attachments/assets/8af694d6-0911-417c-8fb4-570ef77bad58" />

Large ship arm: \
<img width="400" height="300" alt="large-ship-arm" src="https://github.com/user-attachments/assets/68e3c2c7-0ba8-4d4e-ade0-5100c4da931a" />

## Program Design Process

### Code Organization
For easy tuning and code generation, we wanted the programmer to only interact with one line functions that they can use to command the robot. For this, we needed functions that could make the robot do basic movements, such as driving, turning, line following, and line squaring. We also wanted these functions to be precise. The robot run is split up into zones, based on what the robot is doing, making it easier to debug.

### Function Capabilities

### `movePID`
This function is able to make the robot move straight and turn. By changing the kP, acceleration, motor speed, and motor distance parameters, the robot can drive most paths. For example, to drive forwards or backwards, the parameters should be the same. To turn, the motor distance should be opposite for one motor and the other. To create this function, we first thought of making the motors accurately settle on their target positions. This could be done with a PID loop. However, the integral term introduces too many complications, making it easier to add a minimum speed with similar performance, so a PD loop is used instead. Another inaccuracy in robot movement is wheel slippage, caused by high acceleration. To solve this, we added the acceleration limiter.

### `lfPID`
This function is able to make the robot follow the edge of a line. It uses a PID algorithm, as explained earlier. The integral term is not used due to the increased complexity it adds. To prevent having multiple line following functions depending on the stopping conditions, we included a `state` parameter, allowing the same function to be used in all relevant stopping conditions.

### `lsPID`
This function is able to make the robot align itself perpendicular to a line, as explained earlier. The integral term is not used due to the increased complexity it adds.


### Zone Programming
When writing the robot commands, we followed an iterative process, where commands where written one at a time and then tested. Based on the results, the distances and parameters were tweaked until it moved correctly. This was done until all zones were complete.


### Iteration for Nationals
To reduce the time for our run, we thought of ways to optimize the block collection and deposition. After collecting the blocks for the large ship on the first pass, the robot crossed the blocks to go to the ship. It then passes the blocks again to collect blocks for the small ship. This second pass was eliminated by collecting the blocks for the second ship, reducing the run time.
