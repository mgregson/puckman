public class DefaultCellRenderer
    implements PuckmanCellRenderer
{
    public void render(int x, int y, int width, int height, Cell c, Graphics g)
    {
	switch(c)
	    {
	    case Cell.PILL:
		g.fillArc(x, y, int(0.60*width),int(0.60*height), 0, 360);
		break;
	    case Cell.DOT:
		g.fillArc(x, y, int(0.30*width),int(0.30*height), 0, 360);
		break;
	    case CELL.SELF:
	    case CELL.PUCK:
		g.fillArc(x, y, int(0.80*width),int(0.80*height), 10, 350);
		break;
	    case CELL.SSELF:
	    case CELL.SPUCK:
		g.fillArc(x, y, int(0.80*width),int(0.80*height), 10, 350);
		break;
	    case Cell.GHOST:
		break;
	    case Cell.UNKNOWN:
		break;
	    }
    }
}