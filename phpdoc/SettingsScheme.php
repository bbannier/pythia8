<html>
<head>
<title>The Settings Scheme</title>
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

<form method='post' action='SettingsScheme.php'>

<h2>The Settings Scheme</h2>

The <code>Settings</code> class keeps track of all the flags, modes, 
parameters and words used during the event generation. As such, it 
serves all the <code>Pythia</code> program elements from one central 
repository. Accessing it allows the user to modify the generator 
behaviour. 

<p/>
Each <code>Pythia</code> object has a public member <code>settings</code> 
of the <code>Settings</code> class. Therefore you access the 
settings methods as <code>pythia.settings.command(argument)</code>,
assuming that <code>pythia</code> is an instance of the <code>Pythia</code> 
class. Further, for the most frequent user tasks, <code>Pythia</code> 
methods have been defined, so that <code>pythia.command(argument)</code> 
would work, see further below.

<p/>
The central section on this page is the Operation one. The preceding 
concepts section is there mainly to introduce the basic structure and 
the set of properties that can be accessed. The subsequent sections 
provide a complete listing of the existing public methods, which most 
users probably will have little interaction with.

<h3>Concepts</h3>

We distinguish four kinds of user-modifiable variables, by the way
they have to be stored:
<ol>
<li>Flags are on/off switches, and are stored as <code>bool</code>.</li>
<li>Modes corresponds to a finite enumeration of separate options,
   and are stored as <code>int</code>.</li>
<li>Parameters take a continuum of values, and are stored as 
<code>double</code>. The shorthand notation parm is used in the C++ 
code and XML tags, so that all four kinds are represented by
four-letter type names.</li>
<li>Words are simple character strings and are stored as 
<code>string</code>. No blanks or double quotation marks (&quot;) may 
appear inside a word, the former to simplify parsing of an input file
and the latter not to cause conflicts with XML attribute delimiters.
Currently the main application is to store file names.</li>
</ol>

<p/>
In general, each variable stored in <code>Settings</code> is associated 
with four kinds of information:
<ul>
<li>The variable name, of the form <code>class:name</code> 
(or <code>file:name</code>, usually these agree), e.g. 
<code>TimeShower:pTmin</code>. The class/file part usually identifies 
the <code>.xml</code> file where the variable is defined, and the part of 
the program where it is used, but such a connection cannot be strictly
upheld, since e.g. the same variable may be used in a few different
cases (even if most of them are not).</li> 
<li>The default value, set in the original declaration, and intended
to represent a reasonable choice.</li> 
<li>The current value, which differs from the default when the user so 
requests.</li>
<li>An allowed range of values, represented by meaningful
minimum and maximum values. This has no sense for a <code>flag</code> 
or a <code>word</code> (and is not used there), is usually rather 
well-defined for a <code>mode</code>, but less so for a <code>parm</code>. 
Often the allowed range exaggerates the degree of our current knowledge, 
so as not to restrict too much what the user can do. One may choose 
not to set the lower or upper limit, in which case the range is 
open-ended.</li>   
</ul>

<p/>
Technically, the <code>Settings</code> class is implemented with the 
help of four separate maps, one for each kind of variable, with the 
variable <code>name</code> used as key. 

<h3>Operation</h3>
    
The normal flow of setting values is:

<ol>

<p/> <li>
When a <code>Pythia</code> object <code>pythia </code>is created, 
the member <code>pythia.settings</code> is asked to scan the files
listed in the <code>Index.xml</code> file in the <code>xmldoc</code> 
subdirectory.

<p/>
In all of the files scanned, lines beginning with 
<code>&lt;flag</code>, <code>&lt;mode</code>, <code>&lt;parm</code> 
or <code>&lt;word</code> are identified, and the information on 
such a line is used to define a new flag, mode, parameter or word. 
To exemplify, consider a line
<pre>
&lt;parm name="TimeShower:pTmin" default="0.5" min="0.1" max="2.0">
</pre> 
which appears in the <code>TimeShower.xml</code> file, and there
defines a parameter <code>TimeShower:pTmin</code> with default value 
0.5 GeV and allowed variation in the range 0.1 - 2.0 GeV. The min 
and max values are optional.
<br/><b>Important:</b> the values in the <code>.xml</code> files should 
not be changed, except by the PYTHIA authors. Any changes should be 
done with the help of the methods described below.
</li>

