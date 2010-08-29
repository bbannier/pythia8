<html>
<head>
<title>Diffraction</title>
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

<form method='post' action='Diffraction.php'>

<h2>Diffraction</h2>

<h3>Introduction</h3>

Diffraction is not well understood, and several alternative approaches
have been proposed. Here we follw a fairly conventional Pomeron-based
one, but integrated to make full use of the standard PYTHIA machinery
for multiple interactions, parton showers and hadronization. This
is the approach pioneered in the PomPyt program by 
Ingelman and collaborators [<a href="Bibliography.php" target="page">Ing97</a>].

<p/>
For ease of use (and of modelling), the Pomeron-specific parts of the 
generation are subdivided into three sets of parameters that are rather 
independent of each other:
<br/>(i) the total, elastic and diffractive cross sections are 
parametrized as functions of the CM energy, or can be set by the user
to the desired values, see the
<?php $filepath = $_GET["filepath"];
echo "<a href='TotalCrossSections.php?filepath=".$filepath."' target='page'>";?>Total Cross Sections</a> page; 
<br/>(ii) once it has been decided to have a diffractive process,
a Pomeron flux parametrization is used to pick the mass of the 
diffractive system(s) and the <i>t</i> of the exchanged Pomeron,
see below;
<br/>(iii) a diffractive system of a given mass is classified either
as low-mass unresolved, which gives a simple low-<i>pT</i> string
topology, or as high-mass resolved, for which the full machinery of 
multiple interactions and parton showers are applied, making use of
<?php $filepath = $_GET["filepath"];
echo "<a href='PDFSelection.php?filepath=".$filepath."' target='page'>";?>Pomeron PDFs</a>.
<br/>The parameters related to multiple interactions, parton showers
and hadronization are kept the same as for normal nondiffractive events,
with only one exception. This may be questioned, especially for the 
multiple interactions, but we do not believe that there are currently 
enough good diffractive data that would allow detailed separate tunes. 
 
<p/>
The above subdivision may not represent the way "physics comes about". 
For instance, the total diffractive cross section can be viewed as a 
convolution of a Pomeron flux with a Pomeron-proton total cross section. 
Since neither of the two is known from first principles there will be 
a significant amount of ambiguity in the flux factor. The picture is 
further complicated by the fact that the possibility of simultaneous 
further multiple interactions ("cut Pomerons") will screen the rate of 
diffractive systems. In the end, our set of parameters refers to the
effective description that emerges out of these effects, rather than 
to the underlying "bare" parameters.  

<h3>Pomeron flux</h3>

As already mentioned above, the total diffractive cross section is fixed 
by a default energy-dependent parametrization or by the user, see the
<?php $filepath = $_GET["filepath"];
echo "<a href='TotalCrossSections.php?filepath=".$filepath."' target='page'>";?>Total Cross Sections</a> page.
Therefore we do not attribute any significance to the absolute 
normalization of the Pomeron flux. The choice of Pomeron flux model 
still will decide on the mass spectrum of diffractive states and the 
<i>t</i> spectrum of the Pomeron exchange.

<br/><br/><table><tr><td><strong>Diffraction:PomFlux  </td><td>  &nbsp;&nbsp;(<code>default = <strong>1</strong></code>; <code>minimum = 1</code>; <code>maximum = 4</code>)</td></tr></table>
Parametrization of the Pomeron flux <ei>f_Pom/p( x_Pom, t)</ei>.
<br/>
<input type="radio" name="1" value="1" checked="checked"><strong>1 </strong>: Schuler and Sj&ouml;strand <ref>Sch94</ref>: based on a  critical Pomeron, giving a mass spectrum roughly like <ei>dm^2/m^2</ei>; a mass-dependent exponential <ei>t</ei> slope that reduces the rate  of low-mass states; partly compensated by a very-low-mass (resonance region)  enhancement. Is currently the only one that contains a separate  <ei>t</ei> spectrum for double diffraction and separate parameters for pion beams.<br/>
<input type="radio" name="1" value="2"><strong>2 </strong>: Bruni and Ingelman <ref>Bru93</ref>: also a critical Pomeron giving close to <ei>dm^2/m^2</ei>,  with a <ei>t</ei> distribution  the sum of two exponentials.  <br/>
<input type="radio" name="1" value="3"><strong>3 </strong>: a conventional Pomeron description, in the RapGap manual <ref>Jun95</ref> attributed to Berger et al. and Streng  <ref>Ber87a</ref>, but there (and here) with values updated to a  supercritical Pomeron with <ei>epsilon &gt; 0</ei> (see below),  which gives a stronger peaking towards low-mass diffractive states,  and with a mass-dependent (the <ei>alpha'</ei> below) exponential  <ei>t</ei> slope.<br/>
<input type="radio" name="1" value="4"><strong>4 </strong>: a conventional Pomeron description, attributed to Donnachie and Landshoff <ref>Don84</ref>, again with supercritical Pomeron,  with the same two parameters as option 3 above, but this time with a  power-law <ei>t</ei> distribution.<br/>

<p/>
In the last two options above, the Pomeron Regge trajectory is
parametrized as 
<br/><i>
alpha(t) = 1 + epsilon + alpha' t
</i><br/>
The <i>epsilon</i> and <i>alpha'</i> parameters can be set 
separately:

<br/><br/><table><tr><td><strong>Diffraction:PomFluxEpsilon </td><td></td><td> <input type="text" name="2" value="0.085" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>0.085</strong></code>; <code>minimum = 0.02</code>; <code>maximum = 0.15</code>)</td></tr></table>
The Pomeron trajectory intercept <i>epsilon</i> above. For technical
reasons <i>epsilon &gt; 0</i> is necessary in the current implementation.

