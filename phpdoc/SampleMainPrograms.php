<html>
<head>
<title>Sample Main Programs</title>
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

<form method='post' action='SampleMainPrograms.php'>

<h2>Sample Main Programs</h2>

Descriptions of available classes, methods and settings are all
very good and useful. Ultimately they are necessary for you to
be able to fine-tune your runs to the task at hand. To get going, 
however, nothing helps like having explicit examples to study. 
This is what is provided in the <code>examples</code> subdirectory, 
along with instructions how they should be run: 
<ul>

<li><code>main01.cc</code> : a simple study of the charged multiplicity
for jet events at the LHC. (Brief example fitting on one slide.)</li>

<li><code>main02.cc</code> : a simple study of the <i>pT</i> spectrum 
of Z bosons at the Tevatron. (Brief example fitting on one slide.)</li>

<li><code>main03.cc</code> : a simple single-particle analysis of jet 
events, where input is set by <code>main03.cmnd</code> "cards file".</li>

<li><code>main04.cc</code> : a simple study of several different kinds 
of events, with the choice to be made in the <code>main04.cmnd</code> 
"cards file".</li>

<li><code>main05.cc</code> : generation of QCD jet events at the LHC, 
with jet analysis using the <code>CellJet</code> cone-jet finder.</li>

<li><code>main06.cc</code> : tests of cross sections for elastic and 
diffractive topologies, using <code>main06.cmnd</code> to pick process.</li>

<li><code>main07.cc</code> : tests of cross sections for minimum-bias 
events, using <code>main07.cmnd</code> to pick options.</li>

<li><code>main08.cc</code> : generation of the QCD jet cross section
by splitting the run into subruns, each in its own <i>pT</i> bin,
and adding the results properly reweighted. Two options, with limits 
set either in the main program or by subrun specification in the
<code>main08.cmnd</code> file.</li>

<li><code>main09.cc</code> : generation of LEP1 hadronic events, i.e. 
<i>e^+e^- -> gamma*/Z^0 -> q qbar</i>, with charged multiplicity, 
sphericity, thrust and jet analysis.</li>

<li><code>main10.cc</code> : illustration how userHooks can be used
interact directly with the event-generation process.</li>

<li><code>main11.cc</code> : generation of two predetermined hard
interactions in each event.</li>

<li><code>main12.cc</code> : a study of top events, fed in from the 
Les Houches Event File <code>ttbar.lhe</code>, here generated by 
PYTHIA 6.4. This file currently only contains 100 events 
so as not to make the distributed PYTHIA package too big, and so serves 
mainly as a demonstration of the principles involved. </li> 

<li><code>main13.cc</code> : a more sophisticated variant of 
<code>main12.cc</code>, where two Les Houches Event Files
(<code>ttbar.lhe</code> and <code>ttbar2.lhe</code>) successively
are used as input. Also illustrating some other aspects, like the
capability to mix in internally generated events.</li> 

<li><code>main14.cc</code> : a systematic comparison of several 
cross section values with their corresponding values in PYTHIA 6.4,
the latter available as a table in the code.</li> 

<li><code>main15.cc</code> : loop over several tries, either to redo 
B decays only or to redo the complete hadronization chain of an event.
Since much of the generation process is only made once this is a way 
to increase efficiency.</li> 

<li><code>main16.cc</code> : put all user analysis code into a class
of its own, separate from the main program; provide the "cards file" 
name as a command-line argument.</li> 

<li><code>main17.cc</code> : collect the Pythia calls in a wrapper class, 
thereby simplifying the main program; provide the "cards file" name 
as a command-line argument.</li> 

<li><code>main18.cc</code> : shows how to write an event filter class,
where you keep a vector of pointers to the subset of particles you
want to study further. The event record itself remains unchanged.</li> 

<li><code>main19.cc</code> : use several instances of Pythia, one for 
signal events and others for a variable number of pileup and "beam-gas"
events, combined into one common event record.</li> 

