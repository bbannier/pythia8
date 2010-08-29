<html>
<head>
<title>Hidden Valley Processes</title>
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

<form method='post' action='HiddenValleyProcesses.php'>

<h2>Hidden Valley Processes</h2>

This Hidden Valley (HV) scenario has been developed specifically 
to allow the study of visible consequences of radiation in a 
hidden sector, by recoil effect. A key aspect is therefore that 
the normal timelike showering machinery has been expanded with a 
third kind of radiation, in addition to the QCD and QED ones.
These three kinds of radiation are fully interleaved, i.e.
evolution occurs in a common <i>pT</i>-ordered sequence.
The scenario is described in [<a href="Bibliography.php" target="page">Car10</a>].

<h2>Particle content and properties</h2>

For simplicity we assume that the HV contains an unbroken <b>SU(N)</b> 
gauge symmetry. This is used in the calculation of production cross 
sections. These could be rescaled by hand for other gauge groups.
 
<br/><br/><table><tr><td><strong>HiddenValley:Ngauge  </td><td></td><td> <input type="text" name="1" value="3" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>3</strong></code>; <code>minimum = 1</code>)</td></tr></table>
is <b>U(1)</b> for <code>Ngauge = 1</code>, is <b>SU(N)</b> if 
<code>Ngauge &gt; 1</code>. Note that pair production cross sections 
contains a factor of <code>Ngauge</code> for new particles
in the fundamental representation of this group.
  

<p/>
A minimal HV particle content has been introduced. Firstly, there is
a set of 12 particles that mirrors the Standard Model flavour 
structure, and is charged under both the SM and the HV symmetry groups. 
Each new particle couples flavour-diagonally to a corresponding SM 
state, and has the same SM charge and colour, but in addition is in 
the fundamental representation of the HV colour, as follows:
<br/><code>Dv</code>, identity 4900001, partner to the normal
<code>d</code> quark;
<br/><code>Uv</code>, identity 4900002, partner to the normal
<code>u</code> quark;
<br/><code>Sv</code>, identity 4900003, partner to the normal
<code>s</code> quark;
<br/><code>Cv</code>, identity 4900004, partner to the normal
<code>c</code> quark;
<br/><code>Bv</code>, identity 4900005, partner to the normal
<code>b</code> quark;
<br/><code>Tv</code>, identity 4900006, partner to the normal
<code>t</code> quark;
<br/><code>Ev</code>, identity 4900011, partner to the normal
<code>e</code> lepton;
<br/><code>nuEv</code>, identity 4900012, partner to the normal
<code>nue</code> neutrino;
<br/><code>MUv</code>, identity 4900013, partner to the normal
<code>mu</code> lepton;
<br/><code>nuMUv</code>, identity 4900014, partner to the normal
<code>numu</code> neutrino;
<br/><code>TAUv</code>, identity 4900015, partner to the normal
<code>tau</code> lepton;
<br/><code>nuTAUv</code>, identity 4900016, partner to the normal
<code>nutau</code> neutrino.
<br/>Collectively we will refer to these states as <code>Fv</code>;
note, however, that they need not be fermions themselves.

<p/>
In addition the model contains the HV gauge particle, either 
a HV gluon or a HV photon, but not both; see <code>Ngauge</code>
above:
<br/><code>gv</code>, identity 4900021, is the massless 
gauge boson of the HV <b>SU(N)</b> group;
<br/><code>gammav</code>, identity 4900022,  is the massless 
gauge boson of the HV <b>U(1)</b> group.

<p/>
Finally, there is a new massive particle with only HV charge sitting 
in the fundamental representation of the HV gauge group:
<br/><code>qv</code>, identity 4900101.

<p/>The typical scenario would be for pair production of one of the
states presented first above, e.g. <i>g g -> Dv Dvbar</i>.
Such a <i>Dv</i> can radiate gluons and photons like an SM quark,
but in addition HV gluons or HV photons in a similar fashion.
Eventually the <i>Dv</i> will decay like <i>Dv -> d + qv</i>.
The strength of this decay is not set as such, but is implicit in 
your choice of width for the <i>Dv</i> state.  
Thereafter the <i>d</i> and <i>qv</i> can radiate
further within their respective sectors. The fate of the 
<i>qv</i>, <i>gv</i> or <i>gammav</i>, once formed, 
is not considered further: they remain invisible.

<p/>
Only the spin of the HV gluon or HV photon is determined unambiguously
to be unity; for the others you can make your choice.
 
