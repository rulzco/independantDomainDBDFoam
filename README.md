# dbdSuzenFoam
OpenFoam implementation of the Suzen-Huang DBD model.

suzenPotential solves the electric potential, then the computed fields must be mapped to domain for the force and induced flow computations
suzenSimple solves the charge density and force (time-independant) and the computes the induced flow with the SIMPLE algorithm 
suzenPimple solves the charge density and force (time-dependant) and the computes the induced flow with the PIMPLE algorithm 
