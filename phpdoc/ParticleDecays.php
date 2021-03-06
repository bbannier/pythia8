<html>
<head>
<title>Particle Decays</title>
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

<form method='post' action='ParticleDecays.php'>

<h2>Particle Decays</h2>

The <code>ParticleDecays</code> class performs the sequential decays of 
all unstable hadrons produced in the string fragmentation stage,
i.e. up to and including <i>b</i> hadrons and their decay products, 
such as the <i>tau</i> lepton. It is not to be used for the decay of 
more massive <?php $filepath = $_GET["filepath"];
echo "<a href='ResonanceDecays.php?filepath=".$filepath."' target='page'>";?>resonances</a>, such as top, 
<i>Z^0</i> or SUSY, where decays must be performed already at the 
<code>ProcessLevel</code> of the event generation.

<p/>
The decay description essentially copies the one present in 
PYTHIA since many years, but with some improvements, e.g. in the decay
tables and the number of decay models available. Some issues may need 
further polishing.

<h3>Variables determining whether a particle decays</h3>

Before a particle is actually decayed, a number of checks are made.

<p/>
(i) Decay modes must have been defined for the particle kind;    
tested by the <code>canDecay()</code> method of <code>Event</code> 
(and <code>ParticleData</code>).        

<p/>
(ii) The main switch for allowing this particle kind to decay must 
be on; tested by the <code>mayDecay()</code> method of <code>Event</code> 
(and <code>ParticleData</code>). 

<p/>
(iii) Particles may be requested to have a nominal proper lifetime 
<i>tau0</i> below a threshold.

<br/><br/><strong>ParticleDecays:limitTau0</strong>  <input type="radio" name="1" value="on"><strong>On</strong>
<input type="radio" name="1" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
When on, only particles with <i>tau0 &lt; tau0Max</i> are decayed.
  

<br/><br/><table><tr><td><strong>ParticleDecays:tau0Max </td><td></td><td> <input type="text" name="2" value="10." size="20"/>  &nbsp;&nbsp;(<code>default = <strong>10.</strong></code>; <code>minimum = 0.</code>)</td></tr></table>
The above <i>tau0Max</i>, expressed in mm/c.
  

<p/>
(iv) Particles may be requested to have an actual proper lifetime 
<i>tau</i> below a threshold.

<br/><br/><strong>ParticleDecays:limitTau</strong>  <input type="radio" name="3" value="on"><strong>On</strong>
<input type="radio" name="3" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
When on, only particles with <i>tau &lt; tauMax</i> are decayed.
  

<br/><br/><table><tr><td><strong>ParticleDecays:tauMax </td><td></td><td> <input type="text" name="4" value="10." size="20"/>  &nbsp;&nbsp;(<code>default = <strong>10.</strong></code>; <code>minimum = 0.</code>)</td></tr></table>
The above <i>tauMax</i>, expressed in mm/c.<br/>
In order for this and the subsequent tests to work, a <i>tau</i> 
is selected and stored for each particle, whether in the end it
decays or not. (If each test would use a different temporary 
<i>tau</i> it would lead to inconsistencies.)
  

<p/>
(v) Particles may be requested to decay within a given distance 
of the origin.

<br/><br/><strong>ParticleDecays:limitRadius</strong>  <input type="radio" name="5" value="on"><strong>On</strong>
<input type="radio" name="5" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
When on, only particles with a decay within a radius <i>r &lt; rMax</i> 
are decayed. There is assumed to be no magnetic field or other 
detector effects.
  

<br/><br/><table><tr><td><strong>ParticleDecays:rMax </td><td></td><td> <input type="text" name="6" value="10." size="20"/>  &nbsp;&nbsp;(<code>default = <strong>10.</strong></code>; <code>minimum = 0.</code>)</td></tr></table>
The above <i>rMax</i>, expressed in mm.
   

<p/>
(vi) Particles may be requested to decay within a given cylidrical 
volume around the origin.

<br/><br/><strong>ParticleDecays:limitCylinder</strong>  <input type="radio" name="7" value="on"><strong>On</strong>
<input type="radio" name="7" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
When on, only particles with a decay within a volume limited by
<i>rho = sqrt(x^2 + y^2) &lt; xyMax</i> and <i>|z| &lt; zMax</i> 
are decayed. There is assumed to be no magnetic field or other 
detector effects.
  

<br/><br/><table><tr><td><strong>ParticleDecays:xyMax </td><td></td><td> <input type="text" name="8" value="10." size="20"/>  &nbsp;&nbsp;(<code>default = <strong>10.</strong></code>; <code>minimum = 0.</code>)</td></tr></table>
The above <i>xyMax</i>, expressed in mm.
   

