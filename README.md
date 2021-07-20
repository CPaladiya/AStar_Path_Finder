# 15_LOS_Path_Finder (Continue..)
My original algorithm that uses the result of A-Star search algorithm to predict better path to destination

## Linux OS : Installation Requirements
(1) <code>gcc 9.3.0</code> or above, if not already installed please follow the steps shown [here.](https://linuxize.com/post/how-to-install-gcc-on-ubuntu-20-04/)</br>
(2) <code>cmake 3.20.4</code> or above, if not already installed please follow the steps shown [here.](https://cgold.readthedocs.io/en/latest/first-step/installation.html)</br>
(3) <code>QMake 3.1</code> or above and <code>Qt 5.12.8</code> or above, if not already installed please follow the steps shown [here.](https://www.addictivetips.com/ubuntu-linux-tips/how-to-install-qt-5-on-ubuntu/)</br>
(4) please run the command <code>sudo apt-get install qtmultimedia5-dev libqt5multimediawidgets5 libqt5multimedia5-plugins libqt5multimedia5</code> in terminal to install multimedia package from Qt, required to produce the sound effets. </br>
(5) Please keep all the files as it is in the repo. Once, cloned in your local computer, open the terminal and nevigate to the source directory <code>15_LOS_Path_Finder</code>, then run <code>qmake && make && ./15_LOS_Path_Finder</code> in your terminal.</br>

## File/Qt Variable Layout
Here is overall file structure of the visualizer </br>

<img src="https://github.com/CPaladiya/15_LOS_Path_Finder/blob/main/.vscode/FileStructure.png" width="680"> </br>

Here is variable map I used for overall GUI implementation </br>

<img src="https://github.com/CPaladiya/15_LOS_Path_Finder/blob/main/.vscode/Variables.png" width="680"> </br>

## Game GUI

<img src="https://github.com/CPaladiya/Chirag-Paladiya/blob/main/AStar.gif" width="500"> </br>