<p/> <li>
Between the creation of the <code>Pythia</code> object and the 
<code>init</code> call for it, you may use several alternative 
methods to modify some of the default values. The same variable 
can be changed several times. If so, it is the last read value 
that counts. The two special 
<code><?php $filepath = $_GET["filepath"];
echo "<a href='Tunes.php?filepath=".$filepath."' target='page'>";?>Tune:ee</a></code> and 
<code><?php $filepath = $_GET["filepath"];
echo "<a href='Tunes.php?filepath=".$filepath."' target='page'>";?>Tune:pp</a></code> 
modes are expanded to change several settings in one go, but these obey 
the same ordering rules.

<p/> 
a) Inside your main program you can directly set values with
<pre>
    pythia.readString(string) 
</pre>
where both the variable name and the value are contained inside
the character string, separated by blanks and/or a =, e.g. 
<pre>
    pythia.readString("TimeShower:pTmin = 1.0"); 
</pre>
The match of the name to the database is case-insensitive. Names 
that do not match an existing variable are ignored. A warning is
printed, however. Strings beginning with a non-alphanumeric character, 
like # or !, are assumed to be comments and are not processed at all. 
Values below the minimum or above the maximum are set at 
the respective border. For <code>bool</code> values, the following 
notation may be used interchangeably: 
<code>true = on = yes = ok = 1</code>, while everything else gives 
<code>false</code> (including but not limited to 
<code>false</code>, <code>off</code>, <code>no</code> and 0).<br/> 

<p/> 
b) The <code>Pythia</code> <code>readString(string)</code> method 
actually does not do changes itself, but sends on the string either 
to the <code>Settings</code> class or to <code>ParticleData</code>. 
The former holds if the string begins with a letter, the latter
if it begins with a digit. If desired, it is possible to communicate
directly with the corresponding <code>Settings</code> method:
<pre>
    pythia.settings.readString("TimeShower:pTmin = 1.0"); 
</pre>
In this case, changes intended for <code>ParticleData</code> 
would not be understood.

<p/> 
c) Underlying the <code>settings.readString(string)</code> method are 
the settings-type-sensitive commands in the <code>Settings</code>, that 
are split by names containing <code>flag</code>, <code>mode</code>, 
<code>parm</code> or <code>word</code>. Thus, the example now reads
<pre>
    pythia.settings.parm("TimeShower:pTmin", 1.0); 
</pre>
Such a form could be convenient e.g. if a parameter is calculated
at the beginning of the main program, and thus is available as a 
variable rather than as a character string.
Note that Boolean values must here be given as <code>true</code> or 
<code>false</code> i.e. there is less flexibility than with the 
previous methods.

<p/> 
At the same level, there are several different methods available.
These are included in the full description below, but normally the user 
should have no need for them. 

<p/>
d) A simpler and more useful way is to collect all your changes
in a separate file, with one line per change, e.g. 
<pre>
    TimeShower:pTmin = 1.0
</pre>
Each line is read in as a string and processed with the methods already
introduced.

The file can be read by the 
<pre>
    pythia.readFile(fileName); 
</pre>
method (or an <code>istream</code> instead of a <code>fileName</code>). 
The file can freely mix commands to the <code>Settings</code> and 
<code>ParticleData</code> classes, and so is preferable. Lines with 
settings are handled by calls to the 
<code>pythia.settings.readString(string)</code> method.
</li>

<p/> <li>
In the <code>pythia.init(...)</code> call, many of the various other program  
elements are initialized, making use of the current values in the database. 
Once initialized, the common <code>Settings</code> database is likely not 
consulted again by these routines. It is therefore not productive to do 
further changes in mid-run: at best nothing changes, at worst you may 
set up inconsistencies. 

<p/>
A routine <code>reInit(fileName)</code> is provided, and can be used to 
zero all the maps and reinitialize them from scratch. Such a call might be 
useful if several subruns are to be made with widely different parameter 
sets - normally the maps are only built from scratch once, namely when the 
<code>Pythia()</code> object is created. A more economical alternative is 
offered by <code>resetAll()</code>, however, which sets all variables back 
to their default values.
</li> 

<p/> <li>
You may at any time obtain a listing of all variables in the 
database by calling  
<pre>
    pythia.settings.listAll();
