13 May 2020
The ELPH/FNAL 2020 beam test set up is simulated.
Total six(two sofist4 and four fpix2) sensors are instlled.

Sensor    Xwid Ywid  Sig   Total SOI  Depl     Z
          um   um     um    um    um   um     mm
fpix2      8    8     10    500   10   300     0.0
fpix2      8    8     10    500   10   300    30.0
sofist4   20   20     10    500   10    10    60.0
sofist4   20   20     10    500   10    10    90.0
fpix2      8    8     10    500   10   300   120.0
fpix2      8    8     10    500   10   300   150.0

The program did not run. Just after modification.
If the pixel structure is displayed, the visualization program needs 1 minutes to 
prepare a 128x128 fpix2 sensor. It looks the waiting time increases with speed of (Number of sensors)^2.
This was the main reason of very slow startup, already a problem in the past versions.
It took a few hours before I realized the reason.
I had to stop displaying the detail pixel structure, with this version.
After the change, the program started work without delay.
The change is for the graphical display only.  The simulation output is not affected.

10 May 2020
In the previous version, the "charge share region" was 3x3. 
In this version it can be set NxN. 
The creation of the look up table gets faster by changing from "Adding gaussian functions" 
to "subtraction of the integration of the gaussian function".

7 May 2020
1) The charge in one pixel is spread to neighbor pixels. The amount of spread is
calculated ChargeShare.cc.
2) BUG report: In very rare case, the program stops in the particle tracing..
   The error happens even the Stepping function (user digitization) is skipped. 
   In this case, the problem does not happen if the beam start position is moved 
   by 0.1 um. --> I gave up the debugging.


-----------------------
You can compile the programs in this directory

    $ cd build
    $ rm -r C*
    $ cmake ../source
    $ make

Then the executable ./exampleB4a   is created.
You can execute the program by

    $ ./exampleB4a

in the GUI mode. You can enter commands to the GUI.   The simplest one is 

     /run/beamOn 100

You can also run the program in batch mode.

  $ ./exampleB4a -m fnal.mac

The output root file is "B4_2MeV.root"  (I am sorry for the strange name).
The output file can be read by p3.C as follows:

  $ root -l
  root [0] .x p4.C

Then you can see the simple histogram and the Hit map.
At present all the root macros "*.C" work somehow.

--------------------------------------------
If you need to add pixel sensors, you should 
$ grep el2  source/src/*cc
$ grep el2  source/include/*cc
and find the variables related to pixel1 or pixel2.
Then you can add sensors by adding pixel3 pixel4 ...
And obvious modifications.

If you like to change pixel sensor types, you find
   Pixel2= new apixel(120);
in the DetectorConstruction.cc
The parameter is "sensor ID." However, you can add parameters like
Pixel4= new apixel(cn,Ny,Nx,Sy,sx,tc,td,tw);
where cn=ID number NY/NX number of pixels in Y and X direction
Sy/Sx pixel size.  tc/td/tw thickness of CMOScircuit/Depletionlayer/wafer

In the DetectorConstruction, you can specify the location and orientation of the sensors.
So you can add mis alighment artificially. (Source code is obvious.)
------------- Running parmeters
Sensor position and orientation        DetectorConstruction.cc
Sensor properties (thickness, pixel size, pixel array, charge spread...) 
       Default parameters:   apixel.hh   
       Individual parameters:  DetectorConstruction.cc 
Beam type energy position direction
       PrimaryGenerator.cc
