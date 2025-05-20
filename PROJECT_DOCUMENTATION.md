# 11SE Task 2 2025 - Gravity Simulation
### By Marcel de Jong

# Sprint 1
## Requirements Definition
### Functional Requirements

#### Graphics

* Circles in a window at positions representing the objects.
* Coloured Circles 

#### Physics

* Gravity

#### Simulated Space

* Toroidal space 

#### Optimisation

* N/A

#### User Interface <Sprint 1 priority>

* Right-click to open a terminal on the cursor’s position
* Reopen terminal in new position on right-click
* Typable inputs
* Implement terminal potence

### Non-Functional Requirements

* Statically Compiled

## Determining Specifications
### Functional Specifications

#### User Requirements

* The user needs to be able to spawn objects in the programme.
* The user will be able to specify information about the object prior to spawning it via a terminal menu opened by left-clicking at a position on the window.
* The menu will include x and y velocities of the object, it's size, mass and type.

#### Inputs & Outputs
* Left-click mouse input.
* Terminal textual input.

* Circles on window in motion display output.

#### Core Features
* Objects move around in accordance with their gravitational mass following the gravitational equations.
* Objects be displayed on a resizable window and will not be stretched by window resizings
* User can insert their own objects.

#### User Interaction
* Simple CLI opened at an appropriate size and location with clear instructions printed out on how to operate the programme.

#### Error Handling
* Potential division by zero if two objects occupied the exact same position. This is because gravitational attraction is $`G\frac{m_1+m_2}{d^2}`$ where d is distance. If they occupy the same spot then distance will be zero hence the division by zero. It is however an extremely unlikely edge case as each coordinate is stored as a double and generally objects travel several orders of magnitude higher distances per step than $`2^{-52}`$.
* This would be handled by simply returning a gravitational attraction of zero if the programme detects a distance of 0.

### Non-Functional Specifications
* Graphics are generated utilising openGL.
* Circles are generated as a regular polygon with a large number of sides.
* User interaction via CLI utilises the windows API via windows.h.
* Gravity is calculated as $`G\frac{m_1+m_2}{d^2}`$.
* Distance is calculated as $`d=\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}`$.
* Classes and functions are almost all defined in seperate header files for code readability and hygiene.
* Positions are stored as doubles which allows for high-precision calculations.

### Use Case
[image](https://github.com/user-attachments/assets/0f931a1e-c35a-4d6d-8fa2-5bf75922ac1c)

## Design
>User runs the programme as an executable (.exe).

>Programme starts with objects already present as a window of dimensions 2048x1024.

>User right clicks on a location on the window

>CLI for user interaction opens

>CLI displays "Enter object mass:".

>User inputs a floating point number.

>CLI displays "Enter object x position:".

>User inputs a floating point number or presses enter to skip.

>CLI displays "Enter object y position:".

>User inputs a floating point number or presses enter to skip.

>CLI displays "Enter object x motion:".

>User inputs a floating point number or presses enter to skip.

>CLI displays "Enter object y motion:".

>User inputs a floating point number or presses enter to skip.

>Object with the specified mass spawns at position specified at motion speicified, if the latter two fields were skipped then it spawns at the position the cursor was when the CLI was opened with no motion.

>User closes the programme by clicking the close window button at the top right of the window border.

## Build and Test
* The code is split into many files and cannot be represented as a single block.
* To compile it, run `cmake --build .` in the root directory of the project. The code will compile into the Debug folder.
  **Note**: This *requires* cmake to be installed. (cmake is the compiler).

## Review
**Sprint 1 - End of Sprint Review Questions**
### 1. Does it meet the requirements planned?
The programme mostly meets the requirements with some niche aspects not implemented (such as the CLI killing itself).

### 2. Does the programme perform properly?
Currently there is a bug where it is impossible to textually specify the x-coordinate of an spawned object because the CLI automagically skips it.
Otherwise, all input is handled properly!
It runs well`*` on my laptop (GTX 1060, Core i5-8350U, 16GB DDR4, Windows 11) with as many as 100 objects.
*But* due to the $`O(n^2)`$ time complexity when 256 objects were tested the framerate was in the single digits.

`*`*>=60fps*

### 3. How readable, structured and maintainable is the code?
The code is very readable with numerous comments detailing its functions.
It is structured properly with functions and classes seperated into header files.
It is maintainable because of this proper segmentation of code and reliance on a minimal amount of foreign modules.

### 4. What are some improvements for sprint 2?
Fix the CLI bug, have the CLI close itself and properly work the inheritence of the classes.


# Sprint 2

## Requirements Definition
### Functional Requirements

#### Graphics

* Projection lines / trails

#### Physics

* Collision
* Elasticity
* Orbits

#### Simulated Space

* Movable camera <not a priority>

#### Optimisation


#### User Interface

* Click and drag objects
* Objects retain cursor’s momentum after being dropped
* Remember previous inputs




### Non-Functional Requirements
*

## Determining Specifications
### Functional Specifications
*

### Non-Functional Specifications
*

### Use Case
Add diagramme here

## Design
Add Storyboard and data flow here

## Build and Test
Add first build code block here

## Review
**Sprint 2 - End of Sprint Review Questions**








# Sprint 3
## Requirements Definition
### Functional Requirements

#### Graphics

* Glow <difficult>

#### Physics


* Path Traced collisions
* Network collision optimisation <My own idea>
* Orbits

#### Simulated Space

* Movable camera <not a priority>

#### Optimisation

* Multithreading <difficult>

#### User Interface

* 




### Non-Functional Requirements
*

## Determining Specifications
### Functional Specifications
*

### Non-Functional Specifications
*

### Use Case
Add diagramme here

## Design
Add Storyboard and data flow here

## Build and Test
Add first build code block here

## Review
**Sprint 3 - End of Sprint Review Questions**