<br/><br/><table><tr><td><strong>ParticleDecays:zMax </td><td></td><td> <input type="text" name="9" value="10." size="20"/>  &nbsp;&nbsp;(<code>default = <strong>10.</strong></code>; <code>minimum = 0.</code>)</td></tr></table>
The above <i>zMax</i>, expressed in mm.
   

<h3>Mixing</h3>

<br/><br/><strong>ParticleDecays:mixB</strong>  <input type="radio" name="10" value="on" checked="checked"><strong>On</strong>
<input type="radio" name="10" value="off"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>on</strong></code>)<br/>
Allow or not <i>B^0 - B^0bar</i> and <i>B_s^0 - B_s^0bar</i> mixing.
  

<br/><br/><table><tr><td><strong>ParticleDecays:xBdMix </td><td></td><td> <input type="text" name="11" value="0.776" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>0.776</strong></code>; <code>minimum = 0.74</code>; <code>maximum = 0.81</code>)</td></tr></table>
The mixing parameter <i>x_d = Delta(m_B^0)/Gamma_B^0</i> in the 
<i>B^0 - B^0bar</i> system. (Default from RPP2006.)
   

<br/><br/><table><tr><td><strong>ParticleDecays:xBsMix </td><td></td><td> <input type="text" name="12" value="26.05" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>26.05</strong></code>; <code>minimum = 22.0</code>; <code>maximum = 30.0</code>)</td></tr></table>
The mixing parameter <i>x_s = Delta(m_B_s^0)/Gamma_B_s^0</i> in the 
<i>B_s^0 - B_s^0bar</i> system. (Delta-m from CDF hep-ex-0609040,
Gamma from RPP2006.)
   

<h3>Other variables</h3>

<br/><br/><table><tr><td><strong>ParticleDecays:mSafety </td><td></td><td> <input type="text" name="13" value="0.0005" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>0.0005</strong></code>; <code>minimum = 0.</code>; <code>maximum = 0.01</code>)</td></tr></table>
Minimum mass difference required between the decaying mother mass 
and the sum of the daughter masses, kept as a safety margin to avoid
numerical problems in the decay generation.
   

<br/><br/><table><tr><td><strong>ParticleDecays:sigmaSoft </td><td></td><td> <input type="text" name="14" value="0.5" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>0.5</strong></code>; <code>minimum = 0.2</code>; <code>maximum = 2.</code>)</td></tr></table>
In semileptonic decays to more than one hadron, such as 
<i>B -> nu l D pi</i>, decay products after the first three are 
dampened in momentum by an explicit weight factor 
<i>exp(-p^2/sigmaSoft^2)</i>, where <i>p</i> is the 
three-momentum in the rest frame of the decaying particle.
This takes into account that such further particles come from the
fragmentation of the spectator parton and thus should be soft.   
   

<p/>
When a decay mode is defined in terms of a partonic content, a random 
multiplicity (and a random flavour set) of hadrons is to be picked, 
especially for some charm and bottom decays. This is done according to 
a Poissonian distribution, for <i>n_p</i> normal particles and 
<i>n_q</i> quarks the average value is chosen as  
<br/><i>
  n_p/ 2 + n_q/4 + multIncrease * ln ( mDiff / multRefMass)
</i><br/>
with <i>mDiff</i> the difference between the decaying particle mass 
and the sum of the normal-particle masses and the constituent quark masses. 
For gluonic systems <i>multGoffset</i> offers and optional additional 
term to the multiplicity. The lowest possible multiplicity is 
<i>n_p + n_q/2</i> (but at least 2) and the highest possible 10.
If the picked hadrons have a summed mass above that of the mother a 
new try is made, including a new multiplicity. These constraints 
imply that the actual average multiplicity does not quite agree with
the formula above.

<br/><br/><table><tr><td><strong>ParticleDecays:multIncrease </td><td></td><td> <input type="text" name="15" value="4.5" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>4.5</strong></code>; <code>minimum = 3.</code>; <code>maximum = 6.</code>)</td></tr></table>
The above <i>multIncrease</i> parameter.
   

<br/><br/><table><tr><td><strong>ParticleDecays:multRefMass </td><td></td><td> <input type="text" name="16" value="0.7" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>0.7</strong></code>; <code>minimum = 0.2</code>; <code>maximum = 2.0</code>)</td></tr></table>
The above <i>multRefMass</i> parameter.
   

