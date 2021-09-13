#include "createRDeltaT.H"
Info<< "Reading tansportProperties\n" << endl;
IOdictionary transportProperties
(
     IOobject
     (
    "transportProperties",
    runTime.constant(),
    mesh,
    IOobject::MUST_READ_IF_MODIFIED,
    IOobject::NO_WRITE
     )
 );
  
Info << "Reading density rho" << endl;
dimensionedScalar rho
(
    "rho",
    dimensionSet(1, -3, 0, 0, 0, 0, 0),
    transportProperties.lookup("rho")
);
Info << "    rho = " << rho << endl;

Info << "Reading kinematic viscosity nu" << endl;
dimensionedScalar nu
(
    "nu",
    dimViscosity,
    transportProperties.lookup("nu")
);
Info << "    nu = " << nu << endl;

Info << "Reading relative permitivity eps" << endl;
dimensionedScalar eps
(
    "eps",
    dimensionSet(0, 0, 0, 0, 0, 0, 0),
    transportProperties.lookup("eps")
);
Info << "    eps = " << eps << endl;

Info << "Reading Debye length lambda" << endl;
dimensionedScalar lambda
(
    "lambda",
    dimensionSet(0, 1, 0, 0, 0, 0, 0),
    transportProperties.lookup("lambda")
);
Info << "    lambda = " << lambda << endl;

Info << "Reading frequency of signal omega" << endl;
dimensionedScalar omega
(
    "omega",
    dimensionSet(0, 0, -1, 0, 0, 0, 0),
    transportProperties.lookup("omega")
);
Info << "    omega = " << omega << endl;

Info << "Reading Max electric potential elPotMax" << endl;
dimensionedScalar elPotMax
(
     "elPotMax",
     dimensionSet(0, 0, 0, 0, 0, 0, 0),
     transportProperties.lookup("elPotMax")
);
Info << "    elPotMax = " << elPotMax << endl;

Info << "Reading Max charge density rhoCMax" << endl;
dimensionedScalar rhoCMax
(
     "rhoCMax",
     dimensionSet(0, 0, 0, 0, 0, 0, 0),
     transportProperties.lookup("rhoCMax")
 );
Info << "    rhoCMax = " << rhoCMax << endl;

Info<< "Reading field electric potential ElPot\n" << endl;
volScalarField ElPot
(
    IOobject
    (
        "ElPot",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field electric field Efield\n" << endl;
volVectorField Efield
(
    IOobject
    (
        "Efield",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field relative permitivity epsR\n" << endl;
volScalarField epsR
(
     IOobject
     (
        "epsR",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
     ),
     mesh
);

Info<< "Reading field charge density rhoC\n" << endl;
volScalarField rhoC
(
      IOobject
      (
        "rhoC",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
      ),
      mesh
);


Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

#include "createPhi.H"


label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell(p, pimple.dict(), pRefCell, pRefValue);
mesh.setFluxRequired(p.name());


singlePhaseTransportModel laminarTransport(U, phi);

autoPtr<incompressible::momentumTransportModel> turbulence
(
    incompressible::momentumTransportModel::New(U, phi, laminarTransport)
);

#include "createMRF.H"
#include "createFvOptions.H"