<br/><br/><table><tr><td><strong>Diffraction:PomFluxAlphaPrime </td><td></td><td> <input type="text" name="3" value="0.25" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>0.25</strong></code>; <code>minimum = 0.1</code>; <code>maximum = 0.4</code>)</td></tr></table>
The Pomeron trajectory slope <i>alpha'</i> above. 


<h3>Separation into low and high masses</h3>

Preferably one would want to have a perturbative picture of the 
dynamics of Pomeron-proton collisions, like multiple interactions
provide for proton-proton ones. However, while PYTHIA by default
will only allow collisions with a CM energy above 10 GeV, the 
mass spectrum of diffractive systems will stretch to down to 
the order of 1.2 GeV. It would not be feasible to attempt a 
perturbative description there. Therefore we do offer a simpler
low-mass description, with only longitudinally stretched strings,
with a gradual switch-over to the perturbative picture for higher
masses. The probability for the latter picture is parametrized as
<br/><i>
P_pert = 1 - exp( (m_diffr - m_min) / m_width )
</i><br/> 
which vanishes for the diffractive system mass 
<i>m_diffr &lt; m_min</i>, and is <i>1 - 1/e = 0.632</i> for
<i>m_diffr = m_min + m_width</i>.

<br/><br/><table><tr><td><strong>Diffraction:mMinPert </td><td></td><td> <input type="text" name="4" value="10." size="20"/>  &nbsp;&nbsp;(<code>default = <strong>10.</strong></code>; <code>minimum = 5.</code>)</td></tr></table>
The abovementioned threshold mass <i>m_min</i> for phasing in a
perturbative treatment. If you put this parameter to be bigger than 
the CM energy then there will be no perturbative description at all, 
but only the older low-<i>pt</i> description.
  

<br/><br/><table><tr><td><strong>Diffraction:mWidthPert </td><td></td><td> <input type="text" name="5" value="10." size="20"/>  &nbsp;&nbsp;(<code>default = <strong>10.</strong></code>; <code>minimum = 0.</code>)</td></tr></table>
The abovementioned threshold width <i>m_width.</i>
  

<h3>Low-mass diffraction</h3>

When an incoming hadron beam is diffractively excited, it is modeled 
as if either a valence quark or a gluon is kicked out from the hadron.
In the former case this produces a simple string to the leftover 
remnant, in the latter it gives a hairpin arrangement where a string
is stretched from one quark in the remnant, via the gluon, back to the   
rest of the remnant. The latter ought to dominate at higher mass of 
the diffractive system. Therefore an approximate behaviour like 
<br/><i>
P_q / P_g = N / m^p
</i><br/> 
is assumed.

<br/><br/><table><tr><td><strong>Diffraction:pickQuarkNorm </td><td></td><td> <input type="text" name="6" value="5.0" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>5.0</strong></code>; <code>minimum = 0.</code>)</td></tr></table>
The abovementioned normalization <i>N</i> for the relative quark
rate in diffractive systems.
  

<br/><br/><table><tr><td><strong>Diffraction:pickQuarkPower </td><td></td><td> <input type="text" name="7" value="1.0" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>1.0</strong></code>; <code>minimum = 0.</code>)</td></tr></table>
The abovementioned mass-dependence power <i>p</i> for the relative 
quark rate in diffractive systems.
  

<p/>
When a gluon is kicked out from the hadron, the longitudinal momentum
sharing between the the two remnant partons is determined by the
same parameters as above. It is plausible that the primordial 
<i>kT</i> may be lower than in perturbative processes, however:

<br/><br/><table><tr><td><strong>Diffraction:primKTwidth </td><td></td><td> <input type="text" name="8" value="0.5" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>0.5</strong></code>; <code>minimum = 0.</code>)</td></tr></table>
The width of Gaussian distributions in <i>p_x</i> and <i>p_y</i> 
separately that is assigned as a primordial <i>kT</i> to the two 
beam remnants when a gluon is kicked out of a diffractive system.
  

