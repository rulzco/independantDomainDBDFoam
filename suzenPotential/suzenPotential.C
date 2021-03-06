/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is based on the laplacian solver of OpenFOAM, and was modified to
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
    suzenPotential

Description
    Laplace equation solver for the electric potential of the DBD Suzen model,
    and the electric field E=-grad(phi).

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

    Info<< "\nCalculating Electric Potential\n" << endl;
    
    solve ( fvm::laplacian(epsR,ElPot) );
    
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

    runTime++;
    ElPot.write();
    Efield.write();

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
