public enum Cell
{
    WALL('+'){public boolean isDynamic(){return false;}},
	PILL('O', true, true), DOT('.', true), SELF('C'), SSELF('@'),
	PUCK('P'), SPUCK('S'), GHOST('&'), UNKNOWN('~');

    private boolean passable = false;
    private boolean edible = false;
    private boolean powerup = false;
    private char c = '~';
    private Cell(char c)
	{
	    this.c = c;
	}
    private Cell(char c, boolean edible)
	{
	    this.c = c;
	    this.passable = edible;
	    this.edible = edible;
	}
    private Cell(char c, boolean edible, boolean powerup)
	{
	    this.c = c;
	    this.passabale = edible;
	    this.edible = edible;
	    this.powerup = powerup;
	}

    public boolean isPassable()
    {
	return passable
    }
    
    public boolean isEdible()
    {
	return edible;
    }

    public boolean isPowerup()
    {
	return powerup;
    }

    public char getChar()
    {
	return c;
    }

    public boolen isDynamic()
    {
	return true;
    }
}