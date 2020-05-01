rm -r A*
rm -r C*
rm Makefile
rm -r c*

H=/Users/tsuboy/work/geant

cmake  ../source


G4=$H/geant4.10.06.p01-install/lib/Geant4-10.6.1/
#cmake -DGeant4_DIR=${G4}  ${H}/pixel2/source
 
#cmake ${PRE}=$H/$I ${DATA}=ON ${OPENGL}=OFF ${QT}=ON  $H/$S

#From  https://github.com/smarco17/geant4/blob/master/manual/geant4_build_and_install_guide_for_ubuntu.md
#cmake -DCMAKE_INSTALL_PREFIX=/home/user/Downloads/geant4.10.03.p03-install -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_OPENGL_X11=ON /home/user/Downloads/geant4.10.03.p03


