#!/bin/bash

for i in {0..3376}
do
    echo $i
    COMMAND="mv rootfile_CaloScoutingHT2016BCD_HTBCD_JEC_CaloHLT_plus_V10p2_SecondAttempt_20170125_184349_"$i"_reduced_skim.root rootfile_CaloScoutingHT2016BCD_HTBCD_JEC_CaloHLT_plus_V10p2_20170125_184349_"$i"_reduced_skim.root"
    COMMAND2="mv rootfile_CaloScoutingHT2016BCD_HTBCD_JEC_CaloHLT_plus_V10p2_SecondAttempt_20170125_184349_$i.root rootfile_CaloScoutingHT2016BCD_HTBCD_JEC_CaloHLT_plus_V10p2_20170125_184349_$i.root"
    COMMAND3="mv cutEfficiencyFile_CaloScoutingHT2016BCD_HTBCD_JEC_CaloHLT_plus_V10p2_SecondAttempt_20170125_184349_$i.dat  cutEfficiencyFile_CaloScoutingHT2016BCD_HTBCD_JEC_CaloHLT_plus_V10p2_20170125_184349_$i.dat "
    echo $COMMAND
    echo $COMMAND2
    echo $COMMAND3
    $COMMAND
    $COMMAND2
    $COMMAND3
done
