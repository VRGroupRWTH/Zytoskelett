# Zytoskelett VR project

## Table of Contents

[[_TOC_]]

## Project Description

Keratin intermediate filaments are protein threads that are located inside cells of epithelial tissues such as skin and are responsible for the mechanical stability of these tissues.

This project allows you to view these filaments in a 3-Dimensional space, either in VR or on your Desktop and provides you with the tool to classify and color them to your specifications.
It was created in cooperation with Prof. Dr. rer. nat. Reinhard Windoffer from the [Institute of Molecular and Cellular Anatomy of the RWTH Aachen University Hospital][KRN] for the corresponding paper [Quantitative mapping of keratin networks in 3D][PPR].

## Installation

### Hardware requirements

- VR Headset (Recomended: HTC Vive)
- VR-ready PC


### Software requirements
- **Unreal Engine 4.22.3**
  
  You can download the Unreal Engine [here][UE4]. You need a free epic games account before you can download the Unreal Engine. Choose a creator's license, when asked.
- **Microsoft Visual Studio 2017** Community or Professional, at least version 15.9.0 

    Older Visual Studio versions can be found [here][MVS]. A free microsoft account is needed to download and continuously use Visual Studio. 
    <br>During installation of visual studio, make sure to install the following workloads: __Desktop development with C++__ and __Game development with C++__
    
> Please note that versions of Unreal Engine greater than 4.22 and Visual Studio 2017 **do not currently work**. 

### Cloning the project

First you have to clone this repository with the following command: 
```bash
git clone --recurse-submodules https://devhub.vr.rwth-aachen.de/VR-Group/zytoskelett.git
```
In order to start the Project, navigate to the root directory and double-click the __zytoskelett2.uproject__ file. If you have multiple Unreal Engines installed, make sure to launch it with 4.22.3.

## Usage

### Importing Data
In order to load a cytoskeleton into the scene, you need an input file located in the subfolder **Content/Data**, relative to the project's root directory. If it doesn't exist, create it yourself. You will need one line for each vertex of your cell. Each line has to contain the following values:

- **n_segment** as an integer for every filament. Each vertex belonging to the same filament has the same line number.
- **n_vert** as an integer. Unique for every vertex within the same filament.
- **(x, y, z)-position** as a floating point number.
- **density** as a floating point number. Describes the thickness of the segment.
- **class identifier**, a number between 1 and 5.
  id|color
  :--:|--
  1|<span style="color: turquoise">green</span>
  2|<span style="color: blue">blue</span>
  3|<span style="color: red">red</span>
  4|<span style="color: orange">orange</span>
  5|<span style="color: lightgray">white</span>
- **flag** not used here but required by another program

> All these values are seperated by tabulators. The values have to be in **exactly this order**. No values can be left out.

**Example**:
```
n_segment	n_vert	x	y	z	density	class	flag
1	1	10.2	20.34	3.17	1422.89875	1	NaN
1	2	10.23	20.4	3.23	1422.89875	1	NaN
2	1	10.53	20.72	3.59	1964.99	1	NaN
2	2	10.62	20.81	3.56	1964.99	1	NaN
```

To change the name of the file to import, load your project in the Unreal Engine Editor and select the __Zytoskelett Data__ Actor from the scene browser on the right. In the properties window below, choose **Filename** in the Menu **Zytoskelett - Eingabe** and change the name to your data files name including the file extension (e.g. .dat). Also, an actor is created in the subfolder __Content/Data__ for easy reuse.
![Import Data Settings][ueidata]

### Exporting Data
The changed cytoskeleton can be exported into a file of the same format as the input file. It will have an __\_exported__ added to its input file name. The only value that will be changed is the class, so when importing that file the next time your filaments will keep their assigned class.

### Data examples
The Zytoskelett project comes with an example file, found here: `zytoskelett\Content\Data\ex_003_2_UNREAL.dat`<br>
Further Datasets can be found [here][KRNDL].

## Running it ...
### ... on PC
You can select different viewport options by clicking the little arrow on the right side of the __Play__ button. In order to run the project on desktop, use the option "Selected Viewport" or "New Editor Window".

![dropdownmenu for viewport selection][UEPlay]

### ... in VR

When running in VR, make sure the HMD is connected and correctly set up. Then click "VR Preview" and use the project on the HMD.

![Dropdown menu with VR Preview selected][ueplayhmd]

## Controls
### Desktop

![keyboard control scheme][keybschem]

