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
  
Info << "....density, rho" << endl;
dimensionedScalar rho
(
    "rho",
    dimensionSet(1, -3, 0, 0, 0, 0, 0),
    transportProperties.lookup("rho")
);
Info << "    rho = " << rho << endl;

Info << "....kinematic viscosity, nu" << endl;
dimensionedScalar nu
(
    "nu",
    dimViscosity,
    transportProperties.lookup("nu")
);
Info << "    nu = " << nu << endl;

Info << "....relative permitivity, eps" << endl;
dimensionedScalar eps
(
    "eps",
    dimensionSet(0, 0, 0, 0, 0, 0, 0),
    transportProperties.lookup("eps")
);
Info << "    eps = " << eps << endl;

Info << "....Debye length, lambda" << endl;
dimensionedScalar lambda
(
    "lambda",
    dimensionSet(0, 1, 0, 0, 0, 0, 0),
    transportProperties.lookup("lambda")
);
Info << "    lambda = " << lambda << endl;

Info << "....Max electric potential, epMax" << endl;
dimensionedScalar epMax
(
     "epMax",
     dimensionSet(0, 0, 0, 0, 0, 0, 0),
     transportProperties.lookup("epMax")
);
Info << "    epMax = " << epMax << endl;

Info << "....Max charge density, rhoCMax" << endl;
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

