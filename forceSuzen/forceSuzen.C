/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    forceSuzen

Description
    Solves a Poisson equation for the charge density, the solves the body force for the
	DBD Suzen model, suzenPotential should be used first to solve the electric potential,
	then the potential muts be mapped to the case in which forceSuzen is executed.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
//#include "fvOptions.H"
//#include "simpleControl.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCaseLists.H"

    #include "createTime.H"
    #include "createMesh.H"

    //simpleControl simple(mesh);

    #include "createFields.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    //Info<< "\nCalculating Electric Potential\n" << endl;
    
    //solve ( fvm::laplacian(epsR,ElPot) ); /Laplace eq. electric potential see suzenPotential

    Info<< "\nCalculating Charge Density\n" << endl;
    solve ( fvm::laplacian(epsR,rhoC) == fvm::Sp(1. / (lambda * lambda),rhoC) ); //Poisson eq. for charge density

    volVectorField Efield
    (
     	IOobject
     	(
			"Efield",
			runTime.timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
        ),
        - fvc::grad(ElPot)
    );		   

    Info<< "\nCalculating time-independent force field\n" << endl;

    volVectorField bForce
    (
		IOobject
		(
			"bForce",
			runTime.timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		rhoCMax * epMax * rhoC * Efield / rho
    );

    runTime++;
    ElPot.write();
    rhoC.write();
	Efield.write();
	bForce.write();
    /*
    while (simple.loop(runTime))
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

       i while (simple.correctNonOrthogonal())
        {
            fvScalarMatrix TEqn
            (
                fvm::ddt(T) - fvm::laplacian(DT, T)
             ==
                fvOptions(T)
            );

            fvOptions.constrain(TEqn);
            TEqn.solve();
            fvOptions.correct(T);
        }

        #include "write.H"

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }*/

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
