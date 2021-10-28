/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2020 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is based on the simpleFoam solver of OpenFOAM, and was modified to
    integrate a DBD solver.

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
    suzenSimple

Description
    Stead-state solver for charge density and DBD induced body force by the Suzen model coupled 
    with a steady-state solver for incompressible, turbulent flow, using the SIMPLE algorithm.
    
    NOTE: a suzenPotential solver case must be exectuded first, since 
    its computed fields are required as initial conditions by suzenSimple.
\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "singlePhaseTransportModel.H"
#include "kinematicMomentumTransportModel.H"
#include "simpleControl.H"
#include "fvOptions.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "postProcess.H"

    #include "setRootCaseLists.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createControl.H"
    #include "createFields.H"
    //#include "physicalProperties"
    #include "initContinuityErrs.H"

    turbulence->validate();

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
    
    //Info<< "\nCalculating Electric Potential\n" << endl;
    
    //solve ( fvm::laplacian(epsR,ElPot) ); /Laplace eq. for the electric potential solved with suzenPotential
    
        /*volVectorField Efield // Calculated with suzenPotential
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
    );  */     
    
    Info<< "\nCalculating Charge Density\n" << endl;
    solve ( fvm::laplacian(epsR,rhoC) == fvm::Sp(1. / (lambda * lambda),rhoC) ); //Poisson eq. for the charge density

    Info<< "\nStarting time loop\n" << endl;
    
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
        rhoCMax * elPotMax * rhoC * Efield / rho
    );
    
    runTime++;
    ElPot.write();
    rhoC.write();
    Efield.write();
    bForce.write();

    Info<< "\nStarting time loop\n" << endl;

    while (simple.loop(runTime))
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        // --- Pressure-velocity SIMPLE corrector
        {
            #include "UEqn.H"
            #include "pEqn.H"
        }

        laminarTransport.correct();
        turbulence->correct();

        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
