AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = -I$(srcdir)/include

lib_LTLIBRARIES =
lib_LTLIBRARIES += libpythia8.la liblhapdfdummy.la
if BUILD_HEPMC
lib_LTLIBRARIES += libhepmcinterface.la
endif
#AM_CPPFLAGS += -I${HEPMCLOC}

SUBDIRS = . examples

liblhapdfdummy_la_SOURCES = \
	lhapdfdummy/LHAPDFDummy.cc

libhepmcinterface_la_SOURCES = \
	hepmcinterface/HepMCInterface.cc

libpythia8_la_SOURCES = \
	src/Analysis.cc \
	src/Basics.cc \
	src/BeamParticle.cc \
	src/BeamRemnants.cc \
	src/BeamShape.cc \
	src/BoseEinstein.cc \
	src/Event.cc \
	src/FragmentationFlavZpT.cc \
	src/FragmentationSystems.cc \
	src/HadronLevel.cc \
	src/Info.cc \
	src/LesHouches.cc \
	src/MiniStringFragmentation.cc \
	src/MultipleInteractions.cc \
	src/ParticleData.cc \
	src/ParticleDecays.cc \
	src/PartonDistributions.cc \
	src/PartonLevel.cc \
	src/PartonSystems.cc \
	src/PhaseSpace.cc \
	src/ProcessContainer.cc \
	src/ProcessLevel.cc \
	src/Pythia.cc \
	src/PythiaStdlib.cc \
	src/ResonanceDecays.cc \
	src/ResonanceWidths.cc \
	src/Settings.cc \
	src/SigmaCompositeness.cc \
	src/SigmaEW.cc \
	src/SigmaExtraDim.cc \
	src/SigmaGeneric.cc \
	src/SigmaHiggs.cc \
	src/SigmaLeftRightSym.cc \
	src/SigmaLeptoquark.cc \
	src/SigmaNewGaugeBosons.cc \
	src/SigmaOnia.cc \
	src/SigmaProcess.cc \
	src/SigmaQCD.cc \
	src/SigmaSUSY.cc \
	src/SigmaTotal.cc \
	src/SpaceShower.cc \
	src/StandardModel.cc \
	src/StringFragmentation.cc \
	src/SusyCouplings.cc \
	src/SusyLesHouches.cc \
	src/TimeShower.cc \
	src/UserHooks.cc

pkginclude_HEADERS = \
	include/Analysis.h \
	include/Basics.h \
	include/BeamParticle.h \
	include/BeamRemnants.h \
	include/BeamShape.h \
	include/BoseEinstein.h \
	include/Event.h \
	include/FragmentationFlavZpT.h \
	include/FragmentationSystems.h \
	include/HadronLevel.h \
	include/HepMCInterface.h \
	include/Info.h \
	include/LesHouches.h \
	include/LHAFortran.h \
	include/LHAPDFInterface.h \
	include/MiniStringFragmentation.h \
	include/MultipleInteractions.h \
	include/ParticleData.h \
	include/ParticleDecays.h \
	include/PartonDistributions.h \
	include/PartonLevel.h \
	include/PartonSystems.h \
	include/PhaseSpace.h \
	include/ProcessContainer.h \
	include/ProcessLevel.h \
	include/PythiaComplex.h \
	include/Pythia.h \
	include/PythiaStdlib.h \
	include/ResonanceDecays.h \
	include/ResonanceWidths.h \
	include/Settings.h \
	include/SigmaCompositeness.h \
	include/SigmaEW.h \
	include/SigmaExtraDim.h \
	include/SigmaGeneric.h \
	include/SigmaHiggs.h \
	include/SigmaLeftRightSym.h \
	include/SigmaLeptoquark.h \
	include/SigmaNewGaugeBosons.h \
	include/SigmaOnia.h \
	include/SigmaProcess.h \
	include/SigmaQCD.h \
	include/SigmaSUSY.h \
	include/SigmaTotal.h \
	include/SpaceShower.h \
	include/StandardModel.h \
	include/StringFragmentation.h \
	include/SusyCouplings.h \
	include/SusyLesHouches.h \
	include/TimeShower.h \
	include/UserHooks.h