<br/><br/><table><tr><td><strong>HiddenValley:spinFv  </td><td>  &nbsp;&nbsp;(<code>default = <strong>1</strong></code>; <code>minimum = 0</code>; <code>maximum = 2</code>)</td></tr></table>
The spin of the HV partners of the SM fermions, e.g. 
<ei>Dv</ei>, <ei>Uv</ei>, <ei>Ev</ei> and <ei>nuEv</ei>.
<br/>
<input type="radio" name="2" value="0"><strong>0 </strong>: spin 0.<br/>
<input type="radio" name="2" value="1" checked="checked"><strong>1 </strong>: spin 1/2.<br/>
<input type="radio" name="2" value="2"><strong>2 </strong>: spin 1/2.<br/>
 
<br/><br/><table><tr><td><strong>HiddenValley:spinqv  </td><td>  &nbsp;&nbsp;(<code>default = <strong>0</strong></code>; <code>minimum = 0</code>; <code>maximum = 1</code>)</td></tr></table>
The spin of <ei>qv</ei> when the <ei>Fv</ei> (the HV partners of 
the SM fermions) have spin 1/2. (While, if they have spin 0 or 1, 
the <ei>qv</ei> spin is fixed at 1/2.) 
<br/>
<input type="radio" name="3" value="0" checked="checked"><strong>0 </strong>: spin 0.<br/>
<input type="radio" name="3" value="1"><strong>1 </strong>: spin 0.<br/>

<br/><br/><table><tr><td><strong>HiddenValley:kappa </td><td></td><td> <input type="text" name="4" value="1." size="20"/>  &nbsp;&nbsp;(<code>default = <strong>1.</strong></code>)</td></tr></table>
If the <i>Fv</i> have spin 1 then their production 
cross section depends on the presence of ananomalous magnetic dipole 
moment, i.e. of a <i>kappa</i> different from unity. For other spins
this parameter is not used.  
  
 
<p/>
You should set the <i>Fv</i> and <i>qv</i> masses appropriately, 
with the latter smaller than the former two to allow decays.

<h2>Production processes</h2>
  
