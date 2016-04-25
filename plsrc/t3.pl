#!/usr/bin/perl
use strict;
my $data;
my $linenumber=-1;
my @cline;
my $dur;
my $string;
my $x;
my $y;
my $z;
$x = 0x6FFF0280;

$y = (0xf0000000 + (((($x) - 0xe0000000) >> 2) & 0x0fffc000) + ((($x) & 0x00003fff)));

printf ("%X->0x%X \n",$x, $y);

$z = ($y - 0xf0000000) - ((($y) & 0x00003fff)) - (((($y) - 0xe0000000) >> 2) & 0x0fffc000);

printf ("%X->%X \n",$y, $z);


