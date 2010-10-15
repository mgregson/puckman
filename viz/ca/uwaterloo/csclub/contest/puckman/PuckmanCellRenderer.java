import java.awt.Graphics2D;
public interface PuckmanCellRenderer
{
    public void renderStatic(int x, int y, int width, int height,
			     Graphics2D g, boolean u, boolean d, boolean l,
			     boolean r);
    public void renderDynamic(int x, int y, int width, int height, Cell c,
			      Graphics2D g);
}