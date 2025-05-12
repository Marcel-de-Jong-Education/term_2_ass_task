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
* Potential division by zero if two objects occupied the exact same position. This is because gravitational attraction is $`G\frac{m_1+m_2}{d^2}`$ where d is distance. If they occupy the same spot then distance will be zero hence the division by zero. It is however an extremely unlikely edge case as each coordinate is stored as a double and generally objects travel several orders of magnitude higher distances per step than $`2^-63`$.
* This would be handled by simply returning a gravitational attraction of zero if the programme detects a distance of 0.

### Non-Functional Specifications
* 

### Use Case
Add diagramme here

## Design
Add Storyboard and data flow here

## Build and Test
Add first build code block here

## Review
**Sprint 1 - End of Sprint Review Questions**




# Sprint 2

## Requirements Definition
### Functional Requirements

#### Graphics

* Projection lines / trails
* Glow <difficult>

#### Physics

* Collision
* Path Traced collisions
* Network collision optimisation <My own idea>
* Orbits
* Destructible objects 
* Objects explode into smaller ones on impact <difficult>

#### Simulated Space

* Movable camera <not a priority>

#### Optimisation

* Multithreading <difficult>

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