<br/><br/><table><tr><td><strong>ParticleDecays:multGoffset </td><td></td><td> <input type="text" name="17" value="0.5" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>0.5</strong></code>; <code>minimum = 0.0</code>; <code>maximum = 2.0</code>)</td></tr></table>
The above <i>multGoffset</i> parameter.
   

<br/><br/><table><tr><td><strong>ParticleDecays:colRearrange </td><td></td><td> <input type="text" name="18" value="0.5" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>0.5</strong></code>; <code>minimum = 0.</code>; <code>maximum = 1.0</code>)</td></tr></table>
When a decay is given as a list of four partons to be turned into
hadrons (primarily for modes 41 - 80)  it is assumed that they are 
listed in pairs, as a first and a second colour singlet, which could 
give rise to separate sets of hadrons. Here <i>colRearrange</i> is 
the probability that this original assignment is not respected, and 
default corresponds to no memory of this original colour topology.
   

<br/><br/><strong>ParticleDecays:FSRinDecays</strong>  <input type="radio" name="19" value="on"><strong>On</strong>
<input type="radio" name="19" value="off"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>true</strong></code>)<br/>
When a particle decays to <i>q qbar</i>, <i>g g</i>, <i>g g g</i> 
or <i>gamma g g</i>, with <code>meMode > 90</code>, allow or not a 
shower to develop from it, before the partonic system is hadronized. 
(The typical example is <i>Upsilon</i> decay.)
  

In addition, some variables defined for string fragmentation and for
flavour production are used also here.
 
<h3>Modes for Matrix Element Processing</h3>

Some decays can be treated better than what pure phase space allows,
by reweighting with appropriate matrix elements. In others a partonic
content has to be converted to a set of hadrons. The presence of such
corrections is signalled by a nonvanishing <code>meMode()</code> value
for a decay mode in the <?php $filepath = $_GET["filepath"];
echo "<a href='ParticleDataScheme.php?filepath=".$filepath."' target='page'>";?>particle
data table</a>. The list of allowed possibilities almost agrees with the 
PYTHIA 6 ones, but several obsolete choices have been removed, 
a few new introduced, and most have been moved for better consistency. 
Here is the list of currently allowed <code>meMode()</code> codes:
<ul>
<li>  0 : pure phase space of produced particles ("default");
input of partons is allowed and then the partonic content is 
converted into the minimal number of hadrons (i.e. one per
parton pair, but at least two particles in total)</li>
<li>  1 : <i>omega</i> and <i>phi -> pi+ pi- pi0</i></li>
<li>  2 : polarization in <i>V -> PS + PS</i> (<i>V</i> = vector, 
<i>PS</i> = pseudoscalar), when <i>V</i> is produced by 
<i>PS -> PS + V</i> or <i>PS -> gamma + V</i></li>
<li> 11 : Dalitz decay into one particle, in addition to the 
lepton pair (also allowed to specify a quark-antiquark pair that 
should collapse to a single hadron)</li>
<li> 12 : Dalitz decay into two or more particles in addition 
to the lepton pair</li>
<li> 13 : double Dalitz decay into two lepton pairs</li>
<li> 21 : decay to phase space, but weight up <i>neutrino_tau</i> spectrum
in <i>tau</i> decay</li>
<li> 22 : weak decay; if there is a quark spectator system it collapses to 
one hadron; for leptonic/semileptonic decays the <i>V-A</i> matrix element
is used, for hadronic decays simple phase space</li>
<li> 23 : as 22, but require at least three particles in decay</li>
<li> 31 : decays of type B -> gamma X, very primitive simulation where
X is given in terms of its flavour content, the X multiplicity is picked 
according to a geometrical distribution with average number 2, and 
the photon energy spectrum is weighted up relative to pure phase space</li>
<li> 42 - 50 : turn partons into a random number of hadrons, picked according 
to a Poissonian with average value as described above, but at least 
<code>code</code> - 40 and at most 10, and then distribute then in pure 
phase space; make a new try with another multiplicity if the sum of daughter
masses exceed the mother one </li>
<li> 52 - 60 : as 42 - 50, with multiplicity between <code>code</code> - 50 
and 10, but avoid already explicitly listed non-partonic channels</li>
<li> 62 - 70 : as 42 - 50, but fixed multiplicity <code>code</code> - 60</li>
<li> 72 - 80 : as 42 - 50, but fixed multiplicity <code>code</code> - 70,
and avoid already explicitly listed non-partonic channels</li>
<li> 91 : decay to <i>q qbar</i> or <i>g g</i>, which should shower 
and hadronize</li>
<li> 92 : decay onium to <i>g g g</i> or <i>g g gamma</i> 
(with matrix element), which should shower and hadronize</li>
<li> 100 - : reserved for the description of partial widths of 
<?php $filepath = $_GET["filepath"];
echo "<a href='ResonanceDecays.php?filepath=".$filepath."' target='page'>";?>resonances</a></li>
</ul>

