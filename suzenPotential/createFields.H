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
  
Info << "....relative permitivity, eps" << endl;
dimensionedScalar eps
(
    "eps",
    dimensionSet(0, 0, 0, 0, 0, 0, 0),
    transportProperties.lookup("eps")
);
Info << "    eps = " << eps << endl;

Info << "....maximum electric potential, elPotMax" << endl;
dimensionedScalar elPotMax
(
     "elPotMax",
     dimensionSet(0, 0, 0, 0, 0, 0, 0),
     transportProperties.lookup("elPotMax")
);
Info << "    elPotMax = " << eps << endl;

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
