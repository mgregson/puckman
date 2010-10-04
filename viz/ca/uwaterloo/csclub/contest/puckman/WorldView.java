import java.awt.Graphics;

public class WorldView implements WorldStateListener
{
    private World world;
    private PuckmanCellRenderer renderer;
    public WorldView(World w, PuckmanCellRenderer cr)
    {
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
    }

    public void draw(Graphics g)
    {
	int cwidth;
	int cheight;
	for(World.GridEntry ge : world.getDynamicCells())
	    {
		renderer.render(ge.x, ge.y, cwidth, cheight, ge.c, g);
	    }
    }
}