<br/><br/><table><tr><td><strong>Diffraction:largeMassSuppress </td><td></td><td> <input type="text" name="9" value="2." size="20"/>  &nbsp;&nbsp;(<code>default = <strong>2.</strong></code>; <code>minimum = 0.</code>)</td></tr></table>
The choice of longitudinal and transverse structure of a diffractive
beam remnant for a kicked-out gluon implies a remnant mass 
<i>m_rem</i> distribution (i.e. quark plus diquark invariant mass 
for a baryon beam) that knows no bounds. A suppression like 
<i>(1 - m_rem^2 / m_diff^2)^p</i> is therefore introduced, where 
<i>p</i> is the <code>diffLargeMassSuppress</code> parameter.    
  

<h3>High-mass diffraction</h3>

The perturbative description need to use parton densities of the 
Pomeron. The options are described in the page on
<?php $filepath = $_GET["filepath"];
echo "<a href='PDFSelection.php?filepath=".$filepath."' target='page'>";?>PDF Selection</a>. The standard
perturbative multiple interactions framework then provides 
cross sections for parton-parton interactions. In order to
turn these cross section into probabilities one also needs an
ansatz for the Pomeron-proton total cross section. In the literature
one often finds low numbers for this, of the order of 2 mb. 
These, if taken at face value, would give way too much activity
per event. There are ways to tame this, e.g. by a larger <i>pT0</i>
than in the normal pp framework. Actually, there are many reasons
to use a completely different set of parameters for MI in 
diffraction than in pp collisions, e.g. with respect to the 
impact-parameter picture. A lower number in some frameworks could 
alternatively be regarded as a consequence of screening, with 
a larger "bare" number.   

<p/>
For now, however, an attempt at the most general solution would 
carry too far, and instead we patch up the problem by using a 
larger Pomeron-proton total cross section, such that average 
activity makes more sense. This should be viewed as the main 
tunable parameter in the description of high-mass diffraction.
It is to be fitted to diffractive event-shape data such as the average 
charged multiplicity. It would be very closely tied to the choice of 
Pomeron PDF; we remind that some of these add up to less than unit
momentum sum in the Pomeron, a choice that also affect the value
one ends up with.

<br/><br/><table><tr><td><strong>Diffraction:sigmaPomP </td><td></td><td> <input type="text" name="10" value="10." size="20"/>  &nbsp;&nbsp;(<code>default = <strong>10.</strong></code>; <code>minimum = 2.</code>; <code>maximum = 40.</code>)</td></tr></table>
The assumed Pomeron-proton effective cross section, as used for
multiple interactions in diffractive systems. A larger value gives
less MI activity per event. 
  

There is no point in making the cross section too big, however, since 
then <i>pT0</i> will be adjusted downwards to ensure that the 
integrated perturbative cross section stays above this assumed 
total cross section. (The requirement of at least one perturbative 
interaction per event.)

<p/> 
Also note that, even for a fixed CM energy of events, the diffractive
subsystem will range from the abovementioned threshold mass 
<i>m_min</i> to the full CM energy, with a variation of parameters
such as <i>pT0</i> along this mass range. Therefore multiple 
interactions are initialized for a few different diffractive masses,
currently five, and all relevant parameters are interpolated between
them to obtain the behaviour at a specific diffractive mass. 
Furthermore, <i>A B -&gt;X B</i> and <i>A B -&gt;A X</i> are
initialized separately, to allow for different beams or PDF's on the 
two sides. These two aspects mean that initialization of MI is 
appreciably slower when perturbative high-mass diffraction is allowed. 

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

if($_POST["1"] != "1")
{
$data = "Diffraction:PomFlux = ".$_POST["1"]."\n";
fwrite($handle,$data);
}
if($_POST["2"] != "0.085")
{
$data = "Diffraction:PomFluxEpsilon = ".$_POST["2"]."\n";
fwrite($handle,$data);
}
if($_POST["3"] != "0.25")
{
$data = "Diffraction:PomFluxAlphaPrime = ".$_POST["3"]."\n";
fwrite($handle,$data);
}
if($_POST["4"] != "10.")
{
$data = "Diffraction:mMinPert = ".$_POST["4"]."\n";
fwrite($handle,$data);
}
if($_POST["5"] != "10.")
{
$data = "Diffraction:mWidthPert = ".$_POST["5"]."\n";
fwrite($handle,$data);
}
if($_POST["6"] != "5.0")
{
$data = "Diffraction:pickQuarkNorm = ".$_POST["6"]."\n";
fwrite($handle,$data);
}
if($_POST["7"] != "1.0")
{
$data = "Diffraction:pickQuarkPower = ".$_POST["7"]."\n";
fwrite($handle,$data);
}
if($_POST["8"] != "0.5")
{
$data = "Diffraction:primKTwidth = ".$_POST["8"]."\n";
fwrite($handle,$data);
}
if($_POST["9"] != "2.")
{
$data = "Diffraction:largeMassSuppress = ".$_POST["9"]."\n";
fwrite($handle,$data);
}
if($_POST["10"] != "10.")
{
$data = "Diffraction:sigmaPomP = ".$_POST["10"]."\n";
fwrite($handle,$data);
}
fclose($handle);
}

?>
</body>
</html>

<!-- Copyright (C) 2010 Torbjorn Sjostrand -->