|#|description
|--|--|
|W, A, S, D|move through the scene|
|arrow keys|rotate the view|
|left mouse button|change the class of the selected segment
|number key 1|cycles the currently selected class from 1 through 5
|number key 2|stops the VR-Pawn movement and enables the mouse cursor. The filament under the mouse cursor will change its class when left clicking
|number key 3|starts exporting an existing cytoskeleton into an output file
|number key 4|starts importing the chosen file an creating a cytoskeleton in the scene

### HTC Vive

![vive controller schematic][viveschem]

|#|description|
|----|--------------------------|
| 1  | move forward             |
| 2  | move backward            |
| 3  | move left                |
| 4  | move right               |
| 5  | Assign Class to Filament |
| 6  | Import Data     |
| 7  | Cycle Filament Class |
| 8  | --              |
| 9  | Export Data     |
| 10 | Assign Class to Filament |

### Valve Index

![steam controller schematic][steamschem]

|#|description|
|:--:|--------------------------|
| 1, 2  | __up:__ move forward <br> __down:__ move backward <br> __left:__ move left <br> __right:__ move right
| 3, 6  | Assign Class to Filament |
| 4, 5  | __up:__ Cycle Filament Class <br> __down:__ Export Data <br> __left:__ Import Data <br> __right:__ Export Data |

### HP Reverb

**currently not supported**

## Findig your way around

1. After starting the project, you'll see the following screen 
![PC Viewport in Unreal][ueviewportpc]

1. In the top right corner, a window that shows the numbers of the segment and vertex currently pointed at, and which class is assigned to it. In VR, the window is not shown.

1. A ray is coming out of the camera (or the right controller, when in VR). This points at the segment you are interacting with.
![HMD Viewport in Unreal][ueviewporthmd]

1. The data file (example is provided) can be loaded by pressing the import key (key map see below).

1. Flying close enough to a filament (indicated by square at the end of the ray) lets you assign a different class to it.
![Change Filament Class on Desktop][uechangeclassdesktop]
![Change Filament Class in VR][uechangeclasshmd]

1. Export the annotated data by pressing the export key. The successful export is indicated by a message in the top left corner of the screen.

## Customization

### Change inputs

The input settings can be changed on a per-device basis under `Edit > Project Settings > Engine > Input`.

![unreal edit menu][ueeditmenu]

To change the input, the dropdown menus can be used. Furter input methods can be added by clicking the plus sign. For each action or axis mapping, the first input method represents mouse and keyboard input while the others are used for the HMDs. 

![project input settings][ueinputsettings]

The action mappings trigger the following events:

action mapping name|event description
--|--
Fire|apply filament class
Action1|cycle filament class
Action2|stop movement and enable mouse controls
Action3|export data
Action4|import data

The axis mappings control the following movements:

axis mapping name|movement description
--|--
MoveForward|*Keyboard*: movement parallel to the line of sight<br>*HMD*: movement parallel to the direction to which the right controller is pointing
MoveRight|movement perpendicular to the vector described above
TurnRate|turn the viewport left and right (**keyboard only**)
LookUpRate|turn the viewport up and down (**keyboard only**)

[UE4]: https://www.unrealengine.com/en-US/download/
[MVS]: https://visualstudio.microsoft.com/de/vs/older-downloads/
[KRN]: http://kernet.rwth-aachen.de/index.html
[KRNDL]: http://kernet.rwth-aachen.de/RPE-main.html
[PPR]: https://elifesciences.org/articles/75894

[viveschem]: documentation/vive-controls.jpg "Vive Controller Schematic"
[steamschem]: documentation/steam-controls.jpg "Steam Controller Schematic"
[reverbschem]: documentation/reverb-controls.jpg "HP Reverb Controller Schematic"
[keybschem]: documentation/keyboard-controls.jpg "Keyboard Control Schematic"
[UEPlay]: documentation/unreal-play.png "Viewport Selection"
[ueplayhmd]: documentation/unreal-play-hmd.png "Select VR Viewport"
[ueeditmenu]: documentation/unreal-edit-menu.png "Edit Menu"
[ueidata]: documentation/unreal-change-import-data.png "Change import data Menu"
[ueinputsettings]: documentation/unreal-input-settings.png "Input Settings Window"
[ueviewportpc]: documentation/unreal-viewport-pc.png "Viewport on PC"
[ueviewporthmd]: documentation/unreal-viewport-hmd.jpg "Viewport on HMD"
[uechangeclassdesktop]: documentation/unreal-change-class.png "Change Filament Class Desktop"
[uechangeclasshmd]: documentation/unreal-change-class-hmd.jpg "Change Filament Class on HMD"
