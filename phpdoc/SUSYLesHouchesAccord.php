<html>
<head>
<title>SUSY Les Houches Accord</title>
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

<form method='post' action='SUSYLesHouchesAccord.php'>

<h2>SUSY Les Houches Accord</h2>

The PYTHIA 8 program does not contain an internal spectrum calculator
(a.k.a. RGE package) to provide supersymmetric couplings, mixing angles,
masses and branching ratios. Thus the SUSY Les Houches Accord (SLHA)
[<a href="Bibliography.php" target="page">Ska04</a>][<a href="Bibliography.php" target="page">All08</a>] is the only way of
inputting SUSY models, and SUSY processes cannot be run unless such an
input has taken place. 

<p/>
Most of the SUSY implementation in PYTHIA 8 is compatible with both the 
SLHA1 and SLHA2 conventions (with the exception of R-parity violation and 
the NMSSM extension in the latter case). Internally, PYTHIA 8 uses the 
SLHA2 conventions and translates SLHA1 input to these when necessary. 
See the section on SUSY Processes for more information.

<p/>
When reading LHEF files, Pythia automatically looks for SLHA information
between <code>&lt;slha&gt;...&lt;/slha&gt;</code> tags in the header of such
files. When running Pythia without LHEF input (or if reading an LHEF
file that does not contain SLHA information in the header), a separate 
file containing SLHA information may be specified using 
<code>SLHA:file</code> (see below). 

<p/>
With the so-called <code>QNUMBERS</code> extension [<a href="Bibliography.php" target="page">Alw07</a>], the 
SLHA input format can also be used for more general BSM models, although 
the implementation of this extension is not yet complete in PYTHIA 8. 

<p/>
Finally, the SLHA input capability can of course also be used to input 
SLHA-formatted MASS and DECAY tables for other particles, such as the top 
quark, furnishing a less sophisticated but more universal complement to the
standard PYTHIA 8-specific methods for inputting such information (for the
latter, see the section on <?php $filepath = $_GET["filepath"];
echo "<a href='ParticleData.php?filepath=".$filepath."' target='page'>";?>Particle Data</a>
and the <?php $filepath = $_GET["filepath"];
echo "<a href='ParticleDataScheme.php?filepath=".$filepath."' target='page'>";?>scheme</a> to modify it). This 
may at times not be desirable, so a few options can be used to curb the right 
of SLHA to overwrite particle data.

<p/>
The reading-in of information from SLHA or LHEF files is handled by the
<code>SusyLesHouches</code> class, while the subsequent calculation of 
derived quantities of direct application to SUSY processes is done in the
<code>CoupSUSY</code> class.

<h3>SLHA Switches and Parameters</h3>

<p/><code>mode&nbsp; </code><strong> SLHA:readFrom &nbsp;</strong> 
 (<code>default = <strong>1</strong></code>; <code>minimum = 0</code>; <code>maximum = 2</code>)<br/>
Controls from where SLHA information is read.
<br/><code>option </code><strong> 0</strong> : is not read at all. Useful when SUSY is not simulated
and normal particle properties should not be overwritten.  
<br/><code>option </code><strong> 1</strong> : read in from the <code>&lt;slha&gt;...&lt;/slha&gt;</code> 
block of a LHEF, if such a file is read during initialization, and else
from the <code>SLHA:file</code> below.  
<br/><code>option </code><strong> 2</strong> : read in from the <code>SLHA:file</code> below.  
  

<br/><br/><table><tr><td><strong>SLHA:file  </td><td></td><td> <input type="text" name="1" value="void" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>void</strong></code>)</td></tr></table>
Name of an SLHA (or LHEF) file containing the SUSY/BSM model definition, 
spectra, and (optionally) decay tables. Default <code>void</code>
signals that no such file has been assigned.
  

<br/><br/><strong>SLHA:keepSM</strong>  <input type="radio" name="2" value="on" checked="checked"><strong>On</strong>
<input type="radio" name="2" value="off"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>on</strong></code>)<br/>
Some programs write SLHA output also for SM particles where normally
one would not want to have masses and decay modes changed unwittingly. 
Therefore, by default, known SM particles are ignored in SLHA files. 
To be more specific, particle data for identity codes in the ranges 
1 - 24 and 81 - 999,999 are ignored. Notably this includes <i>Z^0</i>, 
<i>W^+-</i> and <i>t</i>. The SM Higgs is modified by the SLHA input, 
as is other codes in the range 25 - 80 and 1,000,000 - . If you 
switch off this flag then also SM particles are modified by SLHA input.
  

<br/><br/><table><tr><td><strong>SLHA:minMassSM </td><td></td><td> <input type="text" name="3" value="100.0" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>100.0</strong></code>)</td></tr></table>
This parameter provides an alternative possibility to ignore SLHA input 
for all particles with identity codes below 1,000,000 (which mainly
means SM particle, but also includes e.g. the Higgses in 
two-Higgs-doublet scenarios) whose default masses in PYTHIA lie below 
some threshold value, given by this parameter. The default value of 
100.0 allows SLHA input to modify the top quark, but not, e.g., the 
<i>Z^0</i> and <i>W^+-</i> bosons. 
  

<p/><code>mode&nbsp; </code><strong> SLHA:verbose &nbsp;</strong> 
 (<code>default = <strong>1</strong></code>; <code>minimum = 0</code>; <code>maximum = 3</code>)<br/>
Controls amount of text output written by the SLHA interface, with a
value of 0 corresponding to the most quiet mode.
  

<h3>Internal SLHA Variables</h3>

The following variables are used internally by PYTHIA as local copies
of SLHA information. User changes will generally have no effect, since
these variables will be reset by the SLHA reader during initialization.

<br/><br/><strong>SLHA:NMSSM</strong>  <input type="radio" name="4" value="on"><strong>On</strong>
<input type="radio" name="4" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Corresponds to SLHA block MODSEL entry 3.
  

<input type="hidden" name="saved" value="1"/>

<?php
echo "<input type='hidden' name='filepath' value='".$_GET["filepath"]."'/>"?>

<table width="100%"><tr><td align="right"><input type="submit" value="Save Settings" /></td></tr></table>
</form>

<?php

if($_POST["saved"] == 1)
{
$filepath = $_POST["filepath"];
$handle = fopen($filepath, 'a');

if($_POST["1"] != "void")
{
$data = "SLHA:file = ".$_POST["1"]."\n";
fwrite($handle,$data);
}
if($_POST["2"] != "on")
{
$data = "SLHA:keepSM = ".$_POST["2"]."\n";
fwrite($handle,$data);
}
if($_POST["3"] != "100.0")
{
$data = "SLHA:minMassSM = ".$_POST["3"]."\n";
fwrite($handle,$data);
}
if($_POST["4"] != "off")
{
$data = "SLHA:NMSSM = ".$_POST["4"]."\n";
fwrite($handle,$data);
}
fclose($handle);
}

?>
</body>
</html>

<!-- Copyright (C) 2010 Torbjorn Sjostrand -->


