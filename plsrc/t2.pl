#!/usr/bin/perl
use GD::Simple;
use strict;
my $FORMAT="BPS: [ %16d ]";

my $regex = qr/[0-9]bps/;
my $len;
my $num;
my $x1;
my $y1;
my $x2;
my $y2;
my $max_x2;
#my $img = GD::Simple->new(640, 10 * 30);
my $thick = 10;
my $res=5;
my @data;
my $img = GD::Simple->new(640, 3200*2);

$img->fgcolor('black');
$img->bgcolor('yellow');
#$img->rectangle(10,10,50,50);
$len=1;
$img->font('Times:italic');
$img->fontsize(8);

while (<>) {
@data = split /,/ , $_;
#next unless /\((\d+)\)bps/;
$x1 = 10;
$y1 = 10+$thick*($len-1); 
$x2 = $data[0];
$x2 = $x2 * ($res);
$y2 = 10+$thick*$len;

#print sprintf("%d %d %d %d \n", $x1, $y1, $x2, $y2);
if ($x2 < 80)
{
	$img->bgcolor('red');
$img->moveTo(500,$y2);
#$img->moveTo($max_x2,$y2);
$img->fgcolor('black');
$img->string(sprintf("%d(%02f Mbps)",$1,$1/$res));
}
elsif ($x2 < 200)
{
	$img->bgcolor('blue');
}
else
{
	$img->bgcolor('yellow');
	if ($max_x2 < $x2) 
	{
		$max_x2 = $x2;
	}
}
$img->rectangle($x1,$y1, $x2, $y2);

$len=$len+1;
#print $1, "\n";

}
print $img->png;

__DATA__
[StreamInOut]   WrateCache Filewrite (28872000)bps
[StreamInOut]   WriteCache Filewrite (36136000)bps
[StreamInOut]   WriteCache Filewrite (35248000)bps
[StreamInOut]   WriteCache Filewrite (29160000)bps
[StreamInOut]   WriteCache Filewrite (35392000)bps
[StreamInOut]   WriteCache Filewrite (29344000)bps
[StreamInOut]   WriteCache Filewrite (35224000)bps