<br/><br/><strong>HiddenValley:all</strong>  <input type="radio" name="5" value="on"><strong>On</strong>
<input type="radio" name="5" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Common switch for the group of all hard Hidden Valley processes, 
as listed separately in the following.
  
  
<br/><br/><strong>HiddenValley:gg2DvDvbar</strong>  <input type="radio" name="6" value="on"><strong>On</strong>
<input type="radio" name="6" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>g g -> Dv Dvbar</i>.
Code 4901.
  
  
<br/><br/><strong>HiddenValley:gg2UvUvbar</strong>  <input type="radio" name="7" value="on"><strong>On</strong>
<input type="radio" name="7" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>g g -> Uv Uvbar</i>.
Code 4902.
  
  
<br/><br/><strong>HiddenValley:gg2SvSvbar</strong>  <input type="radio" name="8" value="on"><strong>On</strong>
<input type="radio" name="8" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>g g -> Sv Svbar</i>.
Code 4903.
  
  
<br/><br/><strong>HiddenValley:gg2CvCvbar</strong>  <input type="radio" name="9" value="on"><strong>On</strong>
<input type="radio" name="9" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>g g -> Cv Cvbar</i>.
Code 4904.
  
  
<br/><br/><strong>HiddenValley:gg2BvBvbar</strong>  <input type="radio" name="10" value="on"><strong>On</strong>
<input type="radio" name="10" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>g g -> Bv Bvbar</i>.
Code 4905.
  
  
<br/><br/><strong>HiddenValley:gg2TvTvbar</strong>  <input type="radio" name="11" value="on"><strong>On</strong>
<input type="radio" name="11" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>g g -> Tv Tvbar</i>.
Code 4906.
  
  
<br/><br/><strong>HiddenValley:qqbar2DvDvbar</strong>  <input type="radio" name="12" value="on"><strong>On</strong>
<input type="radio" name="12" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>q qbar -> Dv Dvbar</i> 
via intermediate gluon.
Code 4911.
  
  
<br/><br/><strong>HiddenValley:qqbar2UvUvbar</strong>  <input type="radio" name="13" value="on"><strong>On</strong>
<input type="radio" name="13" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>q qbar -> Uv Uvbar</i>
via intermediate gluon.
Code 4912.
  
  
<br/><br/><strong>HiddenValley:qqbar2SvSvbar</strong>  <input type="radio" name="14" value="on"><strong>On</strong>
<input type="radio" name="14" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>q qbar -> Sv Svbar</i> 
via intermediate gluon.
Code 4913.
  
  
<br/><br/><strong>HiddenValley:qqbar2CvCvbar</strong>  <input type="radio" name="15" value="on"><strong>On</strong>
<input type="radio" name="15" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>q qbar -> Cv Cvbar</i>
via intermediate gluon.
Code 4914.
  
  
<br/><br/><strong>HiddenValley:qqbar2BvBvbar</strong>  <input type="radio" name="16" value="on"><strong>On</strong>
<input type="radio" name="16" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>q qbar -> Bv Bvbar</i> 
via intermediate gluon.
Code 4915.
  
  
<br/><br/><strong>HiddenValley:qqbar2TvTvbar</strong>  <input type="radio" name="17" value="on"><strong>On</strong>
<input type="radio" name="17" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>q qbar -> Tv Tvbar</i>
via intermediate gluon.
Code 4916.
  
  
<br/><br/><strong>HiddenValley:ffbar2DvDvbar</strong>  <input type="radio" name="18" value="on"><strong>On</strong>
<input type="radio" name="18" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>f fbar -> Dv Dvbar</i> 
via intermediate <i>gamma*/Z^*</i>.
Code 4921.
  
  
<br/><br/><strong>HiddenValley:ffbar2UvUvbar</strong>  <input type="radio" name="19" value="on"><strong>On</strong>
<input type="radio" name="19" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>f fbar -> Uv Uvbar</i>
via intermediate <i>gamma*/Z^*</i>. 
Code 4922.
  
  
<br/><br/><strong>HiddenValley:ffbar2SvSvbar</strong>  <input type="radio" name="20" value="on"><strong>On</strong>
<input type="radio" name="20" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>f fbar -> Sv Svbar</i> 
via intermediate <i>gamma*/Z^*</i>.
Code 4923.
  
  
<br/><br/><strong>HiddenValley:ffbar2CvCvbar</strong>  <input type="radio" name="21" value="on"><strong>On</strong>
<input type="radio" name="21" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>f fbar -> Cv Cvbar</i>
via intermediate <i>gamma*/Z^*</i>. 
Code 4924.
  
  
<br/><br/><strong>HiddenValley:ffbar2BvBvbar</strong>  <input type="radio" name="22" value="on"><strong>On</strong>
<input type="radio" name="22" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>f fbar -> Bv Bvbar</i> 
via intermediate <i>gamma*/Z^*</i>.
Code 4925.
  
  
<br/><br/><strong>HiddenValley:ffbar2TvTvbar</strong>  <input type="radio" name="23" value="on"><strong>On</strong>
<input type="radio" name="23" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>f fbar -> Tv Tvbar</i>
via intermediate <i>gamma*/Z^*</i>. 
Code 4926.
  
  
<br/><br/><strong>HiddenValley:ffbar2EvEvbar</strong>  <input type="radio" name="24" value="on"><strong>On</strong>
<input type="radio" name="24" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>f fbar -> Ev Evbar</i> 
via intermediate <i>gamma*/Z^*</i>.
Code 4931.
  
  
<br/><br/><strong>HiddenValley:ffbar2nuEvnuEvbar</strong>  <input type="radio" name="25" value="on"><strong>On</strong>
<input type="radio" name="25" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>f fbar -> nuEv nuEvbar</i>
via intermediate <i>gamma*/Z^*</i>. 
Code 4932.
  
    
<br/><br/><strong>HiddenValley:ffbar2MUvMUvbar</strong>  <input type="radio" name="26" value="on"><strong>On</strong>
<input type="radio" name="26" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>f fbar -> MUv MUvbar</i> 
via intermediate <i>gamma*/Z^*</i>.
Code 4933.
  
  
<br/><br/><strong>HiddenValley:ffbar2nuMUvnuMUvbar</strong>  <input type="radio" name="27" value="on"><strong>On</strong>
<input type="radio" name="27" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>f fbar -> nuMUv nuMUvbar</i>
via intermediate <i>gamma*/Z^*</i>. 
Code 4934.
  

<br/><br/><strong>HiddenValley:ffbar2TAUvTAUvbar</strong>  <input type="radio" name="28" value="on"><strong>On</strong>
<input type="radio" name="28" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>f fbar -> TAUv TAUvbar</i> 
via intermediate <i>gamma*/Z^*</i>.
Code 4935.
  
  
<br/><br/><strong>HiddenValley:ffbar2nuTAUvnuTAUvbar</strong>  <input type="radio" name="29" value="on"><strong>On</strong>
<input type="radio" name="29" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
Pair production <i>f fbar -> nuTAUv nuTAUvbar</i>
via intermediate <i>gamma*/Z^*</i>. 
Code 4936.
  

