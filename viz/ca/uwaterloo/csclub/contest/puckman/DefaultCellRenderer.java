import java.awt.Graphics2D;
public class DefaultCellRenderer
    implements PuckmanCellRenderer
{
    public final static int WALL_WIDTH = 4;
    public void renderDynamic(int x, int y, int width, int height, Cell c,
			      Graphics2D g)
    {
	switch(c)
	    {
	    case Cell.PILL:
		g.setColor(java.awt.Color.RED);
		g.fillArc(x, y, int(0.60*width),int(0.60*height), 0, 360);
		break;
	    case Cell.DOT:
		g.setColor(java.awt.Color.WHITE);
		g.fillArc(x, y, int(0.30*width),int(0.30*height), 0, 360);
		break;
	    case CELL.SELF:
	    case CELL.PUCK:
		g.setColor(java.awt.Color.YELLOW);
		g.fillArc(x, y, int(0.80*width),int(0.80*height), 10, 350);
		break;
	    case CELL.SSELF:
	    case CELL.SPUCK:
		g.setColor(java.awt.Color.ORANGE);
		g.fillArc(x, y, int(0.80*width),int(0.80*height), 10, 350);
		break;
	    case Cell.GHOST:
		g.setColor(java.awt.Color.CYAN);
		break;
	    case Cell.UNKNOWN:
	    default:
		break;
	    }
    }

    public void renderStatic(int x, int y, int width, int height, Graphics2D g,
			     boolean u, boolean d, boolean l, boolean r)
    {
	switch(c)
	    {
	    case Cell.WALL:
		g.setColor(java.awt.Color.BLUE);
		if(u || d)
		    g.drawRect(x+(width/2)-(WALL_WIDTH/2),
			       y, WALL_WIDTH, height);
		if(r || l)
		    g.drawRect(x, y+(width/2)-(WALL_WIDTH/2),
			       width, WALL_WIDTH);
		break;
	    default:
		break;
	    }
    }
}