</pre>
The listing is strictly alphabetical, which at least means that names
from the same file are kept together, but otherwise may not be so 
well-structured: important and unimportant ones will appear mixed.
A more relevant alternative is 
<pre>
    pythia.settings.listChanged();
</pre>
where you will only get those variables that differ from their 
defaults. Or you can use 
<pre>
    pythia.settings.list("string");
</pre>
where only those variables with names that contain the string 
(case-insensitive match) are listed. Thus, with a string 
<code>shower</code>, the shower-related variables would be shown.
</li>

<p/> <li>
The above listings are in a tabular form that cannot be read
back in. Assuming you want to save all changed settings (maybe because
you read in changes from several files), you can do that by calling
<pre>
    pythia.settings.writeFile(fileName);
</pre>
This file could then directly be read in by 
<code>readFile(fileName)</code> in a subsequent (identical) run.
Some variants of this command are listed below. 
</li>
</ol>

<h3>Methods</h3>

The complete list of methods and arguments is as follows. Most of the 
ones of interest to the user have already been mentioned above. 
Others can be used, but the same functionality is better achieved
by higher-level routines. Some are part of the internal machinery,
and should not be touched by user. 

<p/>
Note that there is no <code>Settings::readFile(...)</code> method. 
The intention is that you should use <code>Pythia::readFile(...)</code>.
It parses and decides which individual lines should be sent on to 
<code>Settings::readString(...)</code>.

<a name="method1"></a>
<p/><strong>Settings::Settings() &nbsp;</strong> <br/>
the constructor, which takes no arguments. Internal.
  

<a name="method2"></a>
<p/><strong>bool Settings::initPtr(Info* infoPtrIn) &nbsp;</strong> <br/>
initialize pointer to error-message database. Internal.
  

<a name="method3"></a>
<p/><strong>bool Settings::init(string startFile = &quot;../xmldoc/Index.xml&quot;, bool append = false, ostream& os = cout) &nbsp;</strong> <br/>
read in the settings database.
<br/><code>argument</code><strong> startFile </strong> (<code>default = <strong>&quot;../xmldoc/Index.xml&quot;</strong></code>) :   
read in the settings from all the files listed in this file, and 
assumed to be located in the same subdirectory.
  
<br/><code>argument</code><strong> append </strong> (<code>default = <strong>false</strong></code>) :   
By default nothing is done if the method has already been called once.
If true the further settings read in are added to the current database.
  
<br/><code>argument</code><strong> os </strong> (<code>default = <strong>cout</strong></code>) : 
stream for error printout.  
  
<br/><b>Note:</b> The method returns false if it fails.
  

<a name="method4"></a>
<p/><strong>bool Settings::reInit(string startFile = &quot;../xmldoc/Index.xml&quot;, ostream& os = cout) &nbsp;</strong> <br/>
overwrite the existing database.
<br/><code>argument</code><strong> startFile </strong> (<code>default = <strong>&quot;../xmldoc/Index.xml&quot;</strong></code>) :   
read in the settings from all the files listed in this file, and 
assumed to be located in the same subdirectory.
  
<br/><code>argument</code><strong> os </strong> (<code>default = <strong>cout</strong></code>) : 
stream for error printout.  
  
<br/><b>Note:</b> The method returns false if it fails.
  

<a name="method5"></a>
<p/><strong>bool Settings::readString(string line, bool warn = true, ostream& os = cout) &nbsp;</strong> <br/>
read in a string, and change the relevant quantity in the database.
It is normally used indirectly, via 
<code>Pythia::readString(...)</code> and
<code>Pythia::readFile(...)</code>.
<br/><code>argument</code><strong> line </strong>  : 
the string to be interpreted as an instruction.
  
<br/><code>argument</code><strong> warn </strong> (<code>default = <strong>true</strong></code>) : 
write a warning message or not whenever the instruction does not make
sense, e.g. if the variable does not exist in the databases.
  
<br/><code>argument</code><strong> os </strong> (<code>default = <strong>cout</strong></code>) : 
stream for error printout.  
  
<br/><b>Note:</b> the method returns false if it fails to 
make sense out of the input string.
  

<a name="method6"></a>
<p/><strong>bool Settings::writeFile(string toFile, bool writeAll = false) &nbsp;</strong> <br/>
  