<h2>Timelike showers</h2>

One key point of this HV scenario is that radiation off the
HV-charged particles is allowed. This is done by the standard
final-state showering machinery. (HV particles are not produced 
in initial-state radiation.) All the (anti)particles <i>Fv</i>
and <i>qv</i> have one (negative) unit of HV charge. That is,
radiation closely mimics the one in QCD. Both QCD, QED and HV 
radiation are interleaved in one common sequence of decreasing 
emission <i>pT</i> scales. Each radiation kind defines a set of
dipoles, usually spanned between a radiating parton and its recoil
partner, such that the invariant mass of the pair is not changed
when a radiation occurs. This need not follow from trivial colour
assignments, but is often obvious. For instance,  in a decay 
<i>Qv -> q + qv</i> the QCD dipole is between the <i>q</i> and 
the hole after <i>Qv</i>, but <i>qv</i> becomes the recoiler 
should a radiation occur, while the role of <i>q</i> and <i>qv</i> 
is reversed for HV radiation. 

<p/>This also includes matrix-element corrections for a number 
of decay processes, with colour, spin and mass effects included 
[<a href="Bibliography.php" target="page">Nor01</a>]. They were calculated within the context of the 
particle content of the MSSM, however, which does not include spin 1 
particles with unit colour charge. In such cases spin 0 is assumed 
instead. By experience, the main effects come from mass and colour 
flow anyway, so this is not a bad approximation. (Furthermore the
MSSM formulae allow for <i>gamma_5</i> factors from wave 
functions or vertices; these are even less important.)

<p/>An emitted <i>gv</i> can branch in its turn, 
<i>gv -> gv + gv</i>. This radiation may affect momenta 
in the visible sector by recoil effect, but this is a minor 
effect relative to the primary emission of the <i>gv</i>. 

<br/><br/><strong>HiddenValley:FSR</strong>  <input type="radio" name="30" value="on"><strong>On</strong>
<input type="radio" name="30" value="off" checked="checked"><strong>Off</strong>
 &nbsp;&nbsp;(<code>default = <strong>off</strong></code>)<br/>
switch on final-state shower of <i>gv</i> or <i>gammav</i>  
in a HV production process.
  

<br/><br/><table><tr><td><strong>HiddenValley:alphaFSR </td><td></td><td> <input type="text" name="31" value="0.1" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>0.1</strong></code>; <code>minimum = 0.0</code>)</td></tr></table>
fixed alpha scale of <i>gv/gammav</i> emission; corresponds to 
<i>alpha_strong</i> of QCD or <i>alpha_em</i> of QED. For 
shower branchings such as <i>Dv -> Dv + gv</i> the coupling is 
multiplied by <i>C_F = (N^2 - 1) / (2 * N)</i> for an 
<b>SU(N)</b> group and for <i>gv -> gv + gv</i> by <i>N</i>.
  

<br/><br/><table><tr><td><strong>HiddenValley:pTminFSR </td><td></td><td> <input type="text" name="32" value="0.4" size="20"/>  &nbsp;&nbsp;(<code>default = <strong>0.4</strong></code>; <code>minimum = 0.1</code>)</td></tr></table>
lowest allowed <i>pT</i> of emission. Chosen with same default
as in normal QCD showers.
  

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

