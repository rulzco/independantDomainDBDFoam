# independantDomainDBDFoam
OpenFoam implementation of the Suzen-Huang DBD model using an independet domain technique. The technique consist in solving the electricfield in an independent domain and the charge density, force and flow field are computed in another domain, after the elecric field is mappaped from the first domain. Three solvers are provided, one for potential and electric field and two for charge density, force, and flow field. The selection of the second solver depends on whether a stationary or a transient simulation is performed.

* suzenPotential: solves the electric potential, then the computed fields must be mapped to  the domain for the force and induced flow computations.

* suzenSimple: solves the charge density and force (time-independant) and the computes the induced flow with the SIMPLE algorithm. 

* suzenPimple: solves the charge density and force (time-dependant) and the computes the induced flow with the PIMPLE algorithm. 

## Requirements

To install and run this solvers an installation of OpenFOAM is required. For the post processing ParaView is required https://www.paraview.org/. 

The codes were tested with OpenFOAM version 8.0 from the https://openfoam.org/ branch. But it should also work with the older versions and version 9.0 . 

## Installation

To install these solvers go to the user directory and access the ```/solvers``` directory:

```
cd $ WM_PROJECT_USER_DIR/applications/solvers
```

If there is no solvers directory, it must be created:

```
mkdir -p $ WM_PROJECT_USER_DIR/applications/solvers
```

The solvers to install must be unzipped and copied into ```$WM_PROJECT_USER_DIR/applications/solvers```. When they have already been copied, access to the directory of each solver and install it wiith ```wmake```:

```
cd suzenPotential
wmake 
```
