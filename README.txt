7 May 2020 T.Tsuboyama (KEK)
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