if($_POST["1"] != "3")
{
$data = "HiddenValley:Ngauge = ".$_POST["1"]."\n";
fwrite($handle,$data);
}
if($_POST["2"] != "1")
{
$data = "HiddenValley:spinFv = ".$_POST["2"]."\n";
fwrite($handle,$data);
}
if($_POST["3"] != "0")
{
$data = "HiddenValley:spinqv = ".$_POST["3"]."\n";
fwrite($handle,$data);
}
if($_POST["4"] != "1.")
{
$data = "HiddenValley:kappa = ".$_POST["4"]."\n";
fwrite($handle,$data);
}
if($_POST["5"] != "off")
{
$data = "HiddenValley:all = ".$_POST["5"]."\n";
fwrite($handle,$data);
}
if($_POST["6"] != "off")
{
$data = "HiddenValley:gg2DvDvbar = ".$_POST["6"]."\n";
fwrite($handle,$data);
}
if($_POST["7"] != "off")
{
$data = "HiddenValley:gg2UvUvbar = ".$_POST["7"]."\n";
fwrite($handle,$data);
}
if($_POST["8"] != "off")
{
$data = "HiddenValley:gg2SvSvbar = ".$_POST["8"]."\n";
fwrite($handle,$data);
}
if($_POST["9"] != "off")
{
$data = "HiddenValley:gg2CvCvbar = ".$_POST["9"]."\n";
fwrite($handle,$data);
}
if($_POST["10"] != "off")
{
$data = "HiddenValley:gg2BvBvbar = ".$_POST["10"]."\n";
fwrite($handle,$data);
}
if($_POST["11"] != "off")
{
$data = "HiddenValley:gg2TvTvbar = ".$_POST["11"]."\n";
fwrite($handle,$data);
}
if($_POST["12"] != "off")
{
$data = "HiddenValley:qqbar2DvDvbar = ".$_POST["12"]."\n";
fwrite($handle,$data);
}
if($_POST["13"] != "off")
{
$data = "HiddenValley:qqbar2UvUvbar = ".$_POST["13"]."\n";
fwrite($handle,$data);
}
if($_POST["14"] != "off")
{
$data = "HiddenValley:qqbar2SvSvbar = ".$_POST["14"]."\n";
fwrite($handle,$data);
}
if($_POST["15"] != "off")
{
$data = "HiddenValley:qqbar2CvCvbar = ".$_POST["15"]."\n";
fwrite($handle,$data);
}
if($_POST["16"] != "off")
{
$data = "HiddenValley:qqbar2BvBvbar = ".$_POST["16"]."\n";
fwrite($handle,$data);
}
if($_POST["17"] != "off")
{
$data = "HiddenValley:qqbar2TvTvbar = ".$_POST["17"]."\n";
fwrite($handle,$data);
}
if($_POST["18"] != "off")
{
$data = "HiddenValley:ffbar2DvDvbar = ".$_POST["18"]."\n";
fwrite($handle,$data);
}
if($_POST["19"] != "off")
{
$data = "HiddenValley:ffbar2UvUvbar = ".$_POST["19"]."\n";
fwrite($handle,$data);
}
if($_POST["20"] != "off")
{
$data = "HiddenValley:ffbar2SvSvbar = ".$_POST["20"]."\n";
fwrite($handle,$data);
}
if($_POST["21"] != "off")
{
$data = "HiddenValley:ffbar2CvCvbar = ".$_POST["21"]."\n";
fwrite($handle,$data);
}
if($_POST["22"] != "off")
{
$data = "HiddenValley:ffbar2BvBvbar = ".$_POST["22"]."\n";
fwrite($handle,$data);
}
if($_POST["23"] != "off")
{
$data = "HiddenValley:ffbar2TvTvbar = ".$_POST["23"]."\n";
fwrite($handle,$data);
}
if($_POST["24"] != "off")
{
$data = "HiddenValley:ffbar2EvEvbar = ".$_POST["24"]."\n";
fwrite($handle,$data);
}
if($_POST["25"] != "off")
{
$data = "HiddenValley:ffbar2nuEvnuEvbar = ".$_POST["25"]."\n";
fwrite($handle,$data);
}
if($_POST["26"] != "off")
{
$data = "HiddenValley:ffbar2MUvMUvbar = ".$_POST["26"]."\n";
fwrite($handle,$data);
}
if($_POST["27"] != "off")
{
$data = "HiddenValley:ffbar2nuMUvnuMUvbar = ".$_POST["27"]."\n";
fwrite($handle,$data);
}
if($_POST["28"] != "off")
{
$data = "HiddenValley:ffbar2TAUvTAUvbar = ".$_POST["28"]."\n";
fwrite($handle,$data);
}
if($_POST["29"] != "off")
{
$data = "HiddenValley:ffbar2nuTAUvnuTAUvbar = ".$_POST["29"]."\n";
fwrite($handle,$data);
}
if($_POST["30"] != "off")
{
$data = "HiddenValley:FSR = ".$_POST["30"]."\n";
fwrite($handle,$data);
}
if($_POST["31"] != "0.1")
{
$data = "HiddenValley:alphaFSR = ".$_POST["31"]."\n";
fwrite($handle,$data);
}
if($_POST["32"] != "0.4")
{
$data = "HiddenValley:pTminFSR = ".$_POST["32"]."\n";
fwrite($handle,$data);
}
fclose($handle);
}

?>
</body>
</html>

<!-- Copyright (C) 2010 Torbjorn Sjostrand -->