<li><code>main20.cc</code> : shows how PYTHIA 8 can write a Les Houches
Event File, using facilities potentially useful also for other programs
to write an LHEF.</li> 

<li><code>main21.cc</code> : an example how a single particle or various
parton-level configurations can be input directly for hadronization, 
without being tied to the full process-generation machinery, e.g. to 
study the hadronization of junction topologies. </li>

<li><code>main22.cc</code> : tests of internally implemented cross sections
for Supersymmetric particle production, with SYSY spectrum defined in
<code>sps1a.spc</code> and settings in <code>main22.cmnd</code>.</li>

<li><code>main23.cc</code> : shows how an external decay handler can 
be linked to handle the decays of some particles.</li>

<li><code>main24.cc</code> : shows how an external random number 
generator can be linked to replace the internal one.</li>

<li><code>main25.cc</code> : shows how an external process can be 
implemented as a new class derived from a PYTHIA base class, and then
handed in for generation as with a normal internal process.</li>

<li><code>main26.cc</code> : shows how an external resonance can be 
implemented as a new class derived from a PYTHIA base class, and be 
used in an external process, both of which are then handed in for 
generation as with a normal internal resonance and process.</li>

<li><code>main27.cc</code> : shows how an external beam momentum spread
and vertex location generator can be implemented as a new class derived 
from a PYTHIA base class, and then handed in for internal use.</li>

<li><code>main28.cc</code> : test program for processes in scenarios
with large extra dimensions or unparticles.

<li><code>main29.cc</code> : set up a fictitious production process 
to a generic resonance, where you easily can compose your own list
of (two-body) decay modes to a variety of final states. Also traces
decay chains down to truly stable particles: gamma, e+-, p/pbar and
neutrinos. Suitable for astroparticle applications, like neutralino 
pair annihilation, where cross sections are calculated separately 
in another program.

<li><code>main30.cc</code> : production of Kaluza-Klein <i>gamma/Z</i> 
states in TeV-sized extra dimensions.

<li><code>main31.cc</code> : similar to main01, except that the 
event record is output in the HepMC event record format. Requires 
that HepMC is properly linked.</li>

<li><code>main32.cc</code> : a streamlined version for the generation
of events that are then stored in HepMC format, without any event 
analysis. That is, all physics studies will have to be done afterwards.
The name of the input "cards file" (e.g. <code>main32.cmnd</code>)
and output HepMC event file are to be provided as command-line arguments.
Requires that HepMC is properly linked.</li>

<li><code>main41.cc</code> : a test of the shape of parton densities,
as a check prior to using a given PDF set in a generator.  Requires 
that LHAPDF is properly linked.</li>

<li><code>main42.cc</code> : compares the charged multiplicity 
distribution, and a few other minimum-bias physics aspects, between 
default PYTHIA PDF and another one. Requires that LHAPDF is properly 
linked.</li>

<li><code>main43.cc</code> : tests the possibility to do backwards
evolution from an incoming photon at the hard interaction. Requires 
that you link to a LHAPDF set that includes the photon PDF.</li>

<li><code>main44.cc</code> : exemplifies how you create your own 
PDF set and link it in for use in the process generation.</li>

<li><code>main51.cc</code> : exemplifies how you can link in runtime
generation of hard processes from PYTHIA 6, using the Les Houches
Accord facilities. This example is deprecated, since PYTHIA 8 by now
contains essentially all hard processes found in PYTHIA 6.</li>

<li><code>main61.cc</code> : an example how the FastJet jet finding 
package can be linked to allow an analysis of the final state,
in this case for a study of W + jet production.</li>

<li><code>main71.cc</code> : exemplifies an improved matching of
parton showers to LHEF-style input based on the POWHEG approach, 
in this particular case for the POWHEG-hvq program applied to top
pair production [<a href="Bibliography.php" target="page">Cor10</a>]. The small sample of input events 
is stored in the <code>powheg-hvq.lhe</code> file.
</li>

</ul>

</body>
</html>

<!-- Copyright (C) 2010 Torbjorn Sjostrand -->