<strong>bool Settings::writeFile(ostream& os = cout, bool writeAll = false) &nbsp;</strong> <br/>
write current settings to a file or to an <code>ostream</code>.
<br/><code>argument</code><strong> toFile, os </strong>  : 
file or stream on which settings are written.  
  
<br/><code>argument</code><strong> writeAll </strong> (<code>default = <strong>false</strong></code>) : 
normally only settings that have been changed are written, 
but if true then all settings are output.
  
<br/><b>Note:</b> the method returns false if it fails.
  

<a name="method7"></a>
<p/><strong>void Settings::listAll(ostream& os = cout) &nbsp;</strong> <br/>
  
<strong>void Settings::listChanged(ostream& os = cout) &nbsp;</strong> <br/>
  
<strong>void Settings::list(string match, ostream& os = cout) &nbsp;</strong> <br/>
list all or changed settings, or a group of them.
<br/><code>argument</code><strong> match </strong>  : 
list all those settings where the name contains
the <code>match</code> (sub)string (case-insensitive).
  
<br/><code>argument</code><strong> os </strong> (<code>default = <strong>cout</strong></code>) : 
output stream for the listing.
  
  

<a name="method8"></a>
<p/><strong>void Settings::resetAll() &nbsp;</strong> <br/>
reset all current values to their defaults.
  

<a name="method9"></a>
<p/><strong>bool Settings::isFlag(string key) &nbsp;</strong> <br/>
  
<strong>bool Settings::isMode(string key) &nbsp;</strong> <br/>
  
<strong>bool Settings::isParm(string key) &nbsp;</strong> <br/>
  
<strong>bool Settings::isWord(string key) &nbsp;</strong> <br/>
return true if an entry of the given name and kind 
exists, else false.
  

<a name="method10"></a>
<p/><strong>void Settings::addFlag(string key, bool default) &nbsp;</strong> <br/>
  
<strong>void Settings::addMode(string key, int default, bool hasMin, bool hasMax, int min, int max) &nbsp;</strong> <br/>
  
<strong>void Settings::addParm(string key, double default, bool hasMin, bool hasMax, double min, double max) &nbsp;</strong> <br/>
  
<strong>void Settings::addWord(string key, string default) &nbsp;</strong> <br/>
add an entry of the respective kind to the database. The name and default
value always has to be supplied, for <code>Mode</code> and 
<code>Word</code> additionally if lower and/or upper limits are to be 
imposed and, if so, what those limit are.
  

<a name="method11"></a>
<p/><strong>bool Settings::flag(string key) &nbsp;</strong> <br/>
  
<strong>int Settings::mode(string key) &nbsp;</strong> <br/>
  
<strong>double Settings::parm(string key) &nbsp;</strong> <br/>
  
<strong>string Settings::word(string key) &nbsp;</strong> <br/>
return the current value of the respective setting. If the name 
does not exist in the database, a value <code>false</code>,
<code>0</code>, <code>0.</code> and <code>&quot; &quot;</code> 
is returned, respectively.
  

<a name="method12"></a>
<p/><strong>void Settings::flag(string key, bool now) &nbsp;</strong> <br/>
  
<strong>void Settings::mode(string key, int now) &nbsp;</strong> <br/>
  
<strong>void Settings::parm(string key, double now) &nbsp;</strong> <br/>
  
<strong>void Settings::word(string key, string now) &nbsp;</strong> <br/>
change the current value of the respective setting to the provided 
new value. If lower or upper limits have been set, input values 
outside the allowed range are reinterpreted as being a the nearest 
limit.
  

<a name="method13"></a>
<p/><strong>void Settings::forceMode(string key, int now) &nbsp;</strong> <br/>
  
<strong>void Settings::forceParm(string key, double now) &nbsp;</strong> <br/>
as above, but do not check lower and upper limits, so that the current 
value can be put outside the intended borders.
  

<a name="method14"></a>
<p/><strong>void Settings::resetFlag(string key) &nbsp;</strong> <br/>
  
<strong>void Settings::resetMode(string key) &nbsp;</strong> <br/>
  
<strong>void Settings::resetParm(string key) &nbsp;</strong> <br/>
  
<strong>void Settings::resetWord(string key) &nbsp;</strong> <br/>
reset the current value to the default one.
  

</body>
</html>

<!-- Copyright (C) 2010 Torbjorn Sjostrand -->
