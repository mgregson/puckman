import java.util.LinkedList;

public class World
{
    private LinkedList<WorldStateListener> listeners;
    private LinkedList<GridEntry> dynamicCells;
    private GridEntry grid[][];
    private int width;
    public World(int width)
    {
	this.width = width;
	listeners = new LinkedList<WorldStateListener>();
	grid = new GridEntry[width][width]();
	for(int i = 0; i < width; i++)
	    for(int j = 0; j < width; j++)
		grid[i][j] = new GridEntry(i, j);
    }

    public void setCell(int x, int y, Cell c)
    {
	grid[x][y].c = c;
	if(c.isDynamic)
	    dynamicCells.addLast(grid[x][y]);
    }

    public void addListener(WorldStateListener l)
    {
	listeners.addLast(l);
    }

    public void removeListener(WorldStateListener l)
    {
	while(listeners.remove(l));
    }

    public void updateComplete()
    {
	for(WorldStateListener l : listeners)
	    {
		l.worldChanged(this);
	    }
    }

    public LinkedList getDynamicCells()
    {
	return dynamicCells;
    }

    public class GridEntry
    {
	int x, y;
	Cell c;

	public GridEntry(int x, int y)
	{
	    this.x = x;
	    this.y = y;
	}
    }
}