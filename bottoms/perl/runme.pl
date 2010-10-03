#!/usr/bin/perl
use strict;
use warnings;

while (1) {
    my ($width,@tiles) = read_board();
    my @self = find_self($width,@tiles);
    do_move('L');
}

sub find_self {
    my ($width,@tiles) = @_;
    for (my $i = 0 ; $i <= $#tiles; ++$i) {
	if ($tiles[$i] eq 'C' || $tiles[$i] eq '@') {
	    my @pos = (int($i/$width),$i%$width);
	    return @pos;
	}
    }
    return -1;#Should not happen
}

sub is_valid  {
    my $width = shift @_;
    my $x = shift @_;
    my $y = shift @_;
    return (0 <= $x && 0 <= $y && $x < $width && $y < $width);
}

sub do_move {
    my $c = shift @_;
    print $c;
}

sub read_board {
    my $width = <>;
    chomp ($width);
    my @tiles;
    while ($#tiles+1 < $width*$width) {
	my $line = <>;
	chomp ($line);
	@tiles = (@tiles,split (//,$line));
    }
    my @return = ($width,@tiles);
    return @return;
}


