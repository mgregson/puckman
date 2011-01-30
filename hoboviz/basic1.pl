#!/usr/bin/perl
use Term::ANSIColor;

while (1) {
    my $a_score = <>;
    my $b_score = <>;
    my $width = <>;
    chomp ($a_score);
    chomp ($b_score);
    chomp ($width);
    my @tiles;
    for (my $r = 0; $r < $width ; ++$r) {
	my $line = <>;
	chomp($line);
	@line_tiles = split (//, $line);
	@tiles = (@tiles,@line_tiles);
    }
    my $c = 0;
    foreach my $t (@tiles) {
	switch ($t) {
	    'C':
		print color 'bold blue'
		print $t;
		print color 'reset';
		break;
	    '@':
		print color 'bold blue'
		print $t;
		print color 'reset';
		break;
	    'P':
		print color 'bright red'
		print $t;
		print color 'reset';
		break;
	    'S':
		print color 'bright red'
		print $t;
		print color 'reset';
		break;
	  default:
	    print $t;
	}
	$c++;
	if ($c == $width) {
	    print "\n";
	}
    }
}
