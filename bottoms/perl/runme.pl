#!/usr/bin/perl
use strict;
use warnings;

#Main loop
while (1) {
    my ($width,@tiles) = read_board();
    my @self = find_self($width,@tiles);
    do_move('L');
}

#Helper functions
sub find_puckman {
    my ($width,@tiles) = @_;
    return find_one_of_two('P','S',$width,@tiles);
}

sub find_self {
    my ($width,@tiles) = @_;
    return find_one_of_two('C','@',$width,@tiles);
}

sub find_one_of_two {
    my ($op1,$op2,$width,@tiles) = @_;
    for (my $i = 0 ; $i <= $#tiles; ++$i) {
	if ($tiles[$i] eq $op1 || $tiles[$i] eq $op2) {
	    my @pos = (int($i/$width),$i%$width);
	    return @pos;
	}
    }
    return -1;#Should not happen
}

#Is a position valid
sub is_valid  {
    my $width = shift @_;
    my $x = shift @_;
    my $y = shift @_;
    return (0 <= $x && 0 <= $y && $x < $width && $y < $width);
}

#Execute a move
sub do_move {
    my $c = shift @_;
    print $c;
}

#Read in the board state
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


