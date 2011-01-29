import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import javax.swing.JPanel;
import static java.awt.image.BufferedImage.TYPE_INT_RGB;
import static java.awt.image.BufferedImage.TYPE_INT_ARGB;

public class WorldView
    extends JPanel
    implements WorldStateListener
{
    private World world;
    private PuckmanCellRenderer renderer;
    private BufferedImage background = null;
    private BufferedImage foreground = null;
    private BufferedImage state = null;
    private int width;
    private int height;
    public WorldView(int width, int height, World w, PuckmanCellRenderer cr)
    {
	this.width = width;
	this.height = height;
	world = w;
	world.addListener(this);
	renderer = cr;
    }

    public void setCellRenderer(PuckmanCellRenderer cr)
    {
	renderer = cr;
    }

    public void worldChanged(World w)
    {
	if(w != world)
	    {
		w.removeListener(this);
		return;
	    }

	//TODO: Trigger redraw
	if(background == null)
	    {
		drawBackground();
	    }
	if(foreground == null)
	    {
		foreground = new BufferedImage(width, height, TYPE_INT_ARGB);
	    }
	foreground.getGraphics().clearRect(0, 0, foreground.getWidth(),
					   foreground.getHeight());
	drawForeground(foreground.getGraphics());

	if(foreground == null)
	    {
		state = new BufferedImage(width, height, TYPE_INT_RGB);
	    }
	state.getGraphics().drawImage(background, 0, 0, null);
	state.getGraphics().drawImage(foreground, 0, 0, null);
    }

    private void drawBackground()
    {
	background = new BufferedImage(width, height, TYPE_INT_RGB); 
	Graphics2D g = background.getGraphics();

	g.setColor(java.awt.Color.BLACK);
	g.fillRect(0, 0, width, height);
	
	int cwidth = Math.floor(((double)width)/world.width());
	int cheight = Math.floor(((double)height)/world.width());

	for(int x = 0; x < world.getWidth(); x++)
	    for(int y = 0; y < world.getWidth; y++)
		{
		    if(world.isWall(x, y))
			renderer.renderStatic(x*cwidth, y*cheight, cwidth,
					      cheight, g, world.isWall(x,y-1),
					      world.isWall(x,y+1),
					      world.isWall(x-1,y),
					      world.isWall(x+1,y));
		}
    }

    public void drawForeground(Graphics2D g)
    {
	int cwidth = Math.floor(((double)width)/world.getWidth());
	int cheight = Math.floor(((double)height)/world.getWidth());
	for(World.GridEntry ge : world.getDynamicCells())
	    {
		renderer.renderDynamic(ge.x*cwidth, ge.y*cheight, cwidth,
				       cheight, ge.c, g);
	    }
    }

    public void paint(Graphics g)
    {
	super.paint(g);
	g.drawImage(state, 0, 0, getWidth(), getHeight(), null);
    }
}