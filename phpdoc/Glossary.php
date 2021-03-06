<html>
<head>
<title>Glossary</title>
<link rel="stylesheet" type="text/css" href="pythia.css"/>
<link rel="shortcut icon" href="pythia32.gif"/>
</head>
<body>

<script language=javascript type=text/javascript>
function stopRKey(evt) {
var evt = (evt) ? evt : ((event) ? event : null);
var node = (evt.target) ? evt.target :((evt.srcElement) ? evt.srcElement : null);
if ((evt.keyCode == 13) && (node.type=="text"))
{return false;}
}

document.onkeypress = stopRKey;
</script>
<?php
if($_POST['saved'] == 1) {
if($_POST['filepath'] != "files/") {
echo "<font color='red'>SETTINGS SAVED TO FILE</font><br/><br/>"; }
else {
echo "<font color='red'>NO FILE SELECTED YET.. PLEASE DO SO </font><a href='SaveSettings.php'>HERE</a><br/><br/>"; }
}
?>

<form method='post' action='Glossary.php'>

<h2>Glossary</h2>

<dl>

<dt>BR</dt>
<dd>Beam Remnants; not much used since it may be confused with 
Branching Ratio</dd>

<dt>BSM</dt>
<dd>Beyond-the-Standard-Model physics, as a generic term for anything
not contained within the SM</dd>

<dt>FSR</dt>
<dd>Final-State Radiation, implemented in terms of timelike showers</dd>

<dt>LHA</dt>
<dd>Les Houches Accord for user processes, describing which process-level 
information should be stored to allow further showering and hadronization 
of "skeleton" hard processes</dd>

<dt>LHAPDF</dt>
<dd>Les Houches Accord Parton Distribution Functions, originally a standard
format for defining PDF's and later a library with such PDF's</dd>

<dt>LHEF</dt>
<dd>Les Houches Event File(s), a file format for storing LHA process and
event information</dd>

<dt>ISR</dt>
<dd>Initial-State Radiation, implemented in terms of spacelike showers</dd>

<dt>MI</dt>
<dd>Multiple Interactions, i.e. several (more or less) independent 
parton-parton subcollisions as part of a hadron-hadron event (sometimes
also called MPI, with P for parton or parton-parton)</dd>

<dt>MSSM</dt>
<dd>Minimal Supersymmetric extension of the Standard Model</dd>

<dt>PDF</dt>
<dd>Parton Distribution Function (alternatively Parton Density 
Function)</dd>

<dt>PDG code</dt>
<dd>a scheme for assigning unique integers, particle identity codes,
to known and hypothetical particles; code rules and tables are published 
in the RPP (see below).</dd>

<dt>pileup</dt>
<dd>several hadron-hadron collisions in a bunch crossing; not to 
be confused with MI</dd>

<dt>RPP</dt>
<dd>Review of Particle Physics, the biannual review by the ParticleData Group
(PDG) from which many Standard-Model parameter values and much particle data 
has been taken (but, given the poor data on many hadron resonances, a lot of
extra (guess)work is needed)</dd>

<dt>setting</dt>
<dd>collectively used to denote all the boolean <code>flag</code>, 
integer <code>mode</code>, double-precision <code>parm</code>
and string <code>word</code> variables that can be set by the user 
to steer the behaviour of a run; normally particle data are considered
separately but clearly are closely related</dd>

<dt>SLHA</dt>
<dd>SUSY Les Houchs Accord for interchange of mass and coupling information
in SUSY scenarios, via a well-defined file format</dd>

<dt>SM</dt>
<dd>the Standard Model of particle physics</dd>

<dt>SUSY</dt>
<dd>SUperSYmmetry</dd>

<dt>units</dt>
<dd>Normal PYTHIA input, internal operations and output is based on a set of 
standard units, such as:
<br/>GeV for all energies, momenta and masses, always with <i>c = 1</i>;
<br/>mm for all distances and mm/<i>c</i> for all times, 
so that again they match for <i>c = 1</i>;
<br/>mb for all cross sections (but input or output via the Les Houches 
Accord takes into account that the unit there is pb) 
</dd>

</dl>

</body>
</html>

<!-- Copyright (C) 2010 Torbjorn Sjostrand -->
