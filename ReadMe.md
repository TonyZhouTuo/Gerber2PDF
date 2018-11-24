# Gerber2PDF

Gerber2PDF is a command-line tool to convert Gerber files to PDF for proofing and hobbyist printing purposes.

## Installation:

Download and run [Gerber2pdf.exe](https://sourceforge.net/projects/gerber2pdf/files/Gerber2pdf.exe/download) (Windows) or [Gerber2pdf](https://sourceforge.net/projects/gerber2pdf/files/Gerber2pdf/download) (Linux 64-bit).  This will display the copyright and usage information.

## Usage:

A batch-file or script is recommended, but a simple "Open with..." link will also work, resulting in a single Gerber converted to a PDF with the same file-name as the Gerber.

## Source:

The source is available from the [git repository](https://sourceforge.net/p/gerber2pdf/code/) and [GitHub](https://github.com/jpt13653903/Gerber2PDF).

To build on Linux, run `make`.

To build on Windows, install [MinGW](http://tdm-gcc.tdragon.net/) and run `mingw32-make` from within a POSIX-like environment, such as [Git Bash](https://git-scm.com/).

## Changes:

#### 2018-11-20

- Version-bump to 1.4
- Added the `-page_size` command-line option

#### 2017-12-20

- Fixed bug relating to explicit positive numbers

#### 2017-08-13

- Implemented a new "-strokes2fills" command-line option.
- Fixed bug relating to the Open Contour warning.

#### 2016-10-09

- Fixed bug relating to Gerbers that specify units by means of the deprecated codes `G70` or `G71`, instead of the mandatory `%MO??*%` parameter.

#### 2016-09-25

- Added an option to change the background colour

#### 2016-09-24

- Fixed bug relating to arc bounding box calculation

#### 2016-09-21

- Fixed bug relating to the first coordinate of an imaging level

#### 2016-07-20

- Fixed bug relating to closed contour warnings

#### 2015-11-12

- Fixed bug relating to arc bounding box calculation

#### 2015-02-21

- Added silent exit feature

#### 2015-01-20

- Fixed bug where paths were handled wrong when terminated with a flash instead of a move.

#### 2014-12-04

- Multiple instances of negative image Gerbers now render correctly.

#### 2014-08-28

- Fixed bug regarding the calculation of arc centres.
- Fixed bug where paths were sometimes drawn as regions.

#### 2014-06-22

- Added a "-nocombine" option.

#### 2014-06-21

- Added transparency to the layers.  Transparency is specified by adding an optional alpha value to the colour.
- Optimised for smaller PDF output by reusing previous Gerber conversions.
- Added warnings for deprecated features (optionally disabled by the "-nowarnings" option).
- Added an icon to Gerber2pdf.exe.
- Fixed step-and-repeat bug

#### 2014-06-20

- Fixed bug regarding aperture macros and primitives with "exposure off".
- Added an option to change the layer colour.
- Added an option to combine layers onto a single page.
- Added an option to mirror the output.

