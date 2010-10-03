#!/usr/bin/perl
use strict;
use warnings;

while (1) {
    my ($width,@tiles) = read_board();
    do_move('L');
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


