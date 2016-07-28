#!/usr/bin/perl

use GD::Simple;
use strict;
my $FORMAT="BPS: [ %16d ]";

my $regex = qr/[0-9]bps/;
my $len;
my $num;

$img = GD::Simple->new(640, 480);
$img->fgcolor('black');
$img->bgcolor('yellow');

$img->rectangle(10,10,50,50);

while (<DATA>) {

next unless /\((\d+)\)bps/;

print $1, "\n";
}

__DATA__
[StreamInOut]   WriteCache Filewrite (28872000)bps
[StreamInOut]   WriteCache Filewrite (36136000)bps
[StreamInOut]   WriteCache Filewrite (35248000)bps
[StreamInOut]   WriteCache Filewrite (29160000)bps
[StreamInOut]   WriteCache Filewrite (35392000)bps
[StreamInOut]   WriteCache Filewrite (29344000)bps
[StreamInOut]   WriteCache Filewrite (35224000)bps

