#!/usr/bin/perl

# soko2des: read a Sokoban ASCII screenshot (similar to what one would
# use with nhss, but it can have stairs and doors) and produce a .des
# file version of the level.  Levels and monsters are not included.

my $infile  = "s2din.txt";
my $outfile = "s2dout.des";
my $first   = undef;
my $title;

my @arg = @ARGV;
while (@arg) {
  my $a = shift @arg;
  if ($a eq "infile") {
    $infile = shift @arg;
  } elsif ($a eq "outfile") {
    $outfile = shift @arg;
  } elsif ($a =~ /first|soko1/i) {
    $first = "true";
  } elsif ($a eq "title") {
    $title = shift @arg;
  } else {
    warn "Unrecognized argument: $arg";
  }
}
$title ||= $infile;

open IN,  "<", $infile  or die "Cannot read input ($infile): $!\n";
open OUT, ">", $outfile or die "Cannot write output ($outfile): $!\n";

my (@pos, @stair, @door, @boulder, @pit, @scroll, @mimic, %count);
my ($x, $y, $maxx, $maxy) = (0, 0, 0, 0);

for my $line (<IN>) {
  chomp $line;
  $x = 0;
  for my $chr (split //, $line) {
    $count{$chr}++;
    if ($chr eq '0') {
      push @boulder, [$x, $y];
      $chr = '.';
    } elsif ($chr eq '>' or $chr eq '<') {
      push @stair, [$x, $y, $chr];
      $chr = '.';
    } elsif ($chr eq 'm') {
      push @mimic, [$x, $y];
      $chr = '.';
    } elsif ($chr eq '^') {
      push @pit, [$x, $y];
      $chr = '.';
    } elsif ($chr eq '?') {
      push @scroll, [$x, $y];
      $chr = '.';
    }
    if ($chr eq '+') {
      push @door, [$x, $y];
      # but leave the '+', .des format allows it.
    }
    $pos[$x][$y] = $chr;
    $maxx = $x if $maxx < $x;
    $maxy = $y if $maxy < $y;
    $x++;
  }
  $y++;
}

my $hardfloor = $first ? ",hardfloor" : "";
my $traptype  = $first ? "pit" : "hole";
my $note      = $first ? "This level is designed to be the FIRST level in the Sokoban branch"
                       : "This level is NOT designed to be the first level of Sokoban";

print OUT qq{#Generated by soko2des.pl

# "$title"
MAZE: "$infile",' '
# $note
FLAGS:noteleport$hardfloor
MESSAGE:"$title"
GEOMETRY:center,center
#12345678901234567890123456789012345678901234567890
MAP
};


# Pad the ends of lines with spaces as necessary:
for $y (0 .. $maxy) {
  for $x (0 .. $maxx) {
    $pos[$x][$y] = ' ' if not defined $pos[$x][$y];
    print OUT $pos[$x][$y];
  }
  print OUT "\n";
}
print OUT "ENDMAP\n";

for my $s (@stair) {
  ($x, $y, $dir) = @$s;
  ($x,$y) = map { sprintf "%02d", $_ } ($x, $y);
  my $dirname = ($dir eq '<') ? "up" : "down";
  my $command = "STAIR";
  my $coords  = "($x,$y)";
  if ($first and ($dirname eq "down")) {
    $command = "BRANCH";
    $dirname = "levregion()";
    $coords  = "($x,$y,$x,$y)";
  }
  print OUT "" . $command . ":$coords,$dirname\n";
}

for my $d (@door) {
  ($x, $y) = map { sprintf "%02d", $_ } @$d;
  print OUT "DOOR:locked,($x,$y)\n";
}

$maxx = sprintf "%02d", $maxx;
$maxy = sprintf "%02d", $maxy;

print OUT qq[REGION:(00,00,$maxx,$maxy),lit,"ordinary"
NON_DIGGABLE:(00,00,$maxx,$maxy)
NON_PASSWALL:(00,00,$maxx,$maxy)

# Boulders\n];

for my $b (@boulder) {
  ($x,$y) = map { sprintf "%02d", $_ } @$b;
  print OUT qq[OBJECT:'`',"boulder",($x,$y)\n];
}

print OUT "\n# Traps\n";
for my $t (@pit) {
  ($x,$y) = map { sprintf "%02d", $_ } @$t;
  print OUT qq[TRAP:"$traptype",($x,$y)\n];
}

if (scalar @scroll) {
  print OUT "\n# A little help\n";
  for my $s (@scroll) {
    ($x,$y) = map { sprintf "%02d", $_ } @$s;
    print OUT qq[OBJECT:'?',"earth",($x,$y)\n];
  }
}

if (scalar @mimic) {
  print OUT "\n";
  for my $m (@mimic) {
    ($x,$y) = map { sprintf "%02d", $_ } @$m;
    print OUT qq[MONSTER:'m',"giant mimic", ($x,$y), m_object "boulder"\n];
  }
}

print OUT qq[
# Random objects
OBJECT:'%',random,random
OBJECT:'%',random,random
OBJECT:'%',random,random
OBJECT:'%',random,random
OBJECT:'=',random,random
OBJECT:'/',random,random

];


print "
Character Counts:
=================
" . (join "\n", map {
  sprintf " %4d  '$_'", $count{$_}
} sort { $count{$b} <=> $count{$a} } keys %count) . "\n\n";

if (($count{"?"} || 0) ne ($first ? 2 : 0)) {
  warn "Incorrect number of scrolls of earth.\n";
}