dist_doc_DATA = \
	worksheet.pdf
dist_html_DATA = \
	htmldoc/AccessPYTHIA6Processes.html
	htmldoc/AdvancedUsage.html
	htmldoc/ASecondHardProcess.html
	htmldoc/BeamParameters.html
	htmldoc/BeamRemnants.html
	htmldoc/BeamShape.html
	htmldoc/Bibliography.html
	htmldoc/BoseEinsteinEffects.html
	htmldoc/CompositenessProcesses.html
	htmldoc/COPYING
	htmldoc/CouplingsAndScales.html
	htmldoc/Diffraction.html
	htmldoc/ElectroweakProcesses.html
	htmldoc/ErrorChecks.html
	htmldoc/EventAnalysis.html
	htmldoc/EventInformation.html
	htmldoc/EventRecord.html
	htmldoc/EventStatistics.html
	htmldoc/ExternalDecays.html
	htmldoc/ExtraDimensionalProcesses.html
	htmldoc/FlavourSelection.html
	htmldoc/FourthGenerationProcesses.html
	htmldoc/FourVectors.html
	htmldoc/Fragmentation.html
	htmldoc/Frontpage.html
	htmldoc/Glossary.html
	htmldoc/GUIDELINES
	htmldoc/HadronLevelStandalone.html
	htmldoc/HepMCInterface.html
	htmldoc/HiddenValleyProcesses.html
	htmldoc/HiggsProcesses.html
	htmldoc/Histograms.html
	htmldoc/ImplementNewShowers.html
	htmldoc/Index.html
	htmldoc/JetFinders.html
	htmldoc/LeftRightSymmetryProcesses.html
	htmldoc/LeptoquarkProcesses.html
	htmldoc/LesHouchesAccord.html
	htmldoc/MainProgramSettings.html
	htmldoc/MasterSwitches.html
	htmldoc/MultipleInteractions.html
	htmldoc/NewGaugeBosonProcesses.html
	htmldoc/OniaProcesses.html
	htmldoc/ParticleData.html
	htmldoc/ParticleDataScheme.html
	htmldoc/ParticleDecays.html
	htmldoc/ParticleProperties.html
	htmldoc/PartonDistributions.html
	htmldoc/PDFSelection.html
	htmldoc/PhaseSpaceCuts.html
	htmldoc/ProcessSelection.html
	htmldoc/ProgramClasses.html
	htmldoc/ProgramFiles.html
	htmldoc/ProgramFlow.html
	htmldoc/ProgramMethods.html
	htmldoc/pythia32.gif
	htmldoc/PYTHIA6TranslationTable.html
	htmldoc/pythia8100.pdf
	htmldoc/pythia99.gif
	htmldoc/pythia.css
	htmldoc/QCDProcesses.html
	htmldoc/RandomNumberSeed.html
	htmldoc/RandomNumbers.html
	htmldoc/ResonanceDecays.html
	htmldoc/ROOTusage.html
	htmldoc/SampleMainPrograms.html
	htmldoc/SaveSettings.html
	htmldoc/SemiInternalProcesses.html
	htmldoc/SemiInternalResonances.html
	htmldoc/SettingsScheme.html
	htmldoc/SpacelikeShowers.html
	htmldoc/StandardModelParameters.html
	htmldoc/SUSYLesHouchesAccord.html
	htmldoc/SUSYProcesses.html
	htmldoc/TimelikeShowers.html
	htmldoc/TopProcesses.html
	htmldoc/TotalCrossSections.html
	htmldoc/Tunes.html
	htmldoc/UpdateHistory.html
	htmldoc/UserHooks.html
	htmldoc/Version.html
	htmldoc/Welcome.html
	htmldoc/worksheet.pdf

EXTRA_DIST = \
	phpdoc/ \
	xmldoc/
