<html>
<head>
<title>Jet Finders</title>
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

<form method='post' action='JetFinders.php'>

<h2>Jet Finders</h2>

<code>Pythia</code> comes with two <?php $filepath = $_GET["filepath"];
echo "<a href='EventAnalysis.php?filepath=".$filepath."' target='page'>";?>built-in 
jet finders</a>, <code>ClusterJet</code> for <i>e^+e^-</i> events 
and <code>CellJet</code> for hadron collider ones. Especially the 
latter is not so well matched to the standards of its field, however.
(But it is closely related to the anti-<i>kT</i> algorithm,
so is also not completely disconnected [<a href="Bibliography.php" target="page">Cac08</a>].)  

<h3>FastJet</h3>

For realistic jet studies the <code>FastJet</code> package
[<a href="Bibliography.php" target="page">Cac06</a>] has become a standard. Several different
jet options are available, such as <i>kT</i>,
Cambridge/Aachen, anti-<i>kT</i> and SISCone.

<p/>
Linking to <code>FastJet</code> is foreseen in the configure 
file in the <code>examples</code> subdirectory, and the 
<code>main61.cc</code> program contains an example how it can
be used with <code>Pythia</code> events.

</body>
</html>

<!-- Copyright (C) 2010 Torbjorn Sjostrand -->
