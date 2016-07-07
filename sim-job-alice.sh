#!/bin/bash

export HOME=/root

ls -la /cvmfs/alice.cern.ch
ls -la /cvmfs/alice-ocdb.cern.ch
source /cvmfs/alice.cern.ch/etc/login.sh
alienv setenv  VO_ALICE@AliPhysics::vAN-20160627-1 -c ./simrun.sh > OUTPUT
cat /var/log/condor/* > OUTPUT