Three special decay product identity codes are defined.
<ul>
<li>81: remnant flavour. Used for weak decays of c and b hadrons, where the
c or b quark decays and the other quarks are considered as a spectator
remnant in this decay. In practice only used for baryons with multiple 
c and b quarks, which presumably would never be used, but have simple
(copied) just-in-case decay tables. Assumed to be last decay product.</li> 
<li>82: random flavour, picked by the standard fragmentation flavour
machinery, used to start a sequence of hadrons, for matrix element
codes in 41 - 80. Assumed to be first decay product, with -82 as second
and last. Where multiplicity is free to be picked it is selected as for
normal quarkonic systems. Currently unused.</li>  
<li>83: as for 82, with matched pair 83, -83 of decay products. The 
difference is that here the pair is supposed to come from a closed gluon 
loop (e.g. <i>eta_c -> g g</i>) and so have a somewhat higher average
multiplicity than the simple string assumed for 82, see the
<code>ParticleDecays:multGoffset</code> parameter above.</li>
</ul>

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

if($_POST["1"] != "off")
{
$data = "ParticleDecays:limitTau0 = ".$_POST["1"]."\n";
fwrite($handle,$data);
}
if($_POST["2"] != "10.")
{
$data = "ParticleDecays:tau0Max = ".$_POST["2"]."\n";
fwrite($handle,$data);
}
if($_POST["3"] != "off")
{
$data = "ParticleDecays:limitTau = ".$_POST["3"]."\n";
fwrite($handle,$data);
}
if($_POST["4"] != "10.")
{
$data = "ParticleDecays:tauMax = ".$_POST["4"]."\n";
fwrite($handle,$data);
}
if($_POST["5"] != "off")
{
$data = "ParticleDecays:limitRadius = ".$_POST["5"]."\n";
fwrite($handle,$data);
}
if($_POST["6"] != "10.")
{
$data = "ParticleDecays:rMax = ".$_POST["6"]."\n";
fwrite($handle,$data);
}
if($_POST["7"] != "off")
{
$data = "ParticleDecays:limitCylinder = ".$_POST["7"]."\n";
fwrite($handle,$data);
}
if($_POST["8"] != "10.")
{
$data = "ParticleDecays:xyMax = ".$_POST["8"]."\n";
fwrite($handle,$data);
}
if($_POST["9"] != "10.")
{
$data = "ParticleDecays:zMax = ".$_POST["9"]."\n";
fwrite($handle,$data);
}
if($_POST["10"] != "on")
{
$data = "ParticleDecays:mixB = ".$_POST["10"]."\n";
fwrite($handle,$data);
}
if($_POST["11"] != "0.776")
{
$data = "ParticleDecays:xBdMix = ".$_POST["11"]."\n";
fwrite($handle,$data);
}
if($_POST["12"] != "26.05")
{
$data = "ParticleDecays:xBsMix = ".$_POST["12"]."\n";
fwrite($handle,$data);
}
if($_POST["13"] != "0.0005")
{
$data = "ParticleDecays:mSafety = ".$_POST["13"]."\n";
fwrite($handle,$data);
}
if($_POST["14"] != "0.5")
{
$data = "ParticleDecays:sigmaSoft = ".$_POST["14"]."\n";
fwrite($handle,$data);
}
if($_POST["15"] != "4.5")
{
$data = "ParticleDecays:multIncrease = ".$_POST["15"]."\n";
fwrite($handle,$data);
}
if($_POST["16"] != "0.7")
{
$data = "ParticleDecays:multRefMass = ".$_POST["16"]."\n";
fwrite($handle,$data);
}
if($_POST["17"] != "0.5")
{
$data = "ParticleDecays:multGoffset = ".$_POST["17"]."\n";
fwrite($handle,$data);
}
if($_POST["18"] != "0.5")
{
$data = "ParticleDecays:colRearrange = ".$_POST["18"]."\n";
fwrite($handle,$data);
}
if($_POST["19"] != "true")
{
$data = "ParticleDecays:FSRinDecays = ".$_POST["19"]."\n";
fwrite($handle,$data);
}
fclose($handle);
}

?>
</body>
</html>

<!-- Copyright (C) 2010 Torbjorn Sjostrand -->

