#!/bin/bash
echo "void rootlogon() { gSystem->SetIncludePath(\"-I$ALICE_ROOT/include -I$ALICE_PHYSICS/include\");}" > rootlogon.C
aliroot -l -b -q fastGen.